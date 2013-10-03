HEADERS = date.h tldlist.h
BASIC_SOURCE = tldmonitor.c
MY_WORK_SOURCE = date.c tldlist.c
TEST_SOURCE = date.c
TEST_OBJECTS = date.o tldmonitor.o tldlistLL.o
BASIC_TEST_OBJECTS = date.o tldmonitor.o
OUTPUT = tldmonitor

my: $(HEADERS) $(BASIC_SOURCE) $(MY_WORK_SOURCE)
	gcc -g -W -Wall $(BASIC_SOURCE) $(MY_WORK_SOURCE) -o $(OUTPUT)

test: $(HEADERS) date.o tldmonitor.o tldlistLL.o
	gcc -g -W -Wall $(TEST_OBJECTS) -o $(OUTPUT)

date.o: date.c date.h
	gcc -g -W -Wall -c date.c

tldmonitor.o: tldmonitor.c
	gcc -g -W -Wall -c tldmonitor.c

date_test: $(TEST_SOURCE) bench.c
	gcc -g -W -Wall $(TEST_SOURCE) bench.c -o test
