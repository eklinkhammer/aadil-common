MODEL := models
CCEA := ccea

BUILD :=  build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

CXX := g++ -Wall --std=c++11 -lfann -I $(INCLUDE) -I $(MODEL)/$(INCLUDE) -I $(CCEA)/$(INCLUDE)
COMPILEFLAGS := -c -I . -I $(SRC) $(CCEA)/$(LIB)/$(CCEA).a $(MODEL)/$(LIB)/$(MODEL).a
UNIT_TESTS := tests

all: lib

lib:  $(BUILD)/simulation.o $(BUILD)/simNetEval.o
	mkdir -p $(LIB)
	ar rcs $(LIB)/aadil_common.a $(wildcard $(BUILD)/*.o)
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

$(MODEL)/$(LIB)/$(MODEL).a:
	cd $(MODEL) && make

$(CCEA)/$(LIB)/$(CCEA).a:
	cd $(CCEA) && make
