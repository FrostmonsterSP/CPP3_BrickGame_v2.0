//
// Created by frostmonster on 17.11.2024
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

namespace s21 {

class MainWindow : public Gtk::ApplicationWindow {
 public:
  MainWindow();
  ~MainWindow() override;

 private:
  Gtk::HeaderBar headerBar;
  Gtk::MenuButton menuButton;
};  // class MainWindow
};  // namespace s21

#endif  // MAINWINDOW_H
