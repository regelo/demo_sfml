# Compilation à partir du code source

## Linux

Pour compiler et lancer le logiciel sur Linux : 

 0. Dépendances : Vous devez avoir le compilateur GCC et l'outil Make installé sur votre ordinateur.
 1. Ouvrez une invite de commande et déplacez vous à l'endroit où vous voulez que le projet se trouve,
 2. Téléchargez le contenu de GitHub avec `git clone https://github.com/regelo/demo_sfml.git`,
 3. Déplacez-vous dans le répertoire téléchargé,
 4. Compilez et lancez le logiciel avec la commande `make linux`

## Windows

Le logiciel a été programmé sur Linux et compile mieux sur cette plateforme. J'ai réussi à le compiler sur Windows, mais ça pourrait être plus compliqué pour vous. Pour compiler et lancer le logiciel sur Windows : 

 1. Malheureusement, le compilateur TDM64 ne contient pas certaines librairies nécesaires pour que le code puisse être compilé. Il faut donc que vous installiez le _port_ de GCC de MinGW64. Le plus facile est d'utiliser l'outil MSYS2 pour faire le travail : https://www.msys2.org/#installation L'installateur fonctionne normalement assez bien.
 2. Ouvrez une invite de commande et assurez-vous que c'est bien le GCC de MinGW64 qui est exécuté et non le GCC de TDM64 en tapant la commande `g++.exe --version`
 3. Déplacez votre invite de commande dans le répertoire où vous voulez avoir le code.
 5. Téléchargez le contenu de GitHub avec `git clone https://github.com/regelo/demo_sfml.git`,
 6. Déplacez-vous dans le répertoire téléchargé,
 8. Compilez et lancez le logiciel avec la commande `mingw32-make windows`

# Programmation C++ de jeux vidéos avec SFML

SFML (Simple and Fast Multimedia Library)) est un cadriciel ("framework") pour la production d'applications graphiques. C'est un cadriciel de bas niveau, donc il ne contient pas d'éléments permettant de créer des contrôles (boutons, champs de texte, etc.). Si on veut avoir un bouton, il faut donc se le créer nous-mêmes.

SFML n'offre pas non plus de fonctionalités pour faciliter la représentation d'éléments 3D. Il est donc plus approprié pour des applications 2D, comme des jeux utilisant des lutins ("sprites"). C'est donc un cadriciel limité, mais qui a l'avantage d'être simple à utiliser, à compiler, et à comprendre.

Les programmeurEs de jeux vidéos utilisent typiquement des cadriciels plus avancés, mais ça ne fait pas de tort de voir un peu ce qui se passe avec un cadriciel plus simple qui nous demande de tout faire à la main.

## SFML et programmation de jeux vidéos

Le cadriciel SFML est comparable aux cadriciels OpenGL de bas niveau (ex.: freeglut). De nos jours, les jeux vidéos ne sont programmés que rarement dans des cadriciels de bas niveau. Les développeurEs de jeux vidéos vont préférer programmer sur des moteurs ("engines") de haut niveau, comme par exemple Unreal Engine, Unity, CryEngine ou OGRE. L'avantage d'un moteur de haut niveau est que celui-ci va gérer tous les détails laborieux de bas niveau : gestion des événements, gestion des collisions, gestions des éléments graphiques, etc.

Il est cependant intéressant d'étudier au moins une fois un cadriciel de bas niveau comme SFML afin de mieux comprendre ce que font les moteurs de haut niveau. Les développeurEs de jeux vidéos utilisent parfois un cadriciel de bas niveau : 

 * Pour construire leur propre moteur,
 * Pour des raisons techniques : Par exemple, parce que les moteurs actuels ne répondent pas aux besoins du jeu planifié, et qu'il n'est pas possible de simplement ajouter une librairie à un moteur existant.
 * Pour des raisons légales : Les moteurs viennent avec des licences d'utilisation particulières, notamment quand on veut faire de la redistribution commerciale. 

Le cadriciel SFML n'est pas utilisé pour des jeux commerciaux complexes, du moins jusqu'à présent, vu ses limitations. Voir : https://en.wikipedia.org/wiki/Simple_and_Fast_Multimedia_Library#Video_game_use_examples

# Structure du projet

Le code possède six classes, dont une est une classe-mère (ObjetAnime) et trois sont des classes-filles (Joueur, Etoile, Nuage).

## Classe Animateur

Cette classe sert à contenir les images servant à l'animation des lutins ("sprites"). Les objets de cette classe forment un attribut pour l'objet ObjetAnime.

## Classe ObjetAnime

