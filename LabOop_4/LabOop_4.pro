QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    class_folder_facade/3DPoint.cpp \
    class_folder_facade/Facade.cpp \
    class_folder_facade/FacadeOperationResult.cpp \
    class_folder_facade/Figure.cpp \
    class_folder_facade/FileReader.cpp \
    class_folder_facade/NormalizationParametrs.cpp \
    class_folder_facade/QtSceneDrawer.cpp \
    class_folder_facade/Scene.cpp \
    class_folder_facade/TransformMatrix.cpp \
    class_folder_facade/TransformMatrixBuilder.cpp \
    class_folder_facade/Vertex.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    class_folder_facade/3DPoint.h \
    class_folder_facade/Basefilereader.h \
    class_folder_facade/Facade.h \
    class_folder_facade/FacadeOperationResult.h \
    class_folder_facade/Figure.h \
    class_folder_facade/FileReader.h \
    class_folder_facade/NormalizationParametrs.h \
    class_folder_facade/QtSceneDrawer.h \
    class_folder_facade/Scene.h \
    class_folder_facade/SceneDrawerBase.h \
    class_folder_facade/SceneObject.h \
    class_folder_facade/TransformMatrix.h \
    class_folder_facade/TransformMatrixBuilder.h \
    class_folder_facade/Vertex.h \
    library.h \
    mainwindow.h \
    operations.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
