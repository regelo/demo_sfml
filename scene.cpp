#include "scene.h"

// CONSTRUCTEUR

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

// MÉTHODES PUBLIQUES

void Scene::afficherScene(sf::RenderWindow& window, int joueur_x, int joueur_y) {

  // On parcours l'ensemble du vecteur pour afficher tous les obstacles.
  for (int i=0 ; i<this->obstacles.size() ; i++) window.draw(this->obstacles[i]);

  // On parcourt l'ensemble du vecteur pour afficher tous les nuages.
  for (int i=0 ; i<this->nuages.size() ; i++) this->nuages[i].afficherNuage(window, *this, joueur_x, joueur_y);

  // On parcours l'ensemble de la liste pour afficher toutes les étoiles qui existent encore.
  for (int i=0 ; i<5 ; i++) if (this->etoiles[i] != NULL) this->etoiles[i]->afficherEtoile(window);
}


bool Scene::verifierCollisionJoueur(int position_x, int position_y) {

  // Vérifier s'il y a une collision avec une étoile.
  for (int i=0 ; i<5 ; i++) {
    if (this->etoiles[i] != NULL) {
      sf::Rect<float> rectangle = this->etoiles[i]->obtenirLutin().getGlobalBounds();
      if (  (position_x >= rectangle.left-16) && 
            (position_x <= rectangle.left-16+rectangle.width) && 
            (position_y >= rectangle.top-16) && 
            (position_y <= rectangle.top-16+rectangle.height)  ) {
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
          (position_y <= rectangle.top-16+rectangle.height)  ) return true;
  }
  return false;
}


bool Scene::verifierCollisionNuage(int nuage_x, int nuage_y, int joueur_x, int joueur_y) {
  
  // Vérifier collision avec le joueur.
  if (  (joueur_x >= nuage_x-16) &&
        (joueur_x <= nuage_x+16) &&
        (joueur_y >= nuage_y-16) &&
        (joueur_y <= nuage_y+16)  ) {
    this->partie_terminee = true;
  }      
      
  // Vérifier collision avec les bordures du jeu.
  if (nuage_x >= 350) return true;
  if (nuage_x <= 10) return true;
  if (nuage_y >= 150) return true;
  if (nuage_y <= 10) return true;

  // Vérifier collision avec un obstacle.		
  for (int i=0 ; i<obstacles.size() ; i++) {
    sf::Rect<float> rectangle = this->obstacles[i].getGlobalBounds();

    if (  (nuage_x >= rectangle.left-16) && 
          (nuage_x <= rectangle.left-16+rectangle.width) && 
          (nuage_y >= rectangle.top-16) && 
          (nuage_y <= rectangle.top-16+rectangle.height)  ) return true;
  }

  return false;
}

// FONCTION PRIVÉE

void Scene::regenererEtoiles(int position_x) {
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


