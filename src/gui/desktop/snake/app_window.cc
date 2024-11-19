//
// Created by frostmonster on 17.11.2024
//
#include "app_window.h"

#include "constants.h"

namespace s21 {

using namespace constants;

AppWindow::AppWindow() {
  set_title("Brick Game v2.0");
  set_size_request(constants::kWinWidth, constants::kWinHeight);

  // Настройка панели заголовка
  header_bar_.set_visible(true);
  header_bar_.set_can_focus(false);

  menu_button_.set_visible(true);
  menu_button_.set_can_focus(true);
  menu_button_.set_focus_on_click(false);
  menu_button_.set_receives_default(true);
  menu_button_.set_direction(Gtk::ArrowType::NONE);

  header_bar_.pack_end(menu_button_);

  main_frame_.set_ratio(kRatio);
  main_frame_.set_child(game_box_);

  set_titlebar(header_bar_);
  set_child(main_frame_);
}  // constructor

AppWindow::~AppWindow() = default;

}  // namespace s21
