//
// Created by Venyatha MANNE on 4/25/20.
//

#include "mylibrary/Image.h"

#include <mylibrary/GameBoard.h>

#include "cinder/gl/Texture.h"
#include <string>

namespace mylibrary {

/*
cinder::gl::Texture2dRef MakeTexture(int x, int y) {
  cinder::Surface s(300,200,false);
  for (int i = 0; i < 300; i++) {
    for (int j = 0; j < 200; j++) {
      s.setPixel(cinder::ivec2(i,j),surface.getPixel(cinder::ivec2(i+x,j+y)));
    }
  }
  cinder::gl::TextureRef texture = cinder::gl::Texture2d::create(s);
  return texture;
}

std::vector<cinder::gl::Texture2dRef> MakeTexturesVec(std::string filepath) {
  surface = cinder::Surface(cinder::loadImage(filepath));
  std::vector<cinder::gl::Texture2dRef> toReturn;

  for (int x = 0; x <= 900; x = x+300) {
    for (int y = 0; y <= 600; y = y+200) {
      toReturn.push_back(MakeTexture(x,y));
    }
  }

  return toReturn;
}
*/



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
}  // namespace mylibrary