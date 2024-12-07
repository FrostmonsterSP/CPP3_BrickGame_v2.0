#include "engine_wrapper.h"

namespace s21 {

namespace engine {
extern "C" {
#include "engine.h"
}
}  // namespace engine

EngineWrapper::EngineWrapper() : m_game_info_(engine::updateCurrentState()) {}

auto EngineWrapper::UpdateGameState() -> void {
  m_game_info_ = engine::updateCurrentState();
  if (m_game_info_ == nullptr) {
    throw std::runtime_error("UpdateGameState failed");
  }  // if (m_game_info_ == nullptr)
}  // EngineWrapper::UpdateGameState()

auto EngineWrapper::GetFieldCell(int row, int col) -> int {
  if (row < 0 || row >= FIELD_HEIGHT || col < 0 || col >= FIELD_WIDTH) {
    throw std::runtime_error("GetFieldCell: invalid coordinates");
    return 0;
  }
  return m_game_info_->field[row][col];
}  // EngineWrapper::GetFieldCell(int row, int col)

auto EngineWrapper::GetNextCell(int row, int col) -> int {
  if (row < 0 || row >= FIGURE_HEIGHT || col < 0 || col >= FIGURE_WIDTH) {
    throw std::runtime_error("GetNextCell: invalid coordinates");
    return 0;
  }
  int cell_val = 0;  // m_game_info_->next[row][col];
  if (m_game_info_->next != nullptr && !IsInit()) {
    cell_val = m_game_info_->next[row][col];
  }
  return cell_val;
}  // EngineWrapper::GetNextCell(int row, int col)

auto EngineWrapper::GetScore() -> int { return m_game_info_->score; }

auto EngineWrapper::GetHighScore() -> int { return m_game_info_->high_score; }

auto EngineWrapper::GetLevel() -> int { return m_game_info_->level; }

auto EngineWrapper::GetSpeed() -> int { return m_game_info_->speed; }

auto EngineWrapper::IsInit() -> bool {
  return m_game_info_->state == engine::GameState_t::StateInit;
}

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