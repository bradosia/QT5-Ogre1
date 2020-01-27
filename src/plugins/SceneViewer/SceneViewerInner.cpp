#include "SceneViewerInner.hpp"

#include <QPainter>

SceneViewerInner::SceneViewerInner(QWidget *parentWidget_)
    : OgreWidget(parentWidget_), qRubberBand(0), parentWidget(parentWidget_),
      overlayWidget(0) {

  layoutInner = std::make_unique<QVBoxLayout>();
  widgetOverlay = std::make_unique<SceneViewerOverlay>(this);
  // setMargin is deprecated
  // layoutInner->setMargin(0);
  layoutInner->setContentsMargins(0, 0, 0, 0);
  layoutInner->setSpacing(0);
  layoutInner->addWidget(widgetOverlay.get());
  // widgetOverlay->raise();
  this->setLayout(layoutInner.get());

  Ogre::String sceneTypeName =
      Ogre::DefaultSceneManagerFactory::FACTORY_TYPE_NAME;
  Ogre::String sceneName = "Scene001";
  Ogre::Root *root = Ogre::Root::getSingletonPtr();

  if (root->hasSceneManager(sceneName)) {
    mSceneManager = root->getSceneManager(sceneName);
  } else {
    mSceneManager = root->createSceneManager(sceneTypeName, sceneName);
  }

  Ogre::SceneNode *childSceneNode =
      mSceneManager->getRootSceneNode()->createChildSceneNode();

  mCamera = mSceneManager->createCamera("MainCamera");
  mCamera->setNearClipDistance(0.1f);
  mCamera->setFarClipDistance(1000.0f);

  childSceneNode->setPosition(Ogre::Vector3(0.0f, 0.0f, 5.0f));
  childSceneNode->lookAt(Ogre::Vector3(0.0f, 0.0f, 0.0f), Ogre::Node::TS_WORLD);
  childSceneNode->attachObject(mCamera);

  mCameraController = new CameraController(childSceneNode);

  Ogre::Viewport *pViewPort = mRenderWindow->addViewport(mCamera);
  pViewPort->setBackgroundColour(Ogre::ColourValue(0.1f, 0.1f, 0.1f));

  printf("===== DEBUG: Init Render Window Size (%d,%d) =====\n",
         mRenderWindow->getWidth(), mRenderWindow->getHeight());
  // mRenderWindow->resize(100, 100);
  // mRenderWindow->windowMovedOrResized();
  mCamera->setAspectRatio(Ogre::Real(mRenderWindow->getWidth()) /
                          Ogre::Real(mRenderWindow->getHeight()));
  mCamera->setAutoAspectRatio(true);

  createScene();
}

SceneViewerInner::~SceneViewerInner() {
  if (mCameraController) {
    delete mCameraController;
  }
}

