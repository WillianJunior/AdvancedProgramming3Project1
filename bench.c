#include <stdio.h>

#include "date.h"
#include "tldlist.h"

//#define DATE_TEST
#define TLD_TEST

int main () {

	Date *test_date;
	Date *test_date_beg;
	Date *test_date_end;
	TLDList *tld;
	char *hostname;



	// date constructor and destructor testing
	#ifdef DATE_TEST

	char test_string0[] = "31031992";
	char test_string1[] = "31203/1992";
	char test_string2[] = "31/03s1992";
	
	char test_string3[] = "31/03/1992";
	char test_string4[] = "32/03/1992";
	char test_string5[] = "00/03/1992";
	char test_string6[] = "s1/03/1992";
	char test_string7[] = "3a/03/1992";

	char test_string8[] = "31/a3/1992";
	char test_string9[] = "31/0q/1992";
	char test_string10[] = "31/00/1992";
	char test_string11[] = "31/13/1992";
	char test_string12[] = "31/04/1992";
	char test_string13[] = "31/02/1992";

	char test_string14[] = "31/03/a992";
	char test_string15[] = "31/03/1b92";
	char test_string16[] = "31/03/19q2";
	char test_string17[] = "31/03/199l";
	char test_string18[] = "31/03/0000";
	char test_string19[] = "31/03/3204";
	char test_string20[] = "29/02/2012";
	char test_string21[] = "30/02/2012";
	char test_string22[] = "29/02/2013";
	char test_string23[] = "28/02/2013";


	printf("0\t");
	test_date = date_create(test_string0);
	date_destroy(test_date);
	printf("1\t");
	test_date = date_create(test_string1);
	date_destroy(test_date);
	printf("2\t");
	test_date = date_create(test_string2);
	date_destroy(test_date);

	printf("3\t");
	test_date = date_create(test_string3);
	date_destroy(test_date);
	printf("4\t");
	test_date = date_create(test_string4);
	date_destroy(test_date);
	printf("5\t");
	test_date = date_create(test_string5);
	date_destroy(test_date);
	printf("6\t");
	test_date = date_create(test_string6);
	date_destroy(test_date);
	printf("7\t");
	test_date = date_create(test_string7);
	date_destroy(test_date);
	
	printf("8\t");
	test_date = date_create(test_string8);
	date_destroy(test_date);
	printf("9\t");
	test_date = date_create(test_string9);
	date_destroy(test_date);
	printf("10\t");
	test_date = date_create(test_string10);
	date_destroy(test_date);
	printf("11\t");
	test_date = date_create(test_string11);
	date_destroy(test_date);
	printf("12\t");
	test_date = date_create(test_string12);
	date_destroy(test_date);
	printf("13\t");
	test_date = date_create(test_string13);
	date_destroy(test_date);
	printf("14\t");
	test_date = date_create(test_string14);
	date_destroy(test_date);
	printf("15\t");
	test_date = date_create(test_string15);
	date_destroy(test_date);
	printf("16\t");
	test_date = date_create(test_string16);
	date_destroy(test_date);
	printf("17\t");
	test_date = date_create(test_string17);
	date_destroy(test_date);
	printf("18\t");
	test_date = date_create(test_string18);
	date_destroy(test_date);
	printf("19\t");
	test_date = date_create(test_string19);
	date_destroy(test_date);
	printf("20\t");
	test_date = date_create(test_string20);
	date_destroy(test_date);
	printf("21\t");
	test_date = date_create(test_string21);
	date_destroy(test_date);
	printf("22\t");
	test_date = date_create(test_string22);
	date_destroy(test_date);
	printf("23\t");
	test_date = date_create(test_string23);
	date_destroy(test_date);

	#endif

	/**********************/
	/* tree related tests */
	/**********************/

	// new tree structure test

	#ifdef TLD_TEST

	test_date_beg = date_create("01/01/2000");
	test_date_end = date_create("15/09/2003");
	
	tld = tldlist_create(test_date_beg, test_date_end);

	// trying to add 3 dates, only one can be inserted
	hostname = "test0.org";
	test_date = date_create("01/01/2000");
	tldlist_add(tld, hostname, test_date);
	test_date = date_create("02/01/2000");
	tldlist_add(tld, hostname, test_date);
	test_date = date_create("16/09/2003");
	tldlist_add(tld, hostname, test_date);

	tldnode_printout(tld->root);

	// trying to add the second repeated hostname
	test_date = date_create("17/03/2001");
	tldlist_add(tld, hostname, test_date);

	tldnode_printout(tld->root);

	// trying to add more diferent nodes
	hostname = "test1.org";
	test_date = date_create("17/03/2001");
	tldlist_add(tld, hostname, test_date);
	hostname = "test2.org";
	test_date = date_create("17/03/2001");
	tldlist_add(tld, hostname, test_date);

	tldnode_printout(tld->root);	

	#endif

	return 0;


}