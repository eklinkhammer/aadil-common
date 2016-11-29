BUILD :=  build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

CXX := g++ -Wall --std=c++11 -I $(INCLUDE)
CCFLAG := -c -I . -I $(SRC)
LDFLAG := -lfann
TESTFLAG := -lgtest -lgtest_main
UNIT_TESTS := tests

all: test


lib: $(BUILD)/actor.o $(BUILD)/location.o $(BUILD)/world.o $(BUILD)/roverDomain.o $(BUILD)/poi.o $(BUILD)/agent.o $(BUILD)/globalAgent.o $(BUILD)/localAgent.o $(BUILD)/globalAgentDpp.o $(BUILD)/localAgentDpp.o
	mkdir -p $(LIB)
	ar rcs $(LIB)/models.a $(wildcard $(BUILD)/*.o)

tests := $(wildcard $(TEST)/*_test.cpp $(TEST)/*_test.c)

test: lib
	$(CXX) $(LDFLAG) $(TESTFLAG) $(LIB)/models.a $(tests) -o $(TEST)/$(UNIT_TESTS)
	./$(TEST)/$(UNIT_TESTS)
clean:
	rm -rf $(BUILD) $(LIB) $(TEST)/$(UNIT_TESTS)

$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CCFLAG) -o $@ $<
