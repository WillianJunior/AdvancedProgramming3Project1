HEADERS = date.h tldlist.h
BASIC_SOURCE = tldmonitor.c
MY_WORK_SOURCE = date.c tldlist.c
TEST_SOURCE = date.c
TEST_FILES = date.c tldlistLL.o
OUTPUT = tldmonitor

my: $(HEADERS) $(BASIC_SOURCE) $(MY_WORK_SOURCE)
	gcc -g -W -Wall $(BASIC_SOURCE) $(MY_WORK_SOURCE) -o $(OUTPUT)

test: $(HEADERS) $(BASIC_SOURCE) $(TEST_SOURCE)
	gcc -g -W -Wall $(BASIC_SOURCE) $(TEST_FILES) -o $(OUTPUT)

date_test: $(TEST_SOURCE) bench.c
	gcc -g -W -Wall $(TEST_SOURCE) bench.c -o test
