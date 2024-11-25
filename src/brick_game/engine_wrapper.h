#ifndef GUI_H
#define GUI_H

#include <glibmm.h>

namespace s21 {

namespace engine {
extern "C" {
#include "engine_defs.h"
}
}  // namespace engine

class EngineWrapper {
 public:
  EngineWrapper();
  ~EngineWrapper() = default;

  static auto GetFieldHeight() -> int { return FIELD_HEIGHT; }
  static auto GetFieldWidth() -> int { return FIELD_WIDTH; }
  void UserInput(engine::UserAction_t);
  void UpdateGameState();

  auto GetFieldCell(int, int) -> int;
  auto GetNextCell(int, int) -> int;
  auto GetScore() -> int;
  auto GetHighScore() -> int;
  auto GetLevel() -> int;
  auto GetSpeed() -> int;
  auto GetState() -> engine::GameState_t;

 private:
  const engine::GameInfo_t *game_info_;
};

}  // namespace s21

#endif  // GUI_H
