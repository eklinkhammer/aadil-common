MODEL := models
CCEA := ccea
SIM := simulation

BUILD :=  build
INCLUDE := include
SRC := src
TEST := test
LIB := lib
LIBNAME := aadil_common.a
EXEC := experiment

CXX := g++ -Wall --std=c++11 -I $(INCLUDE) -I $(MODEL)/$(INCLUDE) -I $(CCEA)/$(INCLUDE) -I $(SIM)/$(INCLUDE)

CCFLAG := -c -I . -I $(SRC)
LIBS :=  $(CCEA)/$(LIB)/$(CCEA).a $(MODEL)/$(LIB)/$(MODEL).a $(SIM)/$(LIB)/$(SIM).a
LDFLAG := -lfann $(LIB)/$(LIBNAME)

all: $(EXEC)

run: $(EXEC)
	./$(EXEC)

$(EXEC): lib $(BUILD)/$(EXEC).o
	$(CXX) $(LDFLAG) $(BUILD)/$(EXEC).o -o $(EXEC)

lib:  $(LIBS)
	mkdir -p $(LIB)
	libtool -o $(LIB)/$(LIBNAME) $(SIM)/$(LIB)/$(SIM).a $(MODEL)/$(LIB)/$(MODEL).a $(CCEA)/$(LIB)/$(CCEA).a
	mkdir -p $(LIB)/$(INCLUDE)
	cp -R $(MODEL)/$(INCLUDE) $(LIB)
	cp -R $(CCEA)/$(INCLUDE) $(LIB)
	cp -R $(SIM)/$(INCLUDE) $(LIB)

$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CCFLAG) -o $@ $<

clean:
	rm -rf $(BUILD) $(LIB)

cleana:
	cd $(SIM) && make clean
	cd $(MODEL) && make clean
	cd $(CCEA) && make clean
	rm -rf $(BUILD) $(LIB)

$(MODEL)/$(LIB)/$(MODEL).a:
	cd $(MODEL) && make

$(CCEA)/$(LIB)/$(CCEA).a:
	cd $(CCEA) && make

$(SIM)/$(LIB)/$(SIM).a: $(MODEL)/$(LIB)/$(MODEL).a $(CCEA)/$(LIB)/$(CCEA).a
	cd $(CCEA) && make
