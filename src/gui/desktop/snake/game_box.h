//
// Created by frostmonster on 18.11.2024
//
#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>

#include "side_panel.h"

namespace s21 {

class GameBox : public Gtk::Box {
 public:
  GameBox();
  ~GameBox() override;

 private:
  Gtk::Grid field_grid_;
  SidePanel side_panel_;
  Glib::RefPtr<Gtk::CssProvider> provider_;

  void SetStyle_();
};  // class GameBox
}  // namespace s21

#endif  // GAMEFRAME_H
