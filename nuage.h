#ifndef __NUAGE_H__
#define __NUAGE_H__

// Cette "forward declaration" de la classe est nécessaire à cause de dépendances cycliques entre "nuage.h" et "scene.h".
class Nuage;

#include "objetanime.h"
#include "scene.h"

class Nuage : public ObjetAnime {
  private:
    // Type énuméré utilisé seulement au sein de la classe, donc défini de manière privée à l'intérieur de la classe.
    enum Orientation {
      MILIEU=0,
      GAUCHE=1,
      DROITE=2,
      HAUT=3,
      BAS=4
    };

    // Attribut du type énuméré indiquant la direction actuelle du nuage.
    Orientation orientation_courante = GAUCHE;
    
    // Vitesse du nuage en nombre de pixels de déplacement par "tick".
    int vitesse = 2;
  public:
    Nuage(int x, int y);

    // Déplace le nuage si nécessaire avant de l'afficher dans la fenêtre.
    void afficherNuage(sf::RenderWindow& fenetre, Scene& scene, int joueur_x, int joueur_y);

  private:
    // Cette fonction privée contient l'"intelligence artificielle" du nuage. Le nuage a : 
    //    50% de chance de garder la même direction,
    //    25% de chance de se diriger vers le joueur horizontalement ou verticalement,
    //    25% de chance d'aller dans n'importe quelle direction.
    // Notez que "milieu" est une direction, et fait que le nuage ne bouge pas. 
    void deplacerNuage(Scene& scene, int joueur_x, int joueur_y);
};

#endif
