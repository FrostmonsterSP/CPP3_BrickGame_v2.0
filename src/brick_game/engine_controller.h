#ifndef ENGINE_CONTROLLER_H
#define ENGINE_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
namespace engine {
#endif
#include <engine.h>
#ifdef __cplusplus
}  // namespace engine_
}
#endif

namespace s21 {
class EngineController {
 public:
  // Конструктор
  explicit EngineController();

  // Запрещаем копирование
  EngineController(const EngineController&) = delete;
  auto operator=(const EngineController&) -> EngineController& = delete;

  // Разрешаем перемещение
  [[nodiscard]] EngineController(EngineController&& other) noexcept;
  [[nodiscard]] auto operator=(EngineController&& other) noexcept
      -> EngineController&;

  // Деструктор
  ~EngineController();

  void UserAction(int);

  // Проверка на инициализацию
  //   [[nodiscard]] auto IsInitialized() const -> bool { return m_gameInfo_ != nullptr; }

 private:
  const engine::GameInfo_t* m_gameInfo_;
};
}  // namespace s21

#endif  // ENGINE_CONTROLLER_H
