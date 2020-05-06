// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/GameBoard.h>
#include <pretzel/PretzelGui.h>

namespace myapp {

class MyApp : public cinder::app::App {
 private:
  void DrawGrid();
  static void PrintText(const std::string& text, cinder::Color colour,
      cinder::ivec2 loc, cinder::ivec2 size);
  // resets the board back to the original configuration
  void ResetButton();
  // resets the entire board
  void Reset();

 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

 private:
  pretzel::PretzelGuiRef gui;
  int grid_size_ = 3;
  mylibrary::GameBoard game_board_;
  bool won_game_ = false;
  bool picture_game_ = false;
  int moves_ = 0;
  // holds the original config of the grid, used for the 'reset' button
  std::vector<std::vector<mylibrary::Tile>> original_grid_;
  // the textures of the tiles, used in the picture game
  std::vector<cinder::gl::Texture2dRef> texture_vec_;
  // the x-coordinates corresponding to the bottom-right corner of each tile in
  // a row
  std::vector<int> tile_x_;
  // the y-coordinates corresponding to the bottom-right corner of each tile in
  // a column
  std::vector<int> tile_y_;
  // hardcoded width and height of board in pixels
  const int board_width_ = 800;
  const int board_height_ = 600;
  // default board size for picture mode
  const int picture_mode_board_size_ = 3;

};


}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
