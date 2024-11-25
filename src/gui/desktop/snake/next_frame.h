//
// Created by frostmonster on 25.11.2024
//
#ifndef NEXT_FRAME_H
#define NEXT_FRAME_H

#include <gtkmm/aspectframe.h>

#include "brick_game/engine_wrapper.h"

namespace s21 {
class NextFrame : public Gtk::AspectFrame {
 public:
  NextFrame() = default;
  ~NextFrame() override = default;

 private:
  const int kWinHeight = EngineWrapper::GetNextHeight();
  const int kWinWidth = EngineWrapper::GetNextWidth();
  const int kRatio =
      static_cast<float>(kWinWidth) / static_cast<float>(kWinHeight);
};
}  // namespace s21

#endif  // NEXT_WIN_H
