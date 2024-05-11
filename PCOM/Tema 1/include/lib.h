#ifndef _SKEL_H_
#define _SKEL_H_

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PACKET_LEN 1600
#define ROUTER_NUM_INTERFACES 3


/*
 * @brief Sends a packet on a specific interface.
 *
 * @param interface - index of the output interface
 * @param frame_data - region of memory in which the data will be copied; should
 *        have at least MAX_PACKET_LEN bytes allocated
 * @param length - will be set to the total number of bytes received.
 * Returns: the interface it has been received from.
 */
int send_to_link(int interface, char *frame_data, size_t length);

/*
 * @brief Receives a packet. Blocking function, blocks if there is no packet to
 * be received.
 *
 * @param frame_data - region of memory in which the data will be copied; should
 *        have at least MAX_PACKET_LEN bytes allocated 
 * @param length - will be set to the total number of bytes received.
 * Returns: the interface it has been received from.
 */
int recv_from_any_link(char *frame_data, size_t *length);

/* Route table entry */
struct route_table_entry {
	uint32_t prefix;
	uint32_t next_hop;
	uint32_t mask;
	int interface;
} __attribute__((packed));

/* ARP table entry when skipping the ARP exercise */
struct arp_table_entry {
    uint32_t ip;
    uint8_t mac[6];
};

char *get_interface_ip(int interface);

/**
 * @brief Get the interface mac object. The function writes
 * the MAC at the pointer mac. uint8_t *mac should be allocated.
 *
 * @param interface
 * @param mac
 */
void get_interface_mac(int interface, uint8_t *mac);

/**
 * @brief Homework infrastructure function.
 *
 * @param argc
 * @param argv
 */

/**
 * @brief IPv4 checksum per  RFC 791. To compute the checksum
 * of an IP header we must set the checksum to 0 beforehand.
 *
 * also works as ICMP checksum per RFC 792. To compute the checksum
 * of an ICMP header we must set the checksum to 0 beforehand.

 * @param data memory area to checksum
 * @param length in bytes
 */
uint16_t checksum(uint16_t *data, size_t length);

/**
 * hwaddr_aton - Convert ASCII string to MAC address (colon-delimited format)
 * @txt: MAC address as a string (e.g., "00:11:22:33:44:55")
 * @addr: Buffer for the MAC address (ETH_ALEN = 6 bytes)
 * Returns: 0 on success, -1 on failure (e.g., string not a MAC address)
 */
int hwaddr_aton(const char *txt, uint8_t *addr);

/* Populates a route table from file, rtable should be allocated
 * e.g. rtable = malloc(sizeof(struct route_table_entry) * 80000);
 * This function returns the size of the route table.
 */
int read_rtable(const char *path, struct route_table_entry *rtable);

/* Parses a static mac table from path and populates arp_table.
 * arp_table should be allocated and have enough space. This
 * function returns the size of the arp table.
 * */
int parse_arp_table(char *path, struct arp_table_entry *arp_table);

void init(int argc, char *argv[]);

#define DIE(condition, message, ...) \
	do { \
		if ((condition)) { \
			fprintf(stderr, "[(%s:%d)]: " # message "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
			perror(""); \
			exit(1); \
		} \
	} while (0)

#endif /* _SKEL_H_ */
