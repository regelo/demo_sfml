.PHONY: linux
.PHONY: windows


CC:= g++.exe
LDFLAGS:= -static -static-libgcc -static-libstdc++ -Wl,-RSFML-2.5.1/lib
CCFLAGS:= -std=c++11
INCLUDES:= -ISFML-2.5.1/include
LIBS:= -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system 



L_CC:= g++
L_CCFLAGS:= -std=c++11
L_LDFLAGS:= -Llinux_SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-Rlinux_SFML-2.5.1/lib
L_INCLUDES:= -Ilinux_SFML-2.5.1/include

linux: linux_petitjeu
	./linux_petitjeu

linux_petitjeu: linux_main.o linux_nuage.o linux_scene.o linux_etoile.o linux_joueur.o linux_animateur.o linux_objetanime.o
	$(L_CC) $^ -o linux_petitjeu $(L_LDFLAGS)


linux_animateur.o: animateur.cpp animateur.h
	$(L_CC) $(L_CCFLAGS) -o animateur.o -c animateur.cpp -o $@ $(L_INCLUDES)

linux_joueur.o: joueur.cpp joueur.h animateur.h objetanime.h scene.h
	$(L_CC) $(L_CCFLAGS) -o joueur.o -c joueur.cpp -o $@ $(L_INCLUDES)

linux_etoile.o: etoile.cpp etoile.h animateur.h objetanime.h
	$(L_CC) $(L_CCFLAGS) -o etoile.o -c etoile.cpp -o $@ $(L_INCLUDES)

linux_main.o: main.cpp joueur.h scene.h
	$(L_CC) $(L_CCFLAGS) -c main.cpp -o $@ $(L_INCLUDES)

linux_nuage.o: nuage.cpp nuage.h scene.h objetanime.h
	$(L_CC) $(L_CCFLAGS) -c nuage.cpp -o $@ $(L_INCLUDES)

linux_objetanime.o: objetanime.cpp objetanime.h animateur.h
	$(L_CC) $(L_CCFLAGS) -o objetanime.o -c objetanime.cpp -o $@ $(L_INCLUDES)

linux_scene.o: scene.cpp scene.h etoile.h nuage.h
	$(L_CC) $(L_CCFLAGS) -c scene.cpp -o $@ $(L_INCLUDES)



CC:= g++.exe
LDFLAGS:= -static -static-libgcc -static-libstdc++ -Wl,-RSFML-2.5.1/lib
CCFLAGS:= -std=c++11
INCLUDES:= -ISFML-2.5.1/include
LIBS:= -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system 

windows: petitjeu.exe
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



linux_clean:
	rm -f *.o
	rm -f linux_petitjeu

windows_clean:
	del *.o
	del *.exe



