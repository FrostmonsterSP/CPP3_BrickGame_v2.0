//
// Created by frostmonster on 25.11.2024
//
#include "cells_grid.h"

#include <gtkmm.h>

#include "brick_game/engine_wrapper.h"
#include "cell.h"

namespace s21 {

CellsGrid::CellsGrid(GridSize size, EngineWrapper& engine)
    : CellsGrid(size, 0, engine) {};

CellsGrid::CellsGrid(GridSize size, int mode, EngineWrapper& engine)
    : kWinHeight(size.height),
      kWinWidth(size.width),
      kMode(mode),
      m_engine_(engine) {
  set_column_homogeneous(true);
  set_row_homogeneous(true);

  for (int row = 0; row < kWinHeight; ++row) {
    for (int col = 0; col < kWinWidth; ++col) {
      auto* cell = Gtk::make_managed<Cell>();
      attach(*cell, col, row, 1, 1);
    }  // for col
  }  // for row
}  // CellsGrid::CellsGrid(int, int)

void CellsGrid::DrawField() {
  for (int row = 0; row < kWinHeight; ++row) {
    for (int col = 0; col < kWinWidth; ++col) {
      int cell_val = kMode == 0 ? m_engine_.GetFieldCell(row, col)
                                : m_engine_.GetNextCell(row, col);
      Widget* cell = get_child_at(col, row);
      ClearCell_(cell);
      if (cell_val != 0) {
        cell->add_css_class("filled");
        cell->add_css_class("f" + std::to_string(cell_val));
      }  // if (cell_val != 0)
    }  // for col
  }  // for row
}  // CellsGrid::DrawField()

void CellsGrid::ClearCell_(Widget* cell) {
  auto classes = cell->get_css_classes();
  bool is_filled = false;
  for (auto& cls : classes) {
    if (cls.find("filled") != std::string::npos) {
      is_filled = true;
      break;
    }
  }
  if (is_filled) {
    cell->remove_css_class("filled");
    cell->remove_css_class("f1");
    cell->remove_css_class("f2");
    cell->remove_css_class("f3");
    cell->remove_css_class("f4");
    cell->remove_css_class("f5");
    cell->remove_css_class("f6");
    cell->remove_css_class("f7");
  }
}  // CellsGrid::ClearCell_(Widget*)

}  // namespace s21
