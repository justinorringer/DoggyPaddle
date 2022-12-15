#
# Simple Makefile that compiles all .c and .s files in the same folder
#

# make sure GBDK_HOME var is set
# can be env var: export GBDK_HOME = /home/danielagbay/.local/gbdk/
LCC = $(GBDK_HOME)bin/lcc 

# You can uncomment the line below to turn on debug output
# LCC = $(LCC) -Wf--debug

# You can set the name of the .gb ROM file here
PROJECTNAME := DoggyPaddle

BINS	   := $(PROJECTNAME).gb
CSOURCES   := $(wildcard *.c) $(wildcard */*.c)

all: clean $(BINS)

# Compile and link all source files in a single call to LCC
$(BINS):	$(CSOURCES)
	$(LCC) -Wf--debug -o $@ $?

clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm

build: $(BINS)