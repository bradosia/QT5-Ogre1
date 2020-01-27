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
#include "SceneViewerWidget.hpp"

// QT
#include <QObject>
#include <QPainter>
#include <QWidget>

SceneViewerWidget::SceneViewerWidget(QWidget *parentWidget_) {
  layout = std::make_unique<QVBoxLayout>();
  widgetInner = std::make_unique<SceneViewerInner>(this);

  //setAttribute(Qt::WA_NoBackground);
  //setAttribute(Qt::WA_PaintOnScreen);

  layout->setMargin(0);
  layout->addWidget(widgetInner.get());
  this->setLayout(layout.get());

#ifdef DEBUG_SCENE_VIEWER_WIDGET_PARENT
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
    QList<QWidget *> widgetList = parentWidgetTest->findChildren<QWidget *>(
        "centralWidget", Qt::FindDirectChildrenOnly);

    // find specific widget
    QList<QWidget *> widgetToolBarList =
        parentWidgetTest->findChildren<QWidget *>("toolBar",
                                                  Qt::FindDirectChildrenOnly);
    if (!widgetToolBarList.empty()) {
      QWidget *toolBarWidget = widgetList.at(0);
      //toolBarWidget->setFixedHeight(50);
      //toolBarWidget->setContentsMargins(10, 10, 10, 10);
    }

    n = widgetList.length();
    for (unsigned int i = 0; i < n; i++) {
      QWidget *childWidget = widgetList.at(i);
      printf("===== DEBUG: PARENT FIND #%d NAME: %s =====\n", i,
             childWidget->objectName().toStdString().c_str());
      // childWidget->setFixedHeight(100);
      // find widget children
      QList<QObject *> widgetChildList = childWidget->children();
      unsigned int n = widgetChildList.length();
      for (unsigned int i = 0; i < n; i++) {
        QObject *widgetChildObject = widgetChildList.at(i);
        printf("===== DEBUG: FIND WIDGET CHILD #%d NAME: %s =====\n", i,
               widgetChildObject->objectName().toStdString().c_str());
      }
    }
  }
#endif
  // mainView->show();
}

void SceneViewerWidget::paintEvent(QPaintEvent *event) {
  static int count = 0;
  printf("DEBUG: SceneViewerContainer paintEvent: %d\n", count++);
  QPainter painter(this);
  painter.setBrush(Qt::blue);
  painter.drawRect(QRect(0, 0, 200, 100));
  // widgetInner->renderNow();
  // widgetInner->rubberBandPaint(event, painter);
}

void SceneViewerWidget::resizeEvent(QResizeEvent *event) {
  //widgetOverlay->resize(size());
}
