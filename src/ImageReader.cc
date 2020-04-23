// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/ImageReader.h>

#include <string>

namespace mylibrary {

void GridAreas(std::string filepath) {

  cinder::ImageSourceRef img = cinder::loadImage( "/Users/mannev1/Desktop/cinder_0.9.2_mac/"
                                                  "my-projects/final-project-vmanne3/assets/colourwheel.jpeg");

  cinder::Surface oldSurface = cinder::loadImage( "/Users/mannev1/Desktop/cinder_0.9.2_mac/"
                                               "my-projects/final-project-vmanne3/assets/colourwheel.jpeg");


  cinder::Surface newSurface( oldSurface.getWidth() / 3, oldSurface.getHeight() / 3, false );
  newSurface.copyFrom( oldSurface, newSurface.getBounds() );

  cinder::writeImage("/Users/mannev1/Desktop/cinder_0.9.2_mac/my-projects/final-project-vmanne3/assets/write.jpeg", newSurface);
  //cinder::writeImage("/Users/mannev1/Desktop/cinder_0.9.2_mac/my-projects/final-project-vmanne3/assets/write.jpeg", img);



}

}  // namespace mylibrary
