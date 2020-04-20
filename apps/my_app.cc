// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <pretzel/PretzelGui.h>

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  auto img = cinder::loadImage(loadAsset("132927-ocean-clouds-sunset-purple-beach.jpg"));
  mTex = cinder::gl::Texture2d::create( img );

  mRadius = 25;
  gui = pretzel::PretzelGui::create("Puzzle settings");
  gui->setSize(cinder::vec2(10,10));
  gui->setPos(cinder::vec2(0,0));

  gui->addSlider("Puzzle Size", &mRadius, 2, 100);


  gui->addSaveLoad();
  gui->loadSettings();    // load the last saved settings automatically


  ci::gl::enableAlphaBlending();
}

void MyApp::update() {
}

void MyApp::draw() {
  cinder::gl::clear();
  cinder::gl::draw( mTex );


  cinder::gl::drawSolidCircle(cinder::vec2(getWindowCenter()), mRadius);

  gui->draw();



}

void MyApp::keyDown(KeyEvent event) {
  if (event.getChar() == 'g'){
    gui->toggleVisible();	// gui interaction will be disabled when invisible
  }

}

}  // namespace myapp
