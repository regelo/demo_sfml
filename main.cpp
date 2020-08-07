// Librairies standard
#include <iostream>
#include <thread>
#include <chrono>
// Librairies de SFML
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
// Nos propres classes
#include "joueur.h"
#include "scene.h"

// SFML (Simple and Fast Multimedia Library) est un cadriciel ("framework") léger pour produire des dessins graphiques (essentiellement en 2D) en C++. Voir : https://www.sfml-dev.org/

// Le cadriciel est plutôt de bas niveau : il n'offre pas de boutons, pas de champs où on peut entrer du texte, etc. Il faut créer nous-mêmes ces contrôles si on veut en avoir. Mais il fonctionne bien pour faire des petits jeux utilisant des lutins ("sprites").

int main()
{
  // Construction de la fenêtre.
  sf::RenderWindow window;
  window.create(sf::VideoMode(400, 200), "Demo SFML", sf::Style::Titlebar | sf::Style::Close);
  sf::Color white_background(255, 255, 255, 255);
  window.clear(white_background); 

  // Création de l'objet contenant le texte.
  sf::Font font;
  font.loadFromFile("fonts/Roman SD.ttf");
  sf::Text text("Utilisez les touches W-A-S-D pour jouer", font);
  text.setCharacterSize(12);
  text.setFillColor(sf::Color::Black);
  text.setStyle(sf::Text::Bold);
  text.setPosition(0,0);

  // Création de la scène avec laquelle le joueur peut interagir.
  Scene scene;

  // Création de l'objet joueur gérant les lutins et les déplacements.
  Joueur joueur1(&scene, 50, 50);

  // Booléens qui déterminent si les quatre touches utilisées pour le jeu ont été enfoncées.
  bool w_pressed = false;
  bool a_pressed = false;
  bool s_pressed = false;
  bool d_pressed = false;

  // Boucle qui tourne tant que la fenête est ouverte. Cette boucle va vérifier si des événements ont eu lieu dans la fenêtre (ex.: clic de souris).
  while (window.isOpen())
  {
    // On ne recherche les événements (entrée du clavier dans ce cas) que si la partie est encore en cours.
    if (!scene.getPartieTerminee()) {

      // BOUCLE D'ÉVÉNEMENTS QUAND LE JEU EST EN COURS. On regarde si un ou plusieurs événements sont survenus depuis la dernière fois qu'on a vérifié.
      sf::Event evenement;
      while (window.pollEvent(evenement))
      {
        switch(evenement.type) {
          case sf::Event::Closed:
          {
            window.close();
            break;
          }
          case sf::Event::KeyPressed:
          {
            if (evenement.key.code == sf::Keyboard::W) w_pressed = true;
            else if (evenement.key.code == sf::Keyboard::A) a_pressed = true;
            else if (evenement.key.code == sf::Keyboard::S) s_pressed = true;
            else if (evenement.key.code == sf::Keyboard::D) d_pressed = true;
            break;
          }
          case sf::Event::KeyReleased:
          {
            if (evenement.key.code == sf::Keyboard::W) w_pressed = false;
            else if (evenement.key.code == sf::Keyboard::A) a_pressed = false;
            else if (evenement.key.code == sf::Keyboard::S) s_pressed = false;
            else if (evenement.key.code == sf::Keyboard::D) d_pressed = false;		  
            break;
          }
          default:
            // Nécessaire pour éviter un "warning". Il y a beaucoup d'événements qu'on ne veut pas gérer !
            break;
        };
      }

      // Déplacement du joueur si la touche appropriée a été enfoncée.
      if(w_pressed) joueur1.deplacerHaut();
      if(a_pressed) joueur1.deplacerGauche();
      if(s_pressed) joueur1.deplacerBas();
      if(d_pressed) joueur1.deplacerDroite();

      // Affichage des points du joueur.
      if (scene.getPoints() > 0) {
        std::string message = "Points : " + std::to_string(scene.getPoints()); 
        text.setString(message);
      }

      // RAFRAICHISSEMENT DE LA SCÈNE
      // 1. On efface le contenu de la scène.
      window.clear(white_background);
      
      // 2. On ajoute tous les éléments de la scène.
      window.draw(text);
      window.draw(joueur1.obtenirLutin());

      int joueur_x = joueur1.getPositionX();
      int joueur_y = joueur1.getPositionY();
      scene.afficherScene(window, joueur_x, joueur_y);

      // 3. On affiche la scène dans la fenêtre.
      window.display();

      // On attends 0.05s. Ce délai est nécessaire sinon la boucle va trop vite. Cela définit donc un "tick" de 0.05s. Notez que si l'exécution du code d'une itération de la boucle prend trop de temps, ce "tick" peut être plus grand, ce qui va causer une forme de "lag".
      std::this_thread::sleep_for (std::chrono::milliseconds(50));
    }
    else
    {
      // La partie est terminée parce que le joueur a touché un nuage.
      // Affichage du message "game over".
      sf::Text game_over("GAME OVER", font);
      game_over.setCharacterSize(24);
      game_over.setFillColor(sf::Color::Black);
      game_over.setStyle(sf::Text::Bold);
      game_over.setPosition(50,50);
      window.draw(game_over);
      window.display();
      
      // On utilise une autre boucle d'événements lorsque le jeu est terminé.
      sf::Event evenement_fin_de_partie;
      while (window.pollEvent(evenement_fin_de_partie))
      {
        switch(evenement_fin_de_partie.type) {
          case sf::Event::Closed:
          {
            window.close();
            break;
          }
        };
      }	  
    } //  If: si la partie n'est pas terminée.
  } // While: tant que la fenêtre est ouverte.

  return 0;
} 


