#include "scene.h"

Scene::Scene() {
	  // Création des obstacles.
      this->image_obstacle.loadFromFile("sprites/roche.png");
      
      // Initialisation du générateur de nombres aléatoires avec le temps actuel.
      srand(time(NULL));
      
      // Création de trois obstacles à x=150, x=200, x=250 avec une valeur aléatoire entre 50 et 149 pour les y.
      for (int i=0 ; i<3 ; i++){
	    int x = 150 + i*50;
	    int y = 50 + rand()%100;
	    sf::Sprite obstacle;
        obstacle.setTexture(this->image_obstacle);
        obstacle.setPosition(x, y);
	    this->obstacles.push_back(obstacle);
	  }
	  
	  // Création de cinq étoiles à x=18, x=82, x=118, x=282 et x=314, avec une valeur aléatoire entre 50 et 149 pour les y.
	  Etoile* etoile1 = new Etoile(18, 50+rand()%100);
	  this->etoiles[0] = etoile1;
	  Etoile* etoile2 = new Etoile(82, 50+rand()%100);
	  this->etoiles[1] = etoile2;
	  Etoile* etoile3 = new Etoile(118, 50+rand()%100);
	  this->etoiles[2] = etoile3;
	  Etoile* etoile4 = new Etoile(282, 50+rand()%100);
	  this->etoiles[3] = etoile4;
	  Etoile* etoile5 = new Etoile(314, 50+rand()%100);
	  this->etoiles[4] = etoile5;

	  // Création des trois nuages.
	  Nuage nuage1(346, 50);
	  this->nuages.push_back(nuage1);
	  Nuage nuage2(346, 100);
	  this->nuages.push_back(nuage2);
	  Nuage nuage3(346, 150);
	  this->nuages.push_back(nuage3);
	}

void Scene::afficherScene(sf::RenderWindow& window, int joueur_x, int joueur_y) {
		
	  // On parcours l'ensemble du vecteur pour afficher tous les obstacles.
	  for (int i=0 ; i<this->obstacles.size() ; i++) window.draw(this->obstacles[i]);
	  
	  // On parcourt l'ensemble du vecteur pour afficher tous les nuages.
	  for (int i=0 ; i<this->nuages.size() ; i++) this->nuages[i].afficherNuage(window, *this, joueur_x, joueur_y);
	  
	  // On parcours l'ensemble de la liste pour afficher toutes les étoiles qui existent encore.
	  for (int i=0 ; i<5 ; i++) if (this->etoiles[i] != NULL) this->etoiles[i]->afficherEtoile(window);
    }
