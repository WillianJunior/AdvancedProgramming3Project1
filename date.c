#include "date.h"

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr) {
	
	// temporary data fields
	long day, month;//, year;

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

	// test year

	// add day
	// add month
	// add year

}

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d) {
	return d;
}

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2) {
	return 0;
}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d) {
	
}
