//
// Created by frostmonster on 18.11.2024
//
#ifndef MENU_BOX_H
#define MENU_BOX_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>

#include "gtkmm/grid.h"
#include "gtkmm/label.h"
#include "gtkmm/layoutmanager.h"

namespace s21 {
class MenuBox : public Gtk::Box {
 public:
  MenuBox();

  void SetStartGameCallback(const std::function<void()>& start_callback);

  void SetExitCallback(const std::function<void()>& exit_callback);

  void SetLevelCallbacks(const std::function<void()>& up_callback,
                         const std::function<void()>& down_callback);
  void SetSpeedCallbacks(const std::function<void()>& up_callback,
                         const std::function<void()>& down_callback);

 private:
  const int kMargin = 10;
  Gtk::Button start_button_;
  Gtk::Grid config_grid_;
  Gtk::Box level_config_box_;
  Gtk::Box speed_config_box_;
  Gtk::Label level_label_;
  Gtk::Label speed_label_;
  Gtk::Button level_up_button_;
  Gtk::Button level_down_button_;
  Gtk::Button speed_up_button_;
  Gtk::Button speed_down_button_;
  Gtk::Button exit_button_;
};  // class MenuBox
}  // namespace s21

#endif  // MENU_BOX_H
