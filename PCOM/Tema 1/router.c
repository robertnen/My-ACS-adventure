#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"

#define ETHERNET_HTYPE 1

typedef struct {
	char *payload;
	size_t len;
	uint64_t interface;
	uint32_t next_hop;
} Packet;

typedef struct {
	uint8_t request;
	uint8_t reply;
	uint16_t type;
} ARP;

typedef struct {
	uint8_t echo_awk;
	uint8_t prot;
	uint8_t tle;
	uint8_t not_found;
} ICMP;

//! constants to get codes easier
const ARP arp = {.request = 1, .reply = 2, .type = 0x0806};
const ICMP icmp = {.echo_awk = 0, .prot = 1, .tle = 11, .not_found = 3};

//* structs sizes
const uint32_t ETH_SIZE = sizeof(Eth_header);
const uint32_t IPH_SIZE = sizeof(Ip_header);
const uint32_t ARP_SIZE = sizeof(Arp_header);
const uint32_t ICMP_SIZE = sizeof(Icmp);

//? more for ICMP struct
const uint32_t ICMP_DATA_SIZE = 16;
const uint32_t ICMP_START = 34;
const uint32_t ICMP_DATA = 42;

static Arp_table arp_table[150];
static u_int32_t arp_table_size;

static queue arp_queue;
static uint32_t arp_queue_size;

int char_to_num(const char* str) {
	long ans = 0;
    int len = strlen(str), i = 0;
    bool flag = false;

    while (i < len && str[i] == ' ') i++;

    if (i < len && str[i] == '-') {flag = true; i++;}
    if (i < len && i && str[i] == '+' && str[i - 1] == '-') return 0;
    if (i < len && str[i] == '+') i++;

    while (i < len && ('0' <= str[i] && str[i] <= '9')) {
        ans = ans * 10 + str[i] - '0';

        if (ans > INT_MAX && flag) return INT_MIN;
        else if (ans > INT_MAX) return INT_MAX;

        i++;
    }

    return flag ? -ans : ans;
}

//? reads the route file and saves the ips and interfaces in the binary search tree
uint32_t add_routes(const char *file_path, Bst *root, Bst_tuple direction, int size_line)
{
	FILE *routes_input = fopen(file_path, "r");
	uint32_t num_lines = 0;
	char input_line[128];

	while (fgets(input_line, size_line, routes_input)) {
		R_table *route = malloc(sizeof(R_table));  // ? new route in bst
		unsigned char *prefix, *next_hop, *mask;   // ? add by bytes
		char order_byte = 0, ip_part = 0, *route_line;

		mask = (unsigned char *) &route->mask;
		prefix = (unsigned char *) &route->prefix;
		next_hop = (unsigned char *) &route->next_hop;

		route_line = strtok(input_line, " .");

		while (route_line) {
			switch (ip_part) {
				case 0:
					*(prefix + order_byte) = char_to_num(route_line);
					break;

				case 1:
					*(next_hop + order_byte) = char_to_num(route_line);
					break;

				case 2:
					*(mask + order_byte) = char_to_num(route_line);
					break;

				default:
					route->interface = char_to_num(route_line);
					break;
			}

			route_line = strtok(NULL, " .");

			if(order_byte == 3) {  // ? reset for dest
				order_byte = 0;
				ip_part++;
			} else
				order_byte++;
		}

		add_node(root, route, direction);
		num_lines++;
	}

	// * free memory
	fclose(routes_input);

	return num_lines;
}

R_table *find_next_hop(Bst *routes, uint32_t dest_ip)
{
	Bst *ans = find_node_Bst(routes, dest_ip);

	return ans ? ans->ent : NULL;
}

void build_header(Ip_header **ip, uint8_t prot, uint32_t dest,
					uint16_t len, int inf, size_t size) {
	(*ip)->daddr = dest;  //* destination becomes source
	(*ip)->saddr = inet_addr(get_interface_ip(inf));

	(*ip)->ttl = 64;
	(*ip)->protocol = prot;
	(*ip)->tot_len = htons(size + ntohs(len));

	(*ip)->check = 0;
	(*ip)->check = htons(checksum((uint16_t *)(*ip), IPH_SIZE));
}

