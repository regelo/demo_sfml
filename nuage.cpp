#include "nuage.h"

// FONCTIONS PRIVÉES

void Nuage::deplacerNuage(Scene& scene, int joueur_x, int joueur_y) {
		int decision = rand()%20;
		if (decision<10) {
		  // On garde la même direction, donc on ne change rien.
		}
		else if (decision<12) {
		  // On se dirige vers le joueur, horizontalement.
		  if (this->position_x < joueur_x) {
		    this->orientation_courante = DROITE;
		    this->lutin.setTexture(this->images.assignerImageIndex(DROITE));
		  } else {
		    this->orientation_courante = GAUCHE;
		    this->lutin.setTexture(this->images.assignerImageIndex(GAUCHE));
		  }
		}
		else if (decision<15) {
		  // On se dirige vers le joueur, verticalement.
		  if (this->position_y < joueur_y) {
		    this->orientation_courante = BAS;
		    this->lutin.setTexture(this->images.assignerImageIndex(BAS));
		  } else {
		    this->orientation_courante = HAUT;
		    this->lutin.setTexture(this->images.assignerImageIndex(HAUT));
		  }
		}
		else if (decision==15) {
		  // On se dirige vers le milieu
		  this->orientation_courante = MILIEU;
		  this->lutin.setTexture(this->images.assignerImageIndex(MILIEU));
		}
		else if (decision==16) {
		  // On se dirige vers la gauche
		  this->orientation_courante = GAUCHE;
		  this->lutin.setTexture(this->images.assignerImageIndex(GAUCHE));
		}
		else if (decision==17) {
		  // On se dirige vers la droite
		  this->orientation_courante = DROITE;
		  this->lutin.setTexture(this->images.assignerImageIndex(DROITE));
		}
		else if (decision==18) {
		  // On se dirige vers le haut
		  this->orientation_courante = HAUT;
		  this->lutin.setTexture(this->images.assignerImageIndex(HAUT));
		}
		else if (decision==19) {
		  // On se dirige vers le bas
		  this->orientation_courante = BAS;
		  this->lutin.setTexture(this->images.assignerImageIndex(BAS));
		}
		
		// On déplace le lutin selon la direction choisie.
		int x = this->position_x;
		int y = this->position_y;
		
		switch(this->orientation_courante) {
		  case MILIEU:
		  {
		    // Le lutin ne bouge pas, donc on ne change rien.
		    break;
		  }
		  case GAUCHE:
		  {
		    x = x - this->vitesse;
		    break;
		  }
		  case DROITE:
		  {
		    x = x + this->vitesse;
		    break;
		  }
		  case HAUT:
		  {
		    y = y - this->vitesse;
		    break;
		  }
		  case BAS:
		  {
		    y = y + this->vitesse;
		    break;
		  }
		};
		
		// Vérifier s'il y a collision entre les bordures du jeu, les obstacles ou le joueur.
		bool collision = scene.verifierCollisionNuage(x, y, joueur_x, joueur_y);
		
		if (collision) {
		  // Le nuage ne se déplace pas dans la direction prévue et on ne change finalement pas la position.
		  x = this->position_x;
		  y = this->position_y;
		}
		
		this->position_x = x;
		this->position_y = y;
	    this->lutin.setPosition(this->position_x, this->position_y);
	}
