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

// Ulduar Teleporter
class SCRIPT_DECL UlduarTeleporter : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player*  Plr, bool AutoSend);
	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * Code);

	void GossipEnd(Object*  pObject, Player* Plr)
	{
		GossipScript::GossipEnd(pObject, Plr);
	};
	void Destroy()
	{
		delete this;
	};
};

void SetupUlduar(ScriptMgr* mgr);
