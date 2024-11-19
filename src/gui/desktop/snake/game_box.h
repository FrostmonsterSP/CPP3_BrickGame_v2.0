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

#include "gtkmm/aspectframe.h"

namespace s21 {

class GameBox : public Gtk::Box {
 public:
  GameBox();
  ~GameBox() override;

 private:
  Gtk::AspectFrame field_frame_;
  Gtk::Grid field_grid_;
  Gtk::Box side_panel_;
};  // class GameBox
}  // namespace s21

#endif  // GAMEFRAME_H
