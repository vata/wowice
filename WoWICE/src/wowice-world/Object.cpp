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

#include "StdAfx.h"
#include "Unit.h"
using namespace std;

//#define DEG2RAD (M_PI/180.0)
#define M_PI		3.14159265358979323846
#define M_H_PI		1.57079632679489661923
#define M_Q_PI		0.785398163397448309615

void Object::SetRotation( uint64 guid )
{
	WorldPacket data(SMSG_AI_REACTION, 12);
	data << guid;
	data << uint32(2);
	SendMessageToSet(&data, false);
}

Object::Object() : m_position(0,0,0,0), m_spawnLocation(0,0,0,0)
{
	m_mapId = 0;
	m_zoneId = 0;

	m_uint32Values = 0;
	m_objectUpdated = false;


	m_valuesCount = 0;

	//official Values
	m_walkSpeed = 2.5f;
	m_runSpeed = 7.0f;
	m_base_runSpeed = m_runSpeed;
	m_base_walkSpeed = m_walkSpeed;

	m_flySpeed = 7.0f;
	m_backFlySpeed = 4.5f;

	m_backWalkSpeed = 4.5f;	// this should really be named m_backRunSpeed
	m_swimSpeed = 4.722222f;
	m_backSwimSpeed = 2.5f;
	m_turnRate = 3.141593f;

	m_phase = 1; //Set the default phase: 00000000 00000000 00000000 00000001

	m_mapMgr = 0;
	m_mapCell = 0;

	m_faction = NULL;
	m_factionDBC = NULL;

	m_instanceId = 0;
	Active = false;
	m_inQueue = false;
	m_extensions = NULL;
	m_loadedFromDB = false;

	m_faction = dbcFactionTemplate.LookupRow( 0 );
	m_factionDBC = dbcFaction.LookupRow( 0 );

	m_objectsInRange.clear();
	m_inRangePlayers.clear();
	m_oppFactsInRange.clear();
	m_sameFactsInRange.clear();

	Active = false;
}

Object::~Object( )
{
	if(m_objectTypeId != TYPEID_ITEM)
		Wowice::Util::WOWICE_ASSERT(   !m_inQueue);

	Wowice::Util::WOWICE_ASSERT( !IsInWorld() );

	// for linux
	m_instanceId = 0;
	m_objectTypeId=TYPEID_UNUSED;

	if( m_extensions != NULL )
		delete m_extensions;

	//avoid leaving traces in eventmanager. Have to work on the speed. Not all objects ever had events so list iteration can be skipped
	sEventMgr.RemoveEvents( this );
}


void Object::_Create( uint32 mapid, float x, float y, float z, float ang )
{
	m_mapId = mapid;
	m_position.ChangeCoords(x, y, z, ang);
	m_spawnLocation.ChangeCoords(x, y, z, ang);
	m_lastMapUpdatePosition.ChangeCoords(x,y,z,ang);
}

uint32 Object::BuildCreateUpdateBlockForPlayer(ByteBuffer *data, Player *target)
{
	uint16 flags = 0;
	uint32 flags2 = 0;

	uint8 updatetype = UPDATETYPE_CREATE_OBJECT;
	if(m_objectTypeId == TYPEID_CORPSE)
	{
		if(static_cast<Corpse*>(this)->GetDisplayId() == 0)
			return 0;
		updatetype = UPDATETYPE_CREATE_YOURSELF;
	}

	// any other case
	switch(m_objectTypeId)
	{
		// items + containers: 0x8
	case TYPEID_ITEM:
	case TYPEID_CONTAINER:
		flags = 0x10;
		break;

		// player/unit: 0x68 (except self)
	case TYPEID_UNIT:
		flags = 0x70;
		break;

	case TYPEID_PLAYER:
		flags = 0x70;
		break;

		// gameobject/dynamicobject
	case TYPEID_GAMEOBJECT:
		flags = 0x0350;
		if( static_cast<GameObject*>(this)->GetDisplayId()==3831 ) flags= 0x0252; //Deeprun Tram proper flags as of 3.2.0.
		break;

	case TYPEID_DYNAMICOBJECT:
		flags = 0x0150;
		break;

	case TYPEID_CORPSE:
		flags = 0x0150;
		break;
		// anyone else can get fucked and die!
	}

	if(target == this)
	{
		// player creating self
		flags |= 0x01;
		updatetype = UPDATETYPE_CREATE_YOURSELF;
	}

	// gameobject stuff
	if(m_objectTypeId == TYPEID_GAMEOBJECT)
	{
//		switch( GetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_TYPEID) )
		switch(m_uint32Values[GAMEOBJECT_BYTES_1])
		{
			case GAMEOBJECT_TYPE_MO_TRANSPORT:  
				{
					if(GetTypeFromGUID() != HIGHGUID_TYPE_TRANSPORTER)
						return 0;   // bad transporter
					else
						flags = 0x0352;
				}break;

			case GAMEOBJECT_TYPE_TRANSPORT:
				{
					/* deeprun tram, etc */
					flags = 0x252;
				}break;

			case GAMEOBJECT_TYPE_DUEL_ARBITER:
				{
					// duel flags have to stay as updatetype 3, otherwise
					// it won't animate
					updatetype = UPDATETYPE_CREATE_YOURSELF;
				}break;
		}
		//The above 3 checks FAIL to identify transports, thus their flags remain 0x58, and this is BAAAAAAD! Later they don't get position x,y,z,o updates, so they appear randomly by a client-calculated path, they always face north, etc... By: VLack
		if( flags != 0x0352 && GetTypeId() == TYPEID_GAMEOBJECT && static_cast<GameObject*>(this)->GetInfo()->Type == GAMEOBJECT_TYPE_TRANSPORT && !(static_cast<GameObject*>(this)->GetOverrides() & GAMEOBJECT_OVERRIDE_PARENTROT) )
			flags = 0x0352;
	}

	// build our actual update
	*data << updatetype;

	// we shouldn't be here, under any circumstances, unless we have a wowguid..
	Wowice::Util::WOWICE_ASSERT(   m_wowGuid.GetNewGuidLen() > 0);
	*data << m_wowGuid;
	
	*data << m_objectTypeId;

	_BuildMovementUpdate(data, flags, flags2, target);

	// we have dirty data, or are creating for ourself.
	UpdateMask updateMask;
	updateMask.SetCount( m_valuesCount );
	_SetCreateBits( &updateMask, target );

	if(GetTypeId() == TYPEID_GAMEOBJECT && (static_cast<GameObject*>(this)->GetOverrides() & GAMEOBJECT_OVERRIDE_PARENTROT) )
	{
		updateMask.SetBit(GAMEOBJECT_PARENTROTATION_02);
		updateMask.SetBit(GAMEOBJECT_PARENTROTATION_03);
	}

	// this will cache automatically if needed
	_BuildValuesUpdate( data, &updateMask, target );

	// update count: 1 ;)
	return 1;
}


//That is dirty fix it actually creates update of 1 field with
//the given value ignoring existing changes in fields and so on
//useful if we want update this field for certain players
//NOTE: it does not change fields. This is also very fast method
WorldPacket *Object::BuildFieldUpdatePacket( uint32 index,uint32 value)
{
   // uint64 guidfields = GetGUID();
   // uint8 guidmask = 0;
	WorldPacket * packet=new WorldPacket(1500);
	packet->SetOpcode( SMSG_UPDATE_OBJECT );

	*packet << (uint32)1;//number of update/create blocks
//	*packet << (uint8)0;//unknown //VLack: removed for 3.1

	*packet << (uint8) UPDATETYPE_VALUES;		// update type == update
	*packet << GetNewGUID();

	uint32 mBlocks = index/32+1;
	*packet << (uint8)mBlocks;

	for(uint32 dword_n=mBlocks-1;dword_n;dword_n--)
	*packet <<(uint32)0;

	*packet <<(((uint32)(1))<<(index%32));
	*packet << value;

	return packet;
}

void Object::BuildFieldUpdatePacket(Player* Target, uint32 Index, uint32 Value)
{
	ByteBuffer buf(500);
	buf << uint8(UPDATETYPE_VALUES);
	buf << GetNewGUID();

	uint32 mBlocks = Index/32+1;
	buf << (uint8)mBlocks;

	for(uint32 dword_n=mBlocks-1;dword_n;dword_n--)
		buf <<(uint32)0;

	buf <<(((uint32)(1))<<(Index%32));
	buf << Value;

	Target->PushUpdateData(&buf, 1);
}

void Object::BuildFieldUpdatePacket(ByteBuffer * buf, uint32 Index, uint32 Value)
{
	*buf << uint8(UPDATETYPE_VALUES);
	*buf << GetNewGUID();

	uint32 mBlocks = Index/32+1;
	*buf << (uint8)mBlocks;

	for(uint32 dword_n=mBlocks-1;dword_n;dword_n--)
		*buf <<(uint32)0;

	*buf <<(((uint32)(1))<<(Index%32));
	*buf << Value;
}

