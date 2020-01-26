/*
 * @name QT5-OGRE1
 * @author Brad Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Test application using QT5 and OGRE1
 *
 * Portions of this project:
 * Copyright (c) 2018 Naoto Kondo
 * License: MIT
 * https://github.com/buresu/OgreMockup
 *
 * Icons and images owned by their respective owners
 */

#ifndef PLUGIN_SCENE_VIEWER_WINDOW_OGRE_WINDOW_H
#define PLUGIN_SCENE_VIEWER_WINDOW_OGRE_WINDOW_H

// QT5-OGRE1 Config
#include "../../../core/config.hpp"

#include <OgreFrameListener.h>
#include <QWindow>

class OgreWindow : public QWindow, public Ogre::FrameListener {
  Q_OBJECT
public:
  explicit OgreWindow(QWidget *parentWidget, QWindow *parentWindow = nullptr);
  ~OgreWindow();

  virtual void render(QPainter *) {}
  virtual void render();

  virtual void renderLater();
  virtual void renderNow();

  Ogre::RenderWindow *renderWindow() const { return mRenderWindow; }

protected:
  virtual bool eventFilter(QObject *target, QEvent *event) override;

  virtual void initialize();

  bool mAnimating = false;
  Ogre::RenderWindow *mRenderWindow = nullptr;
};

#endif // PLUGIN_SCENE_VIEWER_WINDOW_OGRE_WINDOW_H
