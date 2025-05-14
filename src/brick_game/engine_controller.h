#ifndef ENGINE_CONTROLLER_H
#define ENGINE_CONTROLLER_H

#include <string>
namespace s21 {
class EngineController {

 public:
  // Конструктор
  EngineController(const std::string&);

  // Запрещаем копирование
  EngineController(const EngineController&) = delete;
  auto operator=(const EngineController&) -> EngineController& = delete;

  // Запрещаем перемещение
  EngineController(EngineController&& other) = delete;
  auto operator=(EngineController&& other) = delete;

  // Деструктор
  ~EngineController();

  void UserAction(int);

 private:
  void* game_lib_ = nullptr;
  const void* game_info_ptr_ = nullptr;
  void (*updateCurrentState_fptr_)() = nullptr;
  void (*userInput_fptr_)(int) = nullptr;
  void GameLibLoader_(const std::string&);
};
}  // namespace s21

#endif  // ENGINE_CONTROLLER_H
