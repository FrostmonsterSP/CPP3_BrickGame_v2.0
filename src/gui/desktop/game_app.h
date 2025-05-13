#ifndef BRICK_APP_H
#define BRICK_APP_H

#include <gtkmm.h>

class GameAppWindow;

class GameApplication : public Gtk::Application {
 protected:
  GameApplication();

 public:
  static auto Create() -> Glib::RefPtr<GameApplication>;
  void OpenFileView(const Glib::RefPtr<Gio::File>& file);

 protected:
  void on_activate() override;

 private:
  auto CreateAppwindow_() -> GameAppWindow*;
};  // class GameApplication

#endif  // BRICK_APP_H
