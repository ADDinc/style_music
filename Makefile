#compile
CC = g++
CFLAG = -Wall -Werror -pipe -O2 -fPIC -D__STDC_CONSTANT_MACROS -std=c++11
ESS_LIB_PATH = ./bin
ESS_LIB_FLAG = -L $(ESS_LIB_PATH)/lib -lessentia -Wl,-rpath=$(ESS_LIB_PATH)/lib
ESS_INCLUDE = -I $(ESS_LIB_PATH)/include
GTEST_INCLUDE = -I $(SRCTEST)/$(GTEST)/include -I $(SRCTEST)/$(GTEST) -I $(SRC)
#folder define
SRC = src
SRCTEST = test
BIN = bin
BUILD = build/src
BUILDTEST = build/test
DIRGUARD=@mkdir -p $(@D)
GTEST = gtest_1.8.0
#target
TARGET = main
TARGETTEST = main_test
#sources
SOURCES := $(wildcard $(SRC)/*.cpp)
SOURCESTEST := $(wildcard $(SRCTEST)/*.cpp)
SOURCEFORTEST := $(wildcard $(SRC)/[^mai]*.cpp)
#objects
OBJECTS := $(SOURCES:$(SRC)/%.cpp=$(BUILD)/%.o)
OBJECTSTEST := $(SOURCESTEST:$(SRCTEST)/%.cpp=$(BUILDTEST)/%.o)
OBJECTSFORTEST := $(SOURCEFORTEST:$(SRC)/%.cpp=$(BUILD)/%.o)

#essentia link
ESS_LINK = https://github.com/MTG/essentia/archive/v2.1_beta3.zip
rm = rm -fR

all: build

build: $(ESS_LIB_PATH)/lib/libessentia.so $(OBJECTS)
	@$(CC) $(CFLAG) $(OBJECTS) -o $(BIN)/$(TARGET) $(ESS_LIB_FLAG)
	@echo "\033[0;32mLinking \""$(TARGET)"\" complete!\033[0;0m"

$(OBJECTS): $(BUILD)/%.o : $(SRC)/%.cpp
	@$(DIRGUARD)
	@$(CC) $(CFLAG) -c $< $(ESS_INCLUDE) -o $@
	@echo "\033[0;32mCompiled \""$<"\" successfully!\033[0;0m"

.PHONY: test
test: build_test
	@./$(BIN)/$(TARGETTEST)
		
build_test: $(ESS_LIB_PATH)/lib/libessentia.so $(OBJECTSFORTEST) $(OBJECTSTEST) $(BUILDTEST)/gtest-all.o
	@$(CC) $(CFLAG) $(OBJECTSFORTEST) $(OBJECTSTEST) $(BUILDTEST)/gtest-all.o -o $(BIN)/$(TARGETTEST) $(GTEST_INCLUDE) $(ESS_LIB_FLAG) -lpthread
	@echo "\033[0;32m[TEST] Linking \""$(TARGETTEST)"\" complete!\033[0;0m"

$(OBJECTSTEST): $(BUILDTEST)/%.o : $(SRCTEST)/%.cpp
	@$(DIRGUARD)
	@$(CC) $(CFLAG) -c $< $(ESS_INCLUDE) $(GTEST_INCLUDE) -o $@
	@echo "\033[0;32m[TEST] Compiled \""$<"\" successfully!\033[0;0m"

$(BUILDTEST)/gtest-all.o: $(SRCTEST)/$(GTEST)/src/gtest-all.cc
	@$(CC) $(CFLAG) -c $< $(GTEST_INCLUDE) -o $@
	@echo "\033[0;32m[TEST] Compiled \""$<"\" successfully!\033[0;0m"

$(ESS_LIB_PATH)/lib/libessentia.so: thirdparty/essentia/waf
	@$(MAKE) -C thirdparty/essentia

thirdparty/essentia/waf:
	@mkdir -p thirdparty
	@wget $(ESS_LINK)
	@unzip v2.1_beta3.zip
	@mv essentia-2.1_beta3/* thirdparty/essentia
	@rm -f -R v2.1_beta3.zip essentia-2.1_beta3

.PHONE: clean
clean:
	@$(rm) $(BUILD)/*.o

.PHONY: clean_test
clean_test:
	@$(rm) $(BUILDTEST)/*.o
