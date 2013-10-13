#ifndef _TLDLIST_H_INCLUDED_
#define _TLDLIST_H_INCLUDED_

#define DEBUG

#include <string.h>

#include "date.h"

typedef struct tldlist TLDList;
typedef struct tldnode TLDNode;
typedef struct tlditerator TLDIterator;

struct tldlist {
	TLDNode *root;
	long host_count;
	Date *begin;
	Date *end;
};

struct tldnode {
	char *hostname;
	long host_count;
	TLDNode *left;
	TLDNode *right;
	TLDNode *parent;
};

struct tlditerator {
	TLDNode *node;
};

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end);

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d);

/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld);

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld);

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter);

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter);

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node);

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node);

/*
 * tldnode_new creates a new node with the given hostname
 */
TLDNode *tldnode_new(char *hostname);

 /*
  * tldnode_add update the reference to the pointer that shoud receive
  * the given hostname. the reference can point to either the alreadly
  * existing hostname element or to the left or right subtree where the new 
  * node was be created.
  */
void tldnode_add(char *hostname, TLDNode *node);

/*
 * print the whole tree given the root (not necessary ordered)
 */
void tldnode_printout(TLDNode *this);

 /*
 * return the deepest node to the left (go left before down)
 */
TLDNode *tldnode_find_deepest(TLDNode *node);

#endif /* _TLDLIST_H_INCLUDED_ */
