#include <SFML/Graphics.hpp>

#include <iostream>
#include <set>

// #include "Bullet.h"
#include "common.h"
#include "GameManager.h"


int main(int argc, char const *argv[]) {
  // std::srand(static_cast<unsigned int>(std::time(NULL)));
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SFML Bullet Hell");
  window.setFramerateLimit(60);

  GameSettings gameset;
  GameManager game(gameset);
  bool isPlaying = true;
  sf::Clock clock;
  while (window.isOpen())
  {
      // Handle events
      sf::Event event;
      while (window.pollEvent(event))
      {
          // Window closed or escape key pressed: exit
          if ((event.type == sf::Event::Closed) ||
             ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
          {
              window.close();
              break;
          }

          if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
          {
              // pc.move(1.f, 0.f, deltaTime);
              // std::cout << "Up is pressed" << '\n';
              game.launchBomb();
          }
          if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
          {
              // pc.move(1.f, 0.f, deltaTime);
              // std::cout << "Up is pressed" << '\n';
              game.launchBomb(event.mouseButton.x, event.mouseButton.y);
          }

      }

      if (isPlaying)
      {
          float deltaTime = clock.restart().asSeconds();
          setDeltaTime(deltaTime);

          // Move the player's paddle
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
              game.setPlayerDirection(GameManager::Left);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
              game.setPlayerDirection(GameManager::Right);
          }


          game.process();


      }

      // Clear the window
      // window.clear(sf::Color(50, 200, 50));
      window.clear();

      game.draw(window);
      // Display things on screen
      window.display();
  }

  return 0;
}
