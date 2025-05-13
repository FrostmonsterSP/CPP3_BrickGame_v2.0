#include "engine_controller.h"
#include "engine.h"

/**
 * @brief Создает новый EngineController и инициализирует состояние игры
 * 
 * Запускает входной сигнал старта игры и обновляет текущее состояние
 * игры при создании объекта.
 */
s21::EngineController::EngineController() {
  engine::userInput(engine::Start);
  m_gameInfo_ = engine::updateCurrentState();
}

s21::EngineController::EngineController(EngineController&& other) noexcept {
  m_gameInfo_ = other.m_gameInfo_;
  other.m_gameInfo_ = nullptr;
}

auto s21::EngineController::operator=(EngineController&& other) noexcept
    -> EngineController& {
  m_gameInfo_ = other.m_gameInfo_;
  other.m_gameInfo_ = nullptr;
  return *this;
}

s21::EngineController::~EngineController() {
  engine::userInput(engine::Terminate);
  m_gameInfo_ = engine::updateCurrentState();
  if (m_gameInfo_ != nullptr) {
    m_gameInfo_ = nullptr;
  }
}
