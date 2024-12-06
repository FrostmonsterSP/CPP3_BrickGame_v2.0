//
// Created by frostmonster on 17.11.2024
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

#include "brick_game/engine_wrapper.h"
#include "cells_grid.h"
#include "menu_box.h"
#include "side_panel.h"

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

  Glib::RefPtr<Gtk::Application> app_;
  Glib::RefPtr<Gtk::EventControllerKey> controller_;
  EngineWrapper engine_;
  Gtk::HeaderBar header_bar_;
  Gtk::Button header_exit_button_;
  Gtk::Button header_pause_button_;
  Gtk::Box main_box_;
  Gtk::Stack main_stack_;
  Gtk::AspectFrame main_frame_;
  MenuBox menu_box_;
  CellsGrid game_grid_;
  SidePanel side_panel_;

  void SwitchStackPage_();
  void ExitGame_();
  void ExitApp_();
  void IncreaseLevelAtInit_();
  void DecreaseLevelAtInit_();
  void IncreaseSpeedAtInit_();
  void DecreaseSpeedAtInit_();
  void StartOrPauseGame_();
  void SwitchController_();
  void IsDarkTheme_();
  void InitStyle_();
  void InitTitleBar_();
  void InitSidePanel_();
  auto UpdateState_(const Glib::RefPtr<Gdk::FrameClock>&) -> bool;
  auto OnKeyPressed_(guint, guint, Gdk::ModifierType) -> bool;
};  // class AppWindow
};  // namespace s21

#endif  // MAINWINDOW_H
