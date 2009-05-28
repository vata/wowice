INCLUDES += -I$(srcdir) -I$(srcdir)/../wowice-shared

bin_PROGRAMS = wowice-logonserver

wowice_logonserver_SOURCES = \
	AccountCache.cpp \
	AccountCache.h \
	AuthSocket.cpp \
	AuthSocket.h \
	AuthStructs.h \
	LogonCommServer.cpp \
	LogonCommServer.h \
	LogonConsole.cpp \
	LogonConsole.h \
	LogonOpcodes.cpp \
	LogonOpcodes.h \
	LogonStdAfx.cpp \
	LogonStdAfx.h \
	AutoPatcher.h \
	AutoPatcher.cpp \
	Main.cpp \
	Main.h \
	PeriodicFunctionCall_Thread.h

wowice_logonserver_LDADD = -lshared -lz
wowice_logonserver_LDFLAGS = -L$(srcdir)/../wowice-shared
