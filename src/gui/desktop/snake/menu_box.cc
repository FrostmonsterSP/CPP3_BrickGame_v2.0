//
// Created by frostmonster on 18.11.2024
//
#include "menu_box.h"

namespace s21 {

MenuBox::MenuBox() {
  start_button_.set_label("Start");
  level_button_.set_label("Level");
  speed_button_.set_label("Speed");
  exit_button_.set_label("Exit");

  start_button_.set_margin(5);

  level_button_.set_margin(5);
  speed_button_.set_margin(5);
  exit_button_.set_margin(5);

  set_hexpand(true);
  set_orientation(Gtk::Orientation::VERTICAL);
  set_valign(Gtk::Align::CENTER);
  set_halign(Gtk::Align::CENTER);
  append(start_button_);
  append(level_button_);
  append(speed_button_);
  append(exit_button_);
}  // MenuBox::MenuBox

MenuBox::~MenuBox() = default;

}  // namespace s21
