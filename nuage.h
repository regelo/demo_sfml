#ifndef __NUAGE_H__
#define __NUAGE_H__

// Cette "forward declaration" de la classe est nécessaire à cause de dépendances cycliques entre "nuage.h" et "scene.h".
class Nuage;

#include "objetanime.h"
#include "scene.h"

class Nuage : public ObjetAnime {
  private:
    enum Orientation {
	  MILIEU,
	  GAUCHE,
	  DROITE,
	  HAUT,
	  BAS
	};
	Orientation orientation_courante = GAUCHE;
	int vitesse = 2;
  public:
    Nuage(int x, int y) : ObjetAnime(x, y) {
	  // Les images sont ajoutées dans l'ordre, afin que index 0 soit milieu, index 1 soit gauche, etc. tel que l'enum le décrit.
	  this->images.ajouterImage("sprites/nuage_milieu.png");
	  this->images.ajouterImage("sprites/nuage_gauche.png");
	  this->images.ajouterImage("sprites/nuage_droite.png");
	  this->images.ajouterImage("sprites/nuage_haut.png");
	  this->images.ajouterImage("sprites/nuage_bas.png");
	}
	
	void afficherNuage(sf::RenderWindow& fenetre, Scene& scene, int joueur_x, int joueur_y) {
		deplacerNuage(scene, joueur_x, joueur_y);
		fenetre.draw(this->getLutin());
	}
	
  private:
    // Cette fonction privée contient l'"intelligence artificielle" du nuage. Le nuage a : 
    //    33% de chance de garder la même direction,
    //    33% de chance de se diriger vers le joueur horizontalement ou verticalement,
    //    33% de chance d'aller dans n'importe quelle direction.
    // Notez que "milieu" est une direction, et fait que le nuage ne bouge pas. 
	void deplacerNuage(Scene& scene, int joueur_x, int joueur_y);
};

#endif
