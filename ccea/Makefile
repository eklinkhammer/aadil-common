BUILD := build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

UNIT_TESTS := tests

CXX := g++ -Wall --std=c++11 -I $(INCLUDE)
CCFLAG := -c -I . -I $(SRC)
LDFLAG := -lfann
TESTFLAG := -lgtest -lgtest_main

all: test

lib: $(BUILD)/ccea.o
	mkdir -p $(LIB)
	ar rcs $(LIB)/ccea.a $(wildcard $(BUILD)/*.o)

clean:
	rm -rf $(BUILD) $(TEST)/$(UNIT_TESTS) $(LIB)

tests := $(wildcard $(TEST)/*_test.cpp $(TEST)/*_test.c)

test: lib
	$(CXX) $(LDFLAG) $(TESTFLAG) $(LIB)/ccea.a $(tests) -o $(TEST)/$(UNIT_TESTS)
	./$(TEST)/$(UNIT_TESTS)

$(BUILD)/ccea.o:
	mkdir -p $(BUILD)
	$(CXX) $(CCFLAG) $(SRC)/ccea.cpp -o $(BUILD)/ccea.o
