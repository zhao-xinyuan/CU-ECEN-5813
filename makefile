# Example 13
EXE=program1 program2 program3

# Main target
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lm
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-lm
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
main1.o: main1.c
main2.o: main2.c
main3.o: main3.c


# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
program1:main1.o 
	gcc -O3 -o $@ $^   $(LIBS)
program2:main2.o
	gcc -O3 -o $@ $^   $(LIBS)
program3:main3.o
	gcc -O3 -o $@ $^   $(LIBS)
#  Clean
clean:
	$(CLEAN)
