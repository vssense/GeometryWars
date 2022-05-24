#include "GameTemplate/Engine.h"
#include "Renderer/Renderer.hpp"
#include "Entity/EntityManager.hpp"
#include "Entity/GeometryWarsEntities.hpp"

#include <cstdlib>
#include <cstdio>
#include <memory.h>

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, VK_RETURN)
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  schedule_quit_game() - quit game after act()

const float kWeaponCD = 0.1;
const float kSpawnDelay = 3;

static Renderer* renderer = nullptr;
static EntityManager manager{};
static Player* player = nullptr;
static float time_from_last_shot = 0;
static float time_from_last_spawn = 0;

void CreateGeometryWarsEntities() {
  manager.CreateEntity<BoundingBox>(Vec2<int>(0, 0), Vec2<int>(SCREEN_WIDTH, SCREEN_HEIGHT));
  player = manager.CreateEntity<Player>(Vec2<int>{600, 600});

  manager.CreateEntity<Enemy>(Vec2<int>{700, 70}, Vec2<float>(-121, -59));
  manager.CreateEntity<Enemy>(Vec2<int>{70, 70}, Vec2<float>(121, -59));
  manager.CreateEntity<Enemy>(Vec2<int>{250, 110}, Vec2<float>(231, -62));
  manager.CreateEntity<Enemy>(Vec2<int>{440, 140}, Vec2<float>(251, -77));
}

void initialize() {
  renderer = new Renderer(buffer, SCREEN_HEIGHT, SCREEN_WIDTH);

  CreateGeometryWarsEntities();
}

void act(float dt) {
  time_from_last_shot += dt;
  time_from_last_spawn += dt;

  if (is_key_pressed(VK_ESCAPE)) {
    schedule_quit_game();
  }

  player->Rotate(get_cursor_x(), get_cursor_y());
  if (is_mouse_button_pressed(0)) {
    if (time_from_last_shot > kWeaponCD) {
      player->SpawnBullet(&manager);
      time_from_last_shot = 0;
    }
  }

  if (time_from_last_spawn > kSpawnDelay) {
    manager.CreateEntity<Enemy>(Vec2<int>{std::rand() % 700, std::rand() % 700},
                                Vec2<float>(std::rand() % 400 - 200, std::rand() % 400 - 200));
    time_from_last_spawn = 0;
  }

  player->GetVelocity() = {0, 0};
  if (is_key_pressed(VK_DOWN)) {
    player->GetVelocity() += {0, 500};
  }
  
  if (is_key_pressed(VK_UP)) {
    player->GetVelocity() += {0, -500};
  }
  
  if (is_key_pressed(VK_LEFT)) {
    player->GetVelocity() += {-500, 0};
  }

  if (is_key_pressed(VK_RIGHT)) {
    player->GetVelocity() += {500, 0};
  }

  manager.CollideEntities();
  manager.OnUpdate(dt);
}

void draw() {
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

  renderer->SetColor(kWhite);
  renderer->FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  manager.Render(renderer);
}

void finalize() {
  delete renderer;
}
