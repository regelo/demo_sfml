#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__

#include <vector>
#include <string>

class Animator {
  private:
    std::vector<sf::Texture> frames;
    int current_frame = 0;
  public:
    void addFrame(std::string nom_fichier) {
	  sf::Texture frame;
	  frame.loadFromFile(nom_fichier);
	  
	  this->frames.push_back(frame);
	}
	
    sf::Texture& getPreviousFrame() {
      if (current_frame == 0) current_frame = this->frames.size()-1;
      else current_frame--;
      
      return this->frames[current_frame];
	}
		
    sf::Texture& getCurrentFrame() {
      return this->frames[current_frame];
    }
    
	sf::Texture& getNextFrame() {
      if (current_frame == this->frames.size()-1) current_frame = 0;
      else current_frame++;
      
      return this->frames[current_frame];
	}
};

#endif
