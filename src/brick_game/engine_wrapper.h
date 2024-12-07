#ifndef GUI_H
#define GUI_H

#include <glibmm.h>

namespace s21 {

namespace engine {
extern "C" {
#include "engine_defs.h"
}
}  // namespace engine

struct UserActions {
 public:
  UserActions() = default;
  ~UserActions() = default;
  void Terminate();
  void Start();
  void Pause();
  void Resume();
  void Left();
  void Right();
  void Up();
  void Down();
  void Action();
};  // struct UserActions

class EngineWrapper {
 public:
  EngineWrapper();
  ~EngineWrapper() = default;
  UserActions Action;
  void UpdateGameState();
  auto GetFieldCell(int, int) -> int;
  auto GetNextCell(int, int) -> int;
  auto GetScore() -> int;
  auto GetHighScore() -> int;
  auto GetLevel() -> int;
  auto GetSpeed() -> int;
  auto IsInit() -> bool;

 private:
  const engine::GameInfo_t *m_game_info_;
};

}  // namespace s21

#endif  // GUI_H
