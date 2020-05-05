// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/GameBoard.h>

#include <string>
#include <cmath>
#include <random>

namespace mylibrary {

GameBoard::GameBoard(int size) {
  Reset(size);
}

void GameBoard::Reset(int num) {
  size_ = num;
  // construct the grid_
  std::vector<Tile> temp_vec(size_,Tile(0,0,0));
  std::vector<std::vector<Tile>> vec(size_,temp_vec);
  int count = 1;
  for (int y = 0; y < size_; y++) {
    for (int x = 0; x < size_; x++) {
      if (count == size_ * size_) {
        vec[x][y] = Tile(x,y,count, true);
      } else {
        vec[x][y] = Tile(x,y,count);
        count++;
      }
    }
  }
  grid_ = vec;
  // the solution is the initial grid
  solution_ = vec;
}

bool GameBoard::IsNullTile(int x, int y) { return grid_[x][y].GetNullTile(); }

void GameBoard::MoveTile(int x, int y, Direction dir) {
  // checks that the corresponding adjacent tile is null and if a legal move
  // is possible, moves the tile accordingly
  if (dir == Direction::kUp && y != 0 && IsNullTile(x,y-1)) {
    Tile temp = grid_[x][y - 1];
    grid_[x][y - 1] = grid_[x][y];
    grid_[x][y] = temp;

  } else if (dir == Direction::kDown && y != size_ - 1 && IsNullTile(x,y+1)) {
    Tile temp = grid_[x][y + 1];
    grid_[x][y + 1] = grid_[x][y];
    grid_[x][y] = temp;

  } else if (dir == Direction::kRight && x != size_ - 1 && IsNullTile(x+1,y)) {
    Tile temp = grid_[x+1][y];
    grid_[x+1][y] = grid_[x][y];
    grid_[x][y] = temp;

  } else if (dir == Direction::kRight && x != 0 && IsNullTile(x-1,y)) {
    Tile temp = grid_[x-1][y];
    grid_[x-1][y] = grid_[x][y];
    grid_[x][y] = temp;
  }
}

std::ostream& operator<<(std::ostream& os, GameBoard& gameBoard) {
  for (int i = 0; i < gameBoard.size_; i++) {
    for (int j = 0; j < gameBoard.size_; j++) {
      if (gameBoard.grid_[j][i].GetNum() == gameBoard.size_*gameBoard.size_) {
        // add a space for the null tile
        os << " ";
      } else {
        os << gameBoard.grid_[j][i].GetNum();
      }
    }
    // add a newline after each row in the grid
    os << "\n";
  }
  return os;
}

bool GameBoard::CheckWin() { return grid_ == solution_; }

void GameBoard::ShuffleBoard() {
  // use the random library to pick a random number of times to call MoveTile
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(1000.0, 3000.0);
  int r = ceil(dist(mt));

  for (int i = 0; i < r; i++) {
    int d = rand()%4;
    Direction dir;
    // assigns ints to the Direction enums
    if (d == 1) {
      dir = Direction::kDown;
    } else if (d == 2) {
      dir = Direction::kLeft;
    } else if (d == 3) {
      dir = Direction::kRight;
    } else {
      dir = Direction::kUp;
    }
    // picks a random int between 0 and size - 1
    int x = (rand()% size_);
    int y = (rand()% size_);
    MoveTile(x, y, dir);
  }
}

int GameBoard::GetSize() { return size_; }

std::vector<std::vector<Tile>> GameBoard::GetGrid() {return grid_;}

void GameBoard::SetGrid(std::vector<std::vector<Tile>> new_grid_) {
  grid_ = new_grid_;
}

// the functions below are used mainly for testing, to make sure a shuffled grid
// is solvable
// reference: https://www.sitepoint.com/randomizing-sliding-puzzle-tiles/
int GameBoard::CountInversions(int i, int j) {
  int inversions = 0;
  int tileNum = j * size_ + i;
  int lastTile = size_ * size_;
  int tileValue = grid_[i][j].GetY() * size_ + grid_[i][j].GetX();
  for (int q = tileNum + 1; q < lastTile; ++q) {
    int k = q % size_;
    int l = floor(q / size_);

    int compValue = grid_[k][l].GetY() * size_ + grid_[k][l].GetX();
    if (tileValue > compValue && tileValue != (lastTile - 1)) {
      ++inversions;
    }
  }
  return inversions;
}

int GameBoard::sumInversions() {
  int inversions = 0;
  for (int j = 0; j < size_; ++j) {
    for (int i = 0; i < size_; ++i) {
      inversions += CountInversions(i, j);
    }
  }
  return inversions;
}

int GameBoard::RowOfNullTile() {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      if (grid_[i][j].GetNullTile()) {
        return j + 1;
      }
    }
  }
  return 1;
}

bool GameBoard::IsSolvable() {
  if (size_ % 2 == 1) {
    return (sumInversions() % 2 == 0);
  } else {
    return ((sumInversions() + size_ - RowOfNullTile()) % 2 == 0);
  }
}

}  // namespace mylibrary

