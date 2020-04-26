// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/GameBoard.h>

#include <string>
#include <cmath>

namespace mylibrary {

GameBoard::GameBoard(int size) {
  board_size_ = size;

  std::vector<Tile> temp_vec(board_size_,Tile(0));
  std::vector<std::vector<Tile>> vec(board_size_,temp_vec);

  int count = 1;
  for (int y = 0; y < board_size_; y++) {
    for (int x = 0; x < board_size_; x++) {
      if (count == board_size_ * board_size_) {
        vec[x][y] = Tile(count, true);
      } else {
        vec[x][y] = Tile(count);
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
bool GameBoard::CheckWin() {
  if (grid_ == solution_) {
    return true;
  }
  return false;
}

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

void GameBoard::ShuffleGameBoard() {
  int r = rand()%100;
  for (int i = 0; i < r; i++) {
    Shuffle();
  }
}


}  // namespace mylibrary

/*
GameBoard::GameBoard(int boardSize) {
  board_size_ = boardSize;
  mode_ = "numbers";

  std::vector<int> one(boardSize,'0');
  std::vector<std::vector<int>> two(boardSize,one);

  int count = 0;
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      two[j][i] = count;
      count++;
    }
  }
  grid_ = two;
  current_grid_ = two;

  // the null tile is currently
  null_tile_x_ = board_size_ - 1;
  null_tile_y_ = board_size_ - 1;

}

GameBoard::GameBoard() {
  board_size_ = 3;
  mode_ = "default";
}
void GameBoard::MoveUp(int num) {
  for (int i = 0; i < board_size_; i++) {
    for (int j = 0; j < board_size_; j++) {
      if (grid_[j][i] == num) {
        if (i != 0) {
          grid_[j][i] = grid_[j][i - 1];
          grid_[j][i - 1] = num;
        }
      }
    }
  }
}

void GameBoard::MoveDown(int num) {
  for (int i = 0; i < board_size_; i++) {
    for (int j = 0; j < board_size_; j++) {
      if (grid_[j][i] == num) {
        if (i != board_size_ - 1) {
          grid_[j][i] = grid_[j][i + 1];
          grid_[j][i + 1] = num;
        }
      }
    }
  }
}
void GameBoard::MoveRight(int num){
  for (int i = 0; i < board_size_; i++) {
    for (int j = 0; j < board_size_; j++) {
      if (grid_[j][i] == num) {
        if (j != board_size_ - 1) {
          grid_[j][i] = grid_[j][i + 1];
          grid_[j][i + 1] = num;
        }
      }
    }
  }
}


void GameBoard::MoveTile(int x, int y, Direction dir) {
  if (dir == Direction::kUp && y != 0) {
    int temp = grid_[x][y];
    grid_[x][y] = grid_[x][y - 1];
    grid_[x][y - 1] = temp;

  } else if (dir == Direction::kDown && y != board_size_ - 1) {
    int temp = grid_[x][y];
    grid_[x][y] = grid_[x][y - 1];
    grid_[x][y - 1] = temp;
  }


}
*/