void send_icmp(char *buf, size_t *len, int inf, uint8_t type)
{
	char *icmp_data = calloc(ICMP_DATA_SIZE, 1);
	char *buff_eth = buf + 14, *buff_icmp = buf + 34, *buff_data = buf + 42;

	Ip_header *ip = (Ip_header *) buff_eth;
	Icmp *icmp_hdr = (Icmp *) buff_icmp;

	uint32_t more_size = ICMP_SIZE + ICMP_DATA_SIZE;
	*len += more_size;

	memcpy(icmp_data, ip, ICMP_DATA_SIZE);

	build_header(&ip, icmp.prot, ip->saddr, ip->tot_len, inf, more_size);

	memset(icmp_hdr, 0, ICMP_SIZE); // ? set code and checksum to 0

	icmp_hdr->type = type;
	icmp_hdr->checksum = htons(checksum((uint16_t *) icmp_hdr, ICMP_SIZE));

	memcpy(buff_data, icmp_data, ICMP_DATA_SIZE);

	free(icmp_data);
}

void build_packet(Packet **packet, size_t len, R_table *route) {
		*packet = calloc(1, sizeof(Packet));

		(*packet)->len = len;
		(*packet)->payload = calloc(len + 10, 1);
		(*packet)->interface = route->interface;
		(*packet)->next_hop = route->next_hop;
}

void build_arp_hdr(Arp_header **arp_hdr, R_table *route) {
	*arp_hdr = calloc(ARP_SIZE, 1);

	(*arp_hdr)->htype = htons(ETHERNET_HTYPE);
	(*arp_hdr)->hlen = 6; //! mac length

	(*arp_hdr)->ptype = htons(0x0800);
	(*arp_hdr)->plen = 4;

	(*arp_hdr)->op = htons(arp.request);

	(*arp_hdr)->spa = inet_addr(get_interface_ip(route->interface));
	get_interface_mac(route->interface, (*arp_hdr)->sha);

	(*arp_hdr)->tpa = route->next_hop;
	for (int i = 0; i < 6; i++) (*arp_hdr)->tha[i] = 255;
}

void send_packet(Bst *routes, char *buf, size_t len, int inf)
{
	Eth_header *eth_hdr = (Eth_header *) buf;
	Ip_header *ip = (Ip_header *) (buf + 14);
	R_table *route = NULL;

	if (ip->ttl < 2) send_icmp(buf, &len, inf, icmp.tle); // * TLE

	uint16_t sum = ip->check;
	uint32_t next_hop;
	bool isFound = 0;

	ip->check = 0;

	if (sum != htons(checksum((uint16_t *)ip, 20))) return;

	ip->ttl--;

	ip->check = 0;  // * recalculate checksum
	ip->check = htons(checksum((uint16_t *)ip, IPH_SIZE));

	route = find_next_hop(routes, ntohl(ip->daddr));

	if (!route) {  //* unreachable, send another message
		send_icmp(buf, &len, inf, icmp.not_found);
		route = find_next_hop(routes, ntohl(ip->daddr));
	}

	get_interface_mac(route->interface, eth_hdr->ether_shost);
	next_hop = ntohl(route->next_hop);

	for (int i = 0; i < arp_table_size; i++)  // * find next hop
		if (ntohl(arp_table[i].ip) == next_hop) {
			isFound = true;
			memcpy(eth_hdr->ether_dhost, arp_table[i].mac, 6);
			break;
		}

	if (isFound) {
		send_to_link(route->interface, buf, len);
		return;
	}

	Packet *p = NULL;

	build_packet(&p, len, route);
	memcpy(p->payload, buf, len);

	len = 42;

	queue_enq(arp_queue, (void *) p);

	arp_queue_size++;

	eth_hdr->ether_type = htons(arp.type);
	get_interface_mac(inf, eth_hdr->ether_shost);

	for (int i = 0; i < 6; i++) eth_hdr->ether_dhost[i] = 255;

	Arp_header *arp_hdr = NULL;
	build_arp_hdr(&arp_hdr, route);

	memcpy(buf + 14, arp_hdr, 28);
	free(arp_hdr);

	send_to_link(route->interface, buf, len);
}