uint32 Object::BuildValuesUpdateBlockForPlayer(ByteBuffer *data, Player *target)
{
	UpdateMask updateMask;
	updateMask.SetCount( m_valuesCount );
	_SetUpdateBits( &updateMask, target );
	for(uint32 x = 0; x < m_valuesCount; ++x)
	{
		if(updateMask.GetBit(x))
		{
			*data << (uint8) UPDATETYPE_VALUES;		// update type == update
			Wowice::Util::WOWICE_ASSERT(   m_wowGuid.GetNewGuidLen() > 0);
			*data << m_wowGuid;

			_BuildValuesUpdate( data, &updateMask, target );
			return 1;
		}
	}

	return 0;
}

uint32 Object::BuildValuesUpdateBlockForPlayer(ByteBuffer * buf, UpdateMask * mask )
{
	// returns: update count
	// update type == update
	*buf << (uint8) UPDATETYPE_VALUES;		

	Wowice::Util::WOWICE_ASSERT(   m_wowGuid.GetNewGuidLen() > 0);
	*buf << m_wowGuid;

	_BuildValuesUpdate( buf, mask, 0 );

	// 1 update.
	return 1;
}

///////////////////////////////////////////////////////////////
/// Build the Movement Data portion of the update packet
/// Fills the data with this object's movement/speed info
/// TODO: rewrite this stuff, document unknown fields and flags
uint32 TimeStamp();

void Object::_BuildMovementUpdate(ByteBuffer * data, uint16 flags, uint32 flags2, Player* target )
{
	/* ByteBuffer *splinebuf = (m_objectTypeId == TYPEID_UNIT) ? target->GetAndRemoveSplinePacket(GetGUID()) : 0; */
	uint16 flag16 = 0;	// some other flag

	*data << (uint16)flags;

	Player * pThis = NULL;
	MovementInfo* moveinfo = NULL;
	if(GetTypeId() == TYPEID_PLAYER)
	{
		pThis = static_cast< Player* >( this );
		if(pThis->GetSession())
			moveinfo = pThis->GetSession()->GetMovementInfo();
		if(target == this)
		{
			// Updating our last speeds.
			pThis->UpdateLastSpeeds();
		}
	}
	Creature * uThis = NULL;
	if (GetTypeId() == TYPEID_UNIT)
		uThis = static_cast<Creature*>(this);

	if (flags & UPDATEFLAG_LIVING) //0x20
	{
		if(pThis && pThis->m_TransporterGUID != 0)
			flags2 |= MOVEFLAG_TAXI; //0x200
		else if(uThis != NULL && uThis->m_transportGuid != 0 && uThis->m_transportPosition != NULL)
			flags2 |= MOVEFLAG_TAXI; //0x200

		if(uThis != NULL)
		{
			//		 Don't know what this is, but I've only seen it applied to spirit healers.
			//		 maybe some sort of invisibility flag? :/
			switch(GetEntry())
			{
			case 6491:  // Spirit Healer
			case 13116: // Alliance Spirit Guide
			case 13117: // Horde Spirit Guide
				{
					flags2 |= MOVEFLAG_WATER_WALK; //0x10000000
				}break;
			}

			if(uThis->GetAIInterface()->IsFlying())
				flags2 |= MOVEFLAG_NO_COLLISION; //0x400 Zack : Teribus the Cursed had flag 400 instead of 800 and he is flying all the time 
			if(uThis->GetAIInterface()->onGameobject)
				flags2 |= MOVEFLAG_FLYING;
			if(uThis->GetProto()->extra_a9_flags)
			{
//do not send shit we can't honor
#define UNKNOWN_FLAGS2 ( 0x00002000 | 0x04000000 | 0x08000000 )
				uint32 inherit = uThis->GetProto()->extra_a9_flags & UNKNOWN_FLAGS2;
				flags2 |= inherit;
			}
		}

		*data << (uint32)flags2;

		*data << (uint16)flag16;

		*data << getMSTime(); // this appears to be time in ms but can be any thing. Maybe packet serializer ?

		// this stuff:
		//   0x01 -> Enable Swimming?
		//   0x04 -> ??
		//   0x10 -> disables movement compensation and causes players to jump around all the place
		//   0x40 -> disables movement compensation and causes players to jump around all the place

		//Send position data, every living thing has these
		*data << (float)m_position.x;
		*data << (float)m_position.y;
		*data << (float)m_position.z;
		*data << (float)m_position.o;

		if(flags2 & MOVEFLAG_TAXI) //0x0200
		{
			if(pThis)
			{
				WoWGuid wowguid(pThis->m_TransporterGUID);
				*data << wowguid;
				*data << pThis->m_TransporterX << pThis->m_TransporterY << pThis->m_TransporterZ << pThis->m_TransporterO;
				*data << pThis->m_TransporterUnk;
				*data << (uint8)0;
			}
			else if(uThis != NULL && uThis->m_transportPosition != NULL)
			{
				uint64 tguid = ((uint64)HIGHGUID_TYPE_TRANSPORTER << 32) | uThis->m_transportGuid;
				WoWGuid wowguid( tguid );
				*data << wowguid;
				*data << uThis->m_transportPosition->x << uThis->m_transportPosition->y <<
					uThis->m_transportPosition->z << uThis->m_transportPosition->o;
				*data << uint32(0);
				*data << uint8(0);
			}
		}

		if( (flags2 & (MOVEFLAG_SWIMMING | MOVEFLAG_AIR_SWIMMING)) || (flag16 & 0x20) ) // 0x2000000+0x0200000 flying/swimming, && unk sth to do with vehicles?
		{
			if(pThis && moveinfo)
				*data << moveinfo->pitch;
			else 
				*data << (float)0; //pitch
		}

		if(pThis && moveinfo)
			*data << moveinfo->unklast;
		else
			*data << (uint32)0; //last fall time

		if( flags2 & MOVEFLAG_JUMPING ) // 0x00001000
		{

				*data << (float)0;
				*data << (float)1.0;
				*data << (float)0;
				*data << (float)0;			
		}

		if( flags2 & MOVEFLAG_SPLINE_MOVER ) // 0x4000000
		{
			int err1, err2; err2= 0; err1=10/err2; //FAIL please with divide by zero :)
		}

		if( m_walkSpeed == 0 )
			*data << 8.0f;
		else
			*data << m_walkSpeed;	// walk speed
		if( m_runSpeed == 0 )
			*data << 8.0f;
		else
			*data << m_runSpeed;	// run speed
		*data << m_backWalkSpeed;	// backwards walk speed
		*data << m_swimSpeed;		// swim speed
		*data << m_backSwimSpeed;	// backwards swim speed
		if( m_flySpeed == 0 )
			*data << 8.0f;
		else
			*data << m_flySpeed;	// fly speed
		*data << m_backFlySpeed;	// back fly speed
		*data << m_turnRate;		// turn rate
		*data << float(7);		// pitch rate, now a constant...

		if( flags2 & 0x08000000 ) //VLack: On Mangos this is a nice spline movement code, but we never had such... Also, at this point we haven't got this flag, that's for sure, but fail just in case...
		{
			int err1, err2; err2= 0; err1=10/err2; //FAIL please with divide by zero :)
		}
	}
	else //----------------------------------- No UPDATEFLAG_LIVING -----------------------------------
	{
		if( flags & UPDATEFLAG_POSITION ) //0x0100
		{
			*data << uint8( 0 ); //some say it is like parent guid ?
			*data << (float)m_position.x;
			*data << (float)m_position.y;
			*data << (float)m_position.z;
			*data << (float)m_position.x;
			*data << (float)m_position.y;
			*data << (float)m_position.z;
			*data << (float)m_position.o;

			if (m_objectTypeId == TYPEID_CORPSE)
				*data << (float)m_position.o; //VLack: repeat the orientation!
			else
				*data << (float)0;
		}
		else if (flags & UPDATEFLAG_HAS_POSITION) //0x40
		{
			if(flags & UPDATEFLAG_TRANSPORT && m_uint32Values[GAMEOBJECT_BYTES_1]==GAMEOBJECT_TYPE_MO_TRANSPORT)
			{
				*data << (float)0;
				*data << (float)0;
				*data << (float)0;
			}
			else
			{
				*data << (float)m_position.x;
				*data << (float)m_position.y;
				*data << (float)m_position.z;
			}
			*data << (float)m_position.o;
		}
	}


	if( flags & UPDATEFLAG_LOWGUID ) //0x08
		*data << GetLowGUID();

	if( flags & UPDATEFLAG_HIGHGUID ) //0x10
		*data << GetHighGUID();

	if( flags & UPDATEFLAG_HAS_TARGET ) //0x04
	{
		if (IsUnit())
			FastGUIDPack(*data, TO_UNIT(this)->GetTargetGUID());	//some compressed GUID
		else
			*data << uint64( 0 );
	}


	if( flags & UPDATEFLAG_TRANSPORT ) //0x2
	{
        *data << getMSTime();
    }
	if( flags & UPDATEFLAG_VEHICLE ) //0x80
	{
		*data << uint32( 0 ); //Vehicle ID
		*data << float( 0 ); //Facing
	}

	if( flags & UPDATEFLAG_ROTATION ) //0x0200
	{
		if( IsGameObject() )
			*data << static_cast< GameObject* >( this )->m_rotation;
		else
			*data << uint64( 0 ); //?
	}
}


