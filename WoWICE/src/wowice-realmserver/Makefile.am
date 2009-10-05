INCLUDES += -I$(srcdir) -I$(srcdir)/../wowice-shared

bin_PROGRAMS = wowice-realmserver

wowice_realmserver_SOURCES = \
ClientManager.h \
ClusterManager.h \
LogonCommClient.h \
LogonCommHandler.h \
Master.h \
ObjectStorage.h \
RStdAfx.h \
Session.h \
Structures.h \
WorkerOpcodes.h \
WorkerServer.h \
WorkerServerSocket.h \
WorldSocket.h \
CharacterHandler.cpp \
ClientManager.cpp \
ClusterManager.cpp \
LogonCommClient.cpp \
LogonCommHandler.cpp \
Master.cpp \
ObjectStorage.cpp \
QueryHandler.cpp \
RStdAfx.cpp \
Session.cpp \
WorkerServer.cpp \
WorkerServerSocket.cpp \
WorldSocket.cpp 
	
wowice_realmserver_LDADD = -lshared -lz

wowice_realmserver_LDFLAGS = -L$(srcdir)/../wowice-shared \
               -L/usr/lib
               
