#ifndef _ENTITY_HPP_INCLUDED
#define _ENTITY_HPP_INCLUDED

#include "Math/Vector2.hpp"

class Renderer;

enum EntityTypes {
  kPlayer,
  kEnemy,
  kBullet,
  kBoundingBox,

  kNumEntityTypes
};

class Entity {
 protected:
  explicit Entity(EntityTypes type);

 public:
  virtual void OnUpdate(float dt) = 0;
  virtual void Render(Renderer* renderer) = 0;
  virtual ~Entity() {}

  EntityTypes GetType();
  bool IsDeleted();
  void Delete();

 private:
  EntityTypes type_;
  bool is_deleted_;
};

class CircleShapedEntity : public Entity {
 public:
  CircleShapedEntity(EntityTypes type, Vec2<int> center, int radius);

  int& GetRadius();
  Vec2<int>& GetCenter();

 protected:
  Vec2<int> center_{0, 0};
  int radius_{0};
};

bool CollideCircledEntities(CircleShapedEntity* lhs, CircleShapedEntity* rhs);

#endif // _ENTITY_HPP_INCLUDED
