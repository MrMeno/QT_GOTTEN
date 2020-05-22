#设置项目依赖核心类库，既QT对应安装目录下/include的两个类库文件夹
QT       += core gui network sql script axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#开发语言的版本
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# 条件编译 语法过期提醒
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#设置系统图标
RC_ICONS = \
      resources\img\logo.png
#项目结构
SOURCES += \
    components\bill_list_widget.cpp \
    main.cpp \
    components\close_label_btn.cpp \
    src/MaskWindow.cpp \
           src\CorePageWindow.cpp \
           src\LoginWindow.cpp \
    util\DllHelper.cpp \
    util\ScreenUtil.cpp \
    util\DataBase.cpp \
    util\CodeConstants.cpp \
            util\PublicHelper.cpp \
          util\HttpUtil.cpp \
    components\drag_win_widget.cpp \
    util\httpService.cpp \
    util\shdocvw.cpp \
    util/service/bankConfirmService.cpp \
    util/ScreenCaputredEvent.cpp

HEADERS += \
    components\bill_list_widget.h \
    components\close_label_btn.h \
    src/MaskWindow.h \
           src\LoginWindow.h \
           src\CorePageWindow.h \
    util\DllHelper.h \
    util\ScreenUtil.h \
    util\DataBase.h \
    util\CodeConstants.h \
         util\PublicHelper.h \
          util\HttpUtil.h \
    components\drag_win_widget.h \
    util\httpService.h \
    util\shdocvw.h \
    util/service/bankConfirmService.h \
    util/ScreenCaputredEvent.h

FORMS += \
    src/MaskWindow.ui \
    src\CorePageWindow.ui \
    src\LoginWindow.ui \

TRANSLATIONS += \
    QT_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources\staics.qrc
#项目生成后的文件依赖地址
OBJECTS_DIR  = tmp
MOC_DIR      = tmp

#自己添加的第三方c++库地址
INCLUDEPATH += $$quote(E:/OpenSSL-Win32/include)
LIBS +=$$quote(E:/OpenSSL-Win32/lib/libcrypto.lib)
LIBS +=$$quote(E:/OpenSSL-Win32/lib/libssl.lib)

