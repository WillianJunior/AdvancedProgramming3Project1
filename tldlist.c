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
	
	// if inside the date limit
	if (date_compare(d,tld->begin) && date_compare(tld->end, d)) {

		// check if the hostname exists
		// if it does, increment the host counter from the node
		// if not, create a tldnode
		// add it to the tree
		
		// update the tldlist's node counter
		tldlist->node_count++;

		return 1;
	}
	return 0;
}

/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld) {

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

}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node) {
	
}
