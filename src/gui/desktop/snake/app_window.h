//
// Created by frostmonster on 17.11.2024
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

#include "game_box.h"

namespace s21 {

namespace constants {
constexpr int WIN_HEIGHT = 600;
constexpr int WIN_WIDTH = 400;
}  // namespace constants

class AppWindow : public Gtk::ApplicationWindow {
 public:
  AppWindow();
  ~AppWindow() override;

 private:
  GameBox gameBox;
  Gtk::HeaderBar headerBar;
  Gtk::MenuButton menuButton;
};  // class MainWindow
};  // namespace s21

#endif  // MAINWINDOW_H
