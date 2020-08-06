#include "animateur.h"

const sf::Texture& Animateur::getImageCourante() const {
  return this->images[image_courante];
}

void Animateur::ajouterImage(std::string nom_fichier) {
  sf::Texture image;
  image.loadFromFile(nom_fichier);

  this->images.push_back(image);
}

const sf::Texture& Animateur::assignerImagePrecedente() {
  if (image_courante == 0) image_courante = this->images.size()-1;
  else image_courante--;

  return this->images[image_courante];
}

const sf::Texture& Animateur::assignerImageSuivante() {
  if (image_courante == this->images.size()-1) image_courante = 0;
  else image_courante++;

  return this->images[image_courante];
}

const sf::Texture& Animateur::assignerImageIndex(int index) {
  if (index < 0 || index >= this->images.size()) this->image_courante = 0;  
  else this->image_courante = index;

  return this->images[this->image_courante];
}
