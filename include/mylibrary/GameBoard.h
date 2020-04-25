// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cinder/ImageIo.h>

#include <vector>

#include "Tile.h"

namespace mylibrary {

enum class Direction { kUp, kDown, kLeft, kRight };

class GameBoard {
 public:
  int board_size_;
  std::vector<std::vector<Tile>> grid_;
  std::vector<std::vector<Tile>> solution_;

  explicit GameBoard(int size);

  /*
  int board_size_;
  std::string mode_;
  //int grid_[3][3];
  std::vector<std::vector<int>> grid_;
  std::vector<std::vector<int>> current_grid_;
  int null_tile_x_;
  int null_tile_y_;

  //used for pre-loaded image
  GameBoard();
  //used for numbers mode
  explicit GameBoard(int boardSize);

  void MoveUp(int num);
  void MoveDown(int num);
  void MoveRight(int num);
  void MoveLeft(int num);
   */
  //shuffle
  //check win

  void MoveTile(int x, int y, Direction dir);
};


}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
