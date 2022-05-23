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

static Renderer* renderer = nullptr;
static EntityManager manager{};
static Player* player = nullptr;

void CreateGeometryWarsEntities() {
  player = manager.CreateEntity<Player>(Vec2<int>{40, 40});
  manager.CreateEntity<BoundingBox>(Vec2<int>(0, 0), Vec2<int>(SCREEN_WIDTH, SCREEN_HEIGHT));

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
  if (is_key_pressed(VK_ESCAPE)) {
    schedule_quit_game();
  }

  player->Rotate(get_cursor_x(), get_cursor_y());
  if (is_mouse_button_pressed(0)) {
    player->SpawnBullet(&manager);
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
