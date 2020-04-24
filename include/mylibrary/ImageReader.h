// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cinder/ImageIo.h>

#include <vector>

namespace mylibrary {

void GridAreas(std::string filepath);

class GameBoard {
 public:
  int board_size_;
  int grid_[3][3];

  //used for pre-loaded image
  GameBoard();
  //used for numbers mode
  explicit GameBoard(int boardSize);
};




}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
