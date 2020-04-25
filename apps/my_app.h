// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/ImageReader.h>
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
  float mRadius;
  std::string mFps;
  cinder::gl::TextureRef		mTexture;

  mylibrary::GameBoard game_board_;
  void DrawBoard();
  void PrintNum();
};


}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