void look_arp(char *buf, size_t len, int inf)
{
	Arp_header *arp_hdr = (Arp_header *) (buf + 14);
	u_int32_t hop = ntohl(arp_hdr->spa);
	Eth_header *eth;
	int rem_p = 0;
	Packet *p;

	arp_table[arp_table_size].ip = arp_hdr->spa; //* src address
	for (int i = 0; i < 6; i++)
		arp_table[arp_table_size].mac[i] = arp_hdr->sha[i];

	arp_table_size++;

	for (int i = 0; i < arp_queue_size; i++) {
		p = (Packet *) queue_deq(arp_queue);
		eth = (Eth_header *) p->payload;

		if (ntohl(p->next_hop) == hop) { //* found dest
			rem_p++;
			get_interface_mac(p->interface, eth->ether_shost);

			for (int i = 0; i < 6; i++)
				eth->ether_dhost[i] = arp_hdr->sha[i];

			send_to_link(p->interface, p->payload, p->len);

			free(p->payload);
			free(p);
		} else
			queue_enq(arp_queue, p);
	}

	arp_queue_size -= rem_p;
}

void look_arp_req(char *buf, size_t len, int inf)
{
	Eth_header *eth_hdr = (Eth_header *) buf;
	Arp_header *arp_hdr = (Arp_header *) (buf + 14);

	arp_hdr->op = htons(arp.reply);  //* create request

	for (int i = 0; i < 6; i++)
		arp_hdr->tha[i] = arp_hdr->sha[i];

	get_interface_mac(inf, arp_hdr->sha);

	arp_hdr->tpa = arp_hdr->spa;
	arp_hdr->spa = inet_addr(get_interface_ip(inf));

	for (int i = 0; i < 6; i++)  //* build eth header
		eth_hdr->ether_dhost[i] = eth_hdr->ether_shost[i];

	get_interface_mac(inf, eth_hdr->ether_shost);

	send_to_link(inf, buf, len);
}

void icmp_reply(Bst *routes, char *buf, size_t len, int inf)
{
	char *buf_eth = buf + 14,
		 *buf_icmp = buf + 34;

	Ip_header *ip = (Ip_header *) buf_eth;
	Icmp *ic = (Icmp *) buf_icmp;

	uint16_t sum = ic->checksum;
	uint32_t tmp;

	ic->checksum = 0;

	if (sum != htons(checksum((uint16_t *)ic, 8))) return;

	//? source becomes destination and
	//? destination becomes srouce
	tmp = ip->saddr;
	ip->saddr = ip->daddr;
	ip->daddr = tmp;

	ip->check = 0;
	ip->check = htons(checksum((uint16_t *)ip, 20));

	//* changes to the header
	ic->type = icmp.echo_awk;
	ic->code = 0; //! echo code is 0
	ic->checksum = 0;
	ic->checksum = htons(checksum((uint16_t *)ic, 8));

	send_packet(routes, buf, len, inf);
}

int main(int argc, char *argv[])
{
	Bst *routes;
	Ip_header *ip;
	Arp_header *arp_hdr;
	Eth_header *eth_hdr;
	Bst_tuple direction;
	u_int32_t route_count;
	char buf[MAX_PACKET_LEN];

	arp_table_size = 0;

	routes = create_Bst();
	route_count = add_routes(argv[1], routes, direction, 128);

	//! input is corrupted
	if (route_count < 0) {
		fprintf(stderr, "Invalid input! Numbers of routes can not be negative!\n");
		return 0;
	}

	arp_queue = queue_create();

	// Do not modify this line
	init(argc - 2, argv + 2);

	while (1) {
		int inf;
		size_t len;

		inf = recv_from_any_link(buf, &len);
		DIE(inf < 0, "recv_from_any_links");

		eth_hdr = (Eth_header *) buf;

		if (ntohs(eth_hdr->ether_type) == 0x0800) {  //* eth
			ip = (Ip_header *) (buf + 14);

			if (ip->daddr == inet_addr(get_interface_ip(inf)))
				icmp_reply(routes, buf, len, inf);
			else
				send_packet(routes, buf, len, inf);
		} else if (ntohs(eth_hdr->ether_type) == arp.type) {
					arp_hdr = (Arp_header *) (buf + 14);

					if (ntohs(arp_hdr->op) == arp.reply)
						look_arp(buf, len, inf);
					else if (ntohs(arp_hdr->op) == arp.request)
						look_arp_req(buf, len, inf);
		}
	}

	free_Bst(routes);

	return 0;
}