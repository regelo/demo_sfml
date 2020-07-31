# Compilation et lancement du logiciel

Si vous voulez seulement compiler et lancer le logiciel : 

 1. Ouvrez une invite de commande et déplacez vous à l'endroit où vous voulez que le projet se trouve,
 2. Téléchargez le contenu de GitHub avec `git clone https://github.com/regelo/demo_sfml.git`,
 3. Déplacez-vous dans le répertoire téléchargé,
 4. Compilez et lancez le logiciel avec la commande `make`

# Programmation C++ de jeux vidéos avec SFML

SFML (Simple and Fast Multimedia Library)) est un cadriciel ("framework") pour la production d'applications graphiques. C'est un cadriciel de bas niveau, donc il ne contient pas d'éléments permettant de créer des contrôles (boutons, champs de texte, etc.). Si on veut avoir un bouton, il faut donc se le créer nous-mêmes.

SFML n'offre pas non plus de fonctionalités pour faciliter la représentation d'éléments 3D. Il est donc plus approprié pour des applications 2D, comme des jeux utilisant des lutins ("sprites"). C'est donc un cadriciel limité, mais qui a l'avantage d'être simple à utiliser, à compiler, et à comprendre. L'idéal pour apprendre !

## SFML et programmation de jeux vidéos

Le cadriciel SFML est comparable aux cadriciels OpenGL de bas niveau (ex.: freeglut). De nos jours, les jeux vidéos ne sont programmés que rarement dans des cadriciels de bas niveau. Les développeurEs de jeux vidéos vont préférer programmer sur des moteurs ("engines") de haut niveau, comme par exemple Unreal Engine, Unity, CryEngine ou OGRE. L'avantage d'un moteur de haut niveau est que celui-ci va gérer tous les détails laborieux de bas niveau : gestion des événements, gestion des collisions, gestions des éléments graphiques, etc.

Il est cependant intéressant d'étudier au moins une fois un cadriciel de bas niveau comme SFML afin de mieux comprendre ce que font les moteurs de haut niveau. Les développeurEs de jeux vidéos utilisent parfois un cadriciel de bas niveau : 

 * Pour construire leur propre moteur,
 * Pour des raisons techniques : Par exemple, parce que les moteurs actuels ne répondent pas aux besoins du jeu planifié, et qu'il n'est pas possible de simplement ajouter une librairie à un moteur existant.
 * Pour des raisons légales : Les moteurs viennent avec des licences d'utilisation particulières, notamment quand on veut faire de la redistribution commerciale. 

Le cadriciel SFML n'est pas utilisé pour des jeux commerciaux complexes, du moins jusqu'à présent, vu ses limitations. Voir : https://en.wikipedia.org/wiki/Simple_and_Fast_Multimedia_Library#Video_game_use_examples

# Structure du projet

TODO classes, etc.
Pas sûr de la structure utilisée

# Compilation et Makefile

Jusqu'à présent, nous ne nous sommes pas trop cassé la tête sur la compilation du code. Nous avons fait confiance à CodeLite ou Repl.it pour compiler notre code, en espérant qu'ils devinent correctement la structure de notre projet. Quand on utilise du contenu externe (comme SFML), il faut passer plus de temps sur la configuration du projet, sur la manière dont ce projet est compilé.

Il existe plusieurs outils permettant de gérer cette configuration. Un des plus anciens, et un qui est encore très utilisé, est le Makefile. Il y a une tendance à remplacer les Makefile par d'autres outils plus facile à utiliser, mais il reste que c'est l'application la plus largement utilisée. Voici quelques alternatives populaires, si ça vous intéresse : 

 * CMake : un langage plus facile à utiliser qui permet de générer des Makefile complexes,
 * Apache Ant : populaire pour les applications Java,
 * Rake : pour les applications en langage Ruby.

Un Makefile est un fichier qui définit des suites de commandes à exécuter selon une situation donnée. Le langage de programmation du Makefile est très riche, mais aussi très difficile à lire et à comprendre. Sans entrer dans les (très nombreux) détails, voici ce qu'il permet de faire : 

TODO continuer 

# Boucle d'événements

# Détection de collisions

# Autres détails techniques 

Utilisation de références pour éviter des copies inutiles qui semblent se faire imparfaitement anyway. 
fichiers binaires dans le Git
 
