
#ifndef GAMEMANAGER
#define GAMEMANAGER

#include "common.h"
#include "Bullet.h"
#include "PlayerCharacter.h"
#include "Bomb.h"

#include <memory>
#include <deque>

struct GameSettings {
  int bulletNumber {30};
};

class GameManager {
public:
  enum PlayerMove {Left = -1, None = 0, Right = 1};
private:
  /* data */
  // Settings
  GameSettings gameset;
  BulletSettings bulletset;
  PlayerSettings playerset;
  BombSettings bombset;

  PlayerCharcter player;
  std::vector<Bullet> bullets;

  PlayerMove direction;

  sf::RectangleShape background;
  sf::Shader backshader;
  sf::Shader bulletshader;

  // std::unique_ptr<Bomb> bomb;
  std::deque<Bomb> bombs;

  void bulletsetup();
  void movement(PlayerMove dir);
  sf::Clock shclock;

public:
  GameManager (GameSettings &gamesets);
  // ~GameManager ();
  void process();
  void setPlayerDirection(PlayerMove dir);
  void launchBomb();
  void launchBomb(int x, int y);
  void collisionCheck();
  void bombProccess();
  void draw(sf::RenderWindow &window);
};

//----------------------------------

GameManager::GameManager (GameSettings &gamesets) : gameset(gamesets), player(playerset, Point(gameWidth / 2.f, gameHeight - 50)) {
  bulletsetup();
  if (!backshader.loadFromFile("res/background.frag", sf::Shader::Fragment))
  {
    std::cout << "Shader is not loaded" << '\n';
  }
  if (!bulletshader.loadFromFile("res/shader.vert", sf::Shader::Vertex))
  {
    std::cout << "Shader is not loaded" << '\n';
  }
  background.setSize({gameWidth, gameHeight});
  background.setFillColor(sf::Color::Green);
}


void GameManager::bulletsetup() {
  for (int i = 0; i < gameset.bulletNumber; i++) {
    float x = bullet_spawn_x_range(e1);
    float y = bullet_spawn_y_range(e1);
    // std::cout << "Init x,y :" << x << " , " << y << '\n';
    Bullet b(bulletset, Point(x,y) );
    bullets.push_back(b);
  }
}

void GameManager::bombProccess() {
  for(auto bomb = bombs.begin();bomb != bombs.end(); bomb++) {
    bomb->grow();
    // if (bomb->isFinished()) {
    //   bomb.reset();
    // }
  }
  if(!bombs.empty() && bombs.front().isFinished()) {
    bombs.pop_front();
  }
}

void GameManager::process() {
  movement(direction);
  collisionCheck();
  bombProccess();

  direction = None;
}

void GameManager::setPlayerDirection(PlayerMove dir) {
  direction = dir;
}

void GameManager::movement(PlayerMove dir) {
  player.move(float(dir), 0.f);

  for(auto bomb = bombs.begin(); bomb != bombs.end(); bomb++) {
    bomb->move(0.f, -1.f);
  }

  for (int i = 0; i < bullets.size(); i++) {
    bullets[i].move(0.f, 1.f);
  }
}

void GameManager::collisionCheck() {
  for (int i = 0; i < bullets.size(); i++) {
    if (bullets[i].isActive() && player.collision(bullets[i])) {
      std::cout << "Hit!" << '\n';
    }
    if (bullets[i].isOutOfBounds()) {
      bullets[i].reset();
    }
    for(auto bomb = bombs.begin(); bomb != bombs.end(); bomb++) {
      if (bomb->collision(bullets[i])) {
        bullets[i].setInactive();
      }
    }
  }
}

void GameManager::launchBomb() {

  Bomb bomb(bombset, Point(gameWidth/2,gameHeight/2));
  bombs.push_back(bomb);
  bombs.back().detonate();
}

void GameManager::launchBomb(int x, int y) {
  Bomb bomb(bombset, Point(x,y));
  bombs.push_back(bomb);
  bombs.back().detonate();
}

void GameManager::draw(sf::RenderWindow &window) {
  // backshader.setUniform("time",);
  backshader.setParameter("time", shclock.getElapsedTime().asSeconds());
  bulletshader.setParameter("time", shclock.getElapsedTime().asSeconds());
  window.draw(background, &backshader);
  // player.draw(window, &bulletshader);
  // window.draw(player, &bulletshader);
  window.draw(player);
  for (int i = 0; i < bullets.size(); i++) {
    // bullets[i].draw(window, &bulletshader);
    bullets[i].draw(window);
  }
  for(auto bomb = bombs.begin(); bomb != bombs.end(); bomb++) {
    bomb->draw(window);
  }
}



#endif /* end of include guard: GAMEMANAGER */


// foreach (Shader shader in globalShaders)
// {
//     // draw "back" into "front"
//     front.Clear();
//     front.Draw(new Sprite(back.Image), shader);
//     front.Display();
//
//     // swap front and back buffers
//     RenderImage temp = front;
//     front = back;
//     back = temp;
// }
