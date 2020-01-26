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

enum ObjectType {
  ObjectType_None = 0x00,
  ObjectType_Model = 0x01,
  ObjectType_Grid = 0x01 << 1,
  ObjectType_Camera = 0x01 << 2,
  ObjectType_Gizmo = 0x01 << 3,
};
