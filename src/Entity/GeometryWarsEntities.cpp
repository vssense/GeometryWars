#include "Entity/GeometryWarsEntities.hpp"
#include "Entity/EntityManager.hpp"
#include "Renderer/Renderer.hpp"
#include "GameTemplate/Engine.h"

#include <iostream>

const Color kBoundingBoxColor = kRed;
const Color kPlayerColor = kLightGreen;
const Color kEnemyColor = kRed;

const int kBulletRadius = 3;

Player::Player(Vec2<int> start_coords) : CircleShapedEntity(kPlayer, start_coords, 20), coords_(center_.x, center_.y), velocity_(340, 320) {}

void Player::OnUpdate(float dt) {
  coords_ += dt * velocity_;
  center_ = Vec2<int>(coords_.x, coords_.y);
}

void Player::Render(Renderer* renderer) {
  renderer->SetColor(kPlayerColor);
  renderer->FillCircle(center_.x, center_.y, radius_);
}

int& Player::GetHP() {
  return hp_;
}

Vec2<float>& Player::GetCoords() {
  return coords_;
}

Vec2<float>& Player::GetVelocity() {
  return velocity_;
}

Enemy::Enemy(Vec2<int> start_coords, Vec2<float> velocity)
  : CircleShapedEntity(kEnemy, start_coords, 30),
    coords_(center_.x, center_.y),
    velocity_(velocity) {}

void Enemy::OnUpdate(float dt) {
  coords_ += dt * velocity_;
  center_ = Vec2<int>(coords_.x, coords_.y);
}

void Enemy::Render(Renderer* renderer) {
  renderer->SetColor(kEnemyColor);
  renderer->FillCircle(center_.x, center_.y, radius_);
}

int& Enemy::GetHP() {
  return hp_;
}

Vec2<float>& Enemy::GetCoords() {
  return coords_;
}

Vec2<float>& Enemy::GetVelocity() {
  return velocity_;
}

BoundingBox::BoundingBox(Vec2<int> origin, Vec2<int> size)
    : Entity(kBoundingBox),
      origin_(origin),
      size_(size) {}

void BoundingBox::OnUpdate(float /*dt*/) {}

void BoundingBox::Render(Renderer* renderer) {
  renderer->SetColor(kBoundingBoxColor);
  renderer->DrawRect(origin_.x, origin_.y, size_.x - 1, size_.y - 1);
}

Vec2<int>& BoundingBox::GetOrigin() {
  return origin_;
}

Vec2<int>& BoundingBox::GetSize() {
  return size_;
}

Bullet::Bullet(int damage, Vec2<int> origin, Vec2<float> velocity)
  : CircleShapedEntity(kBullet, origin, kBulletRadius),
    damage_(damage),
    velocity_(velocity) {}

int& Bullet::GetDamage() {
  return damage_;
}

bool CollideCircleWithBox(CircleShapedEntity* entity, BoundingBox* box) {
  return CollideBoxWithCircle(box, entity);
}

bool CollideBoxWithCircle(BoundingBox* box, CircleShapedEntity* entity) {
  assert(box);
  assert(entity);

  Vec2<int> center = entity->GetCenter();
  int radius = entity->GetRadius();

  Vec2<int> origin = box->GetOrigin();
  Vec2<int> end = origin + box->GetSize();

  if (origin.x >= center.x - radius || center.x + radius >= end.x) {
    return true;
  }

  if (origin.y >= center.y - radius || center.y + radius >= end.y) {
    return true;
  }

  return false;
}

void ResposeEnemyWithBox(EntityManager* manager, Enemy* enemy, BoundingBox* box) {
  ResposeBoxWithEnemy(manager, box, enemy);
}

void ResposeBoxWithEnemy(EntityManager* /*manager*/, BoundingBox* box, Enemy* enemy) {
  assert(box);
  assert(enemy);

  Vec2<int> center = enemy->GetCenter();
  int radius = enemy->GetRadius();

  Vec2<int> origin = box->GetOrigin();
  Vec2<int> end = origin + box->GetSize();

  if (origin.x >= center.x - radius) {
    enemy->GetVelocity().x = std::abs(enemy->GetVelocity().x);
  } else if (center.x + radius >= end.x) {
    enemy->GetVelocity().x = -std::abs(enemy->GetVelocity().x);
  }

  if (origin.y >= center.y - radius) {
    enemy->GetVelocity().y = std::abs(enemy->GetVelocity().y);
  } else if (center.y + radius >= end.y) {
    enemy->GetVelocity().y = -std::abs(enemy->GetVelocity().y);
  }
}

void ResposePlayerWithBox(EntityManager* manager, Player* player, BoundingBox* box) {
  ResposeBoxWithPlayer(manager, box, player);
}

void ResposeBoxWithPlayer(EntityManager* /*manager*/, BoundingBox* box, Player* player) {
  assert(box);
  assert(player);

  Vec2<int> center = player->GetCenter();
  int radius = player->GetRadius();

  Vec2<int> origin = box->GetOrigin();
  Vec2<int> end = origin + box->GetSize();

  if (origin.x >= center.x - radius) {
    player->GetVelocity().x = std::abs(player->GetVelocity().x);;
  } else if (center.x + radius >= end.x) {
    player->GetVelocity().x = -std::abs(player->GetVelocity().x);
  }

  if (origin.y >= center.y - radius) {
    player->GetVelocity().y = std::abs(player->GetVelocity().y);
  } else if (center.y + radius >= end.y) {
    player->GetVelocity().y = -std::abs(player->GetVelocity().y);
  }
}

void ResponseEnemyWithEnemy(EntityManager* /*manager*/, Enemy* lhs, Enemy* rhs) {
  assert(lhs);
  assert(rhs);

  Vec2<int> centers_vec = lhs->GetCenter() - rhs->GetCenter();
  Vec2<float> centers_vecf = Vec2<float>(centers_vec.x, centers_vec.y);

  Vec2<float> v1 = lhs->GetVelocity();  
  Vec2<float> v2 = rhs->GetVelocity();  

  float len_squared = centers_vecf.GetLength();
  len_squared *= len_squared;
  centers_vecf= centers_vecf.Normalize();
  rhs->GetVelocity() -= 2 * (v2 * centers_vecf) * centers_vecf;
  lhs->GetVelocity() -= 2 * (v1 * centers_vecf) * centers_vecf;
}

void ResponsePlayerWithEnemy(EntityManager* manager, Player* player, Enemy* enemy) {
  ResponseEnemyWithPlayer(manager, enemy, player);
}

void ResponseEnemyWithPlayer(EntityManager* /*manager*/, Enemy* enemy, Player* player) {
  assert(enemy);
  assert(player);

  std::cout << "DIE\n";
}

void ResponseBulletWithEnemy(EntityManager* manager, Bullet* bullet, Enemy* enemy) {
  ResponseEnemyWithBullet(manager, enemy, bullet);
}

void ResponseEnemyWithBullet(EntityManager* manager, Enemy* enemy, Bullet* bullet) {
  assert(manager);
  assert(enemy);
  assert(bullet);

  enemy->GetHP() -= bullet->GetDamage();

  if (enemy->GetHP() <= 0) {
    manager->Delete(enemy);
  }
}

void ResponseBulletWithBox(EntityManager* manager, Bullet* bullet, BoundingBox* box) {
  ResponseBoxWithBullet(manager, box, bullet);
}

void ResponseBoxWithBullet(EntityManager* manager, BoundingBox* box, Bullet* bullet) {
  assert(manager);
  assert(bullet);
  assert(box);

  manager->Delete(bullet);
}

