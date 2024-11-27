//
// Created by frostmonster on 18.11.2024
//
#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

#include <gtkmm.h>

#include "brick_game/engine_wrapper.h"
#include "cells_grid.h"

namespace s21 {
class SidePanel : public Gtk::Box {
 public:
  SidePanel() = delete;
  SidePanel(EngineWrapper*);
  ~SidePanel() override;

 private:
  const int kSpacing = 10;
  Gtk::Label m_score_label_;
  Gtk::Label m_high_score_label_;
  Gtk::Label m_level_label_;
  Gtk::Label m_speed_label_;
  CellsGrid m_next_frame_;
  EngineWrapper* m_engine_;
};  // class SidePanel
}  // namespace s21

#endif  // SIDE_PANEL_H
