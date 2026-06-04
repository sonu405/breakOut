#include "game.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include <iostream>
#include <filesystem>

using namespace std;

SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

Game::~Game() {}

void Game::Init() {
  // loader shaders
  cout << "Loading shader next" << endl;
  ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");

  cout << "never loaded shader next" << endl;
  // configure shader
  glm::mat4 proj =
      glm::ortho(0.0f, static_cast<float>(Width), static_cast<float>(Height), 0.0f, -1.0f, 1.0f);

  ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
  // setting the projection uniform in the shader of the sprite
  ResourceManager::GetShader("sprite").SetMatrix4("projection", proj);

  // load textures
  cout << "before loading the texture" << endl;
//   cout << std::filesystem::current_path() << endl;

  ResourceManager::LoadTexture("assets/textures/retroText.jpg", true, "retroTex");
  cout << "after loading the texture" << endl;
}

void Game::Update(float dt) {}

void Game::ProcessInput(float dt) {}

void Game::Render() {
  // void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float
  // rotate, glm::vec3 color)
  Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f),
                       glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}