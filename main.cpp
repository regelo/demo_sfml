// Standard libraries
#include <iostream>
#include <thread>
#include <chrono>
// SFML libraries
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
// Our own classes
#include "animator.h"

// SFML (Simple and Fast Multimedia Library) est un cadriciel ("framework") léger pour produire des dessins graphiques (essentiellement en 2D) en C++. Voir : https://www.sfml-dev.org/

// Le cadriciel est plutôt de bas niveau : il n'offre pas de boutons, pas de champs où on peut entrer du texte, etc. Il faut créer nous-mêmes ces contrôles si on veut en avoir. Mais il fonctionne bien pour faire des petits jeux utilisant des lutins ("sprites").

int main()
{
  // Construction de la fenêtre.
  sf::RenderWindow window;
  window.create(sf::VideoMode(400, 200), "Démonstration de SFML", sf::Style::Titlebar | sf::Style::Close);

  sf::Color white_background(255, 255, 255, 255);
  window.clear(white_background); 

  // Création de l'objet contenant le texte.
  sf::Font font;
  font.loadFromFile("fonts/Roman SD.ttf");
  sf::Text text("SFML works!", font);
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);
  text.setPosition(0,0);

  // Création de l'objet contenant le "sprite"
  Animator player;
  player.addFrame("sprites/sprite_1.png");
  player.addFrame("sprites/sprite_2.png");
  player.addFrame("sprites/sprite_3.png");
  sf::Sprite sprite;
  sprite.setPosition(0,50);

  // Création du cercle.
  sf::CircleShape un_cercle(10);
  un_cercle.setFillColor(sf::Color(255, 0, 255));

  // Création du rectangle. 
  sf::RectangleShape carre(sf::Vector2<float>(20, 20));
  carre.setFillColor(sf::Color(255, 0, 0));
  int position_x = 0;
  int position_y = 0;
  carre.setPosition(position_x, position_y);

  window.setKeyRepeatEnabled(false);

  const int step = 5;

  // Boucle qui tourne tant que la fenête est ouverte. Cette boucle va vérifier si des événements ont eu lieu dans la fenêtre (ex.: clic de souris).
  while (window.isOpen())
  {
		// On regarde si un ou plusieurs événements sont survenus depuis la dernière fois qu'on a vérifié.
    sf::Event evenement;
    while (window.pollEvent(evenement))
    {
      switch(evenement.type) {
        case sf::Event::Closed:
        {
          window.close();
          break;
        }
        case sf::Event::MouseButtonPressed:
        { 
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // Affiche un message dans la console.
            sf::Vector2<int> position_dans_la_fenetre = sf::Mouse::getPosition(window);
            int x = position_dans_la_fenetre.x;
            int y = position_dans_la_fenetre.y; 
            std::cout << "Clic du bouton gauche au " << x << ", " << y << std::endl;
            // Déplace le cercle à la position.
            un_cercle.setPosition(x, y);
          }
          break;
        }
        case sf::Event::KeyPressed:
        {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            position_y -= step;
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            position_y += step;
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            position_x -= step;
            sprite.setTexture(player.getPreviousFrame());
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            position_x += step;
            sprite.setTexture(player.getNextFrame());
          }
          break;
        }
        default:
          break;
      };
    }

    // Déplacement du carré, tout en vérifiant qu'il ne sort pas du cadre.
    if (position_x < 0) position_x = 0;
    else if (position_x >= 400) position_x = 399;
    if (position_y < 0) position_y = 0;
    else if (position_y >= 200) position_y = 199;
    sprite.setPosition(position_x, position_y);

    // RAFRAICHISSEMENT DE LA SCÈNE
    // On efface le contenu de la scène.
    window.clear(white_background);
    // On ajoute tous les éléments de la scène.
    window.draw(text);
    window.draw(sprite);
    window.draw(carre);
    window.draw(un_cercle);
    // On affiche la scène dans la fenêtre.
    window.display();

    // Attends 0.05s
    std::this_thread::sleep_for (std::chrono::milliseconds(50));
  }

  return 0;
} 
