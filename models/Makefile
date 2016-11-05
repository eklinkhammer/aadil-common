BUILD :=  build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

CXX := g++ -Wall --std=c++11 -lfann -lgtest

UNIT_TESTS := tests

all: run

run: $(BUILD)/actor.o
	$(CXX) $(BUILD)/actor.o -o run
	./run

lib: $(BUILD)/actor.o $(BUILD)/location.o
	mkdir -p $(LIB)
	ar rcs $(LIB)/models.a $(BUILD)/actor.o $(BUILD)/location.o

test: lib $(TEST)/location_test.cpp
	$(CXX) -I $(INCLUDE) $(TEST)/location_test.cpp $(LIB)/models.a -o $(TEST)/$(UNIT_TESTS)
	./$(TEST)/$(UNIT_TESTS)
clean:
	rm -rf $(BUILD) $(LIB) $(TEST)/$(UNIT_TESTS)

$(BUILD)/actor.o: $(BUILD)/location.o $(INCLUDE)/actor.h $(SRC)/actor.cpp
	$(CXX) -c -I $(INCLUDE)/ -I . -I $(SRC) $(SRC)/actor.cpp $(BUILD)/location.o -o $(BUILD)/actor.o

$(BUILD)/location.o: $(INCLUDE)/location.h $(SRC)/location.cpp
	mkdir -p $(BUILD)
	$(CXX) -c -I $(INCLUDE)/ -I . -I $(SRC) $(SRC)/location.cpp -o $(BUILD)/location.o
