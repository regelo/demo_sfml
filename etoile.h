#ifndef __ETOILE_H__
#define __ETOILE_H__

#include "animateur.h"
#include "objetanime.h"

class Etoile : public ObjetAnime {
  public:
    Etoile(int x, int y);

    void afficherEtoile(sf::RenderWindow& fenetre);
};

#endif
