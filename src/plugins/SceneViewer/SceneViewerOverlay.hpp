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

#ifndef PLUGIN_SCENE_VIEWER_OVERLAY_H
#define PLUGIN_SCENE_VIEWER_OVERLAY_H

// c++
#include <string>

// QT5
#include <QPaintEvent>
#include <QWidget>

class SceneViewerOverlay : public QWidget {
  Q_OBJECT

public:
  SceneViewerOverlay(QWidget *parentWidget = nullptr);
  ~SceneViewerOverlay();

protected:
  void paintEvent(QPaintEvent *event);
};

#endif // PLUGIN_SCENE_VIEWER_OVERLAY_H
