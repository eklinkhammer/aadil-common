BUILD := build
INCLUDE := include
SRC := src
TEST := test
LIB := lib

UNIT_TESTS := cceaGTests

CXX := g++ -Wall --std=c++11 -lfann

all: lib

lib: $(BUILD)/ccea.o
	ar rcs $(LIB)/ccea.a $(BUILD)/ccea.o

clean:
	rm -rf $(BUILD) $(EXECUTABLE) $(TEST)/$(UNIT_TESTS) $(LIB)/ccea.a

test: lib $(TEST)/ccea_test.cpp
	$(CXX) -I $(INCLUDE) $(TEST)/ccea_test.cpp $(LIB)/ccea.a -o $(TEST)/$(UNIT_TESTS) -lgtest
	./$(TEST)/$(UNIT_TESTS)

$(BUILD)/ccea.o: include/ccea.h src/ccea.cpp
	mkdir -p $(BUILD)
	$(CXX) -c -I $(INCLUDE)/ -I . -I $(SRC)/ $(SRC)/ccea.cpp -o $(BUILD)/ccea.o
