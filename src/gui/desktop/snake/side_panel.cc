//
// Created by frostmonster on 18.11.2024
//
#include "side_panel.h"

namespace s21 {
SidePanel::SidePanel() {
  score_label_.set_text("Score: " + std::to_string(score_));
  high_score_label_.set_text("High score: " + std::to_string(high_score_));
  level_label_.set_text("Level: " + std::to_string(level_));
  speed_label_.set_text("Speed: " + std::to_string(speed_));

  set_orientation(Gtk::Orientation::VERTICAL);
  set_valign(Gtk::Align::CENTER);
  set_hexpand(false);
  set_margin(kSpacing * 2);

  append(score_label_);
  append(high_score_label_);
  append(level_label_);
  append(speed_label_);
}

SidePanel::~SidePanel() = default;
}  // namespace s21