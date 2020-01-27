#include "OgreWidget.hpp"
#include <OgreRenderWindow.h>
#include <OgreRoot.h>

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QPainter>
#include <QWidget>

OgreWidget::OgreWidget(QWidget *parentWidget_) : QWidget(parentWidget_) {
  initialize();
  installEventFilter(this);
}

OgreWidget::~OgreWidget() {
  Ogre::RenderSystem *rs = Ogre::Root::getSingletonPtr()->getRenderSystem();
  if (mRenderWindow && rs) {
    rs->destroyRenderWindow(mRenderWindow->getName());
  }
}

void OgreWidget::paintEvent(QPaintEvent *event) {
  if (!isVisible())
    return;
  static int count = 0;
  printf("===== DEBUG: Ogre Widget Render Window Size (%d,%d) =====\n",
         mRenderWindow->getWidth(), mRenderWindow->getHeight());
  printf("===== paintEvent: %d =====\n", count++);
  render();
}

void OgreWidget::resizeEvent(QResizeEvent *event) {
  if (!mRenderWindow)
    return;

  mRenderWindow->resize(width(), height());
  mRenderWindow->windowMovedOrResized();
  // widgetOverlay->resize(size());
}

void OgreWidget::render() { Ogre::Root::getSingletonPtr()->renderOneFrame(); }

void OgreWidget::renderLater() {
  // requestUpdate();
  render();
}

void OgreWidget::renderNow() {
  if (isVisible()) {
    mAnimating ? renderLater() : render();
    printf("===== DEBUG: EXPOSED! =====\n");
  }
}

bool OgreWidget::eventFilter(QObject *target, QEvent *event) {

  if (target == this) {
    if (event->type() == QEvent::Expose) {
      if (isVisible() && mRenderWindow) {
        mRenderWindow->windowMovedOrResized();
        renderNow();
      }
    }
  }

  return false;
}

void OgreWidget::initialize() {
  setAttribute(Qt::WA_NoBackground);
  setAttribute(Qt::WA_PaintOnScreen);

  Ogre::Root *mOgreRoot = Ogre::Root::getSingletonPtr();
  Ogre::RenderSystem *rs = mOgreRoot->getRenderSystem();

  Ogre::NameValuePairList params;

  if (rs->getName().find("GL") <= rs->getName().size()) {
    params["currentGLContext"] = Ogre::String("false");
  }

  Ogre::String handle = Ogre::StringConverter::toString(size_t(winId()));
  unsigned int w = static_cast<unsigned int>(this->width());
  unsigned int h = static_cast<unsigned int>(this->height());

#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
  params["externalWindowHandle"] =
      Ogre::StringConverter::toString((size_t)(this->winId()));
#else
#if QT_VERSION < 0x050000
  const QX11Info info = this->x11Info();
  Ogre::String winHandle;
  winHandle = Ogre::StringConverter::toString((unsigned long)(info.display()));
  winHandle += ":";
  winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
  winHandle += ":";
  winHandle += Ogre::StringConverter::toString((unsigned long)(this->winId()));
  winHandle += ":";
  winHandle += Ogre::StringConverter::toString((unsigned long)(info.visual()));

  params["externalWindowHandle"] = winHandle;

#elif QT_VERSION >= 0x050100 && defined(Q_WS_X11)
  const QX11Info info = this->x11Info();
  Ogre::String winHandle;
  winHandle = Ogre::StringConverter::toString((unsigned long)(info.display()));
  winHandle += ":";
  winHandle +=
      Ogre::StringConverter::toString((unsigned int)(info.appScreen()));
  winHandle += ":";
  winHandle += Ogre::StringConverter::toString((unsigned long)(this->winId()));

  params["externalWindowHandle"] = winHandle;
#else // only for the time between Qt 5.0 and Qt 5.1 when QX11Info was not
      // included
  params["externalWindowHandle"] =
      Ogre::StringConverter::toString((unsigned long)(this->winId()));
#endif
#endif

#if defined(Q_OS_MAC)
  params["macAPI"] = "cocoa";
  params["macAPICocoaUseNSView"] = "true";
#endif

  Ogre::String name = "RenderWindow #" + handle;
  mRenderWindow = mOgreRoot->createRenderWindow(name, w, h, false, &params);

  mRenderWindow->resize(width(), height());
  mRenderWindow->windowMovedOrResized();

  mRenderWindow->setVSyncEnabled(true);
  mRenderWindow->setVisible(true);

  mOgreRoot->addFrameListener(this);
}

//------------------------------------------------------------------------------------
QPaintEngine *OgreWidget::paintEngine() const {
  // We don't want another paint engine to get in the way for our Ogre based
  // paint engine. So we return nothing.
  return NULL;
}
