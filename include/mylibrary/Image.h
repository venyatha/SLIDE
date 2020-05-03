//
// Created by Venyatha MANNE on 4/25/20.
//

#ifndef FINALPROJECT_IMAGE_H
#define FINALPROJECT_IMAGE_H

#include <cinder/Surface.h>
#include <cinder/gl/Context.h>

#include <string>

namespace mylibrary {

  std::vector<cinder::gl::Texture2dRef> MakeTextureVec(std::string filpath);

}  // namespace mylibrary

#endif  // FINALPROJECT_IMAGE_H
