.PHONY: run

run:
	# Compilation du code
	g++ -c main.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include
	g++ -c nuage.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include
	g++ -c scene.cpp -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include
	# Édition de lien ("linking")
	g++ -o main main.o nuage.o scene.o -LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -ISFML-2.5.1/include
	# Exécution du code en spécifiant d'abord une librairie. Les deux commandes doivent être sur la même ligne parce que Make exécute chaque ligne dans une invite de commande ("shell") différente.
	export LD_LIBRARY_PATH=./SFML-2.5.1/lib; ./main
