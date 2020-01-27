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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

// QT5-OGRE1 Config
#include "../core/config.hpp"

// c++
#include <algorithm> // std::find
#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

// plugins
#include "../plugins/SceneViewer/SceneViewerWidget.hpp"
#include "../plugins/RenderViewer/RenderViewerWidget.hpp"

// QT5-OGRE1 UI
#include "ui_main.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow(){};

private:
  // ui
  Ui::main ui;

  // widgets
  std::unique_ptr<SceneViewerWidget> sceneViewerWidget;
  std::unique_ptr<RenderViewerWidget> renderViewerWidget;
};
#endif // MAIN_WINDOW_H
