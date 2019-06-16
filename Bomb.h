#ifndef BOMB
#define BOMB

#include "Bullet.h"

struct BombSettings : GameObjectSettings {
  float speed {200};
  float grow_speed {100};
  float max_dist {200};
  float size {2.0};
  BombSettings() {
    color = sf::Color(0,0,0,0);
    outline_color = sf::Color(0, 150, 0);
    outline_thinkness = 5.0;
  }
};

class Bomb : public GameObject { // probably can be derived from Animation or some abstract class with "process" method
private:
  // Point coord;
  BombSettings bombset;
  sf::CircleShape bomb_shape;
  bool _isBlowing {false};
  bool _isFinished {false};
  Point stopPoint;

  void setSize(float size) { bomb_shape.setRadius(size); }
public:
  Bomb(BombSettings &bspec, Point startPoint);
  float getSize() const { return bomb_shape.getRadius(); }
  // ~Bomb ();
  void move(float x, float y);
  void detonate();
  void grow();
  bool isFinished() { return _isFinished; }
  bool collision(Bullet &bl);
  void draw(sf::RenderWindow &window);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

Bomb::Bomb(BombSettings &bspec, Point startPoint) : bombset(bspec), GameObject() //, GameObject(bullet_shape)  {
{
  setup(bomb_shape, bombset, startPoint);
  bomb_shape.setRadius(bombset.size);
  bomb_shape.setOrigin(bombset.size / 2.f, bombset.size / 2.f);
}

void Bomb::move(float x, float y) {
  GameObject::move(bomb_shape, x,y, bombset.speed);
}

void Bomb::detonate() {
  bombset.speed = 0;
  _isBlowing = true;
  stopPoint = getCenter();
}

void Bomb::grow() {
  if (_isBlowing) {
    // sf::Vector2f p = bomb_shape.getPosition();
    // std::cout << "Bomb x,y (before): " << p.x << " " << p.y << '\n';
    setSize(getSize() + getDeltaTime()* bombset.grow_speed);
    // setSize(75);
    // p = bomb_shape.getPosition();
    // std::cout << "Bomb x,y (after): " << p.x << " " << p.y << '\n';
    // bomb_shape.setOrigin(bombset.size / 2.f, bombset.size / 2.f);
    // bomb_shape.setOrigin(getSize() / 2.f, getSize() / 2.f);
    bomb_shape.setOrigin(getSize(), getSize());
    // setPosition(bomb_shape, Point(stopPoint.x,stopPoint.y));
  }
  if (getSize() > bombset.max_dist) {
    _isBlowing = false;
    _isFinished = true;
  }
}

bool Bomb::collision(Bullet &bl) {
  if (dist(getCenter(), bl.getCenter()) < (bl.getSize() + getSize())) {
    return true;
  }
}

void Bomb::draw(sf::RenderWindow &window) {
  GameObject::draw(bomb_shape, window);
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // You can draw other high-level objects
    target.draw(bomb_shape, states);
}

#endif /* end of include guard: BOMB */
