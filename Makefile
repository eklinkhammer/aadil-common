MODEL := models
CCEA := ccea

BUILD :=  build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

tests := $(wildcard $(TEST)/*_test.cpp $(TEST)/*_test.c)

CXX := g++ -Wall --std=c++11 -I $(INCLUDE) -I $(MODEL)/$(INCLUDE) -I $(CCEA)/$(INCLUDE)

CCFLAG := -c -I . -I $(SRC)
LIBS :=  $(CCEA)/$(LIB)/$(CCEA).a $(MODEL)/$(LIB)/$(MODEL).a
LDFLAG := -lfann $(LIBS)
TESTFLAG := -lgtest -lgtest_main
UNIT_TESTS := tests

all: test

test: lib
	$(CXX) $(LDFLAG) $(TESTFLAG) $(LIB)/aadil_common.a $(tests) -o $(TEST)/$(UNIT_TESTS)
	./$(TEST)/$(UNIT_TESTS)

lib:  $(LIBS) $(BUILD)/simulation.o $(BUILD)/simNetEval.o
	mkdir -p $(LIB)
	ar rcs $(LIB)/sim.a $(wildcard $(BUILD)/*.o)
	libtool -o $(LIB)/aadil_common.a $(LIB)/sim.a $(MODEL)/$(LIB)/$(MODEL).a $(CCEA)/$(LIB)/$(CCEA).a
	mkdir -p $(LIB)/$(INCLUDE)
	cp -R $(MODEL)/$(INCLUDE) $(LIB)
	cp -R $(CCEA)/$(INCLUDE) $(LIB)
	cp -R $(INCLUDE) $(LIB)

$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CCFLAG) -o $@ $<

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
