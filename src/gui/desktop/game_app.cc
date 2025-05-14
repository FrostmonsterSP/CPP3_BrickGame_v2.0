#include "game_app.h"
#include "game_app_window.h"

s21::GameApplication::GameApplication()
    : Gtk::Application("edu.school21.BrickGame2",
                       Gio::Application::Flags::HANDLES_OPEN) {}

auto s21::GameApplication::Create() -> Glib::RefPtr<GameApplication> {
  return Glib::make_refptr_for_instance<GameApplication>(new GameApplication());
}  // GameApplication::Create

auto s21::GameApplication::CreateAppWindow_() -> GameAppWindow* {
  auto* appwindow = GameAppWindow::Create();

  add_window(*appwindow);

  appwindow->signal_hide().connect([appwindow]() { delete appwindow; });

  return appwindow;
}  // GameApplication::CreateAppwindow_

void s21::GameApplication::on_activate() {
  try {
    // The application has been started, so let's show a window.
    auto* appwindow = CreateAppWindow_();
    appwindow->present();
  } catch (const Glib::Error& ex) {
    g_error("GameApplication::on_activate(): %s\n", ex.what());
  } catch (const std::exception& ex) {
    g_error("GameApplication::on_activate(): %s\n", ex.what());
  }
}  // GameApplication::on_activate
