#include "engine_controller.h"

#include <dlfcn.h>

#include <stdexcept>

#include "glib.h"
#include "include/engine.h"

s21::EngineController::EngineController(const std::string& game) {
  g_message("EngineController::EngineController");
  std::string lib_path = "lib" + game + ".so";
  GameLibLoader_(lib_path);
}

auto s21::EngineController::GetFieldCell(int x, int y) -> int {
  return game_info_ptr_->field[y][x];
}

auto s21::EngineController::GetNextCell(int x, int y) -> int {
  return game_info_ptr_->next[y][x];
}

s21::EngineController::~EngineController() {
  g_message("EngineController::~GameLibLoader_");
  GameLibUnloader_();
}

void s21::EngineController::GameLibLoader_(const std::string& lib_path) {
  g_message("EngineController::GameLibLoader_");
  game_lib_ = dlopen(lib_path.c_str(), RTLD_LAZY);
  if (game_lib_ == nullptr) {
    throw std::runtime_error(dlerror());
  }
  updateCurrentState_fptr_ =
      reinterpret_cast<void (*)()>(dlsym(game_lib_, "updateCurrentState"));
  if (updateCurrentState_fptr_ == nullptr) {
    throw std::runtime_error(dlerror());
  }
  userInput_fptr_ = reinterpret_cast<const GameInfo_t* (*)(int)>(
      dlsym(game_lib_, "userInput"));
  if (userInput_fptr_ == nullptr) {
    throw std::runtime_error(dlerror());
  }
}

void s21::EngineController::GameLibUnloader_() {
  g_message("EngineController::GameLibUnloader_");
  if (game_lib_ != nullptr) {
    dlclose(game_lib_);
    game_lib_ = nullptr;
  }
}
