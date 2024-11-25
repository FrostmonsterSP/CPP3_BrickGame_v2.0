#include "engine_wrapper.h"

#include "engine_defs.h"

namespace s21 {
namespace engine {
extern "C" {
#include "engine.h"
}
}  // namespace engine

EngineWrapper::EngineWrapper() { UpdateGameState(); }

void EngineWrapper::UserInput(engine::UserAction_t action) {
  userInput(action);
}

auto EngineWrapper::UpdateGameState() -> void {
  game_info_ = engine::updateCurrentState();
  if (game_info_ == nullptr) {
    throw std::runtime_error("UpdateGameState failed");
  }
}

auto EngineWrapper::GetFieldCell(int row, int col) -> int {
  return game_info_->field[row][col];
}

auto EngineWrapper::GetNextCell(int row, int col) -> int {
  return game_info_->next[row][col];
}

auto EngineWrapper::GetScore() -> int { return game_info_->score; }

auto EngineWrapper::GetHighScore() -> int { return game_info_->high_score; }

auto EngineWrapper::GetLevel() -> int { return game_info_->level; }

auto EngineWrapper::GetSpeed() -> int { return game_info_->speed; }

auto EngineWrapper::GetState() -> engine::GameState_t {
  return game_info_->state;
}

}  // namespace s21