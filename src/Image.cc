//
// Created by Venyatha MANNE on 4/25/20.
//

#include "mylibrary/Image.h"
#include <mylibrary/GameBoard.h>

#include "cinder/gl/Texture.h"
#include <string>

namespace mylibrary {

cinder::gl::Texture2dRef MakeText(cinder::Surface& surface, int x, int y) {
  cinder::Surface s(267,200,false);
  for (int i = 0; i < 267; i++) {
    for (int j = 0; j < 200; j++) {
      s.setPixel(cinder::ivec2(i,j),surface.getPixel(cinder::ivec2(i+x,j+y)));
    }
  }
  cinder::gl::TextureRef texture = cinder::gl::Texture2d::create(s);
  return texture;
}

std::vector<cinder::gl::Texture2dRef> MakeTextureVec(std::string filepath) {
  cinder::Surface surface(cinder::loadImage(filepath));

  std::vector<cinder::gl::Texture2dRef> toReturn;

  for (int y = 0; y < 600; y = y+200) {
    for (int x = 0; x < 801; x = x+267) {
      toReturn.push_back(MakeText(surface, x,y));
    }
  }
  return toReturn;
}


}  // namespace mylibrary