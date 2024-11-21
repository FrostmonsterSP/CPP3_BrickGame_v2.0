//
// Created by frostmonster on 18.11.2024
//
#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <gtkmm/aspectframe.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>

namespace s21 {

class GameFrame : public Gtk::AspectFrame {
 public:
  GameFrame();
  ~GameFrame() override;

 private:
  const int kFieldHeight = 20;
  const int kFieldWidth = 10;
  const float kRatio = .5;

  Gtk::Grid field_grid_;
};  // class GameFrame
}  // namespace s21

#endif  // GAMEFRAME_H