Cette classe-mère contient les attributs et méthodes communs pour tous les objets qui ont une animation. 

## Classe Etoile

Cette classe-fille gère le fonctionnement d'une étoile. Le but du jeu est que le joueur obtienne des étoiles, qui lui donne des points.

## Classe Joueur

Cette classe-fille gère le fonctionnement d'un joueur. La classe gère le déplacement du joueur et vérifie avec les autres objets de la scène si jamais celui-ci entre en collision avec un obstacle.

## Classe Nuage

Cette classe-fille gère le fonctionnement d'un nuage. Le nuage est un ennemi que le joueur doit éviter sinon la partie se termine.

## Classe Scene

Cette classe contient presque tous les éléments qui doivent être affichés à l'écran, sauf le joueur et le texte. Son objectif est de regrouper tous les affichages, mais ses responsabilités débordent en partie sur la gestion du jeu lui-même.

# Problèmes de qualité

La structure actuelle du code n'est pas optimale et il y aurait place à l'amélioration. 

## Design de la classe Scene

Pour le moment la Scene contient tous les éléments affichés sauf le joueur et le texte. Il faudrait peut-être mettre ces objets dans la scene afin d'être plus cohérent.

Il y aurait aussi matière à créer une autre classe appelée Jeu pour séparer l'affichage de la gestion du jeu lui-même (points, texte, partie terminée, collisions, etc.). 

## Choix du conteneur des Etoile

Les Etoile sont conservées dans la Scene dans un tableau statique de pointeurs. J'ai utilisé ce conteneur car c'est ce qui me semblait plus facile initialement pour la fonction privée "regenererEtoile". La complexité de la fonction semble indiquer que mon choix n'était pas idéal. 

Il y a sûrement un moyen d'améliorer cette approche.

## Relation entre Scene et les objets Etoile, Joueur et Nuage

La Scene fait du travail qui serait peut-être plus approprié de faire directement dans les objets. Il y aurait peut-être moyen de déplacer du code d'une classe à une autre. 

Pas sûr de la structure utilisée - ,  forward declaration, scene->objets

## Nuage et Scene et les "forward declaration"

Avec la structure actuelle, il y a une dépendance cyclique entre Nuage et Scene, c'est-à-dire que la classe Nuage possède un #include "scene.h" et que la classe Scene possède un #include "nuage.h". Cela nous force à faire des "forward declaration". Une "forward declaration" est similaire à un prototype de fonction. C'est une manière d'indiquer que la classe existe avant de la définir au complet.  

Une révision de la structure nous permettrait peut-être d'éviter ces dépendances cycliques et donc de faire des "forward declaration". Ceci dit, ce n'est peut-être pas possible. Il est quand même fréquent d'avoir des dépendances cycliques dans un programme. 

# Compilation et Makefile

Jusqu'à présent, nous ne nous sommes pas trop cassé la tête sur la compilation du code. Nous avons fait confiance à CodeLite ou Repl.it pour compiler notre code, en espérant qu'ils devinent correctement la structure de notre projet. Quand on utilise du contenu externe (comme SFML), il faut passer plus de temps sur la configuration du projet, sur la manière dont ce projet est compilé.

Il existe plusieurs outils permettant de gérer cette configuration. Un des plus anciens, et un qui est encore très utilisé, est le Makefile. Il y a une tendance à remplacer les Makefile par d'autres outils plus facile à utiliser, mais il reste que c'est l'application la plus largement utilisée. Voici quelques alternatives populaires, si ça vous intéresse : 

 * CMake : un langage plus facile à utiliser qui permet de générer des Makefile complexes,
 * Apache Ant : populaire pour les applications Java,
 * Rake : pour les applications en langage Ruby.

Un Makefile est un fichier qui définit des suites de commandes à exécuter selon une situation donnée. Le langage de programmation du Makefile est très riche, mais aussi très difficile à lire et à comprendre. Sans entrer dans les (très nombreux) détails, voici un exemple d'un Makefile partiel : 

`main.o: main.cpp main.h
	gcc -o main.o -c main.cpp`

Où : 

 * "main.o" : La cible, ce que la commande devrait produire.
 * 'main.cpp main.h" : Les fichiers requis pour que les commandes suivantes puissent fonctionner. Si ces fichiers n'existent pas, Make va essayer de trouver une cible capable de les produire. 
 * L'espace entre le bord gauche et le "gcc ..." doit absolument être un caractère de tabulation. Attention ! Certains étuditeurs de texte remplacent automatiquement le caractère de tabulation par des espaces ...
 * "gcc -o main.o -c main.cc" : La commande à exécuter si Make essaie d'exécuter la cible et que les fichiers requis sont présents. Notez qu'il n'y a ici qu'une seulement commande, mais qu'il est possible d'en mettre autant qu'on veut. Chaque commande doit être sur sa ligne, séparées du bord gauche par un caractère de tabulation.

