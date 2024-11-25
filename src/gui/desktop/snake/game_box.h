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

#include "brick_game/engine_wrapper.h"

namespace s21 {

class GameFrame : public Gtk::AspectFrame {
 public:
  GameFrame();
  ~GameFrame() override;

 private:
  const int kFieldHeight = EngineWrapper::GetFieldHeight();
  const int kFieldWidth = EngineWrapper::GetFieldWidth();
  const float kRatio =
      static_cast<float>(kFieldWidth) / static_cast<float>(kFieldHeight);

  Gtk::Grid field_grid_;
  EngineWrapper engine_;

  auto UpdateField_(const Glib::RefPtr<Gdk::FrameClock>& frame_clock) -> bool;
};  // class GameFrame
}  // namespace s21

#endif  // GAMEFRAME_H
