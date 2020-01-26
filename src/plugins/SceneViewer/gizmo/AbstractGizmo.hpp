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
 * Copyright (c) 2008-2013 Ismail TARIM and the Ogitor Team
 * License: MIT
 * https://github.com/OGRECave/ogitor
 *
 * Icons and images owned by their respective owners
 */

#ifndef ABSTRACT_GIZMO_H
#define ABSTRACT_GIZMO_H

#include <OgreManualObject.h>

class AbstractGizmo : public Ogre::ManualObject {
public:
  explicit AbstractGizmo(const Ogre::String &name);
  virtual ~AbstractGizmo();

  void attachNode(Ogre::Node *node);
  void dettachNode() { mTargetNode = nullptr; }

  virtual bool mousePressed(const Ogre::Ray &) { return false; }
  virtual bool mouseMoved(const Ogre::Ray &) { return false; }
  virtual bool mouseReleased(const Ogre::Ray &) { return false; }

  virtual void _notifyCurrentCamera(Ogre::Camera *camera) override;

protected:
  virtual void render() {}

  Ogre::Node *mTargetNode = nullptr;
  Ogre::Camera *mCurrentCamera = nullptr;
};

#endif // ABSTRACT_GIZMO_H
