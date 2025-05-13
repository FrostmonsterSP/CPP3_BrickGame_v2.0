#include "gui/desktop/game_app.h"

auto main(int argc, char* argv[]) -> int {
  auto application = GameApplication::Create();
  return application->run(argc, argv);
}
