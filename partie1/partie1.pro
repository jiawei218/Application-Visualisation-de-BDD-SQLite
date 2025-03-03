QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    disconnecter.cpp \
    gestionutilisateur.cpp \
    main.cpp \
    mainwindow.cpp \
    profils.cpp \
    utilisateurs.cpp

HEADERS += \
    connection.h \
    disconnecter.h \
    gestionutilisateur.h \
    mainwindow.h \
    profils.h \
    utilisateurs.h

FORMS += \
    connection.ui \
    disconnecter.ui \
    gestionutilisateur.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
