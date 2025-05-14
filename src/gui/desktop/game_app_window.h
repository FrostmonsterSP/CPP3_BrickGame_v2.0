//
// Created by frostmonster on 13.05.2025
//
#ifndef GAME_APP_WINDOW_H
#define GAME_APP_WINDOW_H

#include <gtkmm.h>

class GameAppWindow : public Gtk::ApplicationWindow {
 public:
  GameAppWindow(BaseObjectType* cobject,
                const Glib::RefPtr<Gtk::Builder>& ref_builder);

  static auto Create() -> GameAppWindow*;

 protected:
  Glib::RefPtr<Gtk::Builder> ref_builder_m;

 private:
  void InitStyle_();
};

#endif  // GAME_APP_WINDOW_H
