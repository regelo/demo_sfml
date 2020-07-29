#ifndef __SCENE_H__
#define __SCENE_H__

#include <cstdlib>
#include <ctime>
#include <list>
#include <vector>

#include "animateur.h"
#include "etoile.h"

class Scene {
  private:
    // Conteneur des obstacles. Les obstacles ne changent pas durant la vie du programme (pas d'ajouts, pas de retraits), donc un std::vector fait l'affaire.
	std::vector<sf::Sprite> obstacles;
	// Conteneur des étoiles. Je veux pouvoir enlever des étoiles au milieu du conteneur et en ajouter à la fin sans problèmes, donc un std::list fait l'affaire.
    std::list<Etoile> etoiles;
	
	// La texture ne peut pas être une variable locale, car lorsque la variable est détruite, l'affichage du lutin ne fonctionne pas correctement. 
	sf::Texture image_obstacle;
	
	int points = 0;
	
  public:
    Scene() {
	  // Création des obstacles.
      this->image_obstacle.loadFromFile("sprites/roche.png");
      
      // Initialisation du générateur de nombres aléatoires avec le temps actuel.
      srand(time(NULL));
      
      // Création de trois obstacles à x=150, x=200, x=250 avec une valeur aléatoire entre 50 et 149 pour y.
      for (int i=0 ; i<3 ; i++){
	    int x = 150 + i*50;
	    int y = 50 + rand()%100;
	    sf::Sprite obstacle;
        obstacle.setTexture(this->image_obstacle);
        obstacle.setPosition(x, y);
	    this->obstacles.push_back(obstacle);
	  }
	  
	  // Création de cinq étoiles à x=125, x=175, x=225, x=275 et x=325, avec une valeur aléatoire entre 50 et 149 pour y.
	  for (int i=0 ; i<5 ; i++) {
        int x = 125+i*50;
        int y = 50+ rand()%100;
	    Etoile etoile(x, y);
	    etoiles.push_back(etoile);
	  }
	}
	
	int getPoints() {return this->points;}
	
	// Afficher le contenu de la scène
    void afficherScene(sf::RenderWindow& window) {
		
	  // On parcours l'ensemble du vecteur pour afficher tous les obstacles.
	  for (int i=0 ; i<obstacles.size() ; i++) window.draw(this->obstacles[i]);
	  
	  // On parcours l'ensemble de la liste pour afficher toutes les étoiles.
	  std::list<Etoile>::iterator it;
	  for (it=this->etoiles.begin() ; it!=this->etoiles.end() ; it++) it->afficherEtoile(window);
    }
    
    // Vérifier si une position entre en collision avec des objets de la scène.
    bool verifierCollision(int position_x, int position_y) {
		
	  // Vérifier s'il y a une collision avec un étoile.
	  std::list<Etoile>::iterator it;
	  std::list<Etoile>::iterator etoile_touchee = this->etoiles.end();
	  for (it=this->etoiles.begin() ; it!=this->etoiles.end() ; it++) {
			sf::Rect<float> rectangle = it->getLutin().getGlobalBounds();
			if (  (position_x >= rectangle.left-16) && 
			      (position_x <= rectangle.left-16+rectangle.width) && 
			      (position_y >= rectangle.top-16) && 
			      (position_y <= rectangle.top-16+rectangle.height)
			   ) {
		      // Notre joueur a touché une étoile !
		      this->points++;
		      // On prend note de l'étoile à effacer, parce que l'effacer au milieu de la boucle pourrait causer des problèmes avec l'itérateur.
		      etoile_touchee = it;
			}
	  }
	  // Si on a touché une étoile, on peut l'effacer.
	  if (etoile_touchee != this->etoiles.end()) this->etoiles.erase(etoile_touchee);
		
		// Vérification avec les bordures du jeu.
		if (position_x >= 350) return true;
		if (position_x <= 10) return true;
		if (position_y >= 150) return true;
		if (position_y <= 10) return true;
		
		// Vérification avec les obstacles
		for (int i=0 ; i<obstacles.size() ; i++) {
			sf::Rect<float> rectangle = this->obstacles[i].getGlobalBounds();
			
			if (  (position_x >= rectangle.left-16) && 
			      (position_x <= rectangle.left-16+rectangle.width) && 
			      (position_y >= rectangle.top-16) && 
			      (position_y <= rectangle.top-16+rectangle.height)
			   ) return true;
		}
		return false;
	}
};

#endif
