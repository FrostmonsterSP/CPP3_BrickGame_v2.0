//
// Created by frostmonster on 17.11.2024
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

#include "brick_game/engine_wrapper.h"
#include "cells_grid.h"
#include "menu_box.h"

namespace s21 {

class AppWindow : public Gtk::ApplicationWindow {
 public:
  AppWindow() = delete;

  AppWindow(Glib::RefPtr<Gtk::Application>);

 private:
  static constexpr float kRatio = 10.F / 20.F;
  static constexpr int kTrDuration = 500;
  static constexpr Gtk::StackTransitionType kTrType =
      Gtk::StackTransitionType::SLIDE_LEFT_RIGHT;
  static const std::string kStyle;
  static constexpr int kPriority = GTK_STYLE_PROVIDER_PRIORITY_USER;

  Glib::RefPtr<Gtk::Application> m_app_;
  Gtk::HeaderBar m_header_bar_;
  Gtk::Button m_header_exit_button_;
  Gtk::Button m_header_pause_button_;
  Gtk::Box m_main_box_;

  Gtk::Stack m_main_stack_;
  Gtk::AspectFrame m_main_frame_;
  MenuBox m_menu_box_;
  CellsGrid m_game_grid;
  EngineWrapper m_engine_;

  void SwitchStackPage_();
  void ExitGame_();
  void IsDarkTheme_();
  void InitStyle_();
  void InitTitleBar_();
  void InitSidePanel_();
  // void InitMenuBox_(Gtk::Box* menu_box);
  auto UpdateState_(const Glib::RefPtr<Gdk::FrameClock>& frame_clock) -> bool;
};  // class AppWindow
};  // namespace s21

#endif  // MAINWINDOW_H