//=======================================================================================
//  Creates an update block with the values of this object as
//  determined by the updateMask.
//=======================================================================================
void Object::_BuildValuesUpdate(ByteBuffer * data, UpdateMask *updateMask, Player* target)
{
	bool activate_quest_object = false;
	bool reset = false;
	uint32 oldflags = 0;

	if(updateMask->GetBit(OBJECT_FIELD_GUID) && target)	   // We're creating.
	{
		Creature * pThis = static_cast<Creature*>(this);
		if(GetTypeId() == TYPEID_UNIT && pThis->IsTagged() && (pThis->loot.gold || pThis->loot.items.size()))
		{
			// Let's see if we're the tagger or not.
			oldflags = m_uint32Values[UNIT_DYNAMIC_FLAGS];
			uint32 Flags = m_uint32Values[UNIT_DYNAMIC_FLAGS];
			uint32 oldFlags = 0;

			if(pThis->GetTaggerGUID() == target->GetGUID())
			{
				// Our target is our tagger.
				oldFlags = U_DYN_FLAG_TAGGED_BY_OTHER;

				if(Flags & U_DYN_FLAG_TAGGED_BY_OTHER)
					Flags &= ~oldFlags;

				if( !(Flags & U_DYN_FLAG_LOOTABLE) && pThis->HasLootForPlayer( target ) )
					Flags |= U_DYN_FLAG_LOOTABLE;
			}
			else
			{
				// Target is not the tagger.
				oldFlags = U_DYN_FLAG_LOOTABLE;

				if(!(Flags & U_DYN_FLAG_TAGGED_BY_OTHER))
					Flags |= U_DYN_FLAG_TAGGED_BY_OTHER;

				if(Flags & U_DYN_FLAG_LOOTABLE)
					Flags &= ~oldFlags;
			}

			m_uint32Values[UNIT_DYNAMIC_FLAGS] = Flags;

			updateMask->SetBit(UNIT_DYNAMIC_FLAGS);

			reset = true;
		}

		if( target && GetTypeId() == TYPEID_GAMEOBJECT )
		{
			GameObject *go = TO_GAMEOBJECT(this);
			QuestLogEntry *qle;
			GameObjectInfo *info;
			if( go->HasQuests() )
			{
				std::list<QuestRelation *>::iterator itr;
				for( itr = go->QuestsBegin(); itr != go->QuestsEnd(); ++itr ) {
					QuestRelation * qr = (*itr);
					if( qr != NULL )
					{
						Quest * qst = qr->qst;
						if( qst != NULL )
						{
							if(		( qr->type & QUESTGIVER_QUEST_START && !target->HasQuest(qst->id) ) 
								||	( qr->type & QUESTGIVER_QUEST_END && target->HasQuest(qst->id) )
								)
							{
								activate_quest_object = true;
								break;
							}
						}
					}
				}
			}
			else
			{
				info = go->GetInfo();
				if( info && ( info->goMap.size() || info->itemMap.size() ) )
				{
					for( GameObjectGOMap::iterator itr = go->GetInfo()->goMap.begin(); itr != go->GetInfo()->goMap.end(); ++itr )
					{
						qle = target->GetQuestLogForEntry( itr->first->id );
						if( qle != NULL )
						{
							if( qle->GetQuest()->count_required_mob == 0 )
								continue;
							for( uint32 i = 0; i < 4; ++i )
							{
								if( qle->GetQuest()->required_mob[i] == static_cast<int32>( go->GetEntry() ) && qle->GetMobCount(i) < qle->GetQuest()->required_mobcount[i])
								{
									activate_quest_object = true;
									break;
								}
							}
							if( activate_quest_object )
								break;
						}
					}

					if( !activate_quest_object )
					{
						for( GameObjectItemMap::iterator itr = go->GetInfo()->itemMap.begin();
							itr != go->GetInfo()->itemMap.end();
							++itr )
						{
							for( std::map<uint32, uint32>::iterator it2 = itr->second.begin();
								it2 != itr->second.end();
								++it2 )
							{
								if( ( qle = target->GetQuestLogForEntry( itr->first->id ) ) != 0 )
								{
									if( target->GetItemInterface()->GetItemCount(it2->first) < it2->second )
									{
										activate_quest_object = true;
										break;
									}
								}
							}
							if( activate_quest_object )
								break;
						}
					}
				}
			}
		}
	}


	if(activate_quest_object)
	{
		oldflags = m_uint32Values[GAMEOBJECT_DYNAMIC];
		if(!updateMask->GetBit(GAMEOBJECT_DYNAMIC))
			updateMask->SetBit(GAMEOBJECT_DYNAMIC);
		m_uint32Values[GAMEOBJECT_DYNAMIC] = 1 | 8; // 8 to show sparkles
		reset = true;
	}

	Wowice::Util::WOWICE_ASSERT(    updateMask && updateMask->GetCount()  == m_valuesCount );
	uint32 bc;
	uint32 values_count;
	if( m_valuesCount > ( 2 * 0x20 ) )//if number of blocks > 2->  unit and player+item container
	{
		bc = updateMask->GetUpdateBlockCount();
		values_count = min<uint32>( bc * 32, m_valuesCount );

	}
	else
	{
		bc=updateMask->GetBlockCount();
		values_count=m_valuesCount;
	}

	*data << (uint8)bc;
	data->append( updateMask->GetMask(), bc*4 );

	for( uint32 index = 0; index < values_count; index ++ )
	{
		if( updateMask->GetBit( index ) )
		{
			*data << m_uint32Values[ index ];
		}
	}

	if(reset)
	{
		switch(GetTypeId())
		{
		case TYPEID_UNIT:
			m_uint32Values[UNIT_DYNAMIC_FLAGS] = oldflags;
			break;
		case TYPEID_GAMEOBJECT:
			m_uint32Values[GAMEOBJECT_DYNAMIC] = oldflags;
			break;
		}
	}
}

void Object::BuildHeartBeatMsg(WorldPacket *data) const
{
	data->Initialize(MSG_MOVE_HEARTBEAT);

	*data << GetGUID();

	*data << uint32(0); // flags
//	*data << uint32(0); // mysterious value #1
	*data << getMSTime();
	*data << m_position;
	*data << m_position.o;
}

bool Object::SetPosition(const LocationVector & v, bool allowPorting /* = false */)
{
	bool updateMap = false, result = true;

	if (m_position.x != v.x || m_position.y != v.y)
		updateMap = true;

	m_position = const_cast<LocationVector&>(v);

	if (!allowPorting && v.z < -500)
	{
		m_position.z = 500;
		sLog.outError( "setPosition: fell through map; height ported" );

		result = false;
	}

	if (IsInWorld() && updateMap)
	{
		m_mapMgr->ChangeObjectLocation(this);
	}

	return result;
}

