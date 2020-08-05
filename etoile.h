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
};

#endif
