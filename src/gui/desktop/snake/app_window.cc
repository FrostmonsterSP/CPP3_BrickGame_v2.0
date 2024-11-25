//
// Created by frostmonster on 17.11.2024
//
#include "app_window.h"

namespace s21 {

AppWindow::AppWindow(
    Glib::RefPtr<Gtk::Application> app,
    std::function<const s21::tetris::GameInfo_t*()>& update_current_state) {
  const auto kDisplay = get_display();
  app_ = std::move(app);

  set_display(kDisplay);

  auto provider = Gtk::CssProvider::create();
  provider->load_from_resource(kStyle);
  Gtk::StyleProvider::add_provider_for_display(kDisplay, provider, kPriority);

  auto settings = Gtk::Settings::get_default();

  if (settings) {
    const auto kTheme = settings->property_gtk_theme_name().get_value();
    const bool kIsDarkThemeName = kTheme.find("dark") != std::string::npos ||
                                  kTheme.find("Dark") != std::string::npos;
    const bool kIsDarkTheme =
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

  set_title("Brick Game v2.0");
  set_size_request(kWinWidth, kWinHeight);

  header_exit_button_.set_label("Exit");
  header_pause_button_.set_label("Pause");
  header_exit_button_.set_visible(false);
  header_pause_button_.set_visible(false);

  header_exit_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &AppWindow::ExitGame_));
  header_pause_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &AppWindow::SwitchStackPage_));

  header_bar_.pack_start(header_pause_button_);
  header_bar_.pack_end(header_exit_button_);

  menu_box_.SetStartGameCallback([this] { SwitchStackPage_(); });
  menu_box_.SetExitCallback([this] { ExitGame_(); });

  game_box_.SetUpdateFieldCallback(update_current_state);

  main_stack_.add(menu_box_, "menu");
  main_stack_.add(game_box_, "game");
  main_stack_.set_transition_type(kTrType);
  main_stack_.set_transition_duration(kTrDuration);

  main_box_.set_orientation(Gtk::Orientation::HORIZONTAL);
  main_box_.append(main_stack_);
  main_box_.append(side_panel_);

  main_frame_.set_ratio(kRatio);
  main_frame_.set_child(main_box_);

  set_titlebar(header_bar_);
  set_child(main_frame_);
}  // AppWindow::AppWindow(Glib::RefPtr<Gtk::Application> app)

void AppWindow::SwitchStackPage_() {
  if (main_stack_.get_visible_child_name() == "game") {
    main_stack_.set_visible_child("menu");
    header_exit_button_.set_visible(false);
    header_pause_button_.set_visible(false);
  } else {
    main_stack_.set_visible_child("game");
    header_exit_button_.set_visible(true);
    header_pause_button_.set_visible(true);
  }
}  // AppWindow::SwitchStackPage

void AppWindow::ExitGame_() { app_->quit(); }

}  // namespace s21
