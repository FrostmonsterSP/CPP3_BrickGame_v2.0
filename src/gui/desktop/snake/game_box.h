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

namespace constants {
constexpr int FIELD_HEIGHT = 20;
constexpr int FIELD_WIDTH = 10;
constexpr int spacing = 10;

}  // namespace constants
class GameBox : public Gtk::Box {
 public:
  GameBox();
  ~GameBox() override;

 private:
  Gtk::AspectFrame fieldFrame;
  Gtk::Grid fieldGrid;
  Gtk::Box sidePanel;
};  // class GameBox
}  // namespace s21

#endif  // GAMEFRAME_H
