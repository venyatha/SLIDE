// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cinder/ImageIo.h>

#include <vector>

#include "Direction.h"
#include "Tile.h"

namespace mylibrary {

//enum class Direction { kUp, kDown, kLeft, kRight };

class GameBoard {
 public:
  int board_size_;
  std::vector<std::vector<Tile>> grid_;
  std::vector<std::vector<Tile>> solution_;

  explicit GameBoard(int size);
  void MoveTile(int x, int y, Direction dir);
  bool IsNullTile(int x, int y);
  friend std::ostream& operator<<(std::ostream& os, const GameBoard& gameBoard);
  void Shuffle();
  bool CheckWin();
  void SwapTiles(int i, int j, int k, int l);
  void ShuffleGameBoard();
  void ShuffleBoard();
  int countInversions(int i, int j);
  int sumInversions();
  bool isSolvable();
  void Reset(int num);
};


}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
