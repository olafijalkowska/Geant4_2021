DESTDIR=.
CINCLUDEDIRS = -Iinclude
CPPFLAGS  += -O3
CPPFLAGS  += -std=c++0x
CPPFLAGS += $(CINCLUDEDIRS)
SRC = src/

ruletka: szatanskaGra.o Ruletka.o
	g++ szatanskaGra.o Ruletka.o -o ruletka
	
szatanskaGra.o: szatanskaGra.cpp
	g++ $(CPPFLAGS) -c szatanskaGra.cpp
    
Ruletka.o: $(SRC)Ruletka.cpp
	g++ $(CPPFLAGS) -c $(SRC)Ruletka.cpp

clean:
	rm -f *.o *~