bool Object::SetPosition( float newX, float newY, float newZ, float newOrientation, bool allowPorting )
{
	bool updateMap = false, result = true;

	//It's a good idea to push through EVERY transport position change, no matter how small they are. By: VLack aka. VLsoft
	if( GetTypeId() == TYPEID_GAMEOBJECT && static_cast<GameObject*>(this)->GetInfo()->Type == GAMEOBJECT_TYPE_TRANSPORT )
		updateMap = true;

	//if (m_position.x != newX || m_position.y != newY)
		//updateMap = true;
	if(m_lastMapUpdatePosition.Distance2DSq(newX, newY) > 4.0f)		/* 2.0f */
		updateMap = true;

	m_position.ChangeCoords(newX, newY, newZ, newOrientation);

	if (!allowPorting && newZ < -500)
	{
		m_position.z = 500;
		sLog.outError( "setPosition: fell through map; height ported" );

		result = false;
	}

	if (IsInWorld() && updateMap)
	{
		m_lastMapUpdatePosition.ChangeCoords(newX,newY,newZ,newOrientation);
		m_mapMgr->ChangeObjectLocation(this);

		if( m_objectTypeId == TYPEID_PLAYER && static_cast< Player* >( this )->GetGroup() && static_cast< Player* >( this )->m_last_group_position.Distance2DSq(m_position) > 25.0f ) // distance of 5.0
		{
            static_cast< Player* >( this )->GetGroup()->HandlePartialChange( PARTY_UPDATE_FLAG_POSITION, static_cast< Player* >( this ) );
		}
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////
/// Fill the object's Update Values from a space delimitated list of values.
void Object::LoadValues(const char* data)
{
	// thread-safe ;) strtok is not.
	std::string ndata = data;
	std::string::size_type last_pos = 0, pos = 0;
	uint32 index = 0;
	uint32 val;
	do
	{
		// prevent overflow
		if(index >= m_valuesCount)
		{
			break;
		}
		pos = ndata.find(" ", last_pos);
		val = atol(ndata.substr(last_pos, (pos-last_pos)).c_str());
		if(m_uint32Values[index] == 0)
			m_uint32Values[index] = val;
		last_pos = pos+1;
		++index;
	} while(pos != std::string::npos);
}

void Object::_SetUpdateBits(UpdateMask *updateMask, Player *target) const
{
	*updateMask = m_updateMask;
}


void Object::_SetCreateBits(UpdateMask *updateMask, Player *target) const
{

	for(uint32 i = 0; i < m_valuesCount; ++i)
		if(m_uint32Values[i] != 0)
			updateMask->SetBit(i);
}

void Object::AddToWorld()
{
	MapMgr *mapMgr = sInstanceMgr.GetInstance(this);
	if(!mapMgr)
		return;

	if( IsPlayer() )
	{
		Player *plr = static_cast< Player* >( this );
		if(mapMgr->pInstance != NULL && !plr->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_GM))
		{
			// Player limit?
			if(mapMgr->GetMapInfo()->playerlimit && mapMgr->GetPlayerCount() >= mapMgr->GetMapInfo()->playerlimit)
				return;
			Group* group = plr->GetGroup();
			// Player in group?
			if(group == NULL && mapMgr->pInstance->m_creatorGuid == 0)
				return;
			// If set: Owns player the instance?
			if(mapMgr->pInstance->m_creatorGuid != 0 && mapMgr->pInstance->m_creatorGuid != plr->GetLowGUID())
				return;

			if (group != NULL) {
				// Is instance empty or owns our group the instance?
				if(mapMgr->pInstance->m_creatorGroup != 0 && mapMgr->pInstance->m_creatorGroup != group->GetID())
				{
					// Player not in group or another group is already playing this instance.
					sChatHandler.SystemMessageToPlr(plr, "Another group is already inside this instance of the dungeon.");
					if(plr->GetSession()->GetPermissionCount() > 0)
						sChatHandler.BlueSystemMessageToPlr(plr, "Enable your GameMaster flag to ignore this rule.");
					return;
				}
				else if(mapMgr->pInstance->m_creatorGroup == 0)
					// Players group now "owns" the instance.
					mapMgr->pInstance->m_creatorGroup = group->GetID();
			}
		}
	}

	m_mapMgr = mapMgr;
	m_inQueue = true;

	// correct incorrect instance id's
	m_instanceId = m_mapMgr->GetInstanceID();
	mapMgr->AddObject(this);
}

void Object::AddToWorld(MapMgr * pMapMgr)
{
	if( !pMapMgr|| (pMapMgr->GetMapInfo()->playerlimit && this->IsPlayer() && pMapMgr->GetPlayerCount() >= pMapMgr->GetMapInfo()->playerlimit) )
		return; //instance add failed

	m_mapMgr = pMapMgr;
	m_inQueue = true;

	pMapMgr->AddObject(this);

	// correct incorrect instance id's
	m_instanceId = pMapMgr->GetInstanceID();
}

//Unlike addtoworld it pushes it directly ignoring add pool
//this can only be called from the thread of mapmgr!!!
void Object::PushToWorld(MapMgr*mgr)
{
	if(!mgr/* || (m_mapMgr != NULL && m_mapCell != NULL) */)
	{
		Log.Debug("Object", "Invalid push to world");
 		return; //instance add failed
	}

	m_mapId=mgr->GetMapId();
	m_instanceId = mgr->GetInstanceID();

	if (IsPlayer())
	{
		TO_PLAYER(this)->m_cache->SetInt32Value(CACHE_MAPID, m_mapId);
		TO_PLAYER(this)->m_cache->SetInt32Value(CACHE_INSTANCEID, m_instanceId);
	}

	m_mapMgr = mgr;
	OnPrePushToWorld();

	mgr->PushObject(this);

	// correct incorrect instance id's
	m_inQueue = false;

	event_Relocate();

	// call virtual function to handle stuff.. :P
	OnPushToWorld();
}

//! Remove object from world
void Object::RemoveFromWorld(bool free_guid)
{
	Wowice::Util::WOWICE_ASSERT(   m_mapMgr != NULL );
	MapMgr * m = m_mapMgr;
	m_mapMgr = NULL;

	m->RemoveObject(this, free_guid);

	std::set<Spell*>::iterator itr, itr2;
	for (itr = m_pendingSpells.begin(); itr != m_pendingSpells.end();)
	{
		itr2 = itr++;
		delete *itr2;
	}
	//shouldnt need to clear, spell destructor will erase
	//m_pendingSpells.clear();

	OnRemoveFromWorld();

	m_instanceId = 0;
	// update our event holder
	event_Relocate();
}



//! Set uint32 property
void Object::SetUInt32Value( const uint32 index, const uint32 value )
{
	Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	//! Save updating when val isn't changing.
	if(m_uint32Values[index] == value)
		return;

	m_uint32Values[ index ] = value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}

	//! Group update handling
	if(m_objectTypeId == TYPEID_PLAYER)
	{
		TO_PLAYER(this)->HandleUpdateFieldChanged(index);
		if(IsInWorld())
		{
			Group* pGroup = static_cast< Player* >( this )->GetGroup();
			if( pGroup != NULL )
				pGroup->HandleUpdateFieldChange( index, static_cast< Player* >( this ) );
		}

#ifdef OPTIMIZED_PLAYER_SAVING
		switch(index)
		{
		case UNIT_FIELD_LEVEL:
		case PLAYER_XP:
			static_cast< Player* >( this )->save_LevelXP();
			break;

		case PLAYER_FIELD_COINAGE:
			static_cast< Player* >( this )->save_Gold();
			break;
		}
#endif

		switch (index)
		{
			case UNIT_FIELD_POWER1:
			case UNIT_FIELD_POWER2:
			case UNIT_FIELD_POWER4:
			case UNIT_FIELD_POWER7:
				static_cast< Unit* >( this )->SendPowerUpdate(true);
				break;
			default:
				break;
		}
	}
	else if(m_objectTypeId == TYPEID_UNIT)
	{
		switch(index)
		{
			case UNIT_FIELD_POWER1:
			case UNIT_FIELD_POWER2:
			case UNIT_FIELD_POWER3:
			case UNIT_FIELD_POWER4:
			case UNIT_FIELD_POWER7:
				static_cast< Unit* >( this )->SendPowerUpdate(false);
				break;
			default:
				break;
		}
	}
}

uint32 Object::GetModPUInt32Value(const uint32 index, const int32 value)
{
	Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	int32 basevalue = (int32)m_uint32Values[ index ];
	return ((basevalue*value)/100);
}

void Object::ModUnsigned32Value(uint32 index, int32 mod)
{
	Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	if(mod == 0)
		return;

	m_uint32Values[ index ] += mod;
	if( (int32)m_uint32Values[index] < 0 )
		m_uint32Values[index] = 0;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}

	if(m_objectTypeId == TYPEID_PLAYER)
	{
#ifdef OPTIMIZED_PLAYER_SAVING
		switch(index)
		{
		case UNIT_FIELD_LEVEL:
		case PLAYER_XP:
			static_cast< Player* >( this )->save_LevelXP();
			break;

		case PLAYER_FIELD_COINAGE:
			static_cast< Player* >( this )->save_Gold();
			break;
		}
#endif

		switch (index)
		{
			case UNIT_FIELD_POWER1:
			case UNIT_FIELD_POWER2:
			case UNIT_FIELD_POWER4:
			case UNIT_FIELD_POWER7:
				static_cast< Unit* >( this )->SendPowerUpdate(true);
				break;
			default:
				break;
		}
	}
	else if(m_objectTypeId == TYPEID_UNIT)
	{
		switch(index)
		{
			case UNIT_FIELD_POWER1:
			case UNIT_FIELD_POWER2:
			case UNIT_FIELD_POWER3:
			case UNIT_FIELD_POWER4:
			case UNIT_FIELD_POWER7:
				static_cast< Unit* >( this )->SendPowerUpdate(false);
				break;
			default:
				break;
		}
	}
}

void Object::ModSignedInt32Value(uint32 index, int32 value )
{
	Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	if(value == 0)
		return;

	m_uint32Values[ index ] += value;
	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}

	if(m_objectTypeId == TYPEID_PLAYER)
	{
#ifdef OPTIMIZED_PLAYER_SAVING
		switch(index)
		{
		case UNIT_FIELD_LEVEL:
		case PLAYER_XP:
			static_cast< Player* >( this )->save_LevelXP();
			break;

		case PLAYER_FIELD_COINAGE:
			static_cast< Player* >( this )->save_Gold();
			break;
		}
#endif
	}
}

void Object::ModFloatValue(const uint32 index, const float value )
{
	Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	m_floatValues[ index ] += value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}
void Object::ModFloatValueByPCT( const uint32 index, int32 byPct )
{
	Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	if( byPct > 0 )
		m_floatValues[ index ] *= 1.0f + byPct / 100.0f;
	else
		m_floatValues[ index ] /= 1.0f - byPct / 100.0f;


	if( IsInWorld() )
	{
		m_updateMask.SetBit( index );

		if( !m_objectUpdated )
		{
			m_mapMgr->ObjectUpdated( this );
			m_objectUpdated = true;
		}
	}
}

