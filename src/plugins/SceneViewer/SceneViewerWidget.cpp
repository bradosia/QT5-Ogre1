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
#include "SceneViewerWidget.h"

// QT
#include <QObject>
#include <QPainter>
#include <QWidget>

SceneViewerWidget::SceneViewerWidget(QWidget *parentWidget_) {
  sceneViewerViewContainer =
      std::unique_ptr<QWidget>(QWidget::createWindowContainer(&mainView));
  // overlay.raise();
  layoutInner.addWidget(&overlay);
  sceneViewerViewContainer->setLayout(&layoutInner);
  layout.addWidget(sceneViewerViewContainer.get());
  this->setLayout(&layout);
#ifdef DEBUG
  // scene viewer widget -> Central Widget -> Main Window
  QWidget *parentWidgetTest;
  if (parentWidget_) {
    printf("===== DEBUG: PARENT METHOD #1 FOUND =====\n");
    parentWidgetTest = parentWidget_;
  }
  if (this->parent()) {
    printf("===== DEBUG: PARENT METHOD #2 FOUND =====\n");
  }
  if (this->parentWidget()) {
    printf("===== DEBUG: PARENT METHOD #3 FOUND =====\n");
    parentWidgetTest = this->parentWidget();
  }
  if (parentWidgetTest) {
    printf("===== DEBUG: PARENT NAME: %s =====\n",
           parentWidgetTest->objectName().toStdString().c_str());
    // find children
    QList<QObject *> testList = parentWidgetTest->children();
    unsigned int n = testList.length();
    for (unsigned int i = 0; i < n; i++) {
      QObject *childObject = testList.at(i);
      printf("===== DEBUG: PARENT CHILD #%d NAME: %s =====\n", i,
             childObject->objectName().toStdString().c_str());
    }
    // find specific widget
    QList<QWidget *> widgetList =
        parentWidgetTest->findChildren<QWidget *>("toolBar", Qt::FindDirectChildrenOnly);
    n = widgetList.length();
    for (unsigned int i = 0; i < n; i++) {
      QWidget *childWidget = widgetList.at(i);
      printf("===== DEBUG: PARENT CHILD #%d NAME: %s =====\n", i,
             childWidget->objectName().toStdString().c_str());
      childWidget->setFixedHeight(120);
    }
  }
#endif
  // mainView->show();
}

void SceneViewerWidget::paintEvent(QPaintEvent *event) {
  static int count = 0;
  qDebug("paintEvent, %d", count++);
  // mainView->renderNow();
  QPainter painter(this);
  mainView.rubberBandPaint(event, painter);
  painter.setBrush(Qt::green);
  painter.drawRect(QRect(0, 0, 1000, 1000));
}

void SceneViewerWidget::resizeEvent(QResizeEvent *event) {
  overlay.resize(size());
}
