HEADERS = date.h tldlist.h
BASIC_SOURCE = tldmonitor.c
MY_WORK_SOURCE = date.c tldlist.c
TEST_SOURCE = date.c
TEST_OBJECTS = date.o tldmonitor.o tldlistLL.o
BASIC_TEST_OBJECTS = date.o tldmonitor.o
OUTPUT = tldmonitor

all: clean my
	-rm *.o

clean: 
	-rm *.o
	-rm $(OUTPUT)
	-rm test

my: $(HEADERS) $(BASIC_SOURCE) $(MY_WORK_SOURCE)
	gcc -g -W -Wall $(BASIC_SOURCE) $(MY_WORK_SOURCE) -o $(OUTPUT)

testmytld: $(HEADERS) date.o tldlist.o bench.c
	gcc -g -W -Wall $(MY_WORK_SOURCE) bench.c -o test

testworkingtld: $(HEADERS) date.o tldmonitor.o tldlistLL.o
	gcc -g -W -Wall $(TEST_OBJECTS) -o $(OUTPUT)

date.o: date.c date.h
	gcc -g -W -Wall -c date.c

tldlist.o: tldlist.c tldlist.h
	gcc -g -W -Wall -c tldlist.c

tldmonitor.o: tldmonitor.c
	gcc -g -W -Wall -c tldmonitor.c