//! Set uint64 property
void Object::SetUInt64Value( const uint32 index, const uint64 value )
{
	Wowice::Util::WOWICE_ASSERT(    index + 1 < m_valuesCount );

    uint64 *p = reinterpret_cast< uint64* >( &m_uint32Values[ index ] );

    if( *p == value )
        return;
    else
        *p = value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );
		m_updateMask.SetBit( index + 1 );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated( this );
			m_objectUpdated = true;
		}
	}
}

//! Set float property
void Object::SetFloatValue( const uint32 index, const float value )
{
	Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	if(m_floatValues[index] == value)
		return;

	m_floatValues[ index ] = value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}


void Object::SetFlag( const uint32 index, uint32 newFlag )
{
	SetUInt32Value(index, GetUInt32Value(index) | newFlag);
}


void Object::RemoveFlag( const uint32 index, uint32 oldFlag )
{
	SetUInt32Value(index, GetUInt32Value(index) & ~oldFlag);
}

////////////////////////////////////////////////////////////

float Object::CalcDistance(Object *Ob)
{
	Wowice::Util::WOWICE_ASSERT(   Ob != NULL);
	return CalcDistance(this->GetPositionX(), this->GetPositionY(), this->GetPositionZ(), Ob->GetPositionX(), Ob->GetPositionY(), Ob->GetPositionZ());
}
float Object::CalcDistance(float ObX, float ObY, float ObZ)
{
	return CalcDistance(this->GetPositionX(), this->GetPositionY(), this->GetPositionZ(), ObX, ObY, ObZ);
}
float Object::CalcDistance(Object *Oa, Object *Ob)
{
	Wowice::Util::WOWICE_ASSERT(   Oa != NULL);
	Wowice::Util::WOWICE_ASSERT(   Ob != NULL);
	return CalcDistance(Oa->GetPositionX(), Oa->GetPositionY(), Oa->GetPositionZ(), Ob->GetPositionX(), Ob->GetPositionY(), Ob->GetPositionZ());
}
float Object::CalcDistance(Object *Oa, float ObX, float ObY, float ObZ)
{
	Wowice::Util::WOWICE_ASSERT(   Oa != NULL);
	return CalcDistance(Oa->GetPositionX(), Oa->GetPositionY(), Oa->GetPositionZ(), ObX, ObY, ObZ);
}

float Object::CalcDistance(float OaX, float OaY, float OaZ, float ObX, float ObY, float ObZ)
{
	float xdest = OaX - ObX;
	float ydest = OaY - ObY;
	float zdest = OaZ - ObZ;
	return sqrtf(zdest*zdest + ydest*ydest + xdest*xdest);
}

bool Object::IsWithinDistInMap(Object* obj, const float dist2compare) const
{
	Wowice::Util::WOWICE_ASSERT(   obj != NULL);
	float xdest = this->GetPositionX() - obj->GetPositionX();
	float ydest = this->GetPositionY() - obj->GetPositionY();
	float zdest = this->GetPositionZ() - obj->GetPositionZ();
	return sqrtf(zdest*zdest + ydest*ydest + xdest*xdest) <= dist2compare;
}

bool Object::IsWithinLOSInMap(Object* obj)
{
	Wowice::Util::WOWICE_ASSERT(   obj != NULL);
    if (!IsInMap(obj)) return false;
	LocationVector location;
    location = obj->GetPosition();
    return IsWithinLOS(location );
}

bool Object::IsWithinLOS( LocationVector location )
{
    LocationVector location2;
    location2 = GetPosition();

	if (sWorld.Collision) {
		return CollideInterface.CheckLOS(GetMapId(), location2.x, location2.y, location2.z+2.0f, location.x, location.y, location.z+2.0f);
	} else {
		return true;
	}
}


float Object::calcAngle( float Position1X, float Position1Y, float Position2X, float Position2Y )
{
	float dx = Position2X-Position1X;
	float dy = Position2Y-Position1Y;
	double angle= 0.0f;

	// Calculate angle
	if (dx == 0.0)
	{
		if (dy == 0.0)
			angle = 0.0;
		else if (dy > 0.0)
			angle = M_PI * 0.5 /* / 2 */;
		else
			angle = M_PI * 3.0 * 0.5/* / 2 */;
	}
	else if (dy == 0.0)
	{
		if (dx > 0.0)
			angle = 0.0;
		else
			angle = M_PI;
	}
	else
	{
		if (dx < 0.0)
			angle = atanf(dy/dx) + M_PI;
		else if (dy < 0.0)
			angle = atanf(dy/dx) + (2*M_PI);
		else
			angle = atanf(dy/dx);
	}

	// Convert to degrees
	angle = angle * float(180 / M_PI);

	// Return
	return float(angle);
}

float Object::calcRadAngle( float Position1X, float Position1Y, float Position2X, float Position2Y )
{
	double dx = double(Position2X-Position1X);
	double dy = double(Position2Y-Position1Y);
	double angle= 0.0;

	// Calculate angle
	if (dx == 0.0)
	{
		if (dy == 0.0)
			angle = 0.0;
		else if (dy > 0.0)
			angle = M_PI * 0.5/*/ 2.0*/;
		else
			angle = M_PI * 3.0 * 0.5/*/ 2.0*/;
	}
	else if (dy == 0.0)
	{
		if (dx > 0.0)
			angle = 0.0;
		else
			angle = M_PI;
	}
	else
	{
		if (dx < 0.0)
			angle = atan(dy/dx) + M_PI;
		else if (dy < 0.0)
			angle = atan(dy/dx) + (2*M_PI);
		else
			angle = atan(dy/dx);
	}

	// Return
	return float(angle);
}

float Object::getEasyAngle( float angle )
{
	while ( angle < 0 ) {
		angle = angle + 360;
	}
	while ( angle >= 360 ) {
		angle = angle - 360;
	}
	return angle;
}

