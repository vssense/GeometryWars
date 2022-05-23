#include "Entity/EntityManager.hpp"
#include "Entity/GeometryWarsEntities.hpp"

const DetectCollisionFunc EntityManager::DetectCollision[kNumEntityTypes][kNumEntityTypes] = {
  {(DetectCollisionFunc)CollideCircledEntities, (DetectCollisionFunc)CollideCircledEntities,
   (DetectCollisionFunc)CollideCircledEntities, (DetectCollisionFunc)CollideCircleWithBox},
  {(DetectCollisionFunc)CollideCircledEntities, (DetectCollisionFunc)CollideCircledEntities,
   (DetectCollisionFunc)CollideCircledEntities, (DetectCollisionFunc)CollideCircleWithBox},
  {(DetectCollisionFunc)CollideCircledEntities, (DetectCollisionFunc)CollideCircledEntities,
   (DetectCollisionFunc)CollideCircledEntities, (DetectCollisionFunc)nullptr},
  {(DetectCollisionFunc)CollideBoxWithCircle, (DetectCollisionFunc)CollideBoxWithCircle,
   (DetectCollisionFunc)CollideBoxWithCircle, (DetectCollisionFunc)nullptr}
};

const ResponseCollisionFunc EntityManager::ResponseCollision[kNumEntityTypes][kNumEntityTypes] = {
  {(ResponseCollisionFunc)nullptr, (ResponseCollisionFunc)ResponsePlayerWithEnemy,
   (ResponseCollisionFunc)nullptr, (ResponseCollisionFunc)ResposePlayerWithBox},
  {(ResponseCollisionFunc)ResponseEnemyWithPlayer, (ResponseCollisionFunc)ResponseEnemyWithEnemy,
   (ResponseCollisionFunc)ResponseEnemyWithBullet, (ResponseCollisionFunc)ResposeEnemyWithBox},
  {(ResponseCollisionFunc)nullptr, (ResponseCollisionFunc)ResponseBulletWithEnemy,
   (ResponseCollisionFunc)nullptr, (ResponseCollisionFunc)ResponseBulletWithBox},
  {(ResponseCollisionFunc)ResposeBoxWithPlayer, (ResponseCollisionFunc)ResposeBoxWithEnemy,
   (ResponseCollisionFunc)ResponseBoxWithBullet, (ResponseCollisionFunc)nullptr}
};

EntityManager::~EntityManager() {
  for (auto entity : entities_) {
    delete entity;
  }
}

void EntityManager::CollideEntities() {
  for (auto first = entities_.begin(); first != entities_.end(); ++first) {
    auto second = first;
    ++second;
    for (; second != entities_.end(); ++second) {
      Entity* ent1 = *first;
      Entity* ent2 = *second;

      auto detect = DetectCollision[ent1->GetType()][ent2->GetType()];
      if (detect != nullptr && detect(ent1, ent2)) {
        auto response = ResponseCollision[ent1->GetType()][ent2->GetType()];
        if (response != nullptr) {
          response(this, ent1, ent2);
        }

        break;
      }
    }
  }

  RemoveDeletedEntities();
}

void EntityManager::OnUpdate(float dt) {
  for (auto entity : entities_) {
    entity->OnUpdate(dt);
  }
}

void EntityManager::Render(Renderer* renderer) {
  for (auto entity : entities_) {
    entity->Render(renderer);
  }
}

void EntityManager::Delete(Entity* entity) {
  assert(entity);


  for (auto it = entities_.begin(); it != entities_.end(); ++it) {
    if (*it == entity) {
      entities_.erase(it);
      break;
    }
  }

  delete entity;
}

void EntityManager::RemoveDeletedEntities() {
  for (auto it = entities_.begin(); it != entities_.end();) {
    if ((*it)->IsDeleted()) {
      auto it_copy = it;
      ++it;
      delete *it_copy;
      entities_.erase(it_copy);
    } else {
      ++it;
    }
  }
}
