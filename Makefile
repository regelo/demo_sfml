
.PHONY: run

CC:= g++.exe
LDFLAGS:= -static -static-libgcc -static-libstdc++ -Wl,-RSFML-2.5.1/lib
CCFLAGS:= -std=c++11
INCLUDES:= -ISFML-2.5.1/include
LIBS:= -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system 

run: petitjeu.exe
	petitjeu.exe

petitjeu.exe: main.o nuage.o scene.o etoile.o joueur.o animateur.o objetanime.o
	$(CC) $(LDFLAGS) main.o nuage.o scene.o etoile.o joueur.o animateur.o objetanime.o -o petitjeu.exe $(LIBS) 


animateur.o: animateur.cpp animateur.h
	$(CC) $(CCFLAGS) -o animateur.o -c animateur.cpp $(INCLUDES)

joueur.o: joueur.cpp joueur.h animateur.h objetanime.h scene.h
	$(CC) $(CCFLAGS) -o joueur.o -c joueur.cpp $(INCLUDES)

etoile.o: etoile.cpp etoile.h animateur.h objetanime.h
	$(CC) $(CCFLAGS) -o etoile.o -c etoile.cpp $(INCLUDES)

main.o: main.cpp joueur.h scene.h
	$(CC) $(CCFLAGS) -o main.o -c main.cpp $(INCLUDES)

nuage.o: nuage.cpp nuage.h scene.h objetanime.h
	$(CC) $(CCFLAGS) -o nuage.o -c nuage.cpp $(INCLUDES)

objetanime.o: objetanime.cpp objetanime.h animateur.h
	$(CC) $(CCFLAGS) -o objetanime.o -c objetanime.cpp $(INCLUDES)

scene.o: scene.cpp scene.h etoile.h nuage.h
	$(CC) $(CCFLAGS) -c scene.cpp $(INCLUDES)


clean:
	del *.o
	del *.exe



