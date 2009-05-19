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
// MapCell.h
//

#ifndef __MAP_CELL_H
#define __MAP_CELL_H

class Map;

#define MAKE_CELL_EVENT(x,y) ( ((x) * 1000) + 200 + y )
#define DECODE_CELL_EVENT(dest_x, dest_y, ev) (dest_x) = ((ev-200)/1000); (dest_y) = ((ev-200)%1000);

class SERVER_DECL MapCell
{
	friend class MapMgr;
public:
	MapCell() {};
	~MapCell();

	typedef std::set<Object*> ObjectSet;

	//Init
	void Init(uint32 x, uint32 y, uint32 mapid, MapMgr *mapmgr);
	
	WoWICE_INLINE void AquireLock(){ m_objectlock.Acquire(); }
	WoWICE_INLINE void ReleaseLock(){ m_objectlock.Release(); }

	//Object Managing
	void AddObject(Object *obj); 
	void RemoveObject(Object *obj);
	bool HasObject(Object *obj) { return (_objects.find(obj) != _objects.end()); }
	bool HasPlayers() { return ((_playerCount > 0) ? true : false); }
	WoWICE_INLINE size_t GetObjectCount() { return _objects.size(); }
	void RemoveObjects();
	WoWICE_INLINE ObjectSet::iterator Begin() { return _objects.begin(); }
	WoWICE_INLINE ObjectSet::iterator End() { return _objects.end(); }

	//State Related
	void SetActivity(bool state);

	WoWICE_INLINE bool IsActive() { return _active; }
	WoWICE_INLINE bool IsLoaded() { return _loaded; }
	WoWICE_INLINE void SetLoaded( bool Loaded = true ) { _loaded = Loaded; }

	//Object Loading Managing
	void LoadObjects(CellSpawns * sp);
	WoWICE_INLINE uint32 GetPlayerCount() { return _playerCount; }

	WoWICE_INLINE bool IsUnloadPending() { return _unloadpending; }
	WoWICE_INLINE void SetUnloadPending(bool up) { _unloadpending = up; }
	void QueueUnloadPending();
	void CancelPendingUnload();
	void Unload();
	WoWICE_INLINE uint16 GetPositionX() { return _x; }
	WoWICE_INLINE uint16 GetPositionY() { return _y; }

	ObjectSet _respawnObjects;

private:
	uint16 _x,_y;
	ObjectSet _objects;
	bool _active, _loaded;
	bool _unloadpending;

	uint16 _playerCount;
	MapMgr* _mapmgr;

	Mutex m_objectlock;
};

#endif