bool Object::inArc(float Position1X, float Position1Y, float FOV, float Orientation, float Position2X, float Position2Y )
{
	float angle = calcAngle( Position1X, Position1Y, Position2X, Position2Y );
	float lborder = getEasyAngle( ( Orientation - (FOV*0.5f/*/2*/) ) );
	float rborder = getEasyAngle( ( Orientation + (FOV*0.5f/*/2*/) ) );
	//sLog.outDebug("Orientation: %f Angle: %f LeftBorder: %f RightBorder %f",Orientation,angle,lborder,rborder);
	if(((angle >= lborder) && (angle <= rborder)) || ((lborder > rborder) && ((angle < rborder) || (angle > lborder))))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Object::isInFront(Object* target)
{
	// check if we facing something ( is the object within a 180 degree slice of our positive y axis )

    double x = target->GetPositionX() - m_position.x;
    double y = target->GetPositionY() - m_position.y;

    double angle = atan2( y, x );
    angle = ( angle >= 0.0 ) ? angle : 2.0 * M_PI + angle;
	angle -= m_position.o;

    while( angle > M_PI)
        angle -= 2.0 * M_PI;

    while(angle < -M_PI)
        angle += 2.0 * M_PI;

	// replace M_PI in the two lines below to reduce or increase angle

    double left = -1.0 * ( M_PI / 2.0 );
    double right = ( M_PI / 2.0 );

    return( ( angle >= left ) && ( angle <= right ) );
}

bool Object::isInBack(Object* target)
{
	// check if we are behind something ( is the object within a 180 degree slice of our negative y axis )

    double x = m_position.x - target->GetPositionX();
    double y = m_position.y - target->GetPositionY();

    double angle = atan2( y, x );
    angle = ( angle >= 0.0 ) ? angle : 2.0 * M_PI + angle;

	// if we are a unit and have a UNIT_FIELD_TARGET then we are always facing them
	if( m_objectTypeId == TYPEID_UNIT && TO_UNIT(this)->GetTargetGUID() != 0 )
	{
		Unit* pTarget = TO_UNIT(this)->GetAIInterface()->GetNextTarget();
		if( pTarget != NULL )
			angle -= double( Object::calcRadAngle( target->m_position.x, target->m_position.y, pTarget->m_position.x, pTarget->m_position.y ) );
		else
			angle -= target->GetOrientation();
	}
	else
		angle -= target->GetOrientation();

    while( angle > M_PI)
        angle -= 2.0 * M_PI;

    while(angle < -M_PI)
        angle += 2.0 * M_PI;

	// replace M_H_PI in the two lines below to reduce or increase angle

    double left = -1.0 * ( M_H_PI / 2.0 );
    double right = ( M_H_PI / 2.0 );

    return( ( angle <= left ) && ( angle >= right ) );
}
bool Object::isInArc(Object* target , float angle) // angle in degrees
{
    return inArc( GetPositionX() , GetPositionY() , angle , GetOrientation() , target->GetPositionX() , target->GetPositionY() );
}

bool Object::HasInArc( float degrees, Object* target )
{
	return isInArc(target, degrees);
}

bool Object::isInRange(Object* target, float range)
{
  if ( !this->IsInWorld() || !target ) return false;
	float dist = CalcDistance( target );
	return( dist <= range );
}

void Object::_setFaction()
{
	FactionTemplateDBC* factT = NULL;

	if(GetTypeId() == TYPEID_UNIT || GetTypeId() == TYPEID_PLAYER)
	{
		factT = dbcFactionTemplate.LookupEntryForced(TO_UNIT(this)->GetFaction());
		if( !factT )
			sLog.outError("Unit does not have a valid faction. It will make him act stupid in world. Don't blame us, blame yourself for not checking :P, faction %u set to entry %u",TO_UNIT(this)->GetFaction(),GetEntry() );
	}
	else
	if(GetTypeId() == TYPEID_GAMEOBJECT)
	{
		factT = dbcFactionTemplate.LookupEntryForced(static_cast<GameObject*>(this)->GetFaction());
		if( !factT )
			sLog.outError("Game Object does not have a valid faction. It will make him act stupid in world. Don't blame us, blame yourself for not checking :P, faction %u set to entry %u",static_cast<GameObject*>(this)->GetFaction(),GetEntry() );
	}

	if(!factT)
	{
		factT = dbcFactionTemplate.LookupRow( 0 );
		//this is causing a lot of crashes cause people have shitty dbs
//		return;
	}
	m_faction = factT;
	m_factionDBC = dbcFaction.LookupEntryForced(factT->Faction);
	if( !m_factionDBC )
		m_factionDBC = dbcFaction.LookupRow( 0 );
}

void Object::UpdateOppFactionSet()
{
	m_oppFactsInRange.clear();
	
    for( std::set< Object* >::iterator itr = m_objectsInRange.begin(); itr != m_objectsInRange.end(); ++itr)
	{
        Object *i = *itr;

        if( ( i->IsUnit() ) || ( i->GetTypeId() == TYPEID_GAMEOBJECT ) )
		{
			if(isHostile( this, i) )
			{
				if(!i->IsInRangeOppFactSet( this ) )
					i->m_oppFactsInRange.insert( this );
				if (!IsInRangeOppFactSet( i ) )
					m_oppFactsInRange.insert( i );

			}
			else
			{
				if( i->IsInRangeOppFactSet( this ) )
					i->m_oppFactsInRange.erase( this );
				if( IsInRangeOppFactSet( i ) )
					m_oppFactsInRange.erase( i );
			}
		}
	}
}

void Object::UpdateSameFactionSet()
{
	m_sameFactsInRange.clear();


    for( std::set< Object* >::iterator itr = m_objectsInRange.begin(); itr != m_objectsInRange.end(); ++itr)
	{
        Object *i = *itr;

        if( ( i->IsUnit() ) || ( i->GetTypeId() == TYPEID_GAMEOBJECT) )
		{
			if( isFriendly( this, i ) )
			{
				if(!i->IsInRangeSameFactSet( this ) )
					i->m_sameFactsInRange.insert( this );
				
                if (!IsInRangeOppFactSet( i ) )
					m_sameFactsInRange.insert( i );

			}
			else
			{
				if( i->IsInRangeSameFactSet( this ) )
					i->m_sameFactsInRange.erase( this );
				
                if( IsInRangeSameFactSet( i ) )
					m_sameFactsInRange.erase( i );
			}
		}
	}
}

void Object::EventSetUInt32Value(uint32 index, uint32 value)
{
	SetUInt32Value(index,value);
}

void Object::DealDamage(Unit *pVictim, uint32 damage, uint32 targetEvent, uint32 unitEvent, uint32 spellId, bool no_remove_auras)
{
}

void Object::SpellNonMeleeDamageLog(Unit *pVictim, uint32 spellID, uint32 damage, bool allowProc, bool static_damage, bool no_remove_auras)
{
//==========================================================================================
//==============================Unacceptable Cases Processing===============================
//==========================================================================================
	if( pVictim == NULL || !pVictim->isAlive() )
		return;

	SpellEntry *spellInfo = dbcSpell.LookupEntryForced( spellID );
	if( spellInfo == NULL )
        return;

	if( this->IsPlayer() && ! TO_PLAYER(this)->canCast(spellInfo) )
		return;
//==========================================================================================
//==============================Variables Initialization====================================
//==========================================================================================
	float res = float(damage);
	bool critical = false;

	uint32 aproc = PROC_ON_ANY_HOSTILE_ACTION; /*| PROC_ON_SPELL_HIT;*/
	uint32 vproc = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_ANY_DAMAGE_VICTIM; /*| PROC_ON_SPELL_HIT_VICTIM;*/

	//A school damage is not necessarily magic
	switch( spellInfo->Spell_Dmg_Type )
	{
		case SPELL_DMG_TYPE_RANGED:	{
				aproc |= PROC_ON_RANGED_ATTACK;
				vproc |= PROC_ON_RANGED_ATTACK_VICTIM;
			}break;

		case SPELL_DMG_TYPE_MELEE:{
				aproc |= PROC_ON_MELEE_ATTACK;
				vproc |= PROC_ON_MELEE_ATTACK_VICTIM;
			}break;

		case SPELL_DMG_TYPE_MAGIC:{
				aproc |= PROC_ON_SPELL_HIT;
				vproc |= PROC_ON_SPELL_HIT_VICTIM;
			}break;
	}

//==========================================================================================
//==============================+Spell Damage Bonus Calculations============================
//==========================================================================================
//------------------------------by stats----------------------------------------------------
	if( IsUnit() && !static_damage )
	{
		Unit* caster = TO_UNIT(this);

		caster->RemoveAurasByInterruptFlag( AURA_INTERRUPT_ON_START_ATTACK );

		res += caster->GetSpellDmgBonus( pVictim, spellInfo, ( int )res, false );

		if( res < 0 )
			res = 0;
	}
//==========================================================================================
//==============================Post +SpellDamage Bonus Modifications=======================
//==========================================================================================
	if( res > 0 && !( spellInfo->AttributesExB & ATTRIBUTESEXB_CANT_CRIT ) )
	{
		critical = this->IsCriticalDamageForSpell(pVictim, spellInfo);

//==========================================================================================
//==============================Spell Critical Hit==========================================
//==========================================================================================
		if( critical )
		{
			res = this->GetCriticalDamageBonusForSpell(pVictim, spellInfo, res);

			switch( spellInfo->Spell_Dmg_Type )
			{
				case SPELL_DMG_TYPE_RANGED:	{
						aproc |= PROC_ON_RANGED_CRIT_ATTACK;
						vproc |= PROC_ON_RANGED_CRIT_ATTACK_VICTIM;
					}break;

				case SPELL_DMG_TYPE_MELEE:{
						aproc |= PROC_ON_CRIT_ATTACK;
						vproc |= PROC_ON_CRIT_HIT_VICTIM;
					}break;

				case SPELL_DMG_TYPE_MAGIC:{
						aproc |= PROC_ON_SPELL_CRIT_HIT;
						vproc |= PROC_ON_SPELL_CRIT_HIT_VICTIM;
					}break;
			}
		}
	}

	//==========================================================================================
//==============================Post Roll Calculations======================================
//==========================================================================================

//------------------------------absorption--------------------------------------------------
	uint32 ress=(uint32)res;
	uint32 abs_dmg = pVictim->AbsorbDamage(spellInfo->School, &ress);
	uint32 ms_abs_dmg= pVictim->ManaShieldAbsorb(ress);
	if (ms_abs_dmg)
	{
		if(ms_abs_dmg > ress)
			ress = 0;
		else
			ress-=ms_abs_dmg;

		abs_dmg += ms_abs_dmg;
	}

	if(abs_dmg)
		vproc |= PROC_ON_ABSORB;

	// Incanter's Absorption
	if( pVictim->IsPlayer() && pVictim->HasAurasWithNameHash( SPELL_HASH_INCANTER_S_ABSORPTION ) )
	{
		float pctmod = 0.0f;
		Player* pl = static_cast< Player* >( pVictim );
		if( pl->HasAura( 44394 ) )
			pctmod = 0.05f;
		else if( pl->HasAura( 44395 ) )
			pctmod = 0.10f;
		else if( pl->HasAura( 44396 ) )
			pctmod = 0.15f;

		uint32 hp = static_cast<uint32>( 0.05f * pl->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) );
		uint32 spellpower = static_cast<uint32>( pctmod * pl->GetPosDamageDoneMod(SCHOOL_NORMAL) );

		if( spellpower > hp )
			spellpower = hp;

		SpellEntry * entry = dbcSpell.LookupEntryForced( 44413 );
		if( !entry ) 
			return;

		Spell * sp = new Spell( pl, entry, true, NULL );
		sp->GetProto()->EffectBasePoints[0] = spellpower;
		SpellCastTargets targets;
		targets.m_unitTarget = pl->GetGUID();
		sp->prepare(&targets);
	}

	if(ress < 0) ress = 0;

	res=(float)ress;
	dealdamage dmg;
	dmg.school_type = spellInfo->School;
	dmg.full_damage = ress;
	dmg.resisted_damage = 0;

	if(res <= 0)
		dmg.resisted_damage = dmg.full_damage;

	//------------------------------resistance reducing-----------------------------------------
	if(res > 0 && this->IsUnit())
	{
		static_cast<Unit*>(this)->CalculateResistanceReduction( pVictim, &dmg, spellInfo, 0 );
		if( (int32)dmg.resisted_damage > dmg.full_damage )
			res = 0;
		else
			res = float( dmg.full_damage - dmg.resisted_damage );
	}
	//------------------------------special states----------------------------------------------
	if(pVictim->GetTypeId() == TYPEID_PLAYER && static_cast< Player* >(pVictim)->GodModeCheat == true)
	{
		res = float(dmg.full_damage);
		dmg.resisted_damage = dmg.full_damage;
	}

	// Paladin: Blessing of Sacrifice, and Warlock: Soul Link
	if( pVictim->m_damageSplitTarget)
	{
		res = (float)pVictim->DoDamageSplitTarget((uint32)res, spellInfo->School, false);
	}

//==========================================================================================
//==============================Data Sending ProcHandling===================================
//==========================================================================================
	SendSpellNonMeleeDamageLog(this, pVictim, spellID, float2int32(res), static_cast<uint8>( spellInfo->School ), abs_dmg, dmg.resisted_damage, false, 0, critical, IsPlayer());
	DealDamage( pVictim, float2int32( res ), 2, 0, spellID );

	if( IsUnit() )
	{
		int32 dmg2 = float2int32(res);

		pVictim->HandleProc( vproc, static_cast< Unit* >( this ), spellInfo, !allowProc, dmg2, abs_dmg);
		pVictim->m_procCounter = 0;
		static_cast< Unit* >( this )->HandleProc( aproc, pVictim, spellInfo, !allowProc, dmg2, abs_dmg);
		static_cast< Unit* >( this )->m_procCounter = 0;
	}
	if( this->IsPlayer() )
	{
			static_cast< Player* >( this )->m_casted_amount[spellInfo->School] = ( uint32 )res;
	}

	if( !(dmg.full_damage == 0 && abs_dmg) )
	{
		//Only pushback the victim current spell if it's not fully absorbed
		if( pVictim->GetCurrentSpell() )
			pVictim->GetCurrentSpell()->AddTime( spellInfo->School );
	}

//==========================================================================================
//==============================Post Damage Processing======================================
//==========================================================================================
	if( (int32)dmg.resisted_damage == dmg.full_damage && !abs_dmg )
	{
		//Magic Absorption
		if( pVictim->IsPlayer() )
		{
			if( static_cast< Player* >( pVictim )->m_RegenManaOnSpellResist )
			{
				Player* pl = static_cast< Player* >( pVictim );

				uint32 maxmana = pl->GetMaxPower( POWER_TYPE_MANA );
				uint32 amount = uint32( maxmana * pl->m_RegenManaOnSpellResist );

				pVictim->Energize( pVictim, 29442, amount, POWER_TYPE_MANA );
			}
			// we still stay in combat dude
			static_cast< Player* >(pVictim)->CombatStatusHandler_ResetPvPTimeout();
		}
		if( IsPlayer() )
			static_cast< Player* >(this)->CombatStatusHandler_ResetPvPTimeout();
	}
	if( spellInfo->School == SHADOW_DAMAGE )
	{
		if( pVictim->isAlive() && this->IsUnit() )
		{
			//Shadow Word:Death
			if( spellID == 32379 || spellID == 32996 || spellID == 48157 || spellID == 48158 ) 
			{
				uint32 damage2 = uint32( res + abs_dmg );
				uint32 absorbed = static_cast< Unit* >( this )->AbsorbDamage( spellInfo->School, &damage2 );
				DealDamage( static_cast< Unit* >( this ), damage2, 2, 0, spellID );
				SendSpellNonMeleeDamageLog( this, this, spellID, damage2, static_cast<uint8>( spellInfo->School ), absorbed, 0, false, 0, false, IsPlayer() );
			}
		}
	}
}

