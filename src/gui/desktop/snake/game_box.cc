//
// Created by frostmonster on 18.11.2024
//
#include "game_box.h"

#include <gtkmm/box.h>

#include "gdkmm/frameclock.h"
#include "glib.h"

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
  Gtk::Widget* blinking_cell = field_grid_.get_child_at(5, 5);
  blinking_cell->add_css_class("filled-1");

  g_debug("About to enter blinking loop");
  blinking_cell->add_tick_callback(
      sigc::mem_fun(*this, &GameFrame::BlinkingCellCallback_));

  set_ratio(kRatio);
  set_child(field_grid_);
  g_debug("GameFrame constructor end");
}  // GameBox::GameBox

GameFrame::~GameFrame() = default;

auto GameFrame::BlinkingCellCallback_(
    const Glib::RefPtr<Gdk::FrameClock>& frame_clock) -> bool {
  // const Glib::RefPtr<Gdk::FrameClock>& frame_clock) {
  Gtk::Widget* blinking_cell = field_grid_.get_child_at(5, 5);
  g_debug("Frame clock: %ld", frame_clock->get_frame_counter());
  if (blinking_cell->has_css_class("filled-1")) {
    blinking_cell->remove_css_class("filled-1");
    blinking_cell->add_css_class("filled-2");
  } else {
    blinking_cell->remove_css_class("filled-2");
    blinking_cell->add_css_class("filled-1");
  }
  g_debug("Blinking cell callback");
  return true;
}

}  // namespace s21
