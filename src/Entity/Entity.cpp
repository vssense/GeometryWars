#include "Entity/Entity.hpp"

Entity::Entity(EntityTypes type) : type_(type), is_deleted_(false) {}

EntityTypes Entity::GetType() {
  return type_;
}

bool Entity::IsDeleted() {
  return is_deleted_;
}

void Entity::Delete() {
  is_deleted_ = true;
}

CircleShapedEntity::CircleShapedEntity(EntityTypes type, Vec2<int> center, int radius)
    : Entity(type),
      center_(center),
      radius_(radius) {}

int& CircleShapedEntity::GetRadius() {
  return radius_;  
}

Vec2<int>& CircleShapedEntity::GetCenter() {
  return center_;  
}

bool CollideCircledEntities(CircleShapedEntity* lhs, CircleShapedEntity* rhs) {
  assert(lhs);
  assert(rhs);

  Vec2<int> centers_vec = rhs->GetCenter() - lhs->GetCenter();

  return (centers_vec.GetLength() - (lhs->GetRadius() + 0.0f + rhs->GetRadius())) < __FLT_EPSILON__;
}
