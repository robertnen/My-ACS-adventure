#ifndef _BST_H_
#define _BST_H_

    #include <arpa/inet.h>
    #include <limits.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include "protocols.h"
    #include "queue.h"
    #include "lib.h"

    typedef struct route_table_entry R_table;
    typedef struct iphdr Ip_header;
    typedef struct ether_header Eth_header;
    typedef struct icmphdr Icmp;
    typedef struct arp_table_entry Arp_table;
    typedef struct arp_header Arp_header;

    typedef struct node {
        R_table *ent;
        uint32_t prefix, mask;
        struct node *left, *right; //? 0 - left; 1 - right
    } Bst;

    typedef struct {
        uint32_t prefix;
        uint32_t mask;
        R_table *ent;
    } Bst_tuple;

    Bst *create_Bst();
    void add_node(Bst *root, R_table *ent, Bst_tuple direction);
    Bst *find_node_Bst(Bst *root, uint32_t ip_addr);
    void free_Bst(Bst *root);

#endif