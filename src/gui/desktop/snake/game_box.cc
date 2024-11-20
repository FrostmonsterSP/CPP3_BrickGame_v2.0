//
// Created by frostmonster on 18.11.2024
//
#include "game_box.h"

#include <gtkmm/box.h>

namespace s21 {

GameBox::GameBox() {
  const int kFieldHeight = 20;
  const int kFieldWidth = 10;
  const std::string kStyle =
      ".filled-cell {"
      "background-color: #0ff;"
      "border-radius: 10%;"
      "margin: 1px;"
      "}"
      ".field -grid {"
      "background: @shade_color;"
      "border: 1px solid;"
      "border-radius : 8px;"
      "padding: 5px;"
      "margin: 10px;"
      "};";

  auto provider = Gtk::CssProvider::create();
  provider->load_from_string(kStyle);

  for (int row = 0; row < kFieldHeight; ++row) {
    for (int col = 0; col < kFieldWidth; ++col) {
      auto* cell = Gtk::make_managed<Gtk::Box>();
      cell->set_expand();
      field_grid_.attach(*cell, col, row, 1, 1);
    }  // for col
  }  // for row

  field_grid_.get_style_context()->add_provider(
      provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  field_grid_.get_style_context()->add_class("field-grid");

  set_orientation(Gtk::Orientation::HORIZONTAL);

  append(field_grid_);
  append(side_panel_);
}  // GameBox::GameBox

GameBox::~GameBox() = default;

}  // namespace s21
