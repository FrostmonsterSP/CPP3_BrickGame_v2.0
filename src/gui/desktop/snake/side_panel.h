//
// Created by frostmonster on 18.11.2024
//
#ifndef SIDE_PANEL_H
#define SIDE_PANEL_H

#include "constants.h"
#include "gtkmm/box.h"
#include "gtkmm/label.h"

namespace s21 {
class SidePanel : public Gtk::Box {
 public:
  SidePanel();
  ~SidePanel() override;

 private:
  Gtk::Label score_label_;
  Gtk::Label high_score_label_;
  Gtk::Label level_label_;
  Gtk::Label speed_label_;
};  // class SidePanel
}  // namespace s21

#endif  // SIDE_PANEL_H
