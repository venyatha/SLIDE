//
// Created by Venyatha MANNE on 4/25/20.
//

#ifndef FINALPROJECT_TILE_H
#define FINALPROJECT_TILE_H

namespace mylibrary {

// Represents a tile on the GameBoard
class Tile {
 private:
  int num_;
  bool null_tile_;
  int x;
  int y;

 public:
  Tile(int x, int y, int num, bool b);
  Tile(int x, int y, int num);

  bool GetNullTile();
  int GetX();
  int GetY();
  int GetNum();
  bool operator==(const Tile& rhs) const;

};

}  // namespace mylibrary


#endif  // FINALPROJECT_TILE_H
