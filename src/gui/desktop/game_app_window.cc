#include "game_app_window.h"

GameAppWindow::GameAppWindow(BaseObjectType* cobject,
                             const Glib::RefPtr<Gtk::Builder>& ref_builder)
    : Gtk::ApplicationWindow(cobject), ref_builder_m(ref_builder) {
  InitStyle_();
}  // GameAppWindow::GameAppWindow

auto GameAppWindow::Create() -> GameAppWindow* {
  auto ref_builder = Gtk::Builder::create_from_resource(
      "/edu/school21/BrickGame2/assets/interface.ui");

  auto* window = Gtk::Builder::get_widget_derived<GameAppWindow>(ref_builder,
                                                                 "app_window");
  if (window == nullptr) {
    g_error("No \"app_window\" object in interface.ui");
  }

  return window;
}  // GameAppWindow::Create

void GameAppWindow::InitStyle_() {
  const auto* const kStyle =
      "/edu/school21/BrickGame2/assets/css/interface.css";
  const auto kPriority = GTK_STYLE_PROVIDER_PRIORITY_USER;
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
}  // GameAppWindow::InitStyle_

void GameAppWindow::InitMainMenu_() {
  auto* main_stack = ref_builder_m->get_widget<Gtk::Stack>("main_stack");

  auto* tetris_button = ref_builder_m->get_widget<Gtk::Button>("tetris_button");
  if (main_stack != nullptr) {
    tetris_button->signal_clicked().connect(
        [main_stack]() { LoadingHandler_(main_stack); });
  } else {
    g_error("No \"main_stack\" object in interface.ui");
  }
}

void GameAppWindow::LoadingHandler_(Gtk::Stack* main_stack) {

  main_stack->set_visible_child("loading_page");
  Glib::signal_timeout().connect_once(
      [main_stack]() { main_stack->set_visible_child("game_menu_page"); },
      3000);
}