void SceneViewerInner::createScene() {

  mSceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

  Ogre::SceneNode *childSceneNode =
      mSceneManager->getRootSceneNode()->createChildSceneNode();

  //  auto dragon = mOgreSceneManager->createEntity("root", "root.mesh");
  //  childSceneNode->attachObject(dragon);

  AssimpSceneLoader loader(childSceneNode);

  qDebug() << loader.loadFile("CartoonFemale.05.obj");
  // qDebug() << loader.loadFile("fbx_specular/Apricot_02_hi_poly.fbx");

  //  qDebug() << loader.loadFile("test.blend");

  //  auto itr = childSceneNode->getChildIterator();
  //  while (itr.hasMoreElements()) {
  //    Ogre::SceneNode *node = reinterpret_cast<Ogre::SceneNode
  //    *>(itr.getNext()); qDebug() << node->getName().c_str(); auto itr2 =
  //    node->getAttachedObjectIterator(); while (itr2.hasMoreElements()) {
  //      Ogre::MovableObject *obj =
  //          reinterpret_cast<Ogre::MovableObject *>(itr2.getNext());
  //      qDebug() << obj->getName().c_str();
  //      if (mOgreSceneManager->hasCamera(obj->getName())) {

  //        Ogre::Camera *camera = reinterpret_cast<Ogre::Camera *>(obj);

  //        CameraObject *cameraObject = reinterpret_cast<CameraObject *>(
  //            mOgreSceneManager->createMovableObject(
  //                camera->getName() + "001",
  //                CameraObjectFactory::FACTORY_TYPE_NAME));
  //        cameraObject->attachCamera(camera);

  //        camera->getParentSceneNode()->attachObject(cameraObject);
  //      }
  //    }
  //  }

  Ogre::SceneNode *pLightNode =
      mSceneManager->getRootSceneNode()->createChildSceneNode();
  Ogre::Light *light = mSceneManager->createLight("MainLight");
  pLightNode->attachObject(light);
  pLightNode->setPosition(20.0f, -80.0f, 50.0f);

  // Camera Controller
  Ogre::SceneNode *centerSceneNode =
      mSceneManager->getRootSceneNode()->createChildSceneNode();

  mCameraController->setTargetNode(centerSceneNode);
  mCameraController->setCameraStyle(CameraController::CS_ORBIT);

  // Axis Grid Line
  AxisGridLineObject *axisGridLine =
      reinterpret_cast<AxisGridLineObject *>(mSceneManager->createMovableObject(
          "AxisGrid", AxisGridLineObjectFactory::FACTORY_TYPE_NAME));
  axisGridLine->addVisibilityFlags(ObjectType_Grid);

  Ogre::SceneNode *axisGridLineNode =
      mSceneManager->getRootSceneNode()->createChildSceneNode();
  axisGridLineNode->attachObject(axisGridLine);

  // Translate Gizmo
  Ogre::SceneNode *translateGizmoNode =
      mSceneManager->getRootSceneNode()->createChildSceneNode();

  mTranslateGizmo =
      reinterpret_cast<TranslateGizmo *>(mSceneManager->createMovableObject(
          "translateGizmo", TranslateGizmoFactory::FACTORY_TYPE_NAME));

  mTranslateGizmo->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
  mTranslateGizmo->setVisibilityFlags(ObjectType_Gizmo);

  translateGizmoNode->attachObject(mTranslateGizmo);
  translateGizmoNode->setPosition(0, 0, 0);

  // Rotate Gizmo
  Ogre::SceneNode *rotateGizmoNode =
      mSceneManager->getRootSceneNode()->createChildSceneNode();

  mRotateGizmo =
      reinterpret_cast<RotateGizmo *>(mSceneManager->createMovableObject(
          "rotateGizmo", RotateGizmoFactory::FACTORY_TYPE_NAME));

  mRotateGizmo->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
  mRotateGizmo->setVisibilityFlags(ObjectType_Gizmo);

  rotateGizmoNode->attachObject(mRotateGizmo);
  rotateGizmoNode->setPosition(-3, -3, -3);

  // Scale Gizmo
  Ogre::SceneNode *scaleGizmoNode =
      mSceneManager->getRootSceneNode()->createChildSceneNode();

  mScaleGizmo =
      reinterpret_cast<ScaleGizmo *>(mSceneManager->createMovableObject(
          "scaleGizmo", ScaleGizmoFactory::FACTORY_TYPE_NAME));

  mScaleGizmo->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
  mScaleGizmo->setVisibilityFlags(ObjectType_Gizmo);

  scaleGizmoNode->attachObject(mScaleGizmo);
  scaleGizmoNode->setPosition(-2, -1, 1);

  // Active Point
  //  Ogre::SceneNode *activePointNode =
  //      mOgreSceneManager->getRootSceneNode()->createChildSceneNode();

  //  ActivePointObject *activePoint = reinterpret_cast<ActivePointObject *>(
  //      mOgreSceneManager->createMovableObject(
  //          "activePoint", ActivePointObjectFactory::FACTORY_TYPE_NAME));

  //  activePointNode->attachObject(activePoint);

  setGizmoTarget(childSceneNode);

  mTranslateGizmo->setVisible(true);
  mRotateGizmo->setVisible(false);
  mScaleGizmo->setVisible(false);
}

