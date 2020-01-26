/*
 * @name UC Davis 3D Analyzer
 * @author Brad Lee & SiYi Meng
 * @version 1.00
 * @license GNU LGPL v3
 * @brief 3D model analysis of UC Davis utility usage
 *
 * QT and OCC integration:
 * Copyright (c) 2018 Shing Liu (eryar@163.com)
 * License: MIT
 * Source: https://github.com/eryar/occQt
 *
 * Data from OSIsoft and UC Davis
 *
 * Icons and images owned by their respective owners
 */

/*
 * UI
 */
#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
  ui.setupUi(this);
  SceneViewerWidget *sceneViewerWidget = new SceneViewerWidget(this);
  this->setObjectName("hi");
  sceneViewerWidget->setParent(this);

  // QWidget *sceneViewerWidget = new SceneViewerWidget(this);
  // QWidget *container = QWidget::createWindowContainer(mainView);
  // mainView->setParentWidget(container);
  // mainView->resize(1280, 960);
  // mainView->show();

  // sceneViewerWidget.setParent(this);
  setCentralWidget(sceneViewerWidget);

  // subView = new SubView(this);
  // subView->resize(1280 / 2, 960 / 2);
  // subView->show();
}
