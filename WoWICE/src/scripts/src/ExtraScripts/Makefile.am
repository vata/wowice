INCLUDES = -I$(top_srcdir)/src/wowice-logonserver \
   -I$(top_srcdir)/src/wowice-realmserver -I$(top_srcdir)/src/wowice-shared -I$(top_srcdir)/src/wowice-voicechat \
   -I$(top_srcdir)/src/wowice-world -I$(srcdir) -I$(srcdir)/../../../../dep/include \
   -I$(srcdir)/../../../../dep/src -I$(srcdir)/../../../../src
INCLUDES += -I$(srcdir)/../../../wowice-shared/g3dlite -I$(srcdir)/../../../wowice-shared/vmap

AM_CXXFLAGS = -DSCRIPTLIB

lib_LTLIBRARIES = libExtraScripts.la

libExtraScripts_la_SOURCES = NeutralGuards.cpp Setup.cpp
