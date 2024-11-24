//
// Created by frostmonster on 18.11.2024
//
#include "game_box.h"

#include <gdkmm/frameclock.h>
#include <gtkmm/box.h>

#include "gui.h"

namespace s21 {

GameFrame::GameFrame() {
  g_debug("GameFrame constructor");
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
  add_tick_callback(sigc::mem_fun(*this, &GameFrame::BlinkingCellCallback_));

  set_ratio(kRatio);
  set_child(field_grid_);
  g_debug("GameFrame constructor end");
}  // GameBox::GameBox

GameFrame::~GameFrame() = default;

void GameFrame::SetUpdateFieldCallback(
    std::function<const tetris::GameInfo_t*()>& callback) {
  if (callback) {
    update_field_callback_ = callback;
  }
}  // GameBox::SetUpdateFieldCallback

auto GameFrame::BlinkingCellCallback_(
    const Glib::RefPtr<Gdk::FrameClock>& frame_clock) -> bool {
  gint64 now = frame_clock->get_frame_counter();
  if (now != 0) {
    const s21::tetris::GameInfo_t* info = update_field_callback_();
    g_debug("Current state: %d", info->state);
    for (int row = 0; row < kFieldHeight; ++row) {
      for (int col = 0; col < kFieldWidth; ++col) {
        auto* cell = field_grid_.get_child_at(col, row);
        guint cell_value = info->field[row][col];
        if (cell_value == 0) {
          // g_debug("Removing filled class");
          cell->remove_css_class("filled-1");
          cell->remove_css_class("filled-2");
          cell->remove_css_class("filled-3");
          cell->remove_css_class("filled-4");
          cell->remove_css_class("filled-5");
          cell->remove_css_class("filled-6");
          cell->remove_css_class("filled-7");
        } else {
          g_debug("Cell value: %d", cell_value);
          g_debug("Adding filled class");
          cell->add_css_class("filled-" + std::to_string(cell_value));
        }
      }  // for col
    }  // for row
    g_debug("Blinking cell callback");
  }
  return true;
}  // GameBox::BlinkingCellCallback

}  // namespace s21
