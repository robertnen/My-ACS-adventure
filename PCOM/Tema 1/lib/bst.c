#include "bst.h"

const uint32_t INT_LIMIT = 1 << 31;

Bst *create_Bst(void)
{
	return calloc(1, sizeof(Bst));
}

void add_node(Bst *root, R_table *ent, Bst_tuple direction)
{
	Bst *node = root;
	bool bit;

	direction.prefix = ntohl(ent->prefix);
	direction.mask = ntohl(ent->mask);
	direction.ent = ent;

	while (direction.mask) {
		bit = direction.prefix & INT_LIMIT;

		node = bit ? (node->right ? node->right : (node->right = create_Bst())) :
					 (node->left ? node->left : (node->left = create_Bst()));

		direction.prefix *= 2;
		direction.mask *= 2;
	}

	// add the entry to the Bst
	node->prefix = direction.prefix;
	node->mask = direction.mask;
	node->ent = direction.ent;
}

Bst *find_node_Bst(Bst *root, uint32_t ip_addr)
{
	Bst *node = root, *ans = NULL;

	while (node) {
		if (node->ent) ans = node;

		node = (ip_addr & INT_LIMIT) ? node->right :
									   node->left;

		ip_addr *= 2;
	}

	return ans;
}

void free_Bst(Bst *root)
{
	Bst *node;
	queue t_Bst = calloc(1, sizeof(queue));

	if (!root) return;

	queue_enq(t_Bst, (void *) root);  //? fac bfs ca sa sterg arborele

	while (!queue_empty(t_Bst)) {
		node = (Bst *) queue_deq(t_Bst);

		if (node->left) queue_enq(t_Bst, (void *) node->left);
		if (node->right) queue_enq(t_Bst, (void *) node->right);

		free(node);
	}

	free(t_Bst);
}

