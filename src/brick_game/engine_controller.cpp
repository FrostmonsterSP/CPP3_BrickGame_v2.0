#include "engine_controller.h"

#include <dlfcn.h>
#include <stdexcept>

s21::EngineController::EngineController(const std::string& game) {
  std::string lib_path = "lib" + game + ".so";
  GameLibLoader_(lib_path);
}

void s21::EngineController::GameLibLoader_(const std::string& lib_path) {
  game_lib_ = dlopen(lib_path.c_str(), RTLD_LAZY);
  if (game_lib_ == nullptr) {
    throw std::runtime_error(dlerror());
  }
  updateCurrentState_fptr_ =
      reinterpret_cast<void (*)()>(dlsym(game_lib_, "updateCurrentState"));
  if (updateCurrentState_fptr_ == nullptr) {
    throw std::runtime_error(dlerror());
  }
  userInput_fptr_ =
      reinterpret_cast<void (*)(int)>(dlsym(game_lib_, "userInput"));
  if (userInput_fptr_ == nullptr) {
    throw std::runtime_error(dlerror());
  }
}
