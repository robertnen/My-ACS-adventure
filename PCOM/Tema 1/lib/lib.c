#include "lib.h"

#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>
#include <asm/byteorder.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int interfaces[ROUTER_NUM_INTERFACES];

int get_sock(const char *if_name)
{
	int res;
	int s = socket(AF_PACKET, SOCK_RAW, 768);
	DIE(s == -1, "socket");

	struct ifreq intf;
	strcpy(intf.ifr_name, if_name);
	res = ioctl(s, SIOCGIFINDEX, &intf);
	DIE(res, "ioctl SIOCGIFINDEX");

	struct sockaddr_ll addr;
	memset(&addr, 0x00, sizeof(addr));
	addr.sll_family = AF_PACKET;
	addr.sll_ifindex = intf.ifr_ifindex;

	res = bind(s, (struct sockaddr *)&addr , sizeof(addr));
	DIE(res == -1, "bind");
	return s;
}

int send_to_link(int intidx, char *frame_data, size_t length)
{
	/*
	 * Note that "buffer" should be at least the MTU size of the 
	 * interface, eg 1500 bytes 
	 */
	int ret;
	ret = write(interfaces[intidx], frame_data, length);
	DIE(ret == -1, "write");
	return ret;
}

ssize_t receive_from_link(int intidx, char *frame_data)
{
	ssize_t ret;
	ret = read(interfaces[intidx], frame_data, MAX_PACKET_LEN);
	return ret;
}

int socket_receive_message(int sockfd, char *frame_data, size_t *len)
{
	/*
	 * Note that "buffer" should be at least the MTU size of the
	 * interface, eg 1500 bytes
	 * */
	int ret = read(sockfd, frame_data, MAX_PACKET_LEN);
	DIE(ret < 0, "read");
	*len = ret;
	return 0;
}

int recv_from_any_link(char *frame_data, size_t *length) {
	int res;
	fd_set set;

	FD_ZERO(&set);
	while (1) {
		for (int i = 0; i < ROUTER_NUM_INTERFACES; i++) {
			FD_SET(interfaces[i], &set);
		}

		res = select(interfaces[ROUTER_NUM_INTERFACES - 1] + 1, &set,
				NULL, NULL, NULL);
		DIE(res == -1, "select");

		for (int i = 0; i < ROUTER_NUM_INTERFACES; i++) {
			if (FD_ISSET(interfaces[i], &set)) {
				ssize_t ret = receive_from_link(i, frame_data);
				DIE(ret < 0, "receive_from_link");
				*length = ret;
				return i;
			}
		}
	}

	return -1;
}

char *get_interface_ip(int interface)
{
	struct ifreq ifr;
	int ret;
	if (interface == 0)
		sprintf(ifr.ifr_name, "rr-0-1");
	else {
		sprintf(ifr.ifr_name, "r-%u", interface - 1);
	}
	ret = ioctl(interfaces[interface], SIOCGIFADDR, &ifr);
	DIE(ret == -1, "ioctl SIOCGIFADDR");
	return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
}

void get_interface_mac(int interface, uint8_t *mac)
{
	struct ifreq ifr;
	int ret;
	if (interface == 0)
		sprintf(ifr.ifr_name, "rr-0-1");
	else {
		sprintf(ifr.ifr_name, "r-%u", interface - 1);
	}
	ret = ioctl(interfaces[interface], SIOCGIFHWADDR, &ifr);
	DIE(ret == -1, "ioctl SIOCGIFHWADDR");
	memcpy(mac, ifr.ifr_addr.sa_data, 6);
}

static int hex2num(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;

	return -1;
}

int hex2byte(const char *hex)
{
	int a, b;
	a = hex2num(*hex++);
	if (a < 0)
		return -1;
	b = hex2num(*hex++);
	if (b < 0)
		return -1;

	return (a << 4) | b;
}

int hwaddr_aton(const char *txt, uint8_t *addr)
{
	int i;
	for (i = 0; i < 6; i++) {
		int a, b;
		a = hex2num(*txt++);
		if (a < 0)
			return -1;
		b = hex2num(*txt++);
		if (b < 0)
			return -1;
		*addr++ = (a << 4) | b;
		if (i < 5 && *txt++ != ':')
			return -1;
	}
	return 0;
}

void init(int argc, char *argv[])
{
	for (int i = 0; i < argc; ++i) {
		printf("Setting up interface: %s\n", argv[i]);
		interfaces[i] = get_sock(argv[i]);
	}
}


uint16_t checksum(uint16_t *data, size_t length)
{
	unsigned long checksum = 0;
	uint16_t extra_byte;
	while (length > 1) {
		checksum += ntohs(*data++);
		length -= 2;
	}
	if (length) {
		*(uint8_t *)&extra_byte = *(uint8_t *)data;
		checksum += extra_byte;
	}

	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum += (checksum >>16);
	return (uint16_t)(~checksum);
}

int read_rtable(const char *path, struct route_table_entry *rtable)
{
	FILE *fp = fopen(path, "r");
	int j = 0, i;
	char *p, line[64];

	while (fgets(line, sizeof(line), fp) != NULL) {
		p = strtok(line, " .");
		i = 0;
		while (p != NULL) {
			if (i < 4)
				*(((unsigned char *)&rtable[j].prefix)  + i % 4) = (unsigned char)atoi(p);

			if (i >= 4 && i < 8)
				*(((unsigned char *)&rtable[j].next_hop)  + i % 4) = atoi(p);

			if (i >= 8 && i < 12)
				*(((unsigned char *)&rtable[j].mask)  + i % 4) = atoi(p);

			if (i == 12)
				rtable[j].interface = atoi(p);
			p = strtok(NULL, " .");
			i++;
		}
		j++;
	}
	return j;
}

int parse_arp_table(char *path, struct arp_table_entry *arp_table)
{
	FILE *f;
	fprintf(stderr, "Parsing ARP table\n");
	f = fopen(path, "r");
	DIE(f == NULL, "Failed to open %s", path);
	char line[100];
	int i = 0;
	for(i = 0; fgets(line, sizeof(line), f); i++) {
		char ip_str[50], mac_str[50];
		sscanf(line, "%s %s", ip_str, mac_str);
		fprintf(stderr, "IP: %s MAC: %s\n", ip_str, mac_str);
		arp_table[i].ip = inet_addr(ip_str);
		int rc = hwaddr_aton(mac_str, arp_table[i].mac);
		DIE(rc < 0, "invalid MAC");
	}
	fclose(f);
	fprintf(stderr, "Done parsing ARP table.\n");
	return i;
}
