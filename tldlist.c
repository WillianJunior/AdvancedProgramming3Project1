#include "tldlist.h"

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end) {
	TLDList* tldlist = malloc(sizeof(TLDList));
	if (tldlist != NULL) {
		tldlist->root = NULL;
		tldlist->node_count = 0;
		tldlist->begin = begin;
		tldlist->end = end;
	}
	return tldlist;
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d) {
	
	// check if the date is whithin the limit
	if (date_compare(d,tld->begin) > 0 && date_compare(tld->end, d) > 0) {
		#ifdef DEBUG
		printf("[ADD] Valid hostname, will be added\n");
		#endif

		// check if it is the first element of the tree
		if (tld->root == NULL) {
			// create a new node and set it as the first root
			tld->root = tldnode_new(hostname);
			tld->node_count++;
		} else {
			// if not the first node to be added, check if there is a node with its hostname
			tldnode_add(hostname, tld->root);

		}
		

		return 1;
	}
	#ifdef DEBUG
	printf("[ADD] Invalid host, date outside the limit\n");
	#endif

	return 0;


}

/* old

TLDNode* parent = NULL, node = tld->root;
	int cmp;

	// if inside the date limit
	if (date_compare(d,tld->begin) && date_compare(tld->end, d)) {

		// check if the hostname exists
		while (node != NULL && (cpm = strcmp(node->hostname, hostname)) != 0) {
			parent = node;
			if (cmp > 0)
				node = node->right;
			else
				node = node->left;
		}

		// if it does, increment the host counter from the node
		if (node != NULL)
			node->host_count++;
		// if not, create a tldnode
		else {
			// check if it is the first node to be added
			if (parent == NULL) {
				tld->root = malloc(sizeof(TLDNode));
				node = tld->root;
			} else if (cmp > 0) {
				parent->right = malloc(sizeof(TLDNode));
				node = parent->right;
			} else {
				parent->left = malloc(sizeof(TLDNode));
				node = parent->left;
			}
			node->right = NULL;
			node->left = NULL;
			node->host_count = 0;
			strcmp(node->hostname, hostname);

		}

		// add it to the tree
		
		// update the tldlist's node counter
		tld->node_count++;

		return 1;
	}
	return 0;

*/

/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld) {
	return tld->node_count;
}

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld) {

}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter) {

}

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter) {

}

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node) {
	return node->hostname;
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node) {
	return node->host_count;
}

/*
 * tldnode_new creates a new node with the given hostname
 */
TLDNode *tldnode_new(char *hostname) {
	TLDNode* newnode = malloc(sizeof(TLDNode));
	newnode->hostname = malloc(strlen(hostname)*sizeof(char));
	strcpy(newnode->hostname, hostname);
	newnode->host_count = 1;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

/*
 * print the whole tree given the root (not necessary ordered)
 */
void tldnode_printout(TLDNode *this) {
 	if (this != NULL) {
 		printf("hostname: %s - count: %ld\n", this->hostname, this->host_count);
 		tldnode_printout(this->left);
 		tldnode_printout(this->right);
 	}
}

 /*
  * tldnode_add update the reference to the pointer that shoud receive
  * the given hostname. the reference can point to either the alreadly
  * existing hostname element or to the left or right subtree where the new 
  * node was be created.
  */
void tldnode_add(char *hostname, TLDNode *node) {
	
	int cmp;

	if ((cmp = strcmp(hostname, node->hostname)) < 0) {
		// if lower, move to the left subtree
		if (node->left != NULL) {
			// if it haven't found yet, keep searching
			tldnode_add(hostname, node->left);
		} else {
			// if the tree has runout and haven't been found node, create a new one
			node->left = malloc(sizeof(TLDNode));
			node->left->left = NULL;
			node->left->right = NULL;
			node->left->host_count = 1;
			node->left->hostname = malloc(sizeof(char) * strlen(hostname));
			strcpy(node->left->hostname, hostname);
		}
	} else if (cmp > 0) {
		// if greater, move to the right subtree
		if (node->right != NULL) {
			// if it haven't found yet, keep searching
			tldnode_add(hostname, node->right);
		} else {
			// if the tree has runout and haven't been found node, create a new one
			node->right = malloc(sizeof(TLDNode));
			node->right->left = NULL;
			node->right->right = NULL;
			node->right->host_count = 1;
			node->right->hostname = malloc(sizeof(char) * strlen(hostname));
			strcpy(node->right->hostname, hostname);
		}
	} else {
		// if it is the same hostname
		node->host_count++;
	}
}