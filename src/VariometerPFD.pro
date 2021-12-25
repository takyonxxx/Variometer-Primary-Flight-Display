QT += core gui svg positioning sensors multimedia
QT += androidextras

CONFIG += mobility
MOBILITY += sensors

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VarioPFD
TEMPLATE = app

win32: DEFINES += WIN32 _WINDOWS _USE_MATH_DEFINES

win32:CONFIG(release, debug|release):    DEFINES += NDEBUG
else:win32:CONFIG(debug, debug|release): DEFINES += _DEBUG

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
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

