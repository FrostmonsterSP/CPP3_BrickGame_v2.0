#ifndef ENGINE_CONTROLLER_H
#define ENGINE_CONTROLLER_H

#include <string>

#include "include/engine.h"
namespace s21 {
class EngineController {
 public:
  // Конструктор
  EngineController(const std::string&);

  // Запрещаем копирование
  EngineController(const EngineController&) = delete;
  auto operator=(const EngineController&) -> EngineController& = delete;

  // Перемещение
  EngineController(EngineController&&) = default;
  auto operator=(EngineController&&) -> EngineController& = default;

  auto GetFieldCell(int, int) -> int;
  auto GetNextCell(int, int) -> int;
  auto GetScore() -> int;
  auto GetHighScore() -> int;
  auto GetLevel() -> int;
  auto GetSpeed() -> int;
  auto GetState() -> int;

  // Деструктор
  ~EngineController();

 protected:
 private:
  void* game_lib_ = nullptr;
  const GameInfo_t* game_info_ptr_ = nullptr;
  void (*updateCurrentState_fptr_)() = nullptr;
  const GameInfo_t* (*userInput_fptr_)(int) = nullptr;
  void GameLibLoader_(const std::string&);
  void GameLibUnloader_();
};
}  // namespace s21

#endif  // ENGINE_CONTROLLER_H
