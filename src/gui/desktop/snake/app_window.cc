//
// Created by frostmonster on 17.11.2024
//
#include "app_window.h"

namespace s21 {

AppWindow::AppWindow() {
  const float kRatio = 3. / 4.;
  const int kWinHeight = 600;
  const int kWinWidth = 425;
  const std::string kStyle = "edu/school21/BrickGame2/css/game_field.css";
  const int kPriority = GTK_STYLE_PROVIDER_PRIORITY_APPLICATION;
  const auto kDisplay = get_display();

  set_display(kDisplay);

  auto provider = Gtk::CssProvider::create();
  provider->load_from_resource(kStyle);
  Gtk::StyleProvider::add_provider_for_display(kDisplay, provider, kPriority);

  set_title("Brick Game v2.0");
  set_size_request(kWinWidth, kWinHeight);

  menu_button_.set_visible(true);
  menu_button_.set_direction(Gtk::ArrowType::NONE);

  header_bar_.pack_start(menu_button_);

  main_stack_.add(menu_box_, "menu");
  main_stack_.add(game_box_, "game");
  main_stack_.set_transition_type(kTrType);
  main_stack_.set_transition_duration(kTrDuration);

  menu_box_.SetStartGameCallback([this] { SwitchStackPage_(); });

  main_box_.set_orientation(Gtk::Orientation::HORIZONTAL);
  main_box_.append(main_stack_);
  main_box_.append(side_panel_);

  main_frame_.set_ratio(kRatio);
  main_frame_.set_child(main_box_);

  set_titlebar(header_bar_);
  set_child(main_frame_);
}  // AppWindow::AppWindow

AppWindow::~AppWindow() = default;

void AppWindow::SwitchStackPage_() {
  if (main_stack_.get_visible_child_name() == "game") {
    main_stack_.set_visible_child("menu");
  } else {
    main_stack_.set_visible_child("game");
  }
}  // AppWindow::SwitchStackPage

}  // namespace s21
