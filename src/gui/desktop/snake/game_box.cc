//
// Created by frostmonster on 18.11.2024
//
#include "game_box.h"

#include "gtkmm/box.h"
#include "gtkmm/label.h"

namespace s21 {

GameBox::GameBox() {
  Glib::ustring style = "gui/desktop/snake/game_field.css";
  auto provider = Gtk::CssProvider::create();
  provider->load_from_path(style);
  auto provider_priority = GTK_STYLE_PROVIDER_PRIORITY_USER;

  for (int row = 0; row < constants::kFieldHeight; ++row) {
    for (int col = 0; col < constants::kFieldWidth; ++col) {
      auto* cell = Gtk::make_managed<Gtk::Box>();

      cell->get_style_context()->add_provider(provider, provider_priority);
      cell->get_style_context()->add_class("empty-cell");
      // cell->set_sensitive(false);
      cell->set_expand();
      field_grid_.attach(*cell, col, row, 1, 1);
    }  // for col
  }  // for row

  field_grid_.set_column_homogeneous(false);
  field_grid_.set_row_homogeneous(false);

  side_panel_.set_spacing(constants::kSpacing);
  Gtk::Label score_label("Score: 0");
  side_panel_.append(score_label);

  field_frame_.set_ratio(constants::kRatio);
  field_frame_.set_vexpand(false);
  field_frame_.set_margin(constants::kSpacing);
  field_frame_.set_child(field_grid_);

  set_orientation(Gtk::Orientation::HORIZONTAL);

  append(field_frame_);
  append(side_panel_);
}  // Constructor

GameBox::~GameBox() = default;

}  // namespace s21
