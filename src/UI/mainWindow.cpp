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
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  // UI
  ui.setupUi(this);
  // plugins
  // why does setObjectName() not seem to change the name
  this->setObjectName("testName");
  sceneViewerWidget = std::make_unique<SceneViewerWidget>(this);
  renderViewerWidget = std::make_unique<RenderViewerWidget>(this);
  // sceneViewerWidget->setParent(this);

  // QWidget *sceneViewerWidget = new SceneViewerWidget(this);
  // QWidget *container = QWidget::createWindowContainer(mainView);
  // mainView->setParentWidget(container);
  // mainView->resize(1280, 960);
  // mainView->show();

  // sceneViewerWidget.setParent(this);

  // find specific widget
  printf("===== DEBUG: ATTEMPTING TO FIND CENTRAL... =====\n");
  QList<QHBoxLayout *> widgetCentralWidgetList = this->findChildren<QHBoxLayout *>(
      "horizontalLayout", Qt::FindChildrenRecursively);
  if (!widgetCentralWidgetList.empty()) {
    printf("===== DEBUG: CENTRAL FOUND =====\n");
    QHBoxLayout *layout = widgetCentralWidgetList.at(0);
    layout->addWidget(sceneViewerWidget.get());
    layout->addWidget(renderViewerWidget.get());


    // layout->addWidget(sceneViewerWidget.get());

    // toolBarWidget->setFixedHeight(50);
    // toolBarWidget->setContentsMargins(10, 10, 10, 10);
  }

  // setCentralWidget(sceneViewerWidget.get());
}
