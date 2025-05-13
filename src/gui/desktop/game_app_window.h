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
  void OpenFileView(const Glib::RefPtr<Gio::File>& file);

 protected:
  Glib::RefPtr<Gtk::Builder> m_ref_builder;

 private:
  void InitStyle_();
};

#endif  // GAME_APP_WINDOW_H
