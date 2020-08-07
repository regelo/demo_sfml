#ifndef __OBJETANIME_H__
#define __OBJETANIME_H__

#include "animateur.h"

class ObjetAnime {
  protected:
    Animateur images;
    sf::Sprite lutin;
    int position_x;
    int position_y;
  public:
    ObjetAnime(int x, int y);

    int getPositionX();
    int getPositionY();

    // Cette méthode n'est pas un vrai "getter" car elle modifie le contenu de l'attribut "lutin".
    sf::Sprite& obtenirLutin();
};

#endif
