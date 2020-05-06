// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/GeomIo.h>
#include <cinder/app/App.h>
#include <mylibrary/GameBoard.h>
#include <mylibrary/ImageProcessor.h>
#include <pretzel/PretzelGui.h>

#include "util.h"

namespace myapp {

MyApp::MyApp() :game_board_{3}{};

void MyApp::setup() {
  // set up vector of tile textures for picture mode
  texture_vec_ = mylibrary::MakeTextureVec(myapp::file_path_,
      board_width_/picture_mode_board_size_,
      board_height_/picture_mode_board_size_);

  // set up gui
  gui = pretzel::PretzelGui::create("Puzzle settings");
  gui->setSize(ci::vec2(20,200));
  gui->setPos(ci::vec2(920,50));
  gui->addSlider("Grid Size", &grid_size_, 3, 7);
  gui->addButton("Update", &MyApp::Reset, this);
  gui->addToggle("Picture mode", &picture_game_);
  gui->addButton("Reset", &MyApp::ResetButton, this);

  // shuffle game_board_ and save original state
  game_board_.ShuffleBoard();
  original_grid_ = game_board_.GetGrid();
}

void MyApp::Reset() {
  game_board_.Reset(grid_size_);
  game_board_.ShuffleBoard();
  original_grid_ = game_board_.GetGrid();
  tile_x_.clear();
  tile_y_.clear();
  moves_ = 0;
  won_game_ = false;
  picture_game_ = false;
}

void MyApp::ResetButton() {
  // reset the grid to the original configuration
  game_board_.SetGrid(original_grid_);
  moves_ = 0;
}

void MyApp::update() {
  if (game_board_.CheckWin()) {
    won_game_ = true;
  }

  // if user has clicked picture mode while on a different grid size,
  // reset accordingly
  if (picture_game_ && grid_size_ !=3) {
    grid_size_ = 3;
    Reset();
    picture_game_ = true;
  }
}

void MyApp::draw() {
  ci::gl::setMatricesWindow( getWindowSize() );
  ci::gl::clear(ci::Color::black());
  gui->drawAll();

  //draw the current game board
  ci::gl::translate(-360,-250);
  DrawGrid();

  // print current number of moves
  PrintText(std::to_string(moves_), ci::Color(0,0.5,1),
      ci::ivec2(935, -100), ci::ivec2(100,100));

  // print "You won!" message
  if (won_game_) {
    PrintText("You won!", ci::Color(0,0,1),
        ci::ivec2(935, -50), ci::ivec2(100,100));
  }
}

void MyApp::PrintText(const std::string& text, ci::Color color, ci::ivec2 loc, ci::ivec2 size) {
  ci::gl::color(color);
  ci::TextBox box;
  box.setSize(size);
  box.setAlignment(ci::TextBox::CENTER);
  box.setFont(ci::Font("Arial", 30));
  box.setColor(color);
  box.setBackgroundColor(ci::ColorA(0,0,0,0));
  box.setText(text);

  const ci::vec2 locp = loc;
  const auto surface = box.render();
  const auto texture = ci::gl::Texture::create(surface);
  ci::gl::draw(texture, locp);
}

void MyApp::DrawGrid() {
  ci::gl::translate( getWindowCenter().x, getWindowCenter().y);
  ci::gl::translate(-200,-100);

  // calculate width and height of the tiles
  float width = board_width_ / game_board_.GetSize();
  float height = board_height_ / game_board_.GetSize();

  for (int y = 0; y < game_board_.GetSize(); y++) {
    for (int x = 0; x < game_board_.GetSize(); x++) {
      // populate tile_x_ with the x-coordinates of the tiles
      if (tile_x_.size() < game_board_.GetSize()) {
        tile_x_.push_back(40+ (x+1)* width);
      }

      // if a numbers game, draw the whole grid
      if (!picture_game_) {
        ci::gl::color( ci::Color( 1, 1, 1 ) );
        ci::gl::drawStrokedRect(ci::Rectf(ci::Area(0,
            0, width, height)));
      }

      // if not the null tile
      if (!game_board_.GetGrid()[x][y].GetNullTile()) {
        if (picture_game_) {
          // draw the cropped image corresponding to the tile
          ci::Rectf rect(ci::Area(0,0, width, height));
          int index = game_board_.GetGrid()[x][y].GetNum() - 1;
          ci::gl::draw( texture_vec_[index],rect);
        }

        // draw the number of the tile
        std::string str = std::to_string(game_board_.GetGrid()[x][y].GetNum());
        ci::gl::drawStringCentered (str,ci::ivec2(width /2,
            height /2),ci::ColorA(0, 0.5, 1, 1),
            ci::Font("Arial", 30));
      }

      // translate right to draw the next tile
      ci::gl::translate(width,0);
    }

    // populate tile_y_ with the y-coordinates of the tiles
    if (tile_y_.size() < game_board_.GetSize()) {
      tile_y_.push_back(50 + (y+1)* height);
    }

    // translate left and down to draw the next row of tiles
    ci::gl::translate(-(width*game_board_.GetSize()), height);
  }

}

void MyApp::keyDown(ci::app::KeyEvent event) {
  if (event.getChar() == 'g'){
    gui->toggleVisible();
  }
}
void MyApp::mouseDown(ci::app::MouseEvent event) {
  // holds the current state of the grid
  std::vector<std::vector<mylibrary::Tile>> pre_move = game_board_.GetGrid();

  // iterate through the tile_y_ and tile_x_ vectors to find the position of
  // the mouse click in relation to the bounds of the tiles
  for (int y = 0; y < tile_y_.size(); y++) {
    for (int x = 0; x < tile_x_.size(); x++) {
      if (event.getX() <= tile_x_[x] && event.getY() <= tile_y_[y]) {
        // try to move the tile, if the state of the grid doesn't change, try
        // another move
        game_board_.MoveTile(x,y,mylibrary::Direction::kDown);
        if (pre_move == game_board_.GetGrid()) {
          game_board_.MoveTile(x,y,mylibrary::Direction::kUp);
          if (pre_move == game_board_.GetGrid()) {
            game_board_.MoveTile(x,y,mylibrary::Direction::kLeft);
            if (pre_move == game_board_.GetGrid()) {
              game_board_.MoveTile(x,y,mylibrary::Direction::kRight);
              if (pre_move == game_board_.GetGrid()) {
                // no legal move has occurred, return without incrementing moves
                return;
              }
              // legal move has been made, increment number of moves and return
              moves_++;
              return;
            }
            moves_++;
            return;
          }
          moves_++;
          return;
        }
        moves_++;
        return;
      }
    }
  }
}

}  // namespace myapp
