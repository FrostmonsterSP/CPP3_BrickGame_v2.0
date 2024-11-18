#include <gtkmm.h>

#include "gui/desktop/snake/app_window.h"

auto main(int argc, char *argv[]) -> int {
  auto app = Gtk::Application::create("org.gtkmm.example");
  s21::AppWindow window;
  return app->make_window_and_run<s21::AppWindow>(argc, argv);
}