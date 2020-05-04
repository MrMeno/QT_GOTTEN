QT       += core gui network

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
    main.cpp \
    components\close_label_btn.cpp \
           src\CorePageWindow.cpp \
           src\LoginWindow.cpp \
    util\CodeConstants.cpp \
            util\PublicHelper.cpp \
          util\HttpUtil.cpp

HEADERS += \
    components\close_label_btn.h \
           src\LoginWindow.h \
           src\CorePageWindow.h \
    util/CodeConstants.h \
         util\PublicHelper.h \
          util\HttpUtil.h

FORMS += \
    src\CorePageWindow.ui \
    src\LoginWindow.ui

TRANSLATIONS += \
    QT_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources\staics.qrc

OBJECTS_DIR  = tmp
MOC_DIR      = tmp

DISTFILES +=
