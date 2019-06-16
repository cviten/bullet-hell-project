#ifndef PLAYERCHARACTER
#define PLAYERCHARACTER

#include "Bullet.h"

struct PlayerSettings : GameObjectSettings {
  /* data */
  // sf::Color color {250, 250, 250};
  float speed {200.0};
  float size {15.0};
};

class PlayerCharcter : public GameObject {
private:
  /* data */
  // sf::Color color;
  // int speed;
  // float size;
  PlayerSettings player;
  // float x,y;
  sf::CircleShape player_shape;
  // bool bullet_collision {false};
  std::set<const Bullet*> bullet_collision;


public:
  PlayerCharcter (PlayerSettings &playerset, Point startPoint);
  // ~PlayerCharcter ();
  void move(float x, float y);
  float getSpeed() const { return player.speed; }
  float getSize() const { return player.size; }
  bool collision(const Bullet &bl);
  void draw(sf::RenderWindow &window);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

//Implemintaion

PlayerCharcter::PlayerCharcter (PlayerSettings &playerset, Point startPoint) : player(playerset), GameObject() {
    setup(player_shape, playerset, startPoint);
    player_shape.setRadius(player.size);
    player_shape.setOrigin(player.size, player.size);
}

bool PlayerCharcter::collision(const Bullet &bl) {
  auto i = bullet_collision.find(&bl);
  if ( (i == bullet_collision.end()) &&
        (dist(getCenter(), bl.getCenter()) < (bl.getSize() + getSize())) ) {
    const Bullet* b = &bl;
    bullet_collision.insert(b);
    return true;
  }
  if ( (i != bullet_collision.end())  &&
        ( (dist(getCenter(), bl.getCenter())) > (bl.getSize() + getSize())) ) {
    bullet_collision.erase(i);
  }
  return false;
}

void PlayerCharcter::move(float x, float y) {
  GameObject::move(player_shape, x,y, player.speed);
}

void PlayerCharcter::draw(sf::RenderWindow &window) {
  window.draw(player_shape);
}

void PlayerCharcter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // You can draw other high-level objects
    target.draw(player_shape, states);
}

#endif /* end of include guard: PLAYERCHARACTER */
