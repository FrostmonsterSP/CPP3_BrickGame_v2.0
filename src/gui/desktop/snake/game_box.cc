//
// Created by frostmonster on 18.11.2024
//
#include "game_box.h"

#include <gdkmm/frameclock.h>
#include <gtkmm/box.h>

namespace s21 {

GameFrame::GameFrame() {
  g_debug("GameFrame constructor");
  engine_.UserInput(engine::UserAction_t::Start);
  for (int row = 0; row < kFieldHeight; ++row) {
    for (int col = 0; col < kFieldWidth; ++col) {
      auto* cell = Gtk::make_managed<Gtk::Box>();
      cell->set_expand();
      cell->add_css_class("cell");
      field_grid_.attach(*cell, col, row, 1, 1);
    }  // for col
  }  // for row

  field_grid_.add_css_class("main-field");

  g_debug("About to enter blinking loop");
  add_tick_callback(sigc::mem_fun(*this, &GameFrame::UpdateField_));

  set_ratio(kRatio);
  set_child(field_grid_);
  g_debug("GameFrame constructor end");
}  // GameBox::GameBox

GameFrame::~GameFrame() = default;

auto GameFrame::UpdateField_(const Glib::RefPtr<Gdk::FrameClock>& frame_clock)
    -> bool {
  try {
    engine_.UpdateGameState();
  } catch (const std::exception& e) {
    g_error("%s\n", e.what());
  }
  if (frame_clock && engine_.GetState() != engine::GameState_t::StateIdle &&
      engine_.GetState() != engine::GameState_t::State0) {
    for (int row = 0; row < kFieldHeight; ++row) {
      for (int col = 0; col < kFieldWidth; ++col) {
        auto cell_val = engine_.GetFieldCell(row, col);
        auto* cell = field_grid_.get_child_at(col, row);
        if (cell_val != 0) {
          cell->add_css_class("filled-" + std::to_string(cell_val));
        } else {
          cell->remove_css_class("filled-1");
          cell->remove_css_class("filled-2");
          cell->remove_css_class("filled-3");
          cell->remove_css_class("filled-4");
          cell->remove_css_class("filled-5");
          cell->remove_css_class("filled-6");
          cell->remove_css_class("filled-7");
        }  // if (cell_val != 0)
      }  // for col
    }  // for row
  }  // if
  return true;
}  // GameFrame::UpdateField_
}  // namespace s21
