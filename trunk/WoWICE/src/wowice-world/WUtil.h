#ifndef ARCWORLDUTILS__H
#define ARCWORLDUTILS__H

namespace WoWICE{
	
	// Common WoWICE world stuff
    class Util{
    public:
        SERVER_DECL static uint32 GUID_LOPART( uint64 GUID );
        SERVER_DECL static uint32 GUID_HIPART( uint64 GUID );
		static void WoWICE_ASSERT(   bool condition );
    };
}


#endif
