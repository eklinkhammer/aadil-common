BUILD := build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

UNIT_TESTS := tests

CXX := g++ -Wall --std=c++11 -lfann -I $(INCLUDE)
COMPILEFLAGS := -c -I . -I $(SRC)

all: test

lib: $(BUILD)/ccea.o
	mkdir -p $(LIB)
	ar rcs $(LIB)/ccea.a $(wildcard $(BUILD)/*.o)

clean:
	rm -rf $(BUILD) $(TEST)/$(UNIT_TESTS) $(LIB)

tests := $(wildcard $(TEST)/*_test.cpp $(TEST)/*_test.c)

test: lib
	$(CXX) -lgtest -lgtest_main $(LIB)/ccea.a $(tests) -o $(TEST)/$(UNIT_TESTS)
	./$(TEST)/$(UNIT_TESTS)

$(BUILD)/ccea.o:
	mkdir -p $(BUILD)
	$(CXX) $(COMPILEFLAGS)  -I . -I $(INCLUDE)/ccea.h -I $(INCLUDE)/net_evaluator.h $(SRC)/ccea.cpp -o $(BUILD)/ccea.o
