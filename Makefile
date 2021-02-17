# Indique qu'une commande "make run" doit exécuter l'entrée "run" du Makefile même s'il existe un fichier appelé "run".
.PHONY: run


run: petitjeu
	# Exécution du code.
	./petitjeu

petitjeu: main.o nuage.o scene.o etoile.o joueur.o animateur.o objetanime.o
	# Édition de lien ("linking")
	# -Wl,-R est une option donnée au linker pour que l'exécutable se rappelle où se trouve sa librairie.
	g++ -std=c++11 main.o nuage.o scene.o etoile.o joueur.o animateur.o objetanime.o -o petitjeu -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include -Wl,-RSFML-2.5.1/lib


animateur.o: animateur.cpp animateur.h
	# Compilation de animateur.cpp
	g++ -std=c++11 -o animateur.o -c animateur.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include

joueur.o: joueur.cpp joueur.h animateur.h objetanime.h scene.h
	# Compilation de joueur.cpp
	g++ -std=c++11 -o joueur.o -c joueur.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include

etoile.o: etoile.cpp etoile.h animateur.h objetanime.h
	# Compilation de etoile.cpp
	g++ -std=c++11 -o etoile.o -c etoile.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include

main.o: main.cpp joueur.h scene.h
	# Compilation du main.cpp
	g++ -std=c++11 -c main.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include

nuage.o: nuage.cpp nuage.h scene.h objetanime.h
	# Compilation de nuage.cpp
	g++ -std=c++11 -c nuage.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include

objetanime.o: objetanime.cpp objetanime.h animateur.h
	# Compilation de objetanime.cpp
	g++ -std=c++11 -o objetanime.o -c objetanime.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include

scene.o: scene.cpp scene.h etoile.h nuage.h
	# Compilation de scene.cpp
	g++ -std=c++11 -c scene.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include


clean:
    # Effacement des fichiers intermédiaires. Peut être appelé avec la commande "make clean".
	rm -f *.o



