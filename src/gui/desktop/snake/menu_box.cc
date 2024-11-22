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

  start_button_.set_margin(kMarigin);
  level_button_.set_margin(kMarigin);
  speed_button_.set_margin(kMarigin);
  exit_button_.set_margin(kMarigin);

  start_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &MenuBox::StartButtonClicked_));

  set_hexpand(true);
  set_orientation(Gtk::Orientation::VERTICAL);
  set_valign(Gtk::Align::CENTER);
  set_halign(Gtk::Align::CENTER);
  add_css_class("main-field");
  append(start_button_);
  append(level_button_);
  append(speed_button_);
  append(exit_button_);
}  // MenuBox::MenuBox

MenuBox::~MenuBox() = default;

void MenuBox::SetStartGameCallback(
    const std::function<void()>& start_callback) {
  if (start_callback) {
    start_callback_ = start_callback;
  }
}

void MenuBox::StartButtonClicked_() {
  if (start_callback_) {
    start_callback_();
  }
}

}  // namespace s21