//*****************************************************************************************
//* SpellLog packets just to keep the code cleaner and better to read
//*****************************************************************************************

void Object::SendSpellLog(Object *Caster, Object *Target,uint32 Ability, uint8 SpellLogType)
{
	if( Caster == NULL || Target == NULL || Ability == 0 ) 
		return;


	WorldPacket data( SMSG_SPELLLOGMISS, 26 );
	
    data << uint32( Ability );					// spellid
	data << Caster->GetGUID();					// caster / player
	data << uint8( 1 );							// unknown but I think they are const
	data << uint32( 1 );						// unknown but I think they are const
	data << Target->GetGUID();					// target
	data << uint8( SpellLogType );				// spelllogtype
	
    Caster->SendMessageToSet( &data, true );
}


void Object::SendSpellNonMeleeDamageLog( Object* Caster, Object* Target, uint32 SpellID, uint32 Damage, uint8 School, uint32 AbsorbedDamage, uint32 ResistedDamage, bool PhysicalDamage, uint32 BlockedDamage, bool CriticalHit, bool bToset )
{
	if( !Caster || !Target || !SpellID )
		return;
	
	uint32 Overkill = 0;
	
    if( Damage > Target->GetUInt32Value( UNIT_FIELD_HEALTH ) )
		Overkill = Damage - Target->GetUInt32Value( UNIT_FIELD_HEALTH );

	WorldPacket data( SMSG_SPELLNONMELEEDAMAGELOG, 48 );

	data << Target->GetNewGUID();
	data << Caster->GetNewGUID();
	data << uint32( SpellID );                    // SpellID / AbilityID
	data << uint32( Damage );                     // All Damage
	data << uint32( Overkill );					// Overkill
	data << uint8( g_spellSchoolConversionTable[School] );   // School
	data << uint32( AbsorbedDamage );             // Absorbed Damage
	data << uint32( ResistedDamage );             // Resisted Damage
	data << uint8( PhysicalDamage );      // Physical Damage (true/false)
	data << uint8( 0 );                   // unknown or it binds with Physical Damage
    data << uint32( BlockedDamage );		     // Physical Damage (true/false)

    // unknown const
    if( CriticalHit )
        data << uint8( 7 );
    else
        data << uint8( 5 );

    data << uint32( 0 );

	Caster->SendMessageToSet( &data, bToset );
}

void Object::SendAttackerStateUpdate( Object* Caster, Object* Target, dealdamage *Dmg, uint32 Damage, uint32 Abs, uint32 BlockedDamage, uint32 HitStatus, uint32 VState )
{
	if (!Caster || !Target || !Dmg)
		return;

	WorldPacket data( SMSG_ATTACKERSTATEUPDATE, 70 );

	uint32 Overkill = 0;

	if( Damage > Target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
		Overkill = Damage - Target->GetUInt32Value( UNIT_FIELD_HEALTH );
 
	data << uint32( HitStatus );
	data << Caster->GetNewGUID();
	data << Target->GetNewGUID();

	data << uint32( Damage );						// Realdamage
	data << uint32( Overkill );					// Overkill
	data << uint8( 1 );					// Damage type counter / swing type

	data << uint32( g_spellSchoolConversionTable[Dmg->school_type] );				  // Damage school
	data << float( Dmg->full_damage );	// Damage float
	data << uint32( Dmg->full_damage );	// Damage amount

	if( HitStatus & HITSTATUS_ABSORBED ) {
		data << uint32( Abs );				// Damage absorbed
	}

	if( HitStatus & HITSTATUS_RESIST ){
		data << uint32( Dmg->resisted_damage );	// Damage resisted
	}

	data << uint8( VState );
	data << uint32( 0 );				// can be 0,1000 or -1
	data << uint32( 0 );

	if( HitStatus & HITSTATUS_BLOCK ){
		data << uint32( BlockedDamage );		// Damage amount blocked
	}


	if ( HitStatus & HITSTATUS_UNK2 ){
		data << uint32( 0 );				// unknown
	}

	if( HitStatus & HITSTATUS_UNK )
	{
		data << uint32( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );

		data << float( 0 ); // Found in loop
		data << float( 0 );	// Found in loop
		data << uint32( 0 );
	}

	SendMessageToSet(&data, Caster->IsPlayer());
}

int32 Object::event_GetInstanceID()
{
	// return -1 for non-inworld.. so we get our shit moved to the right thread
	//default value is -1, if it's something else then we are/will be soon InWorld.
	return m_instanceId;
}

void Object::EventSpellDamage(uint64 Victim, uint32 SpellID, uint32 Damage)
{
	if( !IsInWorld() )
		return;

	Unit * pUnit = GetMapMgr()->GetUnit( Victim );
	if( pUnit == NULL )
		return;

	SpellNonMeleeDamageLog( pUnit, SpellID, Damage, true );
}

//! Object has an active state
bool Object::CanActivate()
{
	switch(m_objectTypeId)
	{
	case TYPEID_UNIT:
		{
			if ( !IsPet() )
				return true;
		}break;

	case TYPEID_GAMEOBJECT:
		{
			if(static_cast<GameObject*>(this)->HasAI() && GetByte(GAMEOBJECT_BYTES_1, 1) != GAMEOBJECT_TYPE_TRAP)
				return true;
		}break;
	}

	return false;
}

void Object::Activate(MapMgr * mgr)
{
	switch ( m_objectTypeId )
	{
	case TYPEID_UNIT:
		mgr->activeCreatures.insert( TO_CREATURE(this) );
		break;

	case TYPEID_GAMEOBJECT:
		mgr->activeGameObjects.insert( TO_GAMEOBJECT(this) );
		break;
	}
	// Objects are active so set to true.
	Active = true;
}

void Object::Deactivate(MapMgr * mgr)
{
	if ( mgr == NULL )
		return;

	switch(m_objectTypeId)
	{
	case TYPEID_UNIT:
		// check iterator
		if(mgr->creature_iterator != mgr->activeCreatures.end() && (*mgr->creature_iterator)->GetGUID() == GetGUID())
			++mgr->creature_iterator;
		mgr->activeCreatures.erase(TO_CREATURE(this));
		break;

	case TYPEID_GAMEOBJECT:
		mgr->activeGameObjects.erase(TO_GAMEOBJECT(this));
		break;
	}
	Active = false;
}

void Object::SetByte(uint32 index, uint32 index1,uint8 value)
{
	Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	// save updating when val isn't changing.

    uint8 * v =&((uint8*)m_uint32Values)[index*4+index1];

	if(*v == value)
		return;

	*v = value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}

}