void SceneViewerInner::setGizmoTarget(Ogre::SceneNode *node) {

  mGizmoTargetNode = node;

  mTranslateGizmo->attachNode(mGizmoTargetNode);
  mRotateGizmo->attachNode(mGizmoTargetNode);
  mScaleGizmo->attachNode(mGizmoTargetNode);
}

void SceneViewerInner::keyPressEvent(QKeyEvent *event) {

  if (event->key() == Qt::Key_1) {
    mTranslateGizmo->setVisible(true);
    mRotateGizmo->setVisible(false);
    mScaleGizmo->setVisible(false);
    mTranslateGizmo->attachNode(mGizmoTargetNode);
    mRotateGizmo->attachNode(mGizmoTargetNode);
    mScaleGizmo->attachNode(mGizmoTargetNode);
  } else if (event->key() == Qt::Key_2) {
    mTranslateGizmo->setVisible(false);
    mRotateGizmo->setVisible(true);
    mScaleGizmo->setVisible(false);
    mTranslateGizmo->attachNode(mGizmoTargetNode);
    mRotateGizmo->attachNode(mGizmoTargetNode);
    mScaleGizmo->attachNode(mGizmoTargetNode);
  } else if (event->key() == Qt::Key_3) {
    mTranslateGizmo->setVisible(false);
    mRotateGizmo->setVisible(false);
    mScaleGizmo->setVisible(true);
    mTranslateGizmo->attachNode(mGizmoTargetNode);
    mRotateGizmo->attachNode(mGizmoTargetNode);
    mScaleGizmo->attachNode(mGizmoTargetNode);
  } else if (event->key() == Qt::Key_Q) {
    if (auto camera = mSceneManager->getCamera("CameraView1")) {
      setGizmoTarget(camera->getParentSceneNode());
    }
  } else if (event->key() == Qt::Key_W) {
    if (auto camera = mSceneManager->getCamera("CameraView2")) {
      setGizmoTarget(camera->getParentSceneNode());
    }
  } else if (event->key() == Qt::Key_E) {
    if (auto camera = mSceneManager->getCamera("CameraView3")) {
      setGizmoTarget(camera->getParentSceneNode());
    }
  } else if (event->key() == Qt::Key_R) {
    if (auto camera = mSceneManager->getCamera("CameraView4")) {
      setGizmoTarget(camera->getParentSceneNode());
    }
  }

  if (mCameraController) {
    mCameraController->keyPressed(event);
    this->update();
  }
}

void SceneViewerInner::keyReleaseEvent(QKeyEvent *event) {
  if (mCameraController) {
    mCameraController->keyReleased(event);
    this->update();
  }
}

void SceneViewerInner::wheelEvent(QWheelEvent *event) {
  if (mCameraController) {
    mCameraController->mouseWheelRolled(event);
    this->update();
  }
}

void SceneViewerInner::mousePressEvent(QMouseEvent *event) {

  Ogre::Real x = Ogre::Real(event->windowPos().x()) / width();
  Ogre::Real y = Ogre::Real(event->windowPos().y()) / height();
  Ogre::Ray ray = mCamera->getCameraToViewportRay(x, y);

  if (mTranslateGizmo->mousePressed(ray)) {
    this->update();
    return;
  }

  if (mRotateGizmo->mousePressed(ray)) {
    this->update();
    return;
  }

  if (mScaleGizmo->mousePressed(ray)) {
    this->update();
    return;
  }

  if (mCameraController) {
    mCameraController->mousePressed(event);
    this->update();
  }

  if (Qt::LeftButton) {
    QPoint thePoint = event->pos();
    myXmin = thePoint.x();
    myYmin = thePoint.y();
    myXmax = thePoint.x();
    myYmax = thePoint.y();
    isDragging = 1;
  }
}

