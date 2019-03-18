CC= g++
STD = c++11
CCFLAGS     = $(INCLUDES) $(FORMAT) -g
CXFLAGS     =  $(INCLUDES) $(FORMAT) -g
FORMAT      = -m64
LNKCC       = $(CC)
LNKFLAGS    = $(CXFLAGS)
IDIR = ./include
INCLUDES   += -I$(IDIR)
LIBRARIES  += -lm -lX11 -lpthread
SRC = ./src/
BIN = ./bin/



rgb: $(SRC)rgb_d.cpp
	$(info [INFO]Compiling rgb...)
	@$(LNKCC) -std=$(STD) $(LNKFLAGS) $(SRC)rgb_d.cpp -o $(BIN)rgb $(LIBRARIES) -Wall -Wextra -Wfatal-errors -Werror=unknown-pragmas -Werror=unused-label -std=c++11 -pedantic -Dcimg_use_vt100 -Dcimg_display=1    

