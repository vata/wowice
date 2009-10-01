INCLUDES = -I$(top_srcdir)/src/wowice-logonserver \
   -I$(top_srcdir)/src/wowice-realmserver -I$(top_srcdir)/src/wowice-shared -I$(top_srcdir)/src/wowice-voicechat \
   -I$(top_srcdir)/src/wowice-world -I$(srcdir) -I$(srcdir)/../../../../dep/include \
   -I$(srcdir)/../../../../dep/src -I$(srcdir)/../../../../src

AM_CXXFLAGS = -DSCRIPTLIB

lib_LTLIBRARIES = libMoonMiscScripts.la

libMoonMiscScripts_la_SOURCES = Creatures.cpp \
GameObjectTeleportTable.cpp \
GameObjects.cpp \
RandomScripts.cpp \
QuelDanasPortal.cpp \
WyrmrestTemple.cpp \
EbonHold.cpp \
Logride_GrizzlyHills.cpp \
Setup.cpp
