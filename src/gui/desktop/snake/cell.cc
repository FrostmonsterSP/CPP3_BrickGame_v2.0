//
// Created by frostmonster on 26.11.2024
//
#include "cell.h"

namespace s21 {
Cell::Cell() {
  add_css_class("cell");
  add_css_class("flat");
  set_size_request(20, 20);
  set_expand();
  set_sensitive(false);
}  // Cell::Cell()

}  // namespace s21
