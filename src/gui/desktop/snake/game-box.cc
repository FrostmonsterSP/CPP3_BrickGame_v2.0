//
// Created by frostmonster on 18.11.2024
//
#include "game-box.h"

#include "gtkmm/box.h"
#include "gtkmm/label.h"

namespace s21 {

GameBox::GameBox() {
  Glib::ustring style = "gui/desktop/snake/GameField.css";
  auto provider = Gtk::CssProvider::create();
  provider->load_from_path(style);
  auto provider_priority = GTK_STYLE_PROVIDER_PRIORITY_USER;

  for (int row = 0; row < constants::FIELD_HEIGHT; ++row) {
    for (int col = 0; col < constants::FIELD_WIDTH; ++col) {
      auto* cell = Gtk::make_managed<Gtk::Box>();

      cell->get_style_context()->add_provider(provider, provider_priority);
      cell->get_style_context()->add_class("empty-cell");
      // cell->set_sensitive(false);
      cell->set_expand();
      fieldGrid.attach(*cell, col, row, 1, 1);
    }  // for col
  }  // for row

  fieldGrid.set_column_homogeneous(false);
  fieldGrid.set_row_homogeneous(false);

  sidePanel.set_spacing(constants::spacing);
  Gtk::Label scoreLabel("Score: 0");
  sidePanel.append(scoreLabel);

  fieldFrame.set_ratio(0.5);
  fieldFrame.set_vexpand(false);
  fieldFrame.set_margin(constants::spacing);
  fieldFrame.set_child(fieldGrid);

  set_orientation(Gtk::Orientation::HORIZONTAL);

  append(fieldFrame);
  append(sidePanel);
}  // Constructor

GameBox::~GameBox() = default;

}  // namespace s21
