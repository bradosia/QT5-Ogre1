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

#pragma once

// QT
#include <QApplication>

// QT5-OGRE3D UI
#include "mainWindow.h"

class Application final : public QApplication {
public:
  Application(int &argc, char **argv);
  ~Application();
private:
  MainWindow *w;
};
