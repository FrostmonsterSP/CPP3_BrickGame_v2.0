//
// Created by frostmonster on 18.11.2024
//
#include "side_panel.h"

namespace s21 {
SidePanel::SidePanel() {
  score_label_.set_text("Score: 0");
  high_score_label_.set_text("High score: 0");
  level_label_.set_text("Level: 1");
  speed_label_.set_text("Speed: 1");
  set_margin(constants::kSpacing * 2);
}

SidePanel::~SidePanel() = default;
}  // namespace s21