//
// Created by frostmonster on 25.11.2024
//
#ifndef NEXT_FRAME_H
#define NEXT_FRAME_H

#include <gtkmm.h>

namespace s21 {

class EngineWrapper;

class CellsGrid : public Gtk::Grid {
 public:
  CellsGrid(int, int);
  void DrawField();

  void SetEngine(EngineWrapper* engine) { m_engine_ = engine; }

 private:
  const int kWinHeight, kWinWidth;
  const float kRatio =
      static_cast<float>(kWinWidth) / static_cast<float>(kWinHeight);
  EngineWrapper* m_engine_;
  void FillCell_(Widget* cell, int value);
  void ClearCell_(Widget* cell);
};
}  // namespace s21

#endif  // NEXT_WIN_H
