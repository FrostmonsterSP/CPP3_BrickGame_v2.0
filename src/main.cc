#include <gtkmm.h>

#include "gui.h"
#include "gui/desktop/snake/app_window.h"

auto main(int argc, char *argv[]) -> int {
  std::function<const s21::tetris::GameInfo_t *()> update_current_state(
      []() -> const s21::tetris::GameInfo_t * {
        const s21::tetris::GameInfo_t *info = s21::tetris::updateCurrentState();
        s21::tetris::userInput(s21::tetris::Start);
        g_debug("Current state: %d", info->state);
        return s21::tetris::updateCurrentState();
      });
  auto app = Gtk::Application::create("edu.school21.BrickGame2");
  return app->make_window_and_run<s21::AppWindow>(argc, argv, app,
                                                  update_current_state);
}