#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <SFML/Graphics.hpp>
#include <iostream>

struct Point {
  float x {0};
  float y {0};
  Point() {}
  Point(float xx, float yy) : x(xx), y(yy) {}
};

float dist(Point p1, Point p2) {
  return sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y));
}

struct GameObjectSettings {
  // float speed {100.0};
  // float size {10.0};
  sf::Color color {250, 250, 250};
  sf::Color outline_color {250, 30, 30};
  // sf::Color color_erased {30, 30, 30};
  float outline_thinkness {2.0};
};

class GameObject : public sf::Drawable {
private:
  Point center;
  // float size;


protected:
  void move(sf::Shape &shape, float x, float y, float speed) {
    float dx = x * speed * getDeltaTime();
    float dy = y * speed * getDeltaTime();
    center.x += dx;
    center.y += dy;
    shape.move(dx, dy);
  }

  void setSize(sf::Shape &shape, float s) { shape.setScale(s,s); }
  // virtual void setSize(float s) = 0;
  void setRelSize(sf::Shape &shape, float s) { shape.scale(s,s); }
  void setPosition(sf::Shape &shape, Point p) {
    center = p;
    shape.setPosition(p.x, p.y);
  }
  // float getSize() const { return size; }
  Point getPoint() const { return center; }


  void setup(sf::Shape &shape, const GameObjectSettings &gm, Point startPoint) {
    shape.setFillColor(gm.color);
    shape.setOutlineThickness(gm.outline_thinkness);
    shape.setOutlineColor(gm.outline_color);

    center = startPoint;
    shape.setPosition(startPoint.x, startPoint.y);
  }

  // virtual float getSize() const = 0;

public:
  Point getCenter() const { return center; }
  virtual ~GameObject() {}
  // GameObject (float size, sf::Color color, Point startPoint) {
  // GameObject (const GameObjectSettings &gm, sf::Shape &sp, Point startPoint) : shape(sp) {
  // GameObject (sf::Shape &sp) : shape(sp) {
  //
  //   // Find out source of the problem
  //
  //   // shape.setRadius(gm.size);
  //   // shape.setOrigin(gm.size / 2.f, gm.size / 2.f);
  //   // std::cout << "gm: " << gm.outline_thinkness << '\n';
  //   // GameObjectSettings gs2 = gm;
  //   // shape.setFillColor(gs2.color);
  //   // shape.setOutlineThickness(gs2.outline_thinkness);
  //   // shape.setOutlineColor(gs2.outline_color);
  //   //---
  //   // shape.setFillColor(sf::Color(250, 250, 250));
  //   // shape.setOutlineThickness(0.5);
  //   // shape.setOutlineColor(sf::Color(250, 250, 250));
  //   //---
  //   // shape2.setFillColor(sf::Color(250, 250, 250));
  //   // shape2.setOutlineThickness(0.5);
  //   // shape2.setOutlineColor(sf::Color(250, 250, 250));
  //   // shape.setPosition(startPoint.x, startPoint.y);
  // }

  Point getCoord() const { return center; }
  void draw(sf::Shape &shape, sf::RenderWindow &window) const { window.draw(shape); }
  // void move()
  // ~GameObject ();
};


#endif /* end of include guard: GAMEOBJECT */
