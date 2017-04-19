#compile
CC = g++
CFLAG = -Wall -Werror -pipe -O2 -fPIC
ESS_FLAG = -I thirdparty/essentia/ -I thirdparty/essentia/scheduler/ -I thirdparty/essentia/streaming/  -I thirdparty/essentia/utils -D__STDC_CONSTANT_MACROS
ESS_END_FLAG = -lfftw3 -lyaml -lavcodec -lavformat -lavutil -lsamplerate -ltag -lfftw3f
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
	
build: lib/libessentia.so
	g++ -pipe -Wall -O2 -fPIC  -D__STDC_CONSTANT_MACROS src/main.cpp -o standard_mfcc -L ./lib -I ./include -lessentia -Wl,-rpath=./lib

lib/libessentia.so: install_essentia

.PHONE: install_essentia
install_essentia: thirdparty/essentia/waf
	$(MAKE) -C thirdparty/essentia

thirdparty/essentia/waf:
	mkdir -p thirdparty
	wget $(ESS_LINK)
	unzip v2.1_beta3.zip
	mv essentia-2.1_beta3/* thirdparty/essentia
	rm -f -R v2.1_beta3.zip essentia-2.1_beta3