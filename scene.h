#ifndef __SCENE_H__
#define __SCENE_H__

#include <cstdlib>
#include <ctime>
#include <vector>

class Scene {
  private:
	std::vector<sf::Sprite> obstacles;
	
	// La texture ne peut pas être une variable locale, car lorsque la variable est détruite, l'affichage du lutin ne fonctionne pas correctement. 
	sf::Texture image_obstacle;
  public:
    Scene() {
	  // Création des obstacles.
      this->image_obstacle.loadFromFile("sprites/roche.png");
      
      // Initialisation du générateur de nombres aléatoires avec le temps actuel.
      srand(time(NULL));
      
      // Création de trois obstacles à x=150, x=200, x=250 avec une valeur alétoire entre 50 et 149 pour y.
      for (int i=0 ; i<3 ; i++){
	    int x = 150 + i*50;
	    int y = 50 + rand()%100;
	    sf::Sprite obstacle;
        obstacle.setTexture(this->image_obstacle);
        obstacle.setPosition(x, y);
	    this->obstacles.push_back(obstacle);
	  }
	}
	
	// Afficher le contenu de la scène
    void afficherScene(sf::RenderWindow& window) {
	  for(int i=0 ; i<obstacles.size() ; i++) window.draw(this->obstacles[i]);
    }
    
    // Vérifier si une position entre en collision avec des objets de la scène.
    bool verifierCollision(int position_x, int position_y) {
		
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
