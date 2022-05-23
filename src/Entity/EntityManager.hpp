#ifndef _ENTITY_MANAGER_HPP_INCLUDED
#define _ENTITY_MANAGER_HPP_INCLUDED

#include "Renderer/Renderer.hpp"
#include "Entity/Entity.hpp"

#include <list>

class EntityManager;

typedef bool (*DetectCollisionFunc)(Entity*, Entity*);
typedef void (*ResponseCollisionFunc)(EntityManager*, Entity*, Entity*);

class EntityManager {
 public:
  ~EntityManager();

  template <class EntityT, typename... Args>
  EntityT* CreateEntity(Args&&... args) {
    EntityT* entity = new EntityT(std::forward<Args>(args)...);

    entities_.push_back(entity);
    return entity;
  }

  void CollideEntities();

  void OnUpdate(float dt);
  void Render(Renderer* renderer);  
  void Delete(Entity* entity);

 private:
  void RemoveDeletedEntities();

 private:
  std::list<Entity*> entities_;

  static const DetectCollisionFunc DetectCollision[kNumEntityTypes][kNumEntityTypes];

  static const ResponseCollisionFunc ResponseCollision[kNumEntityTypes][kNumEntityTypes];
};

#endif // _ENTITY_MANAGER_HPP_INCLUDED