#include "etoile.h"


Etoile::Etoile(int x, int y) : ObjetAnime(x, y) {
  this->images.ajouterImage("sprites/etoile_a.png");
  this->images.ajouterImage("sprites/etoile_b.png");
  this->images.ajouterImage("sprites/etoile_c.png");
  this->images.ajouterImage("sprites/etoile_b.png");
}


void Etoile::afficherEtoile(sf::RenderWindow& fenetre) {
  this->lutin.setTexture(this->images.assignerImageSuivante());
  fenetre.draw(this->lutin);
}
