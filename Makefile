MODEL := models
CCEA := ccea

BUILD :=  build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

tests := $(wildcard $(TEST)/*_test.cpp $(TEST)/*_test.c)

CXX := g++ -Wall --std=c++11 -lfann -I $(INCLUDE) -I $(MODEL)/$(INCLUDE) -I $(CCEA)/$(INCLUDE)
COMPILEFLAGS := -c -I . -I $(SRC) $(CCEA)/$(LIB)/$(CCEA).a $(MODEL)/$(LIB)/$(MODEL).a
UNIT_TESTS := tests

all: test

test: lib
	$(CXX) -lgtest -lgtest_main $(LIB)/aadil_common.a $(tests) -o $(TEST)/$(UNIT_TESTS)
	./$(TEST)/$(UNIT_TESTS)

lib:  $(BUILD)/simulation.o $(BUILD)/simNetEval.o
	mkdir -p $(LIB)
	ar rcs $(LIB)/sim.a $(wildcard $(BUILD)/*.o)
	libtool -o $(LIB)/aadil_common.a $(LIB)/sim.a $(MODEL)/$(LIB)/$(MODEL).a $(CCEA)/$(LIB)/$(CCEA).a
	mkdir -p $(LIB)/$(INCLUDE)
	cp -R $(MODEL)/$(INCLUDE) $(LIB)
	cp -R $(CCEA)/$(INCLUDE) $(LIB)
	cp -R $(INCLUDE) $(LIB)

$(BUILD)/simNetEval.o: $(CCEA)/$(LIB)/$(CCEA).a $(BUILD)/simulation.o
	$(CXX) $(COMPILEFLAGS) $(SRC)/simNetEval.cpp -o $(BUILD)/simNetEval.o

$(BUILD)/simulation.o: $(CCEA)/$(LIB)/$(CCEA).a $(MODEL)/$(LIB)/$(MODEL).a
	mkdir -p $(BUILD)
	$(CXX) $(COMPILEFLAGS)  $(SRC)/simulation.cpp -o $(BUILD)/simulation.o

clean:
	cd $(MODEL) && make clean
	cd $(CCEA) && make clean
	rm -rf $(BUILD) $(LIB)

cleanl:
	rm -rf $(BUILD) $(LIB)
$(MODEL)/$(LIB)/$(MODEL).a:
	cd $(MODEL) && make

$(CCEA)/$(LIB)/$(CCEA).a:
	cd $(CCEA) && make
