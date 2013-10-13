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
		tldlist->host_count = 0;
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
	
	long i;

	// check if the date is whithin the limit
	if (date_compare(d,tld->begin) > 0 && date_compare(tld->end, d) > 0) {
		#ifdef DEBUG
		printf("[ADD] Valid hostname, will be added\n");
		#endif

		// extract the last dot location
		for (i=strlen(hostname); i>0 && hostname[i] != '.'; i--);

		// check if it is the first element of the tree
		if (tld->root == NULL) {
			// create a new node and set it as the first root
			tld->root = tldnode_new(hostname+i+1);
		} else
			tldnode_add(hostname+i+1, tld->root);

		tld->host_count++;
		return 1;
	}
	#ifdef DEBUG
	printf("[ADD] Invalid host, date outside the limit\n");
	#endif

	return 0;

}

/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld) {
	return tld->host_count;
}

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld) {
	TLDIterator* newiter = malloc(sizeof(TLDIterator));
	newiter->node = tldnode_find_deepest(tld->root);
	return newiter;
}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter) {
	TLDNode* returned = iter->node;

	// if the last iterated element was the root
	if (returned == NULL)
		return NULL;

	// if the current element is the root
	if (iter->node->parent == NULL) {
		iter->node = NULL;
		return returned;
	}

	// update the iterator referenced node
	if (iter->node->parent->right != iter->node && iter->node->parent->right != NULL)
		iter->node = tldnode_find_deepest(iter->node->parent->right);
	else
		iter->node = iter->node->parent;

	return returned;
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
	newnode->parent = NULL;
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
			node->left = tldnode_new(hostname);
			node->left->parent = node;
		}
	} else if (cmp > 0) {
		// if greater, move to the right subtree
		if (node->right != NULL) {
			// if it haven't found yet, keep searching
			tldnode_add(hostname, node->right);
		} else {
			// if the tree has runout and haven't been found node, create a new one
			node->right = tldnode_new(hostname);
			node->right->parent = node;
		}
	} else {
		// if it is the same hostname
		node->host_count++;
	}
}

/*
 * return the deepest node to the left (go left before down)
 */
TLDNode *tldnode_find_deepest(TLDNode *node) {
	TLDNode *this = node;

	// since C will stop the evaluation of || on the first true return, 
	// if the left subtree != NULL it won't evaluate the right subtree
	if (node != NULL && ((this = tldnode_find_deepest(node->left)) != NULL || (this = tldnode_find_deepest(node->right)) != NULL))
		return this;
	return node;
}