/**************************************************/
/**             Authorship Statement             **/
/**************************************************/
/** Author: Willian de Oliveira Barreiros Junior **/
/** Login: 2105514D                              **/
/** Title of Assignment: AP3 Exercise 1          **/
/**************************************************/
/** This is my own work except for the checker   **/
/** of leap years, which was found on the course **/
/** slides (AP3/3013-2014, chap 02 slide 16).    **/
/**************************************************/

#include "date.h"

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr) {
	
	// temporary data fields
	long day, month, year;
	Date *date;

	// test string structure
	if (strlen(datestr) != 10 || datestr[2] != '/' || datestr[5] != '/') {
		printf("[data_create] wrong data string structure \n");
		return NULL;
	}

	// test day chars
	if (datestr[0] < '0' || datestr[0] > '3' || datestr[1] < '0' || datestr[1] > '9') {
		printf("[data_create] day chars not between 00 and 39 \n");
		return NULL;
	}
	
	// convert day to integer
	day = (datestr[0] - '0') * 10 + (datestr[1] - '0');

	// test if the day is between 1 and 31
	if (day > 31 || day < 1) {
		printf("[data_create] day not between 1 and 31 \n");
		return NULL;
	}

	// test month chars
	if (datestr[3] < '0' || datestr[3] > '1' || datestr[4] < '0' || datestr[4] > '9') {
		printf("[data_create] month chars not between 00 and 19 \n");
		return NULL;
	}

	// convert month to integer
	month = (datestr[3] - '0') * 10 + (datestr[4] - '0');

	// test if the month is between 1 and 12
	if (month > 12 || month < 1) {
		printf("[data_create] month not between 1 and 12 \n");
		return NULL;
	}

	// test if the day and month are compatible
	if ((month % 2 == 0 && day > 30 && month != 2)) {
		printf("[data_create] day do not match with the month \n");
		return NULL;
	}

	// test year chars
	if (datestr[6] < '0' || datestr[6] > '2' || datestr[7] < '0' || datestr[7] > '9' || datestr[8] < '0' || datestr[8] > '9' || datestr[9] < '0' || datestr[9] > '9') {
		printf("[data_create] year chars not between 0000 and 2999 \n");
		return NULL;
	}

	// convert year to integer
	year = (datestr[6] - '0') * 1000 + (datestr[7] - '0') * 100 + (datestr[8] - '0') * 10 + (datestr[9] - '0');

	// test if the leap year and the month are compatible
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		// leap year
		if (month == 2 && day > 29) {
			printf("[data_create] day do not match with February on the leap year \n");
			return NULL;
		}
	} else {
		// not a leap year
		if (month == 2 && day > 28) {
			printf("[data_create] day do not match with February on the common year \n");
			return NULL;
		}
	}

	// instanciate a new Date
	date = malloc(sizeof(Date));

	// add year
	date->date_bit = year;
	
	// add month
	date->date_bit <<= 4;
	date->date_bit += month;

	// add day
	date->date_bit <<= 5;
	date->date_bit += day;

	#ifdef DEBUG

	printf("success - hex: ");
	printf("%x\tdate(yyyy/mm/dd): ", date->date_bit);
	date_pretty_print(date);
	printf("\n");
	#endif

	return date;

}

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d) {
	Date *new_date = malloc(sizeof(Date));
	new_date->date_bit = d->date_bit;
	return new_date;
}

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2) {
	return date1->date_bit - date2->date_bit;
}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d) {
	free(d);
}

void date_pretty_print (const Date *d) {
	printf("%u/%u/%u\n", (d->date_bit >> 9), ((d->date_bit << 23) >> 28), ((d->date_bit << 27) >> 27));
}