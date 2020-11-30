CC = gcc
CFLAGS = -c -Wall -g
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit 
COV_LIBS = -lgcov -coverage
SRC_DIR= src
HDR_DIR = hdr
TST_DIR= tests
SRC_FILES = $(addprefix $(SRC_DIR)/, *.c)
HDR_FILES = $(addprefix $(HDR_DIR)/, *.h) 
TST_FILES = $(addprefix $(TST_DIR)/, *.c)

OBJ = hw02.o hw02test.o
GCOV = gcovr 
GCONV_FLAGS = -r . --html --html-details 
TEST=print_integer_tests
EXE=print_integer

all: coverage_report.html

hw02.o: $(SRC_FILES) $(HDR_DIR)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(SRC_FILES) 

hw02test.o: $(TST_FILES)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS)  $(TST_FILES) 

print_integer_tests: $(OBJ)
	$(CC) $(OBJ) $(TST_LIBS) $(COV_LIBS) -o $(EXE)

test: $(TEST)
	./$(EXE)

coverage_report.html: test
	$(GCOV) $(GCONV_FLAGS) -o coverage_report.html

.PHONY: clean all

clean:
	-rm *.o *.html *.gcda *.gcno $(EXE)
