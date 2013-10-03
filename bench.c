#include <stdio.h>

#include "date.h"

int main (int argc, char *argv[]) {

	Date *test_date;

	test_date = malloc(sizeof(Date));

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
	printf("1\t");
	test_date = date_create(test_string1);
	printf("2\t");
	test_date = date_create(test_string2);

	printf("3\t");
	test_date = date_create(test_string3);
	printf("4\t");
	test_date = date_create(test_string4);
	printf("5\t");
	test_date = date_create(test_string5);
	printf("6\t");
	test_date = date_create(test_string6);
	printf("7\t");
	test_date = date_create(test_string7);
	
	printf("8\t");
	test_date = date_create(test_string8);
	printf("9\t");
	test_date = date_create(test_string9);
	printf("10\t");
	test_date = date_create(test_string10);
	printf("11\t");
	test_date = date_create(test_string11);
	printf("12\t");
	test_date = date_create(test_string12);
	printf("13\t");
	test_date = date_create(test_string13);
	printf("14\t");
	test_date = date_create(test_string14);
	printf("15\t");
	test_date = date_create(test_string15);
	printf("16\t");
	test_date = date_create(test_string16);
	printf("17\t");
	test_date = date_create(test_string17);
	printf("18\t");
	test_date = date_create(test_string18);
	printf("19\t");
	test_date = date_create(test_string19);
	printf("20\t");
	test_date = date_create(test_string20);
	printf("21\t");
	test_date = date_create(test_string21);
	printf("22\t");
	test_date = date_create(test_string22);
	printf("23\t");
	test_date = date_create(test_string23);

	free(test_date);


	return 0;


}