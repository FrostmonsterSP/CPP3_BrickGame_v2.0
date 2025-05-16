#include "game_app_window.h"

s21::GameAppWindow::GameAppWindow(BaseObjectType* cobject,
                                  const Glib::RefPtr<Gtk::Builder>& ref_builder)
    : Gtk::ApplicationWindow(cobject), ref_builder_m(ref_builder) {
  InitStyle_();
  InitMainMenu_();
  InitGameMenu_();
}  // GameAppWindow::GameAppWindow

auto s21::GameAppWindow::Create() -> GameAppWindow* {
  auto ref_builder = Gtk::Builder::create_from_resource(
      "/edu/school21/BrickGame2/assets/interface.ui");

  auto* window = Gtk::Builder::get_widget_derived<GameAppWindow>(ref_builder,
                                                                 "app_window");
  if (window == nullptr) {
    g_error("No \"app_window\" object in interface.ui");
  }

  return window;
}  // GameAppWindow::Create

void s21::GameAppWindow::InitStyle_() {
  try {
    const auto kDisplay = get_display();
    set_display(kDisplay);

    auto provider = Gtk::CssProvider::create();
    provider->load_from_resource(
        "/edu/school21/BrickGame2/assets/css/interface.css");
    Gtk::StyleProvider::add_provider_for_display(
        kDisplay, provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  } catch (const Glib::Error& e) {
    g_warning("Failed to load CSS: %s\n", e.what());
  } catch (const std::exception& e) {
    g_error("Unexpected error loading style: %s\n", e.what());
  }
}  // GameAppWindow::InitStyle_

void s21::GameAppWindow::InitMainMenu_() {
  auto* main_stack = ref_builder_m->get_widget<Gtk::Stack>("main_stack");

  auto* tetris_button = ref_builder_m->get_widget<Gtk::Button>("tetris_button");
  if (main_stack != nullptr) {
    tetris_button->signal_clicked().connect(
        [main_stack]() { LoadController_(main_stack); });
  } else {
    g_error("No \"main_stack\" object in interface.ui");
  }
}

void s21::GameAppWindow::InitGameMenu_() {
  auto* main_stack = ref_builder_m->get_widget<Gtk::Stack>("main_stack");

  auto* change_game_button =
      ref_builder_m->get_widget<Gtk::Button>("change_game_button");
  auto* play_button = ref_builder_m->get_widget<Gtk::Button>("play_button");

  if (main_stack != nullptr) {
    change_game_button->signal_clicked().connect(
        [main_stack]() { UnloadController_(main_stack); });
    play_button->signal_clicked().connect(
        [main_stack]() { main_stack->set_visible_child("game_page"); });
  } else {
    g_error("No \"main_stack\" object in interface.ui");
  }
}

void s21::GameAppWindow::LoadController_(Gtk::Stack* main_stack) {
  main_stack->set_visible_child("loading_page");
  Glib::signal_timeout().connect_once(
      [main_stack]() { main_stack->set_visible_child("game_menu_page"); }, 500);
}

void s21::GameAppWindow::UnloadController_(Gtk::Stack* main_stack) {
  main_stack->set_visible_child("loading_page");
  Glib::signal_timeout().connect_once(
      [main_stack]() { main_stack->set_visible_child("main_page"); }, 500);
}