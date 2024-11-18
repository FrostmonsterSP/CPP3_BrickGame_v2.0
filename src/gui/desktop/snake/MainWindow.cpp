#include "MainWindow.h"

namespace s21 {
MainWindow::MainWindow() {
  set_title("Brick Game v2.0");
  set_default_size(constants::winWidth, constants::winHeight);
  set_resizable(false);

  // Настройка панели заголовка
  headerBar.set_visible(true);
  headerBar.set_can_focus(false);

  menuButton.set_visible(true);
  menuButton.set_can_focus(true);
  menuButton.set_focus_on_click(false);
  menuButton.set_receives_default(true);
  menuButton.set_direction(Gtk::ArrowType::NONE);

  headerBar.pack_end(menuButton);
  set_titlebar(headerBar);

  // CSS style
  Glib::ustring style =
      ".filled-cell{background-color:#f00;}.empty-cell{background-color:#000;}";
  auto provider = Gtk::CssProvider::create();
  provider->load_from_data(style);

  auto provider_priority = GTK_STYLE_PROVIDER_PRIORITY_USER;

  // Настройка сетки игрового поля
  for (int row = 0; row < constants::fieldHeight; ++row) {
    for (int col = 0; col < constants::fieldWidth; ++col) {
      auto* cell = Gtk::make_managed<Gtk::Button>();

      cell->get_style_context()->add_provider(provider, provider_priority);
      cell->get_style_context()->add_class("empty-cell");
      cell->set_sensitive(false);
      game_grid.attach(*cell, col, row, 1, 1);
    }  // for col
  }  // for row

  game_grid.get_style_context()->add_provider(provider, provider_priority);
  game_grid.get_style_context()->add_class("empty-cell");

  game_grid.get_child_at(0, 0)->get_style_context()->remove_class("empty-cell");
  game_grid.get_child_at(0, 0)->get_style_context()->add_class("filled-cell");

  side_panel.set_spacing(constants::spacing);
  side_panel.append(score_label);
  side_panel.append(high_score_label);
  side_panel.append(level_label);
  side_panel.append(speed_label);
  side_panel.append(pause_label);

  // Сборка интерфейса
  main_box.append(game_grid);
  main_box.append(side_panel);
  set_child(main_box);
}  // MainWiupdate_game_state

MainWindow::~MainWindow() = default;
}  // namespace s21
