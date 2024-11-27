//
// Created by frostmonster on 17.11.2024
//
#include "app_window.h"

#include "cells_grid.h"
#include "menu_box.h"
#include "side_panel.h"

namespace s21 {

const std::string AppWindow::kStyle =
    "edu/school21/BrickGame2/css/game_field.css";

AppWindow::AppWindow(Glib::RefPtr<Gtk::Application> app)
    : m_app_(std::move(app)) {
  CellsGrid game_grid(m_engine_.kFieldHeight, m_engine_.kFieldWidth);
  game_grid.SetEngine(&m_engine_);
  SidePanel side_panel(&m_engine_);

  m_menu_box_.SetStartGameCallback(
      sigc::mem_fun(*this, &AppWindow::SwitchStackPage_));
  m_menu_box_.SetExitCallback(sigc::mem_fun(*this, &AppWindow::ExitGame_));

  InitStyle_();
  IsDarkTheme_();
  InitTitleBar_();

  m_main_stack_.add(m_menu_box_, "menu");
  m_main_stack_.add(game_grid, "game");
  m_main_stack_.add_css_class("main-field");

  m_main_frame_.set_ratio(kRatio);
  m_main_frame_.set_child(m_main_stack_);

  m_main_box_.append(m_main_frame_);
  m_main_box_.append(side_panel);

  add_tick_callback(sigc::mem_fun(*this, &AppWindow::UpdateState_));

  set_title("Brick Game v2.0");
  set_titlebar(m_header_bar_);
  set_child(m_main_box_);
}  // AppWindow::AppWindow(Glib::RefPtr<Gtk::Application> app)

void AppWindow::SwitchStackPage_() {
  if (m_engine_.IsIdle()) {
    m_engine_.Action.Pause();
  } else {
    m_engine_.Action.Start();
  }

  if (m_main_stack_.get_visible_child_name() == "game") {
    m_main_stack_.set_visible_child("menu");
    m_header_exit_button_.set_visible(false);
    m_header_pause_button_.set_visible(false);
  } else {
    m_main_stack_.set_visible_child("game");
    m_header_exit_button_.set_visible(true);
    m_header_pause_button_.set_visible(true);
  }
}  // AppWindow::SwitchStackPage

void AppWindow::ExitGame_() {
  m_engine_.Action.Terminate();
  m_app_->quit();
}

void AppWindow::IsDarkTheme_() {
  auto settings = Gtk::Settings::get_default();

  if (settings) {
    const auto kTheme = settings->property_gtk_theme_name().get_value();
    const auto kIsDarkThemeName = kTheme.find("dark") != std::string::npos ||
                                  kTheme.find("Dark") != std::string::npos;
    const auto kIsDarkTheme =
        settings->property_gtk_application_prefer_dark_theme().get_value() ||
        kIsDarkThemeName;
    g_debug("Theme: %s\n", kTheme.c_str());
    g_debug("Is dark theme: %s\n", kIsDarkTheme ? "true" : "false");
    if (kIsDarkTheme) {
      add_css_class("dark-mode");
    }
  } else {
    g_warning("Failed to get Gtk::Settings.\n");
  }  // if settings
}  // AppWindow::IsDarkTheme_()

void AppWindow::InitStyle_() {
  const auto kDisplay = get_display();

  set_display(kDisplay);

  auto provider = Gtk::CssProvider::create();
  provider->load_from_resource(kStyle);
  Gtk::StyleProvider::add_provider_for_display(kDisplay, provider, kPriority);
}  // AppWindow::InitStyle_()

void AppWindow::InitTitleBar_() {
  m_header_exit_button_.set_label("Exit");
  m_header_pause_button_.set_label("Pause");
  m_header_exit_button_.set_visible(true);
  m_header_pause_button_.set_visible(true);

  m_header_exit_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &AppWindow::ExitGame_));
  m_header_pause_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &AppWindow::SwitchStackPage_));

  m_header_bar_.pack_start(m_header_pause_button_);
  m_header_bar_.pack_end(m_header_exit_button_);
}  // AppWindow::InitTitleBar_()

auto AppWindow::UpdateState_(const Glib::RefPtr<Gdk::FrameClock>& frame_clock)
    -> bool {
  auto is_idle = !(m_engine_.IsIdle());
  if (is_idle && frame_clock) {
    m_engine_.UpdateGameState();
  }  // if is_idle
  return is_idle;
}  // AppWindow::UpdateState_(const Glib::RefPtr<Gdk::FrameClock>& frame_clock)

}  // namespace s21
