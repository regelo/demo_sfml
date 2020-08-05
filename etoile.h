#ifndef __ETOILE_H__
#define __ETOILE_H__

#include "animateur.h"
#include "objetanime.h"

class Etoile : public ObjetAnime {
  public:
    Etoile(int x, int y) : ObjetAnime(x, y) {
		this->images.ajouterImage("sprites/etoile_a.png");
	    this->images.ajouterImage("sprites/etoile_b.png");
	    this->images.ajouterImage("sprites/etoile_c.png");
	    this->images.ajouterImage("sprites/etoile_b.png");
    }
    
    void afficherEtoile(sf::RenderWindow& fenetre) {
		this->lutin.setTexture(this->images.getImageSuivante());
		fenetre.draw(this->lutin);
	}
	
	// L'operator< permet de mettre les étoiles en ordre. L'ordre est basé sur la position en X de l'étoile dans la scène. C'est nécessaire afin de mettre les étoiles dans un conteneur ordonné comme le std::set. 
	bool operator<(const Etoile& autre_etoile) {
	  if (this->position_x < autre_etoile.position_x) return true;
	  return false;
	}
};

#endif
