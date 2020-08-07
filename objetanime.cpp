#include "objetanime.h"

ObjetAnime::ObjetAnime(int x, int y) {
  // Initialisation de la position de départ
  this->position_x = x;
  this->position_y = y;
  this->lutin.setPosition(this->position_x, this->position_y);
}

sf::Sprite& ObjetAnime::obtenirLutin() {
  this->lutin.setTexture(images.getImageCourante());
  return this->lutin;
}

int ObjetAnime::getPositionX() {
  return this->position_x;
}

int ObjetAnime::getPositionY() {
  return this->position_y;
}	
