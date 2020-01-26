/*
 * UI
 */
#include "SceneViewerWidgetOverlay.h"

#include <QHBoxLayout>
#include <QPainter>

SceneViewerWidgetOverlay::SceneViewerWidgetOverlay(QWidget *parentWidget) : QWidget(parentWidget) {
    //setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::ToolTip | Qt::WindowStaysOnTopHint);
    //setAttribute(Qt::WA_NoSystemBackground);
    //setAttribute(Qt::WA_TransparentForMouseEvents);
}

SceneViewerWidgetOverlay::~SceneViewerWidgetOverlay() { }

void SceneViewerWidgetOverlay::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setBrush(Qt::red);
  painter.drawRect(QRect(0, 0, 1000, 1000));
}
