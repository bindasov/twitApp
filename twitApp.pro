#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T18:33:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = twitApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    userinformation.cpp \
    twitterclient.cpp \
    followersintersection.cpp

HEADERS  += mainwindow.h \
    userinformation.h \
    twitterclient.h \
    followersintersection.h

FORMS    += mainwindow.ui \
    userinformation.ui \
    followersintersection.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -ltwitcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -ltwitcurl
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -ltwitcurl

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/libtwitcurl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/libtwitcurl.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/twitcurl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/twitcurl.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libtwitcurl.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lcurl
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lcurl

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/libcurl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/libcurl.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/curl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/curl.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libcurl.a
