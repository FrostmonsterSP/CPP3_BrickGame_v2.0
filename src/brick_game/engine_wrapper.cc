#include "engine_wrapper.h"

namespace s21 {

namespace engine {
extern "C" {
#include "engine.h"
}
}  // namespace engine

EngineWrapper::EngineWrapper()
    : kFieldHeight(FIELD_HEIGHT),
      kFieldWidth(FIELD_WIDTH),
      kNextHeight(FIGURE_HEIGHT),
      kNextWidth(FIGURE_WIDTH),
      m_game_info_(engine::updateCurrentState()) {}

auto EngineWrapper::UpdateGameState() -> void {
  m_game_info_ = engine::updateCurrentState();
  if (m_game_info_ == nullptr) {
    throw std::runtime_error("UpdateGameState failed");
  }
}

auto EngineWrapper::GetFieldCell(int row, int col) -> int {
  return m_game_info_->field[row][col];
}  // EngineWrapper::GetFieldCell(int row, int col)

auto EngineWrapper::GetNextCell(int row, int col) -> int {
  return m_game_info_->next[row][col];
}  // EngineWrapper::GetNextCell(int row, int col)

auto EngineWrapper::GetScore() -> int { return m_game_info_->score; }

auto EngineWrapper::GetHighScore() -> int { return m_game_info_->high_score; }

auto EngineWrapper::GetLevel() -> int { return m_game_info_->level; }

auto EngineWrapper::GetSpeed() -> int { return m_game_info_->speed; }

auto EngineWrapper::GetState() -> int { return m_game_info_->state; }

auto EngineWrapper::IsIdle() -> bool {
  return m_game_info_->state == engine::GameState_t::StateIdle;
}  // EngineWrapper::IsIdle()

void UserActions::Terminate() {
  engine::userInput(engine::UserAction_t::Terminate);
}  // UserActions::Terminate()

void UserActions::Start() { engine::userInput(engine::UserAction_t::Start); }

void UserActions::Pause() { engine::userInput(engine::UserAction_t::Pause); }

void UserActions::Resume() { engine::userInput(engine::UserAction_t::Start); }

void UserActions::Left() { engine::userInput(engine::UserAction_t::Left); }

void UserActions::Right() { engine::userInput(engine::UserAction_t::Right); }

void UserActions::Up() { engine::userInput(engine::UserAction_t::Up); }

void UserActions::Down() { engine::userInput(engine::UserAction_t::Down); }

void UserActions::Action() { engine::userInput(engine::UserAction_t::Action); }

}  // namespace s21