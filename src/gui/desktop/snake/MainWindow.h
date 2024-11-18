//
// Created by frostmonster on 17.11.2024
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

namespace s21 {

namespace constants {
constexpr int winHeight = 600;
constexpr int winWidth = 600;
constexpr int cellSize = 20;
constexpr int spacing = 10;
constexpr int fieldHeight = 20;
constexpr int fieldWidth = 10;
}  // namespace constants

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
