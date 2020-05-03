// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/GameBoard.h>

#include <string>
#include <cmath>
#include <random>

namespace mylibrary {

GameBoard::GameBoard(int size) {
  board_size_ = size;

  std::vector<Tile> temp_vec(board_size_,Tile(0,0,0));
  std::vector<std::vector<Tile>> vec(board_size_,temp_vec);

  int count = 1;
  for (int y = 0; y < board_size_; y++) {
    for (int x = 0; x < board_size_; x++) {
      if (count == board_size_ * board_size_) {
        vec[x][y] = Tile(x,y,count, true);
      } else {
        vec[x][y] = Tile(x,y,count);
        count++;
      }
    }
  }
  grid_ = vec;
  solution_ = vec;
  //ShuffleBoard();

}

void GameBoard::Reset(int num) {
  board_size_ = num;

  std::vector<Tile> temp_vec(board_size_,Tile(0,0,0));
  std::vector<std::vector<Tile>> vec(board_size_,temp_vec);

  int count = 1;
  for (int y = 0; y < board_size_; y++) {
    for (int x = 0; x < board_size_; x++) {
      if (count == board_size_ * board_size_) {
        vec[x][y] = Tile(x,y,count, true);
      } else {
        vec[x][y] = Tile(x,y,count);
        count++;
      }
    }
  }
  grid_ = vec;
  solution_ = vec;
}

bool GameBoard::IsNullTile(int x, int y) {
  return grid_[x][y].null_tile_;
}

void GameBoard::MoveTile(int x, int y, Direction dir) {

  if (dir == Direction::kUp && y != 0 && IsNullTile(x,y-1)) {
    Tile temp = grid_[x][y - 1];
    grid_[x][y - 1] = grid_[x][y];
    grid_[x][y] = temp;

  } else if (dir == Direction::kDown && y != board_size_ - 1 && IsNullTile(x,y+1)) {
    Tile temp = grid_[x][y + 1];
    grid_[x][y + 1] = grid_[x][y];
    grid_[x][y] = temp;

  } else if (dir == Direction::kRight && x != board_size_ - 1 && IsNullTile(x+1,y)) {
    Tile temp = grid_[x+1][y];
    grid_[x+1][y] = grid_[x][y];
    grid_[x][y] = temp;

  } else if (dir == Direction::kRight && x != 0 && IsNullTile(x-1,y)) {
    Tile temp = grid_[x-1][y];
    grid_[x-1][y] = grid_[x][y];
    grid_[x][y] = temp;
  }

}

std::ostream& operator<<(std::ostream& os, const GameBoard& gameBoard) {
  for (int i = 0; i < gameBoard.board_size_; i++) {
    for (int j = 0; j < gameBoard.board_size_; j++) {
      os << gameBoard.grid_[j][i].num_;
    }
    os << "\n";
  }
  return os;
}
bool GameBoard::CheckWin() { return grid_ == solution_; }

void GameBoard::SwapTiles(int i, int j, int k, int l) {
  Tile temp = grid_[i][j];
  grid_[i][j] = grid_[k][l];
  grid_[k][l] = temp;
}

void GameBoard::Shuffle() {
  for (int i = 0; i < board_size_; ++i) {
    for (int j = 0; j < board_size_; ++j) {
      int k = floor(rand()%board_size_);
      int l = floor(rand()%board_size_);
      SwapTiles(i, j, k, l);
    }
  }
}

void GameBoard::ShuffleBoard() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(1000.0, 3000.0);

  int r = ceil(dist(mt));

  for (int i = 0; i < r; i++) {

    int d = rand()%4;
    Direction dir;
    if (d == 1) {
      dir = Direction::kDown;
    } else if (d == 2) {
      dir = Direction::kLeft;
    } else if (d == 3) {
      dir = Direction::kRight;
    } else {
      dir = Direction::kUp;
    }

    int x = (rand()%board_size_);
    int y = (rand()%board_size_);

    MoveTile(x, y, dir);
  }


}

void GameBoard::ShuffleGameBoard() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(1.0, 1000.0);

  int r = ceil(dist(mt));

  for (int i = 0; i < r; i++) {
    ShuffleBoard();
  }

  std::cout << isSolvable() << std::endl;

}

int GameBoard::countInversions(int i, int j) {
  int inversions = 0;
  int tileNum = j * board_size_ + i;
  int lastTile = board_size_ * board_size_;
  int tileValue = grid_[i][j].y * board_size_ + grid_[i][j].x;
  for (int q = tileNum + 1; q < lastTile; ++q) {
    int k = q % board_size_;
    int l = floor(q / board_size_);

    int compValue = grid_[k][l].y * board_size_ + grid_[k][l].x;
    if (tileValue > compValue && tileValue != (lastTile - 1)) {
      ++inversions;
    }
  }
  return inversions;
}


int GameBoard::sumInversions() {
  int inversions = 0;
  for (int j = 0; j < board_size_; ++j) {
    for (int i = 0; i < board_size_; ++i) {
      inversions += countInversions(i, j);
    }
  }
  return inversions;
}

bool GameBoard::isSolvable() {
  return (sumInversions() % 2 == 0);
}


}  // namespace mylibrary

