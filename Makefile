BUILD := build
INCLUDE := include
SRC := src

# Eventually, this will be a library
EXECUTABLE := a0

CXX := g++ -Wall

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(BUILD) $(EXECUTABLE)

$(EXECUTABLE): $(BUILD)/ccea_main.o
	$(CXX) $(BUILD)/ccea_main.o -o $(EXECUTABLE)

$(BUILD)/ccea_main.o: include/ccea.h src/ccea.cpp
	mkdir -p $(BUILD)
	$(CXX) -c -I $(INCLUDE)/ -I . -I $(SRC)/ $(SRC)/ccea.cpp -o $(BUILD)/ccea_main.o