void Object::SetByteFlag( uint16 index, uint8 offset, uint8 newFlag )
{
    Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	Wowice::Util::WOWICE_ASSERT(    offset < 4 );
	
	offset <<= 3;

    if( !( uint8( m_uint32Values[ index ] >> offset ) & newFlag ) )
    {
        m_uint32Values[ index ] |= uint32( uint32( newFlag ) << offset );

        if(IsInWorld())
        {
			m_updateMask.SetBit( index );

            if(!m_objectUpdated)
            {
                m_mapMgr->ObjectUpdated(this);
                m_objectUpdated = true;
            }
        }
    }
}

void Object::RemoveByteFlag( uint16 index, uint8 offset, uint8 oldFlag )
{
	Wowice::Util::WOWICE_ASSERT(    index < m_valuesCount );
	Wowice::Util::WOWICE_ASSERT(    offset < 4 );
	
	offset <<= 3;

    if( uint8( m_uint32Values[ index ] >> offset ) & oldFlag )
    {
        m_uint32Values[ index ] &= ~uint32( uint32( oldFlag ) << offset );

        if(IsInWorld())
        {
			m_updateMask.SetBit( index );

            if(!m_objectUpdated)
            {
                m_mapMgr->ObjectUpdated(this);
                m_objectUpdated = true;
            }
        }
    }
}

void Object::SetZoneId(uint32 newZone)
{
	m_zoneId = newZone;

	if (IsPlayer())
	{
		TO_PLAYER(this)->m_cache->SetUInt32Value(CACHE_PLAYER_ZONEID, newZone);
		if (TO_PLAYER(this)->GetGroup() != NULL)
			TO_PLAYER(this)->GetGroup()->HandlePartialChange(PARTY_UPDATE_FLAG_ZONEID, TO_PLAYER(this));
	}
}

void Object::PlaySoundToSet(uint32 sound_entry)
{
	WorldPacket data(SMSG_PLAY_SOUND, 4);
	data << sound_entry;
	
    SendMessageToSet(&data, true);
}

void Object::_SetExtension(const string& name, void* ptr)
{
	if( m_extensions == NULL )
		m_extensions = new ExtensionSet;

	m_extensions->insert( make_pair( name, ptr ) );
}

bool Object::IsInBg()
{
	MapInfo *pMapinfo = WorldMapInfoStorage.LookupEntry( GetMapId() );
	
    if( pMapinfo != NULL )
	{
		return ( pMapinfo->type == INSTANCE_BATTLEGROUND );
	}

	return false;
}

uint32 Object::GetTeam()
{
	if (IsPlayer())
	{
		return static_cast< Player* >( this )->GetTeam();
	}
	if (IsPet())
	{
		if (static_cast< Pet* >( this )->GetPetOwner() != NULL)
		{
			return static_cast< Pet* >( this )->GetPetOwner()->GetTeam();
		}
	}
	if (IsUnit() && !IsPlayer() && static_cast< Creature* >( this )->IsTotem() )
	{
		if (static_cast< Creature* >( this )->GetOwner() != NULL)
		{
			return static_cast< Creature* >( this )->GetOwner()->GetTeam();
		}
	}

	return static_cast<uint32>(-1);
}

//Manipulates the phase value, see "enum PHASECOMMANDS" in Object.h for a longer explanation!
void Object::Phase(uint8 command, uint32 newphase)
{
	switch( command )
	{
	case PHASE_SET:
		m_phase = newphase;
		break;
	case PHASE_ADD:
		m_phase |= newphase;
		break;
	case PHASE_DEL:
		m_phase &= ~newphase;
		break;
	case PHASE_RESET:
		m_phase = 1;
		break;
	default:
		Wowice::Util::WOWICE_ASSERT( false );
	}

	return;
}

void Object::AddInRangeObject(Object *pObj){

    Wowice::Util::WOWICE_ASSERT(    pObj != NULL );

	if( pObj == this )
        sLog.outError( "We are in range of ourselves!" );

    if( pObj->IsPlayer() )
        m_inRangePlayers.insert( pObj ); 

    m_objectsInRange.insert( pObj );
}

void Object::OutPacketToSet(uint16 Opcode, uint16 Len, const void * Data, bool self)
{
	if( !IsInWorld() )
		return;

    // We are on Object level, which means we can't send it to ourselves so we only send to Players inrange
	for( std::set< Object* >::iterator itr = m_inRangePlayers.begin(); itr != m_inRangePlayers.end(); ++itr )
	{
        Object *o = *itr;

        o->OutPacket( Opcode, Len, Data );
	}
}

void Object::SendMessageToSet(WorldPacket *data, bool bToSelf,bool myteam_only)
{
    if(!IsInWorld())
        return;

    for( std::set< Object* >::iterator itr = m_inRangePlayers.begin(); itr != m_inRangePlayers.end(); ++itr ){
        Object *o = *itr;

        o->SendPacket( data );
    }
}

void Object::RemoveInRangeObject( Object *pObj ){
    Wowice::Util::WOWICE_ASSERT(    pObj != NULL );    
 
    if( pObj->IsPlayer() ){
        Wowice::Util::WOWICE_ASSERT(    m_inRangePlayers.erase( pObj ) == 1 );
    }
    
    Wowice::Util::WOWICE_ASSERT(    m_objectsInRange.erase( pObj ) == 1 );

    OnRemoveInRangeObject( pObj );
}

void Object::RemoveSelfFromInrangeSets(){
    std::set< Object* >::iterator itr;

    for( itr = m_objectsInRange.begin(); itr != m_objectsInRange.end(); ++itr ){
        Object *o = *itr;

        Wowice::Util::WOWICE_ASSERT(    o != NULL );
        
        o->RemoveInRangeObject( this );
        
    }

}


void Object::OnRemoveInRangeObject( Object *pObj ){
    /* This method will remain empty for now, don't remove it!
    -dfighter
    */
}

Object * Object::GetMapMgrObject(const uint64 & guid)
{
	if(!IsInWorld())
		return NULL;

	return GetMapMgr()->_GetObject(guid);
}

Pet * Object::GetMapMgrPet(const uint64 & guid)
{
	if(!IsInWorld())
		return NULL;

	return GetMapMgr()->GetPet(GET_LOWGUID_PART(guid));
}

Unit * Object::GetMapMgrUnit(const uint64 & guid)
{
	if(!IsInWorld())
		return NULL;

	return GetMapMgr()->GetUnit(guid);
}

Player * Object::GetMapMgrPlayer(const uint64 & guid)
{
	if(!IsInWorld())
		return NULL;

	return GetMapMgr()->GetPlayer(GET_LOWGUID_PART(guid));
}

Creature * Object::GetMapMgrCreature(const uint64 & guid)
{
	if(!IsInWorld())
		return NULL;

	return GetMapMgr()->GetCreature(GET_LOWGUID_PART(guid));
}

GameObject * Object::GetMapMgrGameObject(const uint64 & guid)
{
	if(!IsInWorld())
		return NULL;

	return GetMapMgr()->GetGameObject(GET_LOWGUID_PART(guid));
}

DynamicObject * Object::GetMapMgrDynamicObject(const uint64 & guid)
{
	if(!IsInWorld())
		return NULL;

	return GetMapMgr()->GetDynamicObject(GET_LOWGUID_PART(guid));
}

Player* Object::GetPlayerOwner()
{
	if (IsPlayer())
		return TO_PLAYER(this);

	if (IsCreature() && (IsPet() || TO_CREATURE(this)->IsTotem()) && TO_PET(this)->GetOwner() != NULL && TO_PET(this)->GetOwner()->IsPlayer())
		return TO_PLAYER(TO_CREATURE(this)->GetOwner());
	return NULL;
}