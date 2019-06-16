#ifndef BULLET
#define BULLET

#include "common.h"
#include "GameObject.h"


struct BulletSettings : GameObjectSettings {
  /* data */
  sf::Color color_erased {200, 200, 200, 127};
  float size {7.0};
  float speed {100.0};
};


class Bullet : public GameObject {
private:
  BulletSettings &bullet_spec;
  sf::CircleShape bullet_shape;
  bool _isActive {true};

public:

  Bullet(BulletSettings &bspec, Point startPoint);
  void reset();
  void move(float x, float y);
  bool isOutOfBounds() const;
  Point getSFMLCoord() const;
  float getSpeed() const { return bullet_spec.speed; }
  float getSize() const { return bullet_spec.size; }
  void setActive() { _isActive = true; bullet_shape.setFillColor(bullet_spec.color); }
  void setInactive() { _isActive = false; bullet_shape.setFillColor(bullet_spec.color_erased); }
  bool isActive() { return _isActive; }
  void draw(sf::RenderWindow &window);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

Bullet::Bullet(BulletSettings &bspec, Point startPoint) : bullet_spec(bspec), GameObject() //, GameObject(bullet_shape)  {
{
  setup(bullet_shape, bullet_spec, startPoint);
  bullet_shape.setRadius(bspec.size);
  bullet_shape.setOrigin(getSize(), getSize());
}
void Bullet::reset() {
  Point p(bullet_spawn_x_range(e1), bullet_spawn_y_range(e1));
  setPosition(bullet_shape ,p);
  setActive();
}
void Bullet::move(float x, float y) {
  // std::cout << "Bullet (class) x,y: " << x << " , " <<  y << '\n';
  GameObject::move(bullet_shape, x,y, bullet_spec.speed);
}
bool Bullet::isOutOfBounds() const {
  Point p = getCoord();
  return (p.x < 0) || (p.x > gameWidth) || (p.y < 0) || (p.y > gameHeight);
}
// bool collision(PlayerCharcter &pl);
// ~Bullet ();
Point Bullet::getSFMLCoord() const {
  sf::Vector2f s = bullet_shape.getPosition();
  Point p(s.x, s.y);
  return p;
}

void Bullet::draw(sf::RenderWindow &window) {
  GameObject::draw(bullet_shape, window);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // You can draw other high-level objects
    target.draw(bullet_shape, states);
}


#endif /* end of include guard: BULLET */
