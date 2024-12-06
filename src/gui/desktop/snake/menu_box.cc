//
// Created by frostmonster on 18.11.2024
//
#include "menu_box.h"

namespace s21 {

MenuBox::MenuBox()
    : m_start_button_("Start"),
      m_level_button_("Level"),
      m_speed_button_("Speed"),
      m_exit_button_("Exit") {
  m_start_button_.set_margin(kMarigin);
  m_level_button_.set_margin(kMarigin);
  m_speed_button_.set_margin(kMarigin);
  m_exit_button_.set_margin(kMarigin);

  set_hexpand(true);
  set_orientation(Gtk::Orientation::VERTICAL);
  set_valign(Gtk::Align::CENTER);
  set_halign(Gtk::Align::CENTER);

  append(m_start_button_);
  append(m_level_button_);
  append(m_speed_button_);
  append(m_exit_button_);
}  // MenuBox::MenuBox

void MenuBox::SetStartGameCallback(
    const std::function<void()>& start_callback) {
  // m_start_callback_ = start_callback;
  m_start_button_.signal_clicked().connect(start_callback);
}

void MenuBox::SetExitCallback(const std::function<void()>& exit_callback) {
  m_exit_button_.signal_clicked().connect(exit_callback);
}

}  // namespace s21
