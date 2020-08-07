#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include "animateur.h"
#include "objetanime.h"
#include "scene.h"

class Joueur : public ObjetAnime {
  private:
    // Nombre de pixel que le joueur peut se déplacer à chaque tick.
    int vitesse;
  
    // Pointeur vers la scène dans laquelle évolue le joueur.
    Scene* la_scene;
    
  public:
    Joueur(Scene* une_scene, int x, int y);

    // Méthodes qui essaient de déplacer le joueur. S'il y a une collision avec un obstacle, le déplacement n'a pas lieu.
    void deplacerGauche();
    void deplacerDroite();
    void deplacerHaut();
    void deplacerBas();
};

#endif
