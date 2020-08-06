#ifndef __ANIMATEUR_H__
#define __ANIMATEUR_H__

// SFML libraries
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

// Librairies standard
#include <iostream>
#include <vector>
#include <string>

class Animateur {
  private:
    std::vector<sf::Texture> images;
    int image_courante = 0;
  public:
    // Retourne la texture courante de l'animateur. Notez que la méthode retourne une référence constante, donc une référence vers un objet dont on ne peut pas changer les attributs. 
    const sf::Texture& getImageCourante() const;

    // Ajoute une image au vecteur des textures.
    void ajouterImage(std::string nom_fichier);

    // L'image courante devient l'image précédente. Celle-ci est retournée. Notez que la méthode retourne une référence constante, donc une référence vers un objet dont on ne peut pas changer les attributs.
    const sf::Texture& assignerImagePrecedente();

    // L'image courante devient l'image suivante. Celle-ci est retournée. Notez que la méthode retourne une référence constante, donc une référence vers un objet dont on ne peut pas changer les attributs.
    const sf::Texture& assignerImageSuivante();

    // L'image courante devient l'image spécifiée dans l'index. Celle-ci est retournée. Si l'index est invalide, on retourne la première image. S'il n'y a aucune image, cette méthode peut donc causer un crash. Notez que la méthode retourne une référence constante, donc une référence vers un objet dont on ne peut pas changer les attributs.
    const sf::Texture& assignerImageIndex(int index);
};

#endif
