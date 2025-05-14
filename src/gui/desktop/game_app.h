#ifndef BRICK_APP_H
#define BRICK_APP_H

#include <gtkmm.h>

namespace s21 {
class GameAppWindow;

class GameApplication : public Gtk::Application {
 protected:
  GameApplication();

 public:
  static auto Create() -> Glib::RefPtr<GameApplication>;

 protected:
  void on_activate() override;

 private:
  auto CreateAppWindow_() -> GameAppWindow*;
};  // class GameApplication
}  // namespace s21

#endif  // BRICK_APP_H
