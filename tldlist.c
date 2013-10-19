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
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld) {
	
	TLDIterator *it = tldlist_iter_create(tld);
	TLDNode *node;

	while ((node = tldlist_iter_next(it)) != NULL) {
		#ifdef DEBUG
		printf("freed %s\n", node->hostname);
		#endif
		free(node->hostname);
		free(node);
	}

	free(tld);
	free(it);
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d) {
	
	long i;

	// check if the date is whithin the limit
	if (date_compare(d,tld->begin) >= 0 && date_compare(tld->end, d) >= 0) {
		#ifdef DEBUG
		printf("[ADD] Valid hostname, will be added\n");
		#endif

		// extract the last dot location
		for (i=strlen(hostname); i>0 && hostname[i] != '.'; i--);

		// check if it is the first element of the tree
		if (tld->root == NULL) {
			// create a new node and set it as the first root
			tld->root = tldnode_new(hostname+i+1);
		} else {
			// TODO: here it will be the place to put the AVL code
			tldnode_add(tld, hostname+i+1, tld->root);
		}

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
	free(iter);
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
	
	newnode->hostname = malloc((strlen(hostname) + 1)*sizeof(char));
	strcpy(newnode->hostname, hostname);
	newnode->host_count = 1;
	newnode->height = 1;
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
 		tldnode_printout(this->left);
 		printf("hostname: %s - height: %ld\n", this->hostname, this->height);
 		tldnode_printout(this->right);
 	}
}

 /*
  * tldnode_add update the reference to the pointer that shoud receive
  * the given hostname. the reference can point to either the alreadly
  * existing hostname element or to the left or right subtree where the new 
  * node was be created.
  */
void tldnode_add(TLDList *tld, char *hostname, TLDNode *node) {
	
	int cmp;

	if ((cmp = strcmp(hostname, node->hostname)) < 0) {
		// if lower, move to the left subtree
		if (node->left != NULL) {
			// if it haven't found yet, keep searching
			tldnode_add(tld, hostname, node->left);
		} else {
			// if the tree has runout and haven't been found node, create a new one
			node->left = tldnode_new(hostname);
			node->left->parent = node;
			#ifdef AVL
			tldnode_update_height(node->left);
			tldnode_balance_tree(tld, node->left);
			#ifdef DEBUG
			while(node->parent != NULL)
				node = node->parent;
			tldnode_printout(node);
			printf("\n");
			#endif
			#endif
		}
	} else if (cmp > 0) {
		// if greater, move to the right subtree
		if (node->right != NULL) {
			// if it haven't found yet, keep searching
			tldnode_add(tld, hostname, node->right);
		} else {
			// if the tree has runout and haven't been found node, create a new one
			node->right = tldnode_new(hostname);
			node->right->parent = node;
			#ifdef AVL
			tldnode_update_height(node->right);
			tldnode_balance_tree(tld, node->right);
			#ifdef DEBUG
			while(node->parent != NULL)
				node = node->parent;
			tldnode_printout(node);
			printf("\n");
			#endif
			#endif
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

#ifdef AVL

/*********************************/
/**			AVL Functions		**/
/*********************************/

/*
 * update the height values on the given node and its parents
 */
void tldnode_update_height(TLDNode *node) {
	while (node != NULL) {
		node->height = tldnode_calculate_height(node);
		node = node->parent;
	}
}

/*
 * balance the tree using the AVL algorithm
 */
void tldnode_balance_tree(TLDList *tld, TLDNode *node) {
	
	long balance;

	while (node != NULL) {
		// check if the subtree node is unbalanced
		if (node->height > 2 && abs(balance = tldnode_calculate_height(node->left) - tldnode_calculate_height(node->right)) > 1) {
			if (balance > 0) { // ?-right
				if (tldnode_calculate_height(node->left->right) > tldnode_calculate_height(node->left->left)) { // left-right
					tldnode_rotate_left(tld, node->left);
					if (node->left->left != NULL)
						node->left->left->height = tldnode_calculate_height(node->left->left);
					node->left->height = tldnode_calculate_height(node->left);
				}
				tldnode_rotate_right(tld, node);
				if (node->right != NULL)
					node->right->height = tldnode_calculate_height(node->right);
				node->height = tldnode_calculate_height(node);
			} else { // ?-left
				if (tldnode_calculate_height(node->right->left) > tldnode_calculate_height(node->right->right)) { // right-left
					tldnode_rotate_right(tld, node->right);
					if (node->right->right != NULL)
						node->right->right->height = tldnode_calculate_height(node->right->right);
					node->right->height = tldnode_calculate_height(node->right);
				}
				tldnode_rotate_left(tld, node);
				if (node->left != NULL)
					node->left->height = tldnode_calculate_height(node->left);
				node->height = tldnode_calculate_height(node);
			}
		}
		#ifdef DEBUG
		printf("\n");
		#endif
		// iterate through the tree until it hits the root
		node = node->parent;
	}

	/*
	while (node != NULL) {
		if ((node->height = tldnode_calculate_height(node)) > 2) {
			if (abs(balance = tldnode_calculate_height(node->left) - tldnode_calculate_height(node->right)) > 1) {
				if (balance > 0) { // ?-right
					if (tldnode_calculate_height(node->left->right) > tldnode_calculate_height(node->left->left)) { // left-right
						tldnode_rotate_left(node->left);
						node->left->left->height = tldnode_calculate_height(node->left->left);
						node->left->height = tldnode_calculate_height(node->left);
					}
					tldnode_rotate_right(node);
					node->right->height = tldnode_calculate_height(node->right);
					node->height = tldnode_calculate_height(node);
				} else { // ?-left
					if (tldnode_calculate_height(node->right->left) > tldnode_calculate_height(node->right->right)) { // right-left
						tldnode_rotate_right(node->right);
						
						node->right->right->height = tldnode_calculate_height(node->right->right);
						node->right->height = tldnode_calculate_height(node->right);
					}
					tldnode_rotate_left(node);
					node->left->height = tldnode_calculate_height(node->left);
					node->height = tldnode_calculate_height(node);
				}
			}
		}
		node = node->parent;
	}
	*/

}

/*
 * return the height for a given node, calculated from its children
 */
long tldnode_calculate_height(TLDNode *node) {

	if (node == NULL)
		return 0;

	long height_left = node->left == NULL ? 0 : node->left->height;
	long height_right = node->right == NULL ? 0 : node->right->height;

	return (height_left > height_right ? height_left : height_right) + 1;
}

/*
 * rotate the node to the right
 */
void tldnode_rotate_right (TLDList *tld, TLDNode *node) {
	// check if it is the new first node
	if (node->parent != NULL) {
		if (node->parent->left == node)
			node->parent->left = node->left;
		else
			node->parent->right = node->left;
	} else
		tld->root = node->left;
	node->left->parent = node->parent;
	node->parent = node->left;
	node->left = node->left->right;
	if (node->left != NULL)
		node->left->parent = node;
	node->parent->right = node;
	#ifdef DEBUG
	printf("right rot\n");
	#endif
}

/*
 * rotate the node to the left
 */
void tldnode_rotate_left (TLDList *tld, TLDNode *node) {
	if (node->parent != NULL) {
		if (node->parent->right == node)
			node->parent->right = node->right;
		else 
			node->parent->left = node->right;
	} else
		tld->root = node->right;
	node->right->parent = node->parent;
	node->parent = node->right;
	node->right = node->right->left;
	if (node->right != NULL)
		node->right->parent = node;
	node->parent->left = node;
	#ifdef DEBUG
	printf("left rot\n");
	#endif
}

#endif
