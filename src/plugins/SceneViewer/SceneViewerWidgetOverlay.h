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

#ifndef MAIN_VIEW_OVERLAY_H
#define MAIN_VIEW_OVERLAY_H

// c++
#include <algorithm> // std::find
#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

// QT
#include <QPaintEvent>

#include "SceneViewerView.hpp"
#include "../RenderViewer/RenderViewerView.hpp"

class SceneViewerWidgetOverlay : public QWidget {
  Q_OBJECT

public:
  SceneViewerWidgetOverlay(QWidget *parentWidget = nullptr);
  ~SceneViewerWidgetOverlay();

protected:
  void paintEvent(QPaintEvent *event);
};

#endif // MAIN_VIEW_OVERLAY_H
