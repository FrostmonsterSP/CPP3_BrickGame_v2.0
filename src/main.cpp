#include <gtkmm.h>

#include "gui/desktop/snake/MainWindow.h"

auto main(int argc, char *argv[]) -> int {
  auto app = Gtk::Application::create("org.gtkmm.example");
  s21::MainWindow window;
  return app->make_window_and_run<s21::MainWindow>(argc, argv);
}