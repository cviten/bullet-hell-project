#ifndef COMMON
#define COMMON

#include <random>
#include <iostream>

const int gameWidth = 800;
const int gameHeight = 600;

std::random_device r;
std::default_random_engine e1(r());
std::uniform_real_distribution<float> bullet_spawn_x_range(30.f, (gameWidth * 1.0) - 30.f);
std::uniform_real_distribution<float> bullet_spawn_y_range(10.f, 70.f);

namespace {
  float deltaTime {0};
}

void setDeltaTime(float dt) {
  deltaTime = dt;
}

float getDeltaTime() {
  return deltaTime;
}

#endif /* end of include guard: COMMON */
