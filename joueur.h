#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include "animateur.h"
#include "scene.h"

class Joueur {
  private:
	// Informations propres au joueur.
    Animateur images;
    sf::Sprite lutin;
    int position_x;
    int position_y;
    int vitesse;
    
    // Pointeur vers la scène dans laquelle évolue le joueur.
    Scene* la_scene;
  public:
    Joueur(Scene* une_scene) {
	  this->la_scene = une_scene;
		
	  // Initialisation des images d'animation
      this->images.ajouterImage("sprites/sprite_a.png");
      this->images.ajouterImage("sprites/sprite_b.png");
      this->images.ajouterImage("sprites/sprite_c.png");
      
	  // Position de départ
	  this->position_x = 50;
	  this->position_y = 50;
	  this->lutin.setPosition(this->position_x, this->position_y);
	  
	  // Nombre de pixels de déplacement du lutin.
	  this->vitesse = 3;
	}

	sf::Sprite& getLutin() {
	  return this->lutin;
	}

	void deplacerGauche() {
	  // On essaie de déplacer le lutin vers la gauche.
	  int x = this->position_x - this->vitesse;
	  int y = this->position_y;
		
	  if (!this->la_scene->verifierCollision(x, y)) {
		  // On ne met à jour la position que s'il n'y a pas de collisions.
		  this->position_x = x;
		  this->position_y = y;
		  
		  this->lutin.setPosition(this->position_x, this->position_y);
      
	      // Passe à l'image précédente du lutin.
	      this->lutin.setTexture(this->images.getImagePrecedente());
	  }	
	}
	
	void deplacerDroite() {
	  // On essaie de déplacer le lutin vers la droite.
	  int x = this->position_x + this->vitesse;
	  int y = this->position_y;
	  
	  if (!this->la_scene->verifierCollision(x, y)) {
		  // On ne met à jour la position que s'il n'y a pas de collisions.
		  this->position_x = x;
		  this->position_y = y;
		  
		  this->lutin.setPosition(this->position_x, this->position_y);
      
	      // Passe à l'image suivante du lutin.
	      this->lutin.setTexture(this->images.getImageSuivante());
	  }
	}
	
	void deplacerHaut() {
	  // On essaie de déplacer le lutin vers le haut.
	  int x = this->position_x;
	  int y = this->position_y - this->vitesse;

	  if (!this->la_scene->verifierCollision(x, y)) {
		  // On ne met à jour la position que s'il n'y a pas de collisions.
		  this->position_x = x;
		  this->position_y = y;
		  
		  this->lutin.setPosition(this->position_x, this->position_y);
      
	      // Passe à l'image suivante du lutin.
	      this->lutin.setTexture(this->images.getImageSuivante());
	  }	
	}
	
	void deplacerBas() {
	  // On essaie de déplacer le lutin vers le bas.
	  int x = this->position_x;
	  int y = this->position_y + this->vitesse;

	  if (!this->la_scene->verifierCollision(x, y)) {
		  // On ne met à jour la position que s'il n'y a pas de collisions.
		  this->position_x = x;
		  this->position_y = y;
		  
		  this->lutin.setPosition(this->position_x, this->position_y);
      
	      // Passe à l'image précédente du lutin.
	      this->lutin.setTexture(this->images.getImagePrecedente());
	  }
	}
	
};

#endif
