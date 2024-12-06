//
// Created by frostmonster on 17.11.2024
//
#include "app_window.h"

#include "engine_defs.h"
#include "menu_box.h"

namespace s21 {

const std::string AppWindow::kStyle =
    "edu/school21/BrickGame2/css/game_field.css";

AppWindow::AppWindow(Glib::RefPtr<Gtk::Application> app)
    : app_(std::move(app)),
      game_grid_(GridSize{FIELD_WIDTH, FIELD_HEIGHT}, engine_),
      side_panel_(engine_) {
  menu_box_.SetStartGameCallback(
      sigc::mem_fun(*this, &AppWindow::StartOrPauseGame_));
  menu_box_.SetExitCallback(sigc::mem_fun(*this, &AppWindow::ExitApp_));
  menu_box_.SetLevelCallbacks(
      sigc::mem_fun(*this, &AppWindow::IncreaseLevelAtInit_),
      sigc::mem_fun(*this, &AppWindow::DecreaseLevelAtInit_));
  menu_box_.SetSpeedCallbacks(
      sigc::mem_fun(*this, &AppWindow::IncreaseSpeedAtInit_),
      sigc::mem_fun(*this, &AppWindow::DecreaseSpeedAtInit_));

  InitStyle_();
  IsDarkTheme_();
  InitTitleBar_();

  main_stack_.add(menu_box_, "menu");
  main_stack_.add(game_grid_, "game");
  main_stack_.add_css_class("main-field");

  main_frame_.set_ratio(kRatio);
  main_frame_.set_child(main_stack_);

  main_box_.append(main_frame_);
  main_box_.append(side_panel_);

  add_tick_callback(sigc::mem_fun(*this, &AppWindow::UpdateState_));

  set_title("Brick Game v2.0");
  set_titlebar(header_bar_);
  set_child(main_box_);
}  // AppWindow::AppWindow

void AppWindow::SwitchStackPage_() {
  SwitchController_();
  if (main_stack_.get_visible_child_name() == "game") {
    main_stack_.set_visible_child("menu");
    header_exit_button_.set_visible(false);
    header_pause_button_.set_visible(false);
  } else {
    main_stack_.set_visible_child("game");
    header_exit_button_.set_visible(true);
    header_pause_button_.set_visible(true);
  }  // if main_stack_.get_visible_child_name() == "game"
}  // AppWindow::SwitchStackPage

void AppWindow::StartOrPauseGame_() {
  if (engine_.IsInit()) {
    engine_.Action.Start();
  } else {
    engine_.Action.Pause();
  }
  SwitchStackPage_();
}  // AppWindow::StartPauseGame_

void AppWindow::SwitchController_() {
  if (controller_ == nullptr) {
    controller_ = Gtk::EventControllerKey::create();
    controller_->signal_key_pressed().connect(
        sigc::mem_fun(*this, &AppWindow::OnKeyPressed_), false);
    add_controller(controller_);
  } else {
    remove_controller(controller_);
    controller_ = nullptr;
  }
}

void AppWindow::ExitGame_() {
  engine_.Action.Terminate();
  SwitchStackPage_();
}  // AppWindow::ExitGame_

void AppWindow::ExitApp_() {
  engine_.Action.Terminate();
  app_->quit();
}  // AppWindow::ExitApp_

void AppWindow::IncreaseLevelAtInit_() { engine_.Action.Right(); }

void AppWindow::DecreaseLevelAtInit_() { engine_.Action.Left(); }

void AppWindow::IncreaseSpeedAtInit_() { engine_.Action.Up(); }
void AppWindow::DecreaseSpeedAtInit_() { engine_.Action.Down(); }

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
    }  // if kIsDarkTheme
  } else {
    g_warning("Failed to get Gtk::Settings.\n");
  }  // if settings
}  // AppWindow::IsDarkTheme_

void AppWindow::InitStyle_() {
  try {
    const auto kDisplay = get_display();
    set_display(kDisplay);

    auto provider = Gtk::CssProvider::create();
    provider->load_from_resource(kStyle);
    Gtk::StyleProvider::add_provider_for_display(kDisplay, provider, kPriority);
  } catch (const Glib::Error& e) {
    g_warning("Failed to load CSS: %s\n", e.what());
  } catch (const std::exception& e) {
    g_error("Unexpected error loading style: %s\n", e.what());
  }
}  // AppWindow::InitStyle_

void AppWindow::InitTitleBar_() {
  header_exit_button_.set_label("Exit");
  header_pause_button_.set_label("Pause");
  header_exit_button_.set_can_focus(false);
  header_pause_button_.set_can_focus(false);
  header_exit_button_.set_visible(false);
  header_pause_button_.set_visible(false);

  header_exit_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &AppWindow::ExitGame_));
  header_pause_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &AppWindow::StartOrPauseGame_));

  header_bar_.pack_start(header_pause_button_);
  header_bar_.pack_end(header_exit_button_);
}  // AppWindow::InitTitleBar_

auto AppWindow::UpdateState_(const Glib::RefPtr<Gdk::FrameClock>& frame_clock)
    -> bool {
  if (frame_clock) {
    engine_.UpdateGameState();
    game_grid_.DrawField();
    side_panel_.DrawPanel();
  }  // if frame_clock
  return true;
}  // AppWindow::UpdateState_

auto AppWindow::OnKeyPressed_(guint keyval, guint /*unused*/,
                              Gdk::ModifierType /*unused*/) -> bool {
  bool retval = false;
  switch (keyval) {
    case GDK_KEY_Escape:
      retval = true;
      break;
    case GDK_KEY_Left:
      retval = true;
      engine_.Action.Left();
      break;
    case GDK_KEY_Right:
      retval = true;
      engine_.Action.Right();
      break;
    case GDK_KEY_Up:
      retval = true;
      engine_.Action.Up();
      break;
    case GDK_KEY_Down:
      retval = true;
      engine_.Action.Down();
      break;
    case GDK_KEY_space:
      retval = true;
      engine_.Action.Action();
    default:
      break;
  }  // switch keyval
  return retval;
}  // AppWindow::OnKeyPressed_
}  // namespace s21