En tapant simplement `make` dans l'invite de commandes, Make va lire le fichier Makefile dans le répertoire courant, et exécuter la première cible du fichier. Si on veut exécuter une commande particulière, on peut le faire en spécifiant la cible, comme par exemple en tapant `make main.o`

# Boucle d'événements

La plupart des cadriciels supportant un GUI (Graphical User Interface, ou interface graphique) ont besoin d'une boucle d'événements. Cette boucle tourne continuellement jusqu'à ce que le programme se termine. L'objectif de cette boucle est d'attendre jusqu'à ce que la personne utilisatrice fasse une action (ex.: taper sur une touche du clavier, bouger la souris, cliquer un bouton de la souris). Cette action de la personne utilisatrice produit typiquement un objet de type événement, qui contient les détails de l'événement qui s'est produit (ex.: quelle touche du clavier à été tapée, la souris s'est déplacée de tel endroit à tel endroit, le clic de souris a utilisé tel bouton, et a été cliqué à tel endroit). 

À partir de l'événement reçu, il est alors possible d'exécuter le code approprié pour le traiter. Par exemple, l'événement indique qu'il s'agit du clic du bouton gauche de la souris, et que ce clic a eu lieu à la coordonnée (x=30, y=50), ce qui correspond à un point à l'intérieur du bouton "Soumettre" de l'interface graphique. On sait donc qu'on doit exécuter le code correspondant à ce bouton.

# Système de coordonnées

Typiquement, les cadriciels de GUI utilisent le coin en haut à gauche comme origine (x=0, y=0) du système de coordonnées. Ainsi, plus la valeur de x augmente, et plus on se dirige vers la droite, tandis que plus la valeur de y augmente, et plus on se dirige vers le bas.

# Détection de collisions

L'ensemble de l'interface graphique est souvent appelée la "scène". Un élément dans la scène occupe un certain espace, qu'on nomme typiquement en anglais la "bounding box". Cette "bounding box" est importante car c'est ce qui permet d'évaluer si deux éléments entrent en collision ensemble, ou si un clic de souris a lieu à l'intérieur de cette boîte ou non.

Tous les objets ont une coordonnée, mais celle-ci n'est qu'un point. Si on veut déterminer si deux objets entrent en collision, ce n'est pas suffisant de déterminer si ces deux coordonnées sont identiques. Il faut déterminer si la "bounding box" du premier objet rencontrer la "bounding box" du deuxième objet.

La détection des collisions demande donc des calculs plus complexes. 

# KeyPress et KeyReleased

La plupart des cadriciels graphiques détectent quand une touche est appuyée et quand elle est relâchée. Dans la plupart des cas, on ne saisit que lorsque la touche est initialement appuyée : que la touche soit appuyée brièvement ou pour 15 secondes, cela ne résulte qu'en un seul événement.

Pour le jeu, ce ne serait pas pratique. On veut que si la touche 'D' reste appuyée pendant 5 secondes, que le joueur se déplace vers la droite pendant 5 secondes. On utilise donc des valeurs booléennes, qui sont mises à "true" lorsque la touche est appuyée et à "false" lorsque la touche est relâchée.  

# Autres détails techniques 

## Utilisation de références

Notez que les objets passés dans les méthodes sont généralement passés par référence. Il y a deux raisons à cela : 

 * Pour éviter de faire des copies pour rien. Certains de ces objets peuvent être relativement volumineux car ils contiennent des images. La performance du logiciel est importante ici, car sinon la boucle d'événements pourrait être ralenties, ce qui causerait des délais de la mise-à-jour de la scène.
 * Parce que la copie de certains éléments de SFML ne se fait pas bien. Une copie d'un "sf::Sprite" par exemple, ne fais pas la copie de la "sf::Texture" chargée. Donc le lutin ("sprirte") perd son image. Oups !

## Fichiers binaires dans le dépôt Git

Tel qu'expliqué durant le cours, ce n'est pas une bonne idée de mettre des fichiers binaires dans le dépôt Git. Dans ce cas-ci, j'ai décidé de les mettre quand même parce que :

 * Je n'ai pas l'intention de changer ces fichiers souvents,
 * Il n'y en a pas beaucoup et ils ne sont pas très gros,
 * Je travaille seul, donc il n'y a pas de risque de conflit sur ces fichiers.
 
