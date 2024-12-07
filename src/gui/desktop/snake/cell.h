//
// Created by frostmonster on 26.11.2024
//
#ifndef CELL_H
#define CELL_H

#include <gtkmm.h>

namespace s21 {
class Cell final : public Gtk::Button {
 public:
  Cell();
  ~Cell() override = default;
};  // class Cell
};  // namespace s21

#endif  // CELL_H
