// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cinder/ImageIo.h>

#include <vector>

#include "Direction.h"
#include "Tile.h"

namespace mylibrary {

class GameBoard {
 private:
  bool IsNullTile(int x, int y);
  int countInversions(int i, int j);
  int RowOfNullTile();
  int sumInversions();
  std::vector<std::vector<Tile>> solution_;

 public:
  int size_;
  std::vector<std::vector<Tile>> grid_;

  explicit GameBoard(int size);
  void MoveTile(int x, int y, Direction dir);
  friend std::ostream& operator<<(std::ostream& os, const GameBoard& gameBoard);
  bool CheckWin();
  void ShuffleBoard();
  bool isSolvable();
  void Reset(int num);
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
