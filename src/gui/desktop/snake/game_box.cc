//
// Created by frostmonster on 18.11.2024
//
#include "game_box.h"

#include <gtkmm/box.h>

namespace s21 {

GameFrame::GameFrame() {
  const int kFieldHeight = 20;
  const int kFieldWidth = 10;
  const float kRatio = static_cast<float>(kFieldWidth) / (kFieldHeight);
  field_grid_.add_css_class("field-grid");

  for (int row = 0; row < kFieldHeight; ++row) {
    for (int col = 0; col < kFieldWidth; ++col) {
      auto* cell = Gtk::make_managed<Gtk::Box>();
      cell->set_expand();
      field_grid_.attach(*cell, col, row, 1, 1);
    }  // for col
  }  // for row

  set_ratio(kRatio);
  set_child(field_grid_);
}  // GameBox::GameBox

GameFrame::~GameFrame() = default;

}  // namespace s21