void SceneViewerInner::mouseMoveEvent(QMouseEvent *event) {
  Ogre::Real x = Ogre::Real(event->windowPos().x()) / width();
  Ogre::Real y = Ogre::Real(event->windowPos().y()) / height();
  Ogre::Ray ray = mCamera->getCameraToViewportRay(x, y);

  if (mTranslateGizmo->mouseMoved(ray)) {
    this->update();
    return;
  }

  if (mRotateGizmo->mouseMoved(ray)) {
    this->update();
    return;
  }

  if (mScaleGizmo->mouseMoved(ray)) {
    this->update();
    return;
  }

  if (mCameraController && (event->buttons() & Qt::LeftButton)) {
    mCameraController->mouseMoved(event);
    this->update();
  }

  QPoint thePoint = event->pos();
  myXmax = thePoint.x();
  myYmax = thePoint.y();

  if (Qt::LeftButton && isDragging == 1) {
    QPoint thePoint = event->pos();
    drawRubberBand(myXmin, myYmin, thePoint.x(), thePoint.y());
  }
}

void SceneViewerInner::mouseReleaseEvent(QMouseEvent *event) {

  Ogre::Real x = Ogre::Real(event->windowPos().x()) / width();
  Ogre::Real y = Ogre::Real(event->windowPos().y()) / height();
  Ogre::Ray ray = mCamera->getCameraToViewportRay(x, y);

  mTranslateGizmo->mouseReleased(ray);
  mRotateGizmo->mouseReleased(ray);
  mScaleGizmo->mouseReleased(ray);

  if (mCameraController) {
    mCameraController->mouseReleased(event);
    this->update();
  }

  Ogre::RaySceneQuery *pSceneQuery = mSceneManager->createRayQuery(ray);
  pSceneQuery->setSortByDistance(true);
  Ogre::RaySceneQueryResult vResult = pSceneQuery->execute();
  for (size_t ui = 0; ui < vResult.size(); ui++) {
    if (vResult[ui].movable) {

      //      qDebug() << reinterpret_cast<Ogre::ManualObject
      //      *>(vResult[ui].movable)
      //                      ->getName()
      //                      .c_str();

      //      reinterpret_cast<Ogre::ManualObject *>(vResult[ui].movable)
      //          ->getParentSceneNode()
      //          ->showBoundingBox(true);

      if (vResult[ui].movable->getMovableType().compare("Entity") == 0) {
      }
    }
  }

  mSceneManager->destroyQuery(pSceneQuery);

  // Hide the QRubberBand
  if (qRubberBand) {
    isDragging = 0;
    qRubberBand->hide();
    this->update();
  }
}

bool SceneViewerInner::frameRenderingQueued(
    const Ogre::FrameEvent &event) {
  if (mCameraController) {
    mCameraController->frameRendered(event);
  }
  return true;
}

void SceneViewerInner::drawRubberBand(const int minX, const int minY,
                                            const int maxX, const int maxY) {
  QRect aRect;

  // Set the rectangle correctly.
  (minX < maxX) ? (aRect.setX(minX)) : (aRect.setX(maxX));
  (minY < maxY) ? (aRect.setY(minY)) : (aRect.setY(maxY));

  aRect.setWidth(abs(maxX - minX));
  aRect.setHeight(abs(maxY - minY));

  if (!qRubberBand && widgetOverlay) {
    qRubberBand = new QRubberBand(QRubberBand::Rectangle, widgetOverlay.get());
    // setStyle is important, set to windows style will just draw
    // rectangle frame, otherwise will draw a solid rectangle.
    qRubberBand->setStyle(QStyleFactory::create("windows"));
  }

  if (qRubberBand) {
    qRubberBand->setGeometry(aRect);
    qRubberBand->show();
  }
}

void SceneViewerInner::rubberBandPaint(QPaintEvent *event, QPainter &p) {
  p.setPen(QPen(Qt::black, 2));
  if (myXmax > 10 && myYmax > 10) {
    p.drawText(myXmax, myYmax, QString("%1,%2").arg(myXmax).arg(myYmax));
  }
  p.drawText(2, 10, QString("%1,%2").arg(myXmax).arg(myYmax));
}

void SceneViewerInner::setParentWidget(QWidget *parentWidget_) {
  if (parentWidget_) {
    parentWidget = parentWidget_;
  }
}

void SceneViewerInner::setOverlayWidget(QWidget *overlayWidget_) {
  if (overlayWidget_) {
    overlayWidget = overlayWidget_;
  }
}
