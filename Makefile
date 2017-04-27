#compile
CC = g++
CFLAG = -Wall -Werror -pipe -O2 -fPIC -D__STDC_CONSTANT_MACROS -std=c++11
ESS_LIB_PATH = ./bin
ESS_LIB_FLAG = -L $(ESS_LIB_PATH)/lib -I $(ESS_LIB_PATH)/include -lessentia -Wl,-rpath=$(ESS_LIB_PATH)/lib
#folder define
SRC = src
SRCTEST = test
BIN = bin
BUILD = build/src
BUILDTEST = build/test
DIRGUARD=@mkdir -p $(@D)
#target
TARGET   = main
#sources
SOURCES  := $(wildcard $(SRC)/*.c)
SOURCESTEST  := $(wildcard $(SRCTEST)/*.c)
#INCLUDES := $(wildcard $(SRC)/*.h)
#objects
OBJECTS  := $(SOURCES:$(SRC)/%.c=$(BUILD)/%.o)
OBJECTSTEST  := $(SOURCESTEST:$(SRCTEST)/%.c=$(BUILDTEST)/%.o)

#essentia link
ESS_LINK = https://github.com/MTG/essentia/archive/v2.1_beta3.zip
rm       = rm -f

all: build

build: $(ESS_LIB_PATH)/lib/libessentia.so
	$(CC) $(CFLAG) $(SRC)/main.cpp $(SRC)/essentaisAlgoritms.cpp -o  $(BIN)/standard_mfcc $(ESS_LIB_FLAG)

$(ESS_LIB_PATH)/lib/libessentia.so: install_essentia

.PHONE: install_essentia
install_essentia: thirdparty/essentia/waf
	$(MAKE) -C thirdparty/essentia

thirdparty/essentia/waf:
	mkdir -p thirdparty
	wget $(ESS_LINK)
	unzip v2.1_beta3.zip
	mv essentia-2.1_beta3/* thirdparty/essentia
	rm -f -R v2.1_beta3.zip essentia-2.1_beta3
