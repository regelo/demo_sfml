#ifndef __ANIMATEUR_H__
#define __ANIMATEUR_H__

#include <vector>
#include <string>

class Animateur {
  private:
    std::vector<sf::Texture> images;
    int image_courante = 0;
  public:
    void ajouterImage(std::string nom_fichier) {
	  sf::Texture image;
	  image.loadFromFile(nom_fichier);
	  
	  this->images.push_back(image);
	}
	
    sf::Texture& getImagePrecedente() {
      if (image_courante == 0) image_courante = this->images.size()-1;
      else image_courante--;
      
      return this->images[image_courante];
	}
		
    sf::Texture& getImageCourante() {
      return this->images[image_courante];
    }
    
	sf::Texture& getImageSuivante() {
      if (image_courante == this->images.size()-1) image_courante = 0;
      else image_courante++;
      
      return this->images[image_courante];
	}
	
	sf::Texture& getImageIndex(int index) {
	  if (index < 0 || index >= this->images.size()) return this->images[0];
	  return this->images[index];
	}
};

#endif
