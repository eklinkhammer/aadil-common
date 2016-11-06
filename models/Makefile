BUILD :=  build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

CXX := g++ -Wall --std=c++11 -lfann -I $(INCLUDE)

UNIT_TESTS := tests

all: test

run: $(BUILD)/actor.o
	$(CXX) $(BUILD)/actor.o -o run
	./run

lib: $(BUILD)/actor.o $(BUILD)/location.o $(BUILD)/world.o
	mkdir -p $(LIB)
	ar rcs $(LIB)/models.a $(BUILD)/actor.o $(BUILD)/location.o $(BUILD)/world.o

tests := $(wildcard $(TEST)/*_test.cpp $(TEST)/*_test.c)

test: lib
	$(CXX) -lgtest -lgtest_main $(LIB)/models.a $(tests) -o $(TEST)/$(UNIT_TESTS)
	./$(TEST)/$(UNIT_TESTS)
clean:
	rm -rf $(BUILD) $(LIB) $(TEST)/$(UNIT_TESTS)

$(BUILD)/world.o: $(BUILD)/actor.o $(INCLUDE)/world.h $(SRC)/world.cpp
	$(CXX) -c -I . -I $(SRC) $(SRC)/world.cpp -o $(BUILD)/world.o

$(BUILD)/actor.o: $(BUILD)/location.o $(INCLUDE)/actor.h $(SRC)/actor.cpp
	$(CXX) -c -I . -I $(SRC) $(SRC)/actor.cpp $(BUILD)/location.o -o $(BUILD)/actor.o

$(BUILD)/location.o:
	mkdir -p $(BUILD)
	$(CXX) -c -I . -I $(SRC) $(SRC)/location.cpp -o $(BUILD)/location.o
