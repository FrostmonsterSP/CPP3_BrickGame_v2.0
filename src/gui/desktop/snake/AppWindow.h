//
// Created by frostmonster on 17.11.2024
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

#include "GameBox.h"

namespace s21 {
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
