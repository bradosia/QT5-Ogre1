#include "Application.hpp"

// plugins
#include "../plugins/SceneViewer/controller/CameraController.hpp"
#include "../plugins/SceneViewer/gizmo/RotateGizmo.hpp"
#include "../plugins/SceneViewer/gizmo/ScaleGizmo.hpp"
#include "../plugins/SceneViewer/gizmo/TranslateGizmo.hpp"
#include "../plugins/SceneViewer/object/ActivePointObject.hpp"
#include "../plugins/SceneViewer/object/AxisGridLineObject.hpp"
#include "../plugins/SceneViewer/object/CameraObject.hpp"

// QT
#include <QDebug>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QStandardPaths>

// OGRE
#include <RenderSystems/GL/OgreGLPlugin.h>
#include <RenderSystems/GL3Plus/OgreGL3PlusPlugin.h>
#include <OgreRoot.h>
#include <OgreTextureManager.h>
#include <OgreConfigFile.h>

Application::Application(int &argc, char **argv) : QApplication(argc, argv) {

  // Ogre Initialize
  Ogre::Root *root =
      new Ogre::Root(Ogre::BLANKSTRING, Ogre::BLANKSTRING, Ogre::BLANKSTRING);

#if defined(OGRE_STATIC)
  root->installPlugin(new Ogre::GLPlugin);
  root->installPlugin(new Ogre::GL3PlusPlugin);
#else
  root->loadPlugin("RenderSystem_GL");
  root->loadPlugin("RenderSystem_GL3Plus");
#endif

  root->addMovableObjectFactory(new AxisGridLineObjectFactory);
  root->addMovableObjectFactory(new ActivePointObjectFactory);
  root->addMovableObjectFactory(new CameraObjectFactory);
  root->addMovableObjectFactory(new TranslateGizmoFactory);
  root->addMovableObjectFactory(new RotateGizmoFactory);
  root->addMovableObjectFactory(new ScaleGizmoFactory);

  auto resLocation =
      QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)
          .back();

  // Qt 5.9+ Bug...
  resLocation.replace(".app", ".app/");

  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
      resLocation.toStdString(), "FileSystem",
      Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);

  const Ogre::RenderSystemList &rsList = root->getAvailableRenderers();
  Ogre::RenderSystem *rs = rsList[0];

  Ogre::StringVector renderOrder;
  renderOrder.push_back("OpenGL");
  renderOrder.push_back("OpenGL 3+");

  for (auto itr = renderOrder.begin(); itr != renderOrder.end(); itr++) {
    for (auto it = rsList.begin(); it != rsList.end(); it++) {
      if ((*it)->getName().find(*itr) != Ogre::String::npos) {
        rs = *it;
        break;
      }
    }
    if (rs != nullptr)
      break;
  }

  if (rs == nullptr) {
    QMessageBox::critical(nullptr, "Error", "RenderSystem is not found");
    quit();
  }

  rs->setConfigOption("Full Screen", "No");
  root->setRenderSystem(rs);
  root->initialise(false);

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(0);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  //  QWidget *mainwindow = new QWidget();

  //  QHBoxLayout *layout = new QHBoxLayout(mainwindow);

  //  MainView *view = new MainView;
  //  QWidget *container = QWidget::createWindowContainer(view, mainwindow);

  //  layout->addWidget(container);
  //  mainwindow->setLayout(layout);

  //  mainwindow->show();

  w = new MainWindow();
  w->show();
}

Application::~Application() {}
