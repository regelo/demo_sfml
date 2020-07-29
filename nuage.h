#ifndef __NUAGE_H__
#define __NUAGE_H__

#include "objetanime.h"

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
	int vitesse = 1;
  public:
    Nuage(int x, int y) : ObjetAnime(x, y) {
	  // Les images sont ajoutées dans l'ordre, afin que index 0 soit milieu, index 1 soit gauche, etc. tel que l'enum le décrit.
	  this->images.ajouterImage("sprites/nuage_milieu.png");
	  this->images.ajouterImage("sprites/nuage_gauche.png");
	  this->images.ajouterImage("sprites/nuage_droite.png");
	  this->images.ajouterImage("sprites/nuage_haut.png");
	  this->images.ajouterImage("sprites/nuage_bas.png");
	}
	
	void afficherNuage(sf::RenderWindow& fenetre) {
		deplacerNuage();
		fenetre.draw(this->getLutin());
	}
	
  private:
    // Cette fonction privée contient l'"intelligence artificielle" du nuage. Le nuage a : 
    //    33% de chance de garder la même direction,
    //    33% de chance de se diriger vers le joueur horizontalement ou verticalement,
    //    33% de chance d'aller dans n'importe quelle direction.
    // Notez que "milieu" est une direction, et fait que le nuage ne bouge pas. 
	void deplacerNuage() {
		int decision = rand()%15;
		if (decision<5) {
		  // On garde la même direction.
		}
		else if (decision<7) {
		  // On se dirige vers le joueur, horizontalement.
		}
		else if (decision<10) {
		  // On se dirige vers le joueur, verticalement.
		}
		else if (decision=10) {
		  // On se dirige vers le milieu
		}
		else if (decision=11) {
		  // On se dirige vers la gauche
		}
		else if (decision=12) {
		  // On se dirige vers la droite
		}
		else if (decision=13) {
		  // On se dirige vers le haut
		}
		else if (decision=14) {
		  // On se dirige vers le bas
		}
	}
};

#endif
