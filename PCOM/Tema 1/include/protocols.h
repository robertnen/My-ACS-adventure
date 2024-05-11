#include <unistd.h>
#include <stdint.h>

/* Ethernet ARP packet from RFC 826 */
struct arp_header {
	uint16_t htype;   /* Format of hardware address */
	uint16_t ptype;   /* Format of protocol address */
	uint8_t hlen;    /* Length of hardware address */
	uint8_t plen;    /* Length of protocol address */
	uint16_t op;    /* ARP opcode (command) */
	uint8_t sha[6];  /* Sender hardware address */
	uint32_t spa;   /* Sender IP address */
	uint8_t tha[6];  /* Target hardware address */
	uint32_t tpa;   /* Target IP address */
} __attribute__((packed));

/* Ethernet frame header*/
struct  ether_header {
    uint8_t  ether_dhost[6]; //adresa mac destinatie
    uint8_t  ether_shost[6]; //adresa mac sursa
    uint16_t ether_type;     // identificator protocol encapsulat
};

/* IP Header */
struct iphdr {
    // this means that version uses 4 bits, and ihl 4 bits
    uint8_t    ihl:4, version:4;   // we use version = 4
    uint8_t    tos;      // we don't use this, set to 0
    uint16_t   tot_len;  // total length = ipheader + data
    uint16_t   id;       // id of this packet
    uint16_t   frag_off; // we don't use fragmentation, set to 0
    uint8_t    ttl;      // Time to Live -> to avoid loops, we will decrement
    uint8_t    protocol; // don't care
    uint16_t   check;    // checksum     -> Since we modify TTL,
    // we need to recompute the checksum
    uint32_t   saddr;    // source address
    uint32_t   daddr;    // the destination of the packet
};

struct icmphdr
{
  uint8_t type;                /* message type */
  uint8_t code;                /* type sub-code */
  uint16_t checksum;
  union
  {
    struct
    {
      uint16_t        id;
      uint16_t        sequence;
    } echo;                        /* echo datagram */
    uint32_t        gateway;        /* gateway address */
    struct
    {
      uint16_t        __unused;
      uint16_t        mtu;
    } frag;                        /* path mtu discovery */
  } un;
};
