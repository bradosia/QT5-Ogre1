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

#ifndef PLUGIN_SCENE_VIEWER_INNER_H
#define PLUGIN_SCENE_VIEWER_INNER_H

#include "SceneViewerCommon.hpp"
#include "controller/CameraController.hpp"
#include "loader/AssimpSceneLoader.hpp"
#include "object/ActivePointObject.hpp"
#include "object/AxisGridLineObject.hpp"
#include "object/CameraObject.hpp"
#include "plugins/SceneViewer/gizmo/RotateGizmo.hpp"
#include "plugins/SceneViewer/gizmo/ScaleGizmo.hpp"
#include "plugins/SceneViewer/gizmo/TranslateGizmo.hpp"

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTechnique.h>
#include <OgreViewport.h>

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QRubberBand>
#include <QString>
#include <QStyleFactory>
#include <QToolBar>
#include <QTranslator>
#include <QTreeView>
#include <QVBoxLayout>

#include "SceneViewerOverlay.hpp"
#include "window/OgreWidget.hpp"

class CameraController;
class TranslateGizmo;
class RotateGizmo;
class ScaleGizmo;

class SceneViewerInner : public OgreWidget {
  Q_OBJECT
public:
  explicit SceneViewerInner(QWidget *parentWidget_ = nullptr);
  ~SceneViewerInner();

  float frameRate;

  void setParentWidget(QWidget *parentWidget_);
  void setOverlayWidget(QWidget *overlayWidget_);
  void rubberBandPaint(QPaintEvent *event, QPainter &p);

protected:
  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void keyReleaseEvent(QKeyEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  virtual bool frameRenderingQueued(const Ogre::FrameEvent &event) override;

  void createScene();

  void setGizmoTarget(Ogre::SceneNode *node);

  void drawRubberBand(const int minX, const int minY, const int maxX,
                      const int maxY);

  Ogre::SceneManager *mSceneManager = nullptr;
  Ogre::Camera *mCamera = nullptr;
  CameraController *mCameraController = nullptr;

  // Gizmo
  Ogre::Node *mGizmoTargetNode = nullptr;
  TranslateGizmo *mTranslateGizmo = nullptr;
  RotateGizmo *mRotateGizmo = nullptr;
  ScaleGizmo *mScaleGizmo = nullptr;

  //! save the mouse position.
  int myXmin = 0;
  int myYmin = 0;
  int myXmax = 0;
  int myYmax = 0;
  int isDragging = 0;

  //! rubber rectangle for the mouse selection.
  QRubberBand *qRubberBand;
  QWidget *parentWidget;
  QWidget *overlayWidget;

private:
  std::unique_ptr<SceneViewerOverlay> widgetOverlay;
  std::unique_ptr<QVBoxLayout> layoutInner;
};

#endif // PLUGIN_SCENE_VIEWER_INNER_H
