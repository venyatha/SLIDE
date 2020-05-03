// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/GameBoard.h>
#include <pretzel/PretzelGui.h>

namespace myapp {

class MyApp : public cinder::app::App {
 public:

  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

  pretzel::PretzelGuiRef gui;
  int grid_size_ = 4;
  std::string mFps;
  cinder::gl::TextureRef mTexture;
  std::vector<int> tile_x_;
  std::vector<int> tile_y_;
  bool won_game_ = false;
  int score = 0;

  mylibrary::GameBoard game_board_;
  void PrintNum();
  void DrawEndScreen();
  void DrawGrid();
  void ShuffleButton();
  void UpdateButton();
  void DrawScore();
};


}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
