#ifndef __SCENE_H__
#define __SCENE_H__

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

// Cette "forward declaration" de la classe est nécessaire à cause de dépendances cycliques entre "nuage.h" et "scene.h".
class Scene;

#include "etoile.h"
#include "nuage.h"

class Scene {
  private:
    // Conteneur des obstacles et des nuages. Les obstacles et les nuages ne changent pas durant la vie du programme (pas d'ajouts, pas de retraits), donc un std::vector fait l'affaire.
	std::vector<sf::Sprite> obstacles;
	std::vector<Nuage> nuages;
	
	// Conteneur des étoiles. Il y a un maximum de cinq étoiles. Je veux pouvoir effacer des étoiles au milieu et les ajouter par la suite, donc je prends un tableau statique de pointeurs. Il y aura des cases qui contiennent des étoiles, et des cases à NULL durant le déroulement du jeu.
    Etoile* etoiles[5];
	
	// La texture ne peut pas être une variable locale, car lorsque la variable est détruite, l'affichage du lutin ne fonctionne pas correctement. 
	sf::Texture image_obstacle;
	
	// Points accumulés par le joueur.
	int points = 0;
	
	// Indicateur si la partie est terminée ou non.
	bool partie_terminee = false;
	
  public:
    Scene();
	
	int getPoints() {return this->points;}
	
	// Afficher le contenu de la scène
    void afficherScene(sf::RenderWindow& window, int joueur_x, int joueur_y);
    
    // Vérifier si une position entre en collision avec des objets de la scène.
    bool verifierCollision(int position_x, int position_y) {
		
	  // Vérifier s'il y a une collision avec une étoile.
	  for (int i=0 ; i<5 ; i++) {
	    if (this->etoiles[i] != NULL) {
			sf::Rect<float> rectangle = this->etoiles[i]->getLutin().getGlobalBounds();
			if (  (position_x >= rectangle.left-16) && 
			      (position_x <= rectangle.left-16+rectangle.width) && 
			      (position_y >= rectangle.top-16) && 
			      (position_y <= rectangle.top-16+rectangle.height)
			   ) {
		      // Notre joueur a touché une étoile ! Le joueur gagne un point.
		      this->points++;
		      // On efface l'étoile qui a été touchée.
		      delete this->etoiles[i];
		      this->etoiles[i] = NULL;
			}
		}
	  }
	
	  // S'il ne reste que deux étoiles, on va en ajouter deux autres loin du joueur.
	  int compte = 0;
	  for(int i=0 ; i<5 ; i++) if (this->etoiles[i] != NULL) compte++;
	  if (compte <=2) regenererEtoiles(position_x);
	
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

    bool getPartieTerminee() { return this->partie_terminee; }

    bool verifierCollisionNuage(int nuage_x, int nuage_y, int joueur_x, int joueur_y) {
	  
	  // Vérifier collision avec le joueur.
	  if (  (joueur_x >= nuage_x-16) &&
	        (joueur_x <= nuage_x+16) &&
	        (joueur_y >= nuage_y-16) &&
	        (joueur_y <= nuage_y+16)
	      ) {
	           this->partie_terminee = true;
	           std::cout << "Partie terminée !" << std::endl;
       }

      // Vérifier collision avec un obstacle.
      
      // Vérifier collision avec les bordures du jeu.
	  if (nuage_x >= 350) return true;
	  if (nuage_x <= 10) return true;
	  if (nuage_y >= 150) return true;
	  if (nuage_y <= 10) return true;
		
	  return false;
	}

  private:
    void regenererEtoiles(int position_x) {
	  // Si on est ici, c'est qu'il ne reste que deux étoiles.
	  // Initialement, les étoiles ont comme valeur X les valeurs 18, 82, 118, 282 et 314.
	  // Il faut générer deux nouvelles étoiles (et monter le total à quatre étoiles) qui ont les positions X les plus éloignées du joueur.
	  
	  // Première étape, trouver les étoiles manquantes.
      std::vector<int> etoiles_manquantes;
      if (this->etoiles[0] == NULL) etoiles_manquantes.push_back(18);
      if (this->etoiles[1] == NULL) etoiles_manquantes.push_back(82);
      if (this->etoiles[2] == NULL) etoiles_manquantes.push_back(118);
      if (this->etoiles[3] == NULL) etoiles_manquantes.push_back(282);
      if (this->etoiles[4] == NULL) etoiles_manquantes.push_back(314);
     
     // Deuxième étape, déterminer la distance entre les étoiles manquantes et la position du joueur. On les mets tout de suite dans un conteneur en ordre.
     std::map<int, int> distances;
     for(int i=0 ; i<etoiles_manquantes.size() ; i++) {
       int distance = abs(etoiles_manquantes[i] - position_x);
       distances[distance] = etoiles_manquantes[i];
     }
     
     // Troisième étape, on ajoute les deux étoiles manquantes les plus éloignées.
     std::map<int, int>::iterator it = distances.begin();
     
     // On ne veut pas le X de la distance la plus faible, donc on passe immédiatement à la suivante.
     it++;
     
     // On crée une étoile à la position X qu'on a.
     int x1 = it->second;
     int y1 = 50+rand()%100;
     Etoile* e1 = new Etoile(x1, y1);
     if (x1 == 18) this->etoiles[0] = e1;
     else if (x1 == 82) this->etoiles[1] = e1;
     else if (x1 == 118) this->etoiles[2] = e1;
     else if (x1 == 282) this->etoiles[3] = e1;
     else if (x1 == 314) this->etoiles[4] = e1;     
     
     // On passe à la position suivante et on crée une autre étoile.
     it++;
     int x2 = it->second;
     int y2 = 50+rand()%100;
     Etoile* e2 = new Etoile(x2, y2);
     if (x2 == 18) this->etoiles[0] = e2;
     else if (x2 == 82) this->etoiles[1] = e2;
     else if (x2 == 118) this->etoiles[2] = e2;
     else if (x2 == 282) this->etoiles[3] = e2;
     else if (x2 == 314) this->etoiles[4] = e2; 
    }
};

#endif
