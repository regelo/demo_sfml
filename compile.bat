
REM Effacement des fichiers intermediaires s'ils existent
rm -f *.o
rm -f *.exe

REM Compilation de animateur.cpp sur Windows
g++ -std=c++11 -o w_animateur.o -c animateur.cpp -Lwindows_SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Iwindows_SFML-2.5.1/include

REM Compilation de joueur.cpp sur Windows
g++ -std=c++11 -o w_joueur.o -c joueur.cpp -Lwindows_SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Iwindows_SFML-2.5.1/include

REM Compilation de etoile.cpp sur Windows
g++ -std=c++11 -o w_etoile.o -c etoile.cpp -Lwindows_SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Iwindows_SFML-2.5.1/include

REM Compilation du main.cpp sur Windows
g++ -std=c++11 -o w_main.o -c main.cpp -Lwindows_SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Iwindows_SFML-2.5.1/include

REM Compilation de nuage.cpp sur Windows
g++ -std=c++11 -o w_nuage.o -c nuage.cpp -Lwindows_SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Iwindows_SFML-2.5.1/include

REM Compilation de objetanime.cpp sur Windows
g++ -std=c++11 -o w_objetanime.o -c objetanime.cpp -Lwindows_SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Iwindows_SFML-2.5.1/include

REM Compilation de scene.cpp sur Windows
g++ -std=c++11 -o w_scene.o -c scene.cpp -Lwindows_SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Iwindows_SFML-2.5.1/include


REM Édition de lien ("linking") sur Windows
g++ -std=c++11 w_main.o w_nuage.o w_scene.o w_etoile.o w_joueur.o w_animateur.o w_objetanime.o -o w_main.exe -Lwindows_SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Iwindows_SFML-2.5.1/include


REM Execution du programme
w_main.exe

