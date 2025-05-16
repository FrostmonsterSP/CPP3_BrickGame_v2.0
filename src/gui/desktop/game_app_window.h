//
// Created by frostmonster on 13.05.2025
//
#ifndef GAME_APP_WINDOW_H
#define GAME_APP_WINDOW_H

#include <gtkmm.h>

namespace s21 {
class GameAppWindow : public Gtk::ApplicationWindow {

 public:
  GameAppWindow(BaseObjectType* cobject,
                const Glib::RefPtr<Gtk::Builder>& ref_builder);

  static auto Create() -> GameAppWindow*;

 private:
  Glib::RefPtr<Gtk::Builder> ref_builder_m_;
  std::shared_ptr<EngineController> engine_controller_ = nullptr;
  void InitStyle_();
  void InitMainMenu_();
  void InitGameMenu_();

  void LoadController_(Gtk::Stack*, const std::string&);
  void UnloadController_(Gtk::Stack*);
};
}  // namespace s21

#endif  // GAME_APP_WINDOW_H
