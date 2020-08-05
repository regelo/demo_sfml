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
    ObjetAnime(int x, int y) {
	  // Position de départ
	  this->position_x = x;
	  this->position_y = y;
	  this->lutin.setPosition(this->position_x, this->position_y);
    }

	sf::Sprite& getLutin() {
	  this->lutin.setTexture(images.getImageCourante());
	  return this->lutin;
	}
	
	int getPositionX() {return this->position_x;}
};

#endif
