//
// Created by frostmonster on 17.11.2024
//
#include "MainWindow.h"

namespace s21 {

namespace constants {
constexpr int winHeight = 600;
constexpr int winWidth = 600;
}  // namespace constants

MainWindow::MainWindow() {
  set_title("Brick Game v2.0");
  set_default_size(constants::winWidth, constants::winHeight);
  set_resizable(false);

  headerBar.set_visible(true);
  headerBar.set_can_focus(false);

  menuButton.set_visible(true);
  menuButton.set_can_focus(true);
  menuButton.set_focus_on_click(false);
  menuButton.set_receives_default(true);
  menuButton.set_direction(Gtk::ArrowType::NONE);

  headerBar.pack_end(menuButton);
  set_titlebar(headerBar);
}  // MainWindow::MainWindow

MainWindow::~MainWindow() = default;
}  // namespace s21
