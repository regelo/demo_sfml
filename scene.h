#ifndef __SCENE_H__
#define __SCENE_H__

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

// Cette "forward declaration" de la classe est nécessaire à cause de dépendances cycliques entre "nuage.h" et "scene.h".
class Scene;

#include "etoile.h"
#include "nuage.h"

class Scene {
  private:
    // Conteneur des obstacles et des nuages. Les obstacles et les nuages ne changent pas durant la vie du programme (pas d'ajouts, pas de retraits), donc un std::vector fait l'affaire.
    std::vector<sf::Sprite> obstacles;
    std::vector<Nuage> nuages;

    // Conteneur des étoiles. Il y a un maximum de cinq étoiles. Je veux pouvoir effacer des étoiles au milieu et les ajouter par la suite, donc je prends un tableau statique de pointeurs. Il y aura des cases qui contiennent des étoiles, et des cases à NULL durant le déroulement du jeu.
    Etoile* etoiles[5];

    // La texture ne peut pas être une variable locale, car lorsque la variable est détruite, l'affichage du lutin ne fonctionne pas correctement. 
    sf::Texture image_obstacle;

    // Points accumulés par le joueur.
    int points = 0;

    // Indicateur si la partie est terminée ou non.
    bool partie_terminee = false;

  public:
    Scene();

    int getPoints() {return this->points;}
    bool getPartieTerminee() {return this->partie_terminee;}

    // Afficher le contenu de la scène
    void afficherScene(sf::RenderWindow& window, int joueur_x, int joueur_y);
    
    // Vérifier si la position du joueur entre en collision avec des objets de la scène.
    bool verifierCollisionJoueur(int position_x, int position_y);

    // Vérifier si la position du nuage entre en collision avec des objets de la scène (et le joueur).
    bool verifierCollisionNuage(int nuage_x, int nuage_y, int joueur_x, int joueur_y);

  private:
    // Fonction privée qui permet de créer deux étoiles aux positions X les plus éloignées du joueur. Elle devrait être appelée quand il ne reste que deux des cinq étoiles originales.
    void regenererEtoiles(int position_x);
};

#endif
