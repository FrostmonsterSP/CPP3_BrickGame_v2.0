//
// Created by frostmonster on 17.11.2024
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/enums.h>
#include <gtkmm/stack.h>

#include "game_box.h"
#include "gui.h"
#include "menu_box.h"
#include "side_panel.h"

namespace s21 {

class AppWindow : public Gtk::ApplicationWindow {
 public:
  ~AppWindow() override = default;

  AppWindow(
      Glib::RefPtr<Gtk::Application> app,
      std::function<const s21::tetris::GameInfo_t*()>& update_current_state);

 private:
  const float kRatio = 3. / 4.;
  const int kWinHeight = 600;
  const int kWinWidth = 425;
  const int kTrDuration = 500;
  const Gtk::StackTransitionType kTrType =
      Gtk::StackTransitionType::SLIDE_LEFT_RIGHT;
  const std::string kStyle = "edu/school21/BrickGame2/css/game_field.css";
  const int kPriority = GTK_STYLE_PROVIDER_PRIORITY_APPLICATION;
  Glib::RefPtr<Gtk::Application> app_;

  Gtk::AspectFrame main_frame_;
  Gtk::Box main_box_;
  Gtk::Stack main_stack_;
  Gtk::HeaderBar header_bar_;
  SidePanel side_panel_;
  GameFrame game_box_;
  MenuBox menu_box_;

  Gtk::Button header_exit_button_;
  Gtk::Button header_pause_button_;

  void SwitchStackPage_();
  void ExitGame_();
};  // class MainWindow
};  // namespace s21

#endif  // MAINWINDOW_H
