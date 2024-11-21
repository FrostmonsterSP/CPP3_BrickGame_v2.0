//
// Created by frostmonster on 18.11.2024
//
#ifndef MENU_BOX_H
#define MENU_BOX_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>

namespace s21 {
class MenuBox : public Gtk::Box {
 public:
  MenuBox();
  ~MenuBox() override;

  void SetStartGameCallback(const std::function<void()>& start_callback);

 private:
  const int kMarigin = 10;

  Gtk::Button start_button_;
  Gtk::Button level_button_;
  Gtk::Button speed_button_;
  Gtk::Button exit_button_;

  std::function<void()> start_callback_;
  void StartButtonClicked_();
};  // class MenuBox
}  // namespace s21

#endif  // MENU_BOX_H
