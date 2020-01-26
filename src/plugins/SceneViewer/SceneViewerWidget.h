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
 * Copyright (c) 2008-2013 Ismail TARIM and the Ogitor Team
 * License: MIT
 * https://github.com/OGRECave/ogitor
 *
 * Icons and images owned by their respective owners
 */

#ifndef PLUGIN_SCENE_VIEWER_WIDGET_H
#define PLUGIN_SCENE_VIEWER_WIDGET_H

// QT5-OGRE1 Config
#include "../../core/config.hpp"

// c++
#include <algorithm> // std::find
#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

// QT5
#include <QPaintEvent>
#include <QHBoxLayout>

#include "SceneViewerView.hpp"
#include "../RenderViewer/RenderViewerView.hpp"
#include "SceneViewerWidgetOverlay.h"

class SceneViewerWidget : public QWidget {
  Q_OBJECT

public:
  SceneViewerWidget(QWidget *parentWidget_ = nullptr);
  ~SceneViewerWidget(){};
  void paintEvent(QPaintEvent *event);
  void resizeEvent(QResizeEvent *event);

private:
  // main window view
  SceneViewerView mainView{this};
  SceneViewerWidgetOverlay overlay{this};
  QHBoxLayout layout;
  QHBoxLayout layoutInner;
  std::unique_ptr<QWidget> sceneViewerViewContainer;
};
#endif // MAINWINDOW_H
