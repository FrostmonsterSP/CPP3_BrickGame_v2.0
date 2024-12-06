//
// Created by frostmonster on 18.11.2024
//
#include "side_panel.h"

#include "engine_defs.h"

namespace s21 {
SidePanel::SidePanel(EngineWrapper& engine)
    : m_engine_(engine),
      m_next_frame_({FIGURE_WIDTH, FIGURE_HEIGHT}, 1, engine) {
  m_next_frame_.add_css_class("main-field");
  set_orientation(Gtk::Orientation::VERTICAL);

  m_score_label_.set_halign(Gtk::Align::CENTER);
  m_high_score_label_.set_halign(Gtk::Align::CENTER);
  m_level_label_.set_halign(Gtk::Align::CENTER);
  m_speed_label_.set_halign(Gtk::Align::CENTER);

  m_next_frame_.set_vexpand(false);
  set_hexpand(false);
  set_margin(kSpacing * 2);

  DrawPanel();

  append(m_next_frame_);

  append(m_score_label_);
  append(m_high_score_label_);
  append(m_level_label_);
  append(m_speed_label_);
}

SidePanel::~SidePanel() = default;

void SidePanel::DrawPanel() {
  m_score_ = m_engine_.GetScore();
  m_high_score_ = m_engine_.GetHighScore();
  m_level_ = m_engine_.GetLevel();
  m_speed_ = m_engine_.GetSpeed();

  m_score_label_.set_text("Score: " + std::to_string(m_score_));
  m_high_score_label_.set_text("High score: " + std::to_string(m_high_score_));
  m_level_label_.set_text("Level: " + std::to_string(m_level_));
  m_speed_label_.set_text("Speed: " + std::to_string(m_speed_));
  m_next_frame_.DrawField();
}
}  // namespace s21