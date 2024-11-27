//
// Created by frostmonster on 25.11.2024
//
#include "cells_grid.h"

#include <gtkmm.h>

#include "brick_game/engine_wrapper.h"
#include "cell.h"

namespace s21 {

CellsGrid::CellsGrid(int xaxs, int yaxs) : kWinHeight(xaxs), kWinWidth(yaxs) {
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
  if (m_engine_ == nullptr) {
    throw std::runtime_error("Engine is not initialized for field");
    return;
  }
  for (int row = 0; row < kWinHeight; ++row) {
    for (int col = 0; col < kWinWidth; ++col) {
      int cell_val = m_engine_->GetFieldCell(row, col);
      auto* cell = get_child_at(col, row);
      if (cell_val != 0) {
        FillCell_(cell, cell_val);
      } else {
        ClearCell_(cell);
      }  // if (cell_val != 0)
    }  // for col
  }  // for row
}

void CellsGrid::FillCell_(Widget* cell, const int kValue) {
  cell->add_css_class("filled");
  cell->add_css_class("f" + std::to_string(kValue));
}

void CellsGrid::ClearCell_(Widget* cell) {
  cell->remove_css_class("filled");
  cell->remove_css_class("f1");
  cell->remove_css_class("f2");
  cell->remove_css_class("f3");
  cell->remove_css_class("f4");
  cell->remove_css_class("f5");
  cell->remove_css_class("f6");
  cell->remove_css_class("f7");
}

}  // namespace s21
