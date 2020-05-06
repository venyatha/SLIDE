// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cinder/ImageIo.h>

#include <vector>

#include "Direction.h"
#include "Tile.h"

namespace mylibrary {

// Represents the board which is the primary way for the user to interact with the game
class GameBoard {
 private:
  // the solved board
  std::vector<std::vector<Tile>> solution_;
  // the board's size
  int size_;
  // the current configuration of the board
  std::vector<std::vector<Tile>> grid_;
  // Whether the tile in grid's(x,y) position is the null tile
  bool IsNullTile(int x, int y);
  // helper functions for IsSolvable
  int CountInversions(int i, int j);
  int RowOfNullTile();
  int sumInversions();

 public:
  // GameBoard constructor
  explicit GameBoard(int size);
  // moves Tile with coordinate (x,y) in the Direction dir.
  // If move is illegal (not next to a null tile), nothing is changed
  void MoveTile(int x, int y, Direction dir);
  friend std::ostream& operator<<(std::ostream& os, const GameBoard& gameBoard);
  // checks if the grid is solved
  bool CheckWin();
  // shuffles the grid
  void ShuffleBoard();
  // checks whether the board is actually solvable with legal moves
  bool IsSolvable();
  // resets the GameBoard with regard to the new size
  void Reset(int size);
  // basic getter for the board's size
  int GetSize();
  // basic getter for the grid
  std::vector<std::vector<Tile>> GetGrid();
  // setter for the grid
  void SetGrid(std::vector<std::vector<Tile>> new_grid_);

};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
