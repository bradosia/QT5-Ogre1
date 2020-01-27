/*
 * UI
 */
#include "SceneViewerOverlay.hpp"

#include <QHBoxLayout>
#include <QPainter>

SceneViewerOverlay::SceneViewerOverlay(QWidget *parentWidget)
    : QWidget(parentWidget) {
  setWindowFlags(Qt::Widget | Qt::FramelessWindowHint |
                 Qt::WindowStaysOnTopHint);
  setAttribute(Qt::WA_TranslucentBackground, true);
  // setWindowFlags(Qt::FramelessWindowHint);
  // setAttribute(Qt::WA_TransparentForMouseEvents);
  // setAttribute(Qt::WA_TranslucentBackground, true);
  // setAutoFillBackground(false);
  // this->setFixedSize(QSize(100, 100));
}

SceneViewerOverlay::~SceneViewerOverlay() {}

void SceneViewerOverlay::paintEvent(QPaintEvent *event) {
  // QColor backgroundColor = palette().light().color();
  // backgroundColor.setAlpha(200);
  // QPainter customPainter(this);
  // customPainter.fillRect(rect(), backgroundColor);
  QPainter painter(this);

  painter.setCompositionMode(QPainter::CompositionMode_Source);
  painter.fillRect(event->rect(), Qt::transparent);

  //painter.setBrush(Qt::red);
  //painter.drawRect(QRect(0, 0, 100, 100));
  printf("===== DEBUG: Overlay (%d,%d,%d,%d) =====\n", event->rect().x(),
         event->rect().y(), event->rect().width(), event->rect().height());
}
