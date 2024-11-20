//
// Created by frostmonster on 18.11.2024
//
#include "game_box.h"

#include <gtkmm/box.h>

namespace s21 {

GameBox::GameBox() {
  const int kFieldHeight = 20;
  const int kFieldWidth = 10;
  const float kRatio =
      static_cast<float>(kFieldWidth) / static_cast<float>(kFieldHeight);


  for (int row = 0; row < kFieldHeight; ++row) {
    for (int col = 0; col < kFieldWidth; ++col) {
      auto* cell = Gtk::make_managed<Gtk::Box>();
      cell->set_expand();
      field_grid_.attach(*cell, col, row, 1, 1);
    }  // for col
  }  // for row

  field_frame_.set_ratio(kRatio);
  field_frame_.set_child(field_grid_);

  append(field_frame_);
  append(side_panel_);
}  // GameBox::GameBox

GameBox::~GameBox() = default;

}  // namespace s21
