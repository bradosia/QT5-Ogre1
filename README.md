# QT5 and Ogre1
Test application using QT5 and OGRE1

# Dependencies
- Qt >= 5.9
- Ogre >= 1.10
- Assimp >= 4.0

# Features
- Load scenes with Assimp
- Ogre rendering contained in a QT5 widget
- Ogre based Gizmos

# Build

Only tested for MSYS2/minGW.

Shared Only:

```shell
cmake -G "MSYS Makefiles" -B build -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON
```

Static Only:

```shell
cmake -G "MSYS Makefiles" -B build -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON
```
