//
// Created by frostmonster on 25.11.2024
//
#ifndef NEXT_FRAME_H
#define NEXT_FRAME_H

#include <gtkmm.h>

namespace s21 {

class EngineWrapper;

struct GridSize {
  int width;
  int height;
};  // struct GridSize

class CellsGrid : public Gtk::Grid {
 public:
  CellsGrid(GridSize, EngineWrapper& engine);
  CellsGrid(GridSize, int, EngineWrapper& engine);
  void DrawField();
  ~CellsGrid() override = default;

 private:
  const int kWinHeight, kWinWidth;
  const float kRatio =
      static_cast<float>(kWinWidth) / static_cast<float>(kWinHeight);
  const int kMode;
  EngineWrapper& m_engine_;
  void FillCell_(Widget* cell, int value);
  void ClearCell_(Widget* cell);
};  // class CellsGrid
}  // namespace s21

#endif  // NEXT_WIN_H
