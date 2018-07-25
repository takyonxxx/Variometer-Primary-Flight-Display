<<<<<<< HEAD
#-------------------------------------------------
#
# Project created by QtCreator 2013-09-24T17:03:18
#
#-------------------------------------------------

QT       += core gui svg positioning sensors multimedia
QT += androidextras

CONFIG += mobility
CONFIG += force_debug_info
#CONFIG += c++11
MOBILITY += sensors
#MOBILITY += location sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = VarioPFD
TEMPLATE = app

#-------------------------------------------------

win32: DEFINES += WIN32 _WINDOWS _USE_MATH_DEFINES

win32:CONFIG(release, debug|release):    DEFINES += NDEBUG
else:win32:CONFIG(debug, debug|release): DEFINES += _DEBUG

#-------------------------------------------------

INCLUDEPATH += ./

#-------------------------------------------------

HEADERS += \   
    MainWindow.h \   
    KalmanFilter.h \
    PiecewiseLinearFunction.h \    
    LayoutSquare.h \
    qfi_PFD.h \
    WidgetPFD.h \
    Generator.h \
    BeepThread.h \
    SettingsDialog.h

SOURCES += \   
    main.cpp \
    MainWindow.cpp \   
    KalmanFilter.cpp \
    PiecewiseLinearFunction.cpp \   
    LayoutSquare.cpp \   
    qfi_PFD.cpp \
    WidgetPFD.cpp \
    Generator.cpp \
    BeepThread.cpp \
    SettingsDialog.cpp

FORMS += \
    MainWindow.ui \
    WidgetPFD.ui

RESOURCES += \
    qfi.qrc

winrt: WINRT_MANIFEST.capabilities_device += location

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

=======
#-------------------------------------------------
#
# Project created by QtCreator 2013-09-24T17:03:18
#
#-------------------------------------------------

QT       += core gui svg positioning sensors multimedia
QT += androidextras

CONFIG += mobility
CONFIG += force_debug_info
#CONFIG += c++11
MOBILITY += sensors
#MOBILITY += location sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = VarioPFD
TEMPLATE = app

#-------------------------------------------------

win32: DEFINES += WIN32 _WINDOWS _USE_MATH_DEFINES

win32:CONFIG(release, debug|release):    DEFINES += NDEBUG
else:win32:CONFIG(debug, debug|release): DEFINES += _DEBUG

#-------------------------------------------------

INCLUDEPATH += ./

#-------------------------------------------------

HEADERS += \   
    MainWindow.h \   
    KalmanFilter.h \
    PiecewiseLinearFunction.h \    
    LayoutSquare.h \
    qfi_PFD.h \
    WidgetPFD.h \
    Generator.h \
    BeepThread.h \
    SettingsDialog.h

SOURCES += \   
    main.cpp \
    MainWindow.cpp \   
    KalmanFilter.cpp \
    PiecewiseLinearFunction.cpp \   
    LayoutSquare.cpp \   
    qfi_PFD.cpp \
    WidgetPFD.cpp \
    Generator.cpp \
    BeepThread.cpp \
    SettingsDialog.cpp

FORMS += \
    MainWindow.ui \
    WidgetPFD.ui

RESOURCES += \
    qfi.qrc

winrt: WINRT_MANIFEST.capabilities_device += location

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
>>>>>>> 21491701d214685c2f64806df2193c14a5320ca8
