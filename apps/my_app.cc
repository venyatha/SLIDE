// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/GeomIo.h>
#include <cinder/app/App.h>
#include <mylibrary/GameBoard.h>
#include <mylibrary/Image.h>
#include <pretzel/PretzelGui.h>
#include "path.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() :game_board_{3}{};

void MyApp::setup() {
  texture_vec_ = mylibrary::MakeTextureVec(myapp::file_path_);

  gui = pretzel::PretzelGui::create("Puzzle settings");
  gui->setSize(cinder::vec2(20,10));
  gui->setPos(cinder::vec2(920,50));

  gui->addSlider("Grid Size", &grid_size_, 3, 7);
  gui->addButton("Shuffle", &MyApp::ShuffleButton, this);
  gui->addButton("Update", &MyApp::UpdateButton, this);
  gui->addToggle("Picture mode", &picture_game_);

  game_board_.ShuffleBoard();
}

void MyApp::ShuffleButton() {
  if (won_game_) {
    won_game_ = false;
  }
  game_board_.ShuffleBoard();
}

void MyApp::UpdateButton() {
  game_board_.Reset(grid_size_);
  game_board_.ShuffleBoard();
  tile_x_.clear();
  tile_y_.clear();
  score = 0;
  won_game_ = false;
  picture_game_ = false;
}

void MyApp::update() {
  if (game_board_.CheckWin()) {
    won_game_ = true;
  }

  if (picture_game_ && grid_size_ !=3) {
    grid_size_ = 3;
    game_board_.Reset(grid_size_);
    game_board_.ShuffleBoard();
    tile_x_.clear();
    tile_y_.clear();
    score = 0;
  }

}

void MyApp::draw() {
  cinder::gl::setMatricesWindow( getWindowSize() );
  cinder::gl::clear(cinder::Color::black());
  gui->drawAll();

  cinder::gl::translate(-360,-250);
  DrawGrid();
  PrintText(std::to_string(score), cinder::Color(0,0,1),
      ci::ivec2(935, -100), cinder::ivec2(100,100));
  if (won_game_) {
    PrintText("You won!", cinder::Color(0,0,1),
        ci::ivec2(935, -50), cinder::ivec2(100,100));
  }
}

void MyApp::PrintText(const std::string& text, cinder::Color color, cinder::ivec2 loc, cinder::ivec2 size) {
  cinder::gl::color(color);
  cinder::TextBox box;
  box.setSize(size);
  box.setAlignment(cinder::TextBox::CENTER);
  box.setFont(cinder::Font("Arial", 30));
  box.setColor(color);
  box.setBackgroundColor(cinder::ColorA(0,0,0,0));
  box.setText(text);

  const cinder::vec2 locp = loc;
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawGrid() {
  cinder::gl::translate( getWindowCenter().x, getWindowCenter().y);
  cinder::gl::translate(-200,-100);

  float x = 800 / game_board_.size_;
  float y = 600 / game_board_.size_;

  for (int i = 0; i < game_board_.size_; i++) {
    for (int j = 0; j < game_board_.size_; j++) {

      if (tile_x_.size() < game_board_.size_) {
        tile_x_.push_back(40+ (j+1)*x);
      }

      if (!picture_game_) {
        cinder::gl::color( cinder::Color( 1, 1, 1 ) );
        cinder::gl::drawStrokedRect(cinder::Rectf(cinder::Area(0,0,x,y)));
      }

      if (game_board_.grid_[j][i].num_ != game_board_.size_ *game_board_.size_) {
        if (picture_game_) {
          cinder::Rectf rectangle(cinder::Area(0,0,x,y));
          cinder::gl::draw( texture_vec_[game_board_.grid_[j][i].num_ - 1], rectangle );
        }
        std::string str = std::to_string(game_board_.grid_[j][i].num_);
        cinder::gl::drawStringCentered (str, cinder::ivec2(x/2,y/2),
                                        cinder::ColorA(0, 0.5, 1, 1),
                                        cinder::Font("Arial", 30));
      }
      cinder::gl::translate(x,0);
    }

    if (tile_y_.size() < game_board_.size_) {
      tile_y_.push_back(50 + (i+1)*y);
    }
    cinder::gl::translate(-(x*game_board_.size_),y);
  }

}

void MyApp::keyDown(KeyEvent event) {
  if (event.getChar() == 'g'){
    gui->toggleVisible();  // gui interaction will be disabled when invisible
  }
}
void MyApp::mouseDown(cinder::app::MouseEvent event) {
  std::cout << event.getX() << " " << event.getY() << std::endl;
  std::vector<std::vector<mylibrary::Tile>> pre_move = game_board_.grid_;

  for (int y = 0; y < tile_y_.size(); y++) {
    for (int x = 0; x < tile_x_.size(); x++) {
      if (event.getX() <= tile_x_[x] && event.getY() <= tile_y_[y]) {
        game_board_.MoveTile(x,y,mylibrary::Direction::kDown);
        if (pre_move == game_board_.grid_) {
          game_board_.MoveTile(x,y,mylibrary::Direction::kUp);
          if (pre_move == game_board_.grid_) {
            game_board_.MoveTile(x,y,mylibrary::Direction::kLeft);
            if (pre_move == game_board_.grid_) {
              game_board_.MoveTile(x,y,mylibrary::Direction::kRight);
              if (pre_move == game_board_.grid_) {
                return;
              }
              score++;
              return;
            }
            score++;
            return;
          }
          score++;
          return;
        }
        score++;
        return;
      }
    }
  }
}

}  // namespace myapp
