/*
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

//
// Map.h
//

#ifndef __MAP_H
#define __MAP_H

class MapMgr;
struct MapInfo;
class TerrainMgr;

#include "TerrainMgr.h"

struct Formation;

typedef struct
{
	uint32	id;//spawn ID
	uint32	entry;
	float	x;
	float	y;
	float	z;
	float	o;
	Formation* form;
	uint8 movetype;
	uint32 displayid;
	uint32 factionid;
	uint32 flags;
	uint32 bytes0;
	uint32 bytes1;
	uint32 bytes2;
	uint32 emote_state;
	//uint32 respawnNpcLink;
	uint16 channel_spell;
	uint32 channel_target_go;
	uint32 channel_target_creature;
	uint16 stand_state;
	uint32 death_state;
	uint32 MountedDisplayID;
	uint32 Item1SlotDisplay;
	uint32 Item2SlotDisplay;
	uint32 Item3SlotDisplay;
	uint32 CanFly;
	uint32 phase;

	/* sets one of the bytes of an uint32 */
	uint32 setbyte(uint32 buffer, uint8 index, uint32 byte){
    
	/* We don't want a segfault, now do we? */
	if(index >= 4)
	  return buffer;
  
	byte = byte << index*8;
	buffer = buffer | byte;
        
	return buffer;
	}
}CreatureSpawn;

typedef struct
{
	uint32	id;//spawn ID
	uint32	entry;
	float	x;
	float	y;
	float	z;
	float	o;
	float	o1;
	float	o2;
	float	o3;
	float	facing;
	uint32	flags;
	uint32	state;
	uint32	faction;
	//uint32 level;
	float scale;
	//uint32 stateNpcLink;
	uint32 phase;
	uint32 overrides;
} GOSpawn;

typedef std::vector<CreatureSpawn*> CreatureSpawnList;
typedef std::vector<GOSpawn*> GOSpawnList;

typedef struct
{
	CreatureSpawnList CreatureSpawns;
	GOSpawnList GOSpawns;
}CellSpawns;

class SERVER_DECL Map
{
public:
	Map(uint32 mapid, MapInfo * inf);
	~Map();

	WoWICE_INLINE string GetNameString() { return name; }
	WoWICE_INLINE const char* GetName() { return name.c_str(); }
	WoWICE_INLINE MapEntry* GetDBCEntry() { return me; }

	WoWICE_INLINE CellSpawns *GetSpawnsList(uint32 cellx,uint32 celly)
	{
		Wowice::Util::WOWICE_ASSERT(   cellx < _sizeX);
		Wowice::Util::WOWICE_ASSERT(   celly < _sizeY);
		if(spawns[cellx]== NULL) return NULL;

		return spawns[cellx][celly];
	}
	WoWICE_INLINE CellSpawns * GetSpawnsListAndCreate(uint32 cellx, uint32 celly)
	{
		Wowice::Util::WOWICE_ASSERT(   cellx < _sizeX);
		Wowice::Util::WOWICE_ASSERT(   celly < _sizeY);
		if(spawns[cellx]== NULL)
		{
			spawns[cellx] = new CellSpawns*[_sizeY];
			memset(spawns[cellx],0,sizeof(CellSpawns*)*_sizeY);
		}

		if(spawns[cellx][celly] == 0)
			spawns[cellx][celly] = new CellSpawns;
		return spawns[cellx][celly];
	}

	void LoadSpawns(bool reload);//set to true to make clean up
	uint32 CreatureSpawnCount;
	uint32 GameObjectSpawnCount;

	WoWICE_INLINE float  GetLandHeight(float x, float y)
	{ 
		if(_terrain)
		{
			return _terrain->GetLandHeight(x, y);
		}
		else
		{
			return 999999.0f;
		}
	}

	WoWICE_INLINE float  GetWaterHeight(float x, float y) 
	{ 
		if(_terrain)
		{ 
			return _terrain->GetWaterHeight(x, y); 
		}
		else
		{ 
			return 999999.0f; 
		}
	}

	WoWICE_INLINE uint8  GetWaterType(float x, float y)
	{
		if(_terrain)
		{ 
			return _terrain->GetWaterType(x, y);
		}
		else
		{ 
			return 0;
		}
	}

	WoWICE_INLINE uint8  GetWalkableState(float x, float y)
	{
		if(_terrain)
		{ 
			return _terrain->GetWalkableState(x, y);
		}
		else
		{ 
			return 1; 
		}
	}

	WoWICE_INLINE uint16 GetAreaID(float x, float y)
	{
		if(_terrain)
		{ 
			return _terrain->GetAreaID(x, y);
		}
		else
		{ 
			return 0xFFFF;
		}
	}

	WoWICE_INLINE void CellGoneActive(uint32 x, uint32 y)
	{ 
		if(_terrain)
		{ 
			_terrain->CellGoneActive(x,y);
		}
	}

	WoWICE_INLINE void CellGoneIdle(uint32 x,uint32 y)
	{ 
		if(_terrain)
		{ 
			_terrain->CellGoneIdle(x,y);
		}
	}

private:
	MapInfo *	   _mapInfo;
	TerrainMgr*	 _terrain;
	uint32 _mapId;
	string name;
	MapEntry * me;

	//new stuff
	CellSpawns **spawns[_sizeX];
public:
	CellSpawns staticSpawns;
};

#endif
