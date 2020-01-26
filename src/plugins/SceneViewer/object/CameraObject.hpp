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

#pragma once

#include <OgreManualObject.h>

class CameraObject : public Ogre::ManualObject {
public:
  explicit CameraObject(const Ogre::String &name);
  virtual ~CameraObject();

  void attachCamera(Ogre::Camera *camera);
  void detachCamera();

protected:
  void render();

  Ogre::Camera *mCamera = nullptr;
};

class CameraObjectFactory : public Ogre::MovableObjectFactory {
public:
  static Ogre::String FACTORY_TYPE_NAME;

  CameraObjectFactory() {}
  ~CameraObjectFactory() {}

  const Ogre::String &getType(void) const override;
  void destroyInstance(Ogre::MovableObject *obj) override;

protected:
  Ogre::MovableObject *
  createInstanceImpl(const Ogre::String &name,
                     const Ogre::NameValuePairList *params) override;
};
