BUILD :=  build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

CXX := g++ -Wall --std=c++11 -lfann -I $(INCLUDE)
COMPILEFLAGS := -c -I . -I $(SRC)
UNIT_TESTS := tests

all: test

run: $(BUILD)/actor.o
	$(CXX) $(BUILD)/actor.o -o run
	./run

lib: $(BUILD)/actor.o $(BUILD)/location.o $(BUILD)/world.o $(BUILD)/roverdomain.o $(BUILD)/poi.o $(BUILD)/agent.o
	mkdir -p $(LIB)
	ar rcs $(LIB)/models.a $(wildcard $(BUILD)/*.o)

tests := $(wildcard $(TEST)/*_test.cpp $(TEST)/*_test.c)

test: lib
	$(CXX) -lgtest -lgtest_main $(LIB)/models.a $(tests) -o $(TEST)/$(UNIT_TESTS)
	./$(TEST)/$(UNIT_TESTS)
clean:
	rm -rf $(BUILD) $(LIB) $(TEST)/$(UNIT_TESTS)

$(BUILD)/agent.o: $(BUILD)/actor.o
	$(CXX) $(COMPILEFLAGS) $(SRC)/agent.cpp -o $(BUILD)/agent.o

$(BUILD)/poi.o: $(BUILD)/actor.o
	$(CXX) $(COMPILEFLAGS) $(SRC)/poi.cpp -o $(BUILD)/poi.o

$(BUILD)/roverdomain.o: $(BUILD)/world.o $(INCLUDE)/roverdomain.h $(SRC)/roverdomain.cpp
	$(CXX) $(COMPILEFLAGS) $(SRC)/roverdomain.cpp -o $(BUILD)/roverdomain.o

$(BUILD)/world.o: $(BUILD)/actor.o $(INCLUDE)/world.h $(SRC)/world.cpp
	$(CXX) $(COMPILEFLAGS) $(SRC)/world.cpp -o $(BUILD)/world.o

$(BUILD)/actor.o: $(BUILD)/location.o $(INCLUDE)/actor.h $(SRC)/actor.cpp
	$(CXX) $(COMPILEFLAGS) $(SRC)/actor.cpp -o $(BUILD)/actor.o

$(BUILD)/location.o:
	mkdir -p $(BUILD)
	$(CXX) $(COMPILEFLAGS) $(SRC)/location.cpp -o $(BUILD)/location.o
