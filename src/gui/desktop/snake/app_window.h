//
// Created by frostmonster on 17.11.2024
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/stack.h>

#include "game_box.h"
#include "menu_box.h"
#include "side_panel.h"

namespace s21 {

class AppWindow : public Gtk::ApplicationWindow {
 public:
  AppWindow();
  ~AppWindow() override;

 private:
  Gtk::AspectFrame main_frame_;
  Gtk::Box main_box_;
  Gtk::Stack main_stack_;
  Gtk::HeaderBar header_bar_;
  Gtk::MenuButton menu_button_;
  SidePanel side_panel_;
  GameFrame game_box_;
  MenuBox menu_box_;
};  // class MainWindow
};  // namespace s21

#endif  // MAINWINDOW_H
