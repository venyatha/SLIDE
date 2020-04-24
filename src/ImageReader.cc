// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/ImageReader.h>
#include <string>

namespace mylibrary {

void GridAreas(std::string filepath) {

  //cinder::ImageSourceRef img = cinder::loadImage( "/Users/mannev1/Desktop/cinder_0.9.2_mac/"
  //                                                "my-projects/final-project-vmanne3/assets/colourwheel.jpeg");

  cinder::Surface oldSurface = cinder::loadImage( "/Users/mannev1/Desktop/cinder_0.9.2_mac/"
                                               "my-projects/final-project-vmanne3/assets/colourwheel.jpeg");

  cinder::Surface newSurface( (oldSurface.getWidth() / 3), (oldSurface.getHeight() / 3), false );
  cinder::Area area(200, 200, 600,600);
  newSurface.copyFrom( oldSurface, area);
  cinder::writeImage("/Users/mannev1/Desktop/cinder_0.9.2_mac/my-projects/final-project-vmanne3/assets/crop.jpeg", newSurface);

  /*
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cinder::Surface newSurface( (oldSurface.getWidth() / 3), (oldSurface.getHeight() / 3), false );

      cinder::ivec2 vec(oldSurface.getWidth()*j, oldSurface.getHeight()*i);

      cinder::Area area(oldSurface.getWidth()*j,
                        oldSurface.getHeight()*i,
                        oldSurface.getWidth()*(j+1),
                        oldSurface.getHeight()*(i+1));

      newSurface.copyFrom( oldSurface, area);
      std::string num = std::to_string(count);

      cinder::writeImage("/Users/mannev1/Desktop/cinder_0.9.2_mac/my-projects/final-project-vmanne3/assets/write"
                         + num + ".jpeg", newSurface);

      count++;
    }
  }
   */

  /*
   * cinder::Area area(oldSurface.getWidth()*j,
          oldSurface.getHeight()*i,
          oldSurface.getWidth()*(j+1),
          oldSurface.getHeight()*(i+1));
   */
  /*
  for (int i = 0; i < 9; i++) {
    cinder::Surface newSurface( (oldSurface.getWidth() / 3), oldSurface.getHeight() / 3, false );

    newSurface.copyFrom( oldSurface, newSurface.getBounds());
    std::string num = std::to_string(i);

    cinder::writeImage("/Users/mannev1/Desktop/cinder_0.9.2_mac/my-projects/final-project-vmanne3/assets/write"
    + num + ".jpeg", newSurface);
  }
  */
  //cinder::Surface newSurface( oldSurface.getWidth() / 3, oldSurface.getHeight(), false );
  //newSurface.copyFrom( oldSurface, newSurface.getBounds() );

  //cinder::writeImage("/Users/mannev1/Desktop/cinder_0.9.2_mac/my-projects/final-project-vmanne3/assets/write.jpeg", newSurface);
  //cinder::writeImage("/Users/mannev1/Desktop/cinder_0.9.2_mac/my-projects/final-project-vmanne3/assets/write.jpeg", img);



}

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
}

GameBoard::GameBoard() {
  board_size_ = 3;
  mode_ = "default";
}
void GameBoard::Move(int x, int y, std::string direction) {
}


}  // namespace mylibrary
