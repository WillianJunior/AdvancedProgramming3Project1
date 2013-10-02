#include <stdio.h>

#include "date.h"

int main () {

	Date *test_date;

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


	printf("0\n");
	test_date = date_create(test_string0);
	printf("1\n");
	test_date = date_create(test_string1);
	printf("2\n");
	test_date = date_create(test_string2);

	printf("3\n");
	test_date = date_create(test_string3);
	printf("4\n");
	test_date = date_create(test_string4);
	printf("5\n");
	test_date = date_create(test_string5);
	printf("6\n");
	test_date = date_create(test_string6);
	printf("7\n");
	test_date = date_create(test_string7);
	
	printf("8\n");
	test_date = date_create(test_string8);
	printf("9\n");
	test_date = date_create(test_string9);
	printf("10\n");
	test_date = date_create(test_string10);
	printf("11\n");
	test_date = date_create(test_string11);
	printf("12\n");
	test_date = date_create(test_string12);
	printf("13\n");
	test_date = date_create(test_string13);

	return 0;


}