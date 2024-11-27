//
// Created by frostmonster on 18.11.2024
//
#include "side_panel.h"

namespace s21 {
SidePanel::SidePanel(EngineWrapper* engine)
    : m_next_frame_(4, 4), m_engine_(engine) {
  m_next_frame_.SetEngine(m_engine_);
  m_next_frame_.add_css_class("main-field");
  set_orientation(Gtk::Orientation::VERTICAL);

  auto score = m_engine_->GetScore();
  auto high_score = m_engine_->GetHighScore();
  auto level = m_engine_->GetLevel();
  auto speed = m_engine_->GetSpeed();

  m_score_label_.set_halign(Gtk::Align::CENTER);
  m_high_score_label_.set_halign(Gtk::Align::CENTER);
  m_level_label_.set_halign(Gtk::Align::CENTER);
  m_speed_label_.set_halign(Gtk::Align::CENTER);

  m_score_label_.set_text("Score: " + std::to_string(score));
  m_high_score_label_.set_text("High score: " + std::to_string(high_score));
  m_level_label_.set_text("Level: " + std::to_string(level));
  m_speed_label_.set_text("Speed: " + std::to_string(speed));

  m_next_frame_.set_vexpand(false);
  set_hexpand(false);
  set_margin(kSpacing * 2);

  append(m_next_frame_);

  append(m_score_label_);
  append(m_high_score_label_);
  append(m_level_label_);
  append(m_speed_label_);
}

SidePanel::~SidePanel() = default;
}  // namespace s21