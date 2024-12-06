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
  SidePanel(EngineWrapper&);
  ~SidePanel() override;

  void DrawPanel();

 private:
  const int kSpacing = 10;
  int m_score_;
  int m_high_score_;
  int m_level_;
  int m_speed_;
  Gtk::Label m_score_label_;
  Gtk::Label m_high_score_label_;
  Gtk::Label m_level_label_;
  Gtk::Label m_speed_label_;
  EngineWrapper& m_engine_;
  CellsGrid m_next_frame_;
};  // class SidePanel
}  // namespace s21

#endif  // SIDE_PANEL_H
