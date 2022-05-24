#ifndef _GEOMETRY_WARS_ENTITIES_HPP_INCLUDED
#define _GEOMETRY_WARS_ENTITIES_HPP_INCLUDED

#include "Entity/Entity.hpp"

const int kMaxHP = 100;

class EntityManager;

class Player : public CircleShapedEntity {
 public:
  Player(Vec2<int> start_coords);
  virtual ~Player() {}

  virtual void OnUpdate(float dt) override;
  virtual void Render(Renderer* renderer) override;

  void Rotate(int to_x, int to_y);
  void SpawnBullet(EntityManager* manager);

  Vec2<float>& GetCoords();
  Vec2<float>& GetView();
  Vec2<float>& GetVelocity();

 private:
  Vec2<float> view_;
  Vec2<float> coords_;
  Vec2<float> velocity_;
};

class Enemy : public CircleShapedEntity {
 public:
  Enemy(Vec2<int> start_coords, Vec2<float> velocity);
  virtual ~Enemy() {}

  virtual void OnUpdate(float dt) override;
  virtual void Render(Renderer* renderer) override;

  int& GetHP();

  Vec2<float>& GetCoords();

  Vec2<float>& GetVelocity();

 private:
  int hp_{kMaxHP};

  Vec2<float> coords_;
  Vec2<float> velocity_;
};

class BoundingBox : public Entity {
 public:
  BoundingBox(Vec2<int> origin, Vec2<int> size);

  virtual void OnUpdate(float dt) override;
  virtual void Render(Renderer* renderer) override;

  Vec2<int>& GetOrigin();
  Vec2<int>& GetSize();

 private:
  Vec2<int> origin_;
  Vec2<int> size_;
};

class Bullet : public CircleShapedEntity {
 public:
  Bullet(int damage, Vec2<int> origin, Vec2<float> velocity);

  virtual void OnUpdate(float dt) override;
  virtual void Render(Renderer* renderer) override;

  int& GetDamage();

 private:
  int damage_;
  Vec2<float> velocity_;
};

bool CollideBoxWithCircle(BoundingBox* box, CircleShapedEntity* entity);
bool CollideCircleWithBox(CircleShapedEntity* entity, BoundingBox* box);

void ResponseEnemyWithBox(EntityManager* manager, Enemy* enemy, BoundingBox* box);
void ResponseBoxWithEnemy(EntityManager* manager, BoundingBox* box, Enemy* enemy);

void ResposePlayerWithBox(EntityManager* manager, Player* player, BoundingBox* box);
void ResposeBoxWithPlayer(EntityManager* manager, BoundingBox* box, Player* player);

void ResponseEnemyWithEnemy(EntityManager* manager, Enemy* lhs, Enemy* rhs);

void ResponsePlayerWithEnemy(EntityManager* manager, Player* player, Enemy* enemy);
void ResponseEnemyWithPlayer(EntityManager* manager, Enemy* enemy, Player* player);

void ResponseBulletWithEnemy(EntityManager* manager, Bullet* bullet, Enemy* enemy);
void ResponseEnemyWithBullet(EntityManager* manager, Enemy* enemy, Bullet* bullet);

void ResponseBulletWithBox(EntityManager* manager, Bullet* bullet, BoundingBox* Box);
void ResponseBoxWithBullet(EntityManager* manager, BoundingBox* box, Bullet* bullet);

#endif // _GEOMETRY_WARS_ENTITIES_HPP_INCLUDED
