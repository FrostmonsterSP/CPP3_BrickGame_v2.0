//
// Created by frostmonster on 18.11.2024
//
#include "menu_box.h"

namespace s21 {

MenuBox::MenuBox()
    : start_button_("Start"),
      level_label_("Level"),
      speed_label_("Speed"),
      level_up_button_("+"),
      level_down_button_("-"),
      speed_up_button_("+"),
      speed_down_button_("-"),
      exit_button_("Exit") {
  set_hexpand(true);
  set_orientation(Gtk::Orientation::VERTICAL);
  set_valign(Gtk::Align::CENTER);
  set_halign(Gtk::Align::CENTER);

  config_grid_.set_margin(kMargin);
  config_grid_.set_column_spacing(kMargin);
  config_grid_.set_row_spacing(kMargin);
  start_button_.set_margin(kMargin);
  exit_button_.set_margin(kMargin);

  config_grid_.attach(level_down_button_, 0, 0);
  config_grid_.attach(level_label_, 1, 0);
  config_grid_.attach(level_up_button_, 2, 0);
  config_grid_.attach(speed_down_button_, 0, 1);
  config_grid_.attach(speed_label_, 1, 1);
  config_grid_.attach(speed_up_button_, 2, 1);

  append(start_button_);
  append(config_grid_);
  append(exit_button_);
}  // MenuBox::MenuBox

void MenuBox::SetStartGameCallback(
    const std::function<void()>& start_callback) {
  start_button_.signal_clicked().connect(start_callback);
}  // MenuBox::SetStartGameCallback

void MenuBox::SetExitCallback(const std::function<void()>& exit_callback) {
  exit_button_.signal_clicked().connect(exit_callback);
}  // MenuBox::SetExitCallback

void MenuBox::SetLevelCallbacks(const std::function<void()>& up_callback,
                                const std::function<void()>& down_callback) {
  if (up_callback != nullptr) {
    level_up_button_.signal_clicked().connect(up_callback);
  }  // if (up_callback != nullptr)
  if (down_callback != nullptr) {
    level_down_button_.signal_clicked().connect(down_callback);
  }  // if (down_callback != nullptr)
}  // MenuBox::SetLevelCallbacks

void MenuBox::SetSpeedCallbacks(const std::function<void()>& up_callback,
                                const std::function<void()>& down_callback) {
  if (up_callback != nullptr) {
    speed_up_button_.signal_clicked().connect(up_callback);
  }  // if (up_callback != nullptr)
  if (down_callback != nullptr) {
    speed_down_button_.signal_clicked().connect(down_callback);
  }  // if (down_callback != nullptr)
}  // MenuBox::SetSpeedCallbacks
}  // namespace s21
