//
// Created by frostmonster on 18.11.2024
//
#include "game_box.h"

#include <gtkmm/box.h>

namespace s21 {

GameBox::GameBox() {
  const int kFieldHeight = 20;
  const int kFieldWidth = 10;
  const int kStylePrioriy = GTK_STYLE_PROVIDER_PRIORITY_APPLICATION;

  SetStyle_();

  for (int row = 0; row < kFieldHeight; ++row) {
    for (int col = 0; col < kFieldWidth; ++col) {
      auto* cell = Gtk::make_managed<Gtk::Box>();
      cell->set_expand();
      field_grid_.attach(*cell, col, row, 1, 1);
    }  // for col
  }  // for row

  field_grid_.get_style_context()->add_provider(provider_, kStylePrioriy);

  field_grid_.get_style_context()->add_class("field-grid");

  set_orientation(Gtk::Orientation::HORIZONTAL);

  append(field_grid_);
  append(side_panel_);
}  // GameBox::GameBox

GameBox::~GameBox() = default;

void GameBox::SetStyle_() {
  if (provider_ != nullptr) {
    return;
  }

  const std::string kStyle =
      ".filled-cell {\
    border-radius: 10%;\
    margin: 1px;\
}\
.field-grid {\
    background-color: #282a36;\
    border: 1px solid;\
    border-radius: 8px;\
    padding: 5px;\
    margin: 10px;\
}";

  provider_ = Gtk::CssProvider::create();
  provider_->load_from_string(kStyle);
}

}  // namespace s21
