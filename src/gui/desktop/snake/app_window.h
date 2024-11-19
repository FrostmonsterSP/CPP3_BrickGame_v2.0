//
// Created by frostmonster on 17.11.2024
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

#include "game_box.h"

namespace s21 {

class AppWindow : public Gtk::ApplicationWindow {
 public:
  AppWindow();
  ~AppWindow() override;

 private:
  GameBox game_box_;
  Gtk::HeaderBar header_bar_;
  Gtk::MenuButton menu_button_;
};  // class MainWindow
};  // namespace s21

#endif  // MAINWINDOW_H
