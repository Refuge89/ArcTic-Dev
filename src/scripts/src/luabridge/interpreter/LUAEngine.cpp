#include "StdAfx.h"
#include "LUAEngine.h"
#include "LUAFunctions.h"
//#define SKIP_ALLOCATOR_SHARING 1
#include <ScriptSetup.h>
#pragma warning(disable:4244)

#pragma warning(disable:4800)
//#pragma warning(disable:2660)

#if PLATFORM != PLATFORM_WIN32
#include <dirent.h>
#endif

LuaEngineMgr g_luaMgr;
LuaEngine g_engine;

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)
{
	m_scriptMgr = mgr;
	g_luaMgr.Startup();
}

extern "C" SCRIPT_DECL void _exp_script_restart(ScriptMgr * mgr)
{
	//m_scriptMgr = mgr;
	printf("_exp_script_restart called. \n");
	g_luaMgr.Unload();
}


/************************************************************************/
/* SCRIPT FUNCTION TABLES                                               */
/************************************************************************/
//#include "..\luabridge_src\FunctionTables.h"

RegType<Item> ItemMethods[] = 
{
    // Item Gossip functions
    { "GossipCreateMenu", &luaItem::GossipCreateMenu },
	{ "GossipMenuAddItem", &luaItem::GossipMenuAddItem },
	{ "GossipSendMenu", &luaItem::GossipSendMenu },
	{ "GossipComplete", &luaItem::GossipComplete },
	{ "GossipSendPOI", &luaItem::GossipSendPOI },
	{ NULL, NULL },
};

RegType<Unit> UnitMethods[] = 
{
    { "GossipCreateMenu", &luaUnit::GossipCreateMenu }, 
    { "GossipMenuAddItem", &luaUnit::GossipMenuAddItem },
    { "GossipSendMenu", &luaUnit::GossipSendMenu },
    { "GossipComplete", &luaUnit::GossipComplete },
    { "GossipSendPOI", &luaUnit::GossipSendPOI },
    { "GetName", &luaUnit::GetName },
	{ "SendChatMessage", &luaUnit::SendChatMessage },
	{ "MoveTo", &luaUnit::MoveTo },
	{ "SetMovementType", &luaUnit::SetMovementType },
	{ "CastSpell", &luaUnit::CastSpell },
	{ "FullCastSpell", &luaUnit::FullCastSpell },
	{ "CastSpellOnTarget", &luaUnit::CastSpellOnTarget },
	{ "FullCastSpellOnTarget", &luaUnit::FullCastSpellOnTarget },
	{ "SpawnCreature", &luaUnit::SpawnCreature },
	{ "SpawnGameObject", &luaUnit::SpawnGameObject },
	{ "GetX", &luaUnit::GetX },
	{ "GetY", &luaUnit::GetY },
	{ "GetZ", &luaUnit::GetZ },
	{ "GetO", &luaUnit::GetO },
	{ "IsPlayer", &luaUnit::IsPlayer },
	{ "IsCreature", &luaUnit::IsCreature },
	{ "RegisterEvent", &luaUnit::RegisterEvent },
	{ "RemoveEvents", &luaUnit::RemoveEvents },
	{ "BroadcastMessage", &luaUnit::SendBroadcastMessage },
	{ "SendAreaTriggerMessage", &luaUnit::SendAreaTriggerMessage },
	{ "MarkQuestObjectiveAsComplete", &luaUnit::MarkQuestObjectiveAsComplete },
	{ "LearnSpell", &luaUnit::LearnSpell },
	{ "UnlearnSpell", &luaUnit::UnlearnSpell },
	{ "HasFinishedQuest", &luaUnit::HasFinishedQuest },
//	{ "GetItemCount", &luaUnit::GetItemCount },
	{ "IsInCombat", &luaUnit::IsInCombat },
	{ "GetMainTank", &luaUnit::GetMainTank },
	{ "GetAddTank", &luaUnit::GetAddTank },
	{ "ClearThreatList", &luaUnit::ClearThreatList },
	{ "GetTauntedBy", &luaUnit::GetTauntedBy },
	{ "SetTauntedBy", &luaUnit::SetTauntedBy },
	{ "SetSoulLinkedWith", &luaUnit::SetSoulLinkedWith },
	{ "GetSoulLinkedWith", &luaUnit::GetSoulLinkedWith },
	{ "ChangeTarget", &luaUnit::ChangeTarget },
	{ "GetHealthPct", &luaUnit::GetHealthPct },
	{ "SetHealthPct", &luaUnit::SetHealthPct },
	{ "GetManaPct", &luaUnit::GetManaPct },
	{ "Despawn", &luaUnit::Despawn },
	{ "GetUnitBySqlId", &luaUnit::GetUnitBySqlId },
	{ "PlaySoundToSet", &luaUnit::PlaySoundToSet },
	{ "RemoveAura", &luaUnit::RemoveAura },
	{ "StopMovement", &luaUnit::StopMovement },
	{ "Emote", &luaUnit::Emote },
	{ "GetInstanceID", &luaUnit::GetInstanceID },
	{ "GetClosestPlayer", &luaUnit::GetClosestPlayer },
	{ "GetRandomPlayer", &luaUnit::GetRandomPlayer },
	{ "GetRandomFriend", &luaUnit::GetRandomFriend },
//	{ "AddItem", &luaUnit::AddItem },
	{ "RemoveItem", &luaUnit::RemoveItem },
	{ "CreateCustomWaypointMap", &luaUnit::CreateCustomWaypointMap },
	{ "CreateWaypoint", &luaUnit::CreateWaypoint },
	{ "MoveToWaypoint", &luaUnit::MoveToWaypoint },
	{ "DestroyCustomWaypointMap", &luaUnit::DestroyCustomWaypointMap },
	{ "SetCombatCapable", &luaUnit::SetCombatCapable },
	{ "SetCombatMeleeCapable", &luaUnit::SetCombatMeleeCapable },
	{ "SetCombatRangedCapable", &luaUnit::SetCombatRangedCapable },
	{ "SetCombatSpellCapable", &luaUnit::SetCombatSpellCapable },
	{ "SetCombatTargetingCapable", &luaUnit::SetCombatTargetingCapable },
	{ "SetModel", &luaUnit::SetModel },
	{ "SetScale", &luaUnit::SetScale },
	{ "SetFaction", &luaUnit::SetFaction },
	{ "SetStandState",&luaUnit::SetStandState },
//	{ "Teleport" , &luaUnit::TeleportUnit },
	{ "GetPlayerClass", &luaUnit::GetPlayerClass },
	{ "ClearThreatList", &luaUnit::ClearHateList },
	{ "WipeThreatList", &luaUnit::WipeHateList },
	{ "WipeTargetList", &luaUnit::WipeTargetList },
	{ "WipeCurrentTarget", &luaUnit::WipeCurrentTarget },
	{ "GetHealth", &luaUnit::GetHealth },
	{ "GetMaxHealth", &luaUnit::GetMaxHealth },
	{ "SetHealth", &luaUnit::SetHealth },
	{ "SetMaxHealth", &luaUnit::SetMaxHealth },
	{ "IsPvPFlagged", &luaUnit::PvPFlagged },
	{ "GetModel", &luaUnit::GetModel },
	{ "GetRunSpeed", &luaUnit::GetRunSpeed },
	{ "GetFlySpeed", &luaUnit::GetFlySpeed },
	{ "Disconnect", &luaUnit::Disconnect },
	{ "GetZone", &luaUnit::GetZone },
	{ "GetMapId", &luaUnit::GetMapId },
	{ "BroadcastWideMessage", &luaUnit::SendWideBroadcastMessage },
	{ "IsBehind", &luaUnit::IsBehind },
	{ "RemoveFlag", &luaUnit::RemoveFlag },
	{ "IsFlying", &luaUnit::IsFlying },
	{ "SetFactionStanding", &luaUnit::SetFactionStanding },
	{ "GetLevel", &luaUnit::GetLevel },
	{ "IsAlive", &luaUnit::IsAlive },
	{ "IsStealthed", &luaUnit::IsStealthed },
	{ "IsGM", &luaUnit::IsGM },
	{ "IsAlliance", &luaUnit::IsAlliance },
	{ "IsHorde", &luaUnit::IsHorde },
	{ "HasAmountOfPlayers", &luaUnit::HasAmountOfPlayers },
	{ "HasGMTagOn", &luaUnit::HasGMTagOn },
	{ "CastSpellAoF", &luaUnit::CastSpellAoF },
	{ "RemoveAllAuras", &luaUnit::RemoveAllAuras },
	{ "TogglePvP", &luaUnit::TogglePvP },
	{ "ApplyRestState", &luaUnit::ApplyRestState },
	{ "ResurrectPlayer", &luaUnit::ResurrectPlayer },
	{ "SetEmoteState", &luaUnit::SetEmoteState },
	{ "GetPlayerAccountName", &luaUnit::GetPlayerAccountName },
	{ "RemoveStealth", &luaUnit::RemoveStealth },
	{ "SetPVPRank", &luaUnit::SetPVPRank },
	{ "Die", &luaUnit::Die },
	{ "SetStealth", &luaUnit::SetStealth },
	{ "WorldQuery", &luaUnit::WorldQuery },
	{ "CharacterQuery", &luaUnit::CharacterQuery },
	{ "AddCreatureLoot", &luaUnit::AddCreatureLoot },
	{ "SystemMessageToPlayer", &luaUnit::SystemMessageToPlr },
	{ "SaveToDB", &luaUnit::SaveToDB },
	{ "IsInvincible", &luaUnit::IsInvincible },
	{ "IsAttacking", &luaUnit::IsAttacking },
	{ "SetInvincible", &luaUnit::SetInvincible },
	{ "IsInRange", &luaUnit::IsInRange },
	{ "FinishQuest", &luaUnit::FinishQuest },
	{ "SubtractTime", &luaUnit::SubtractTime },
	{ "IfQuestCanBeFinished", &luaUnit::IfQuestCanBeFinished },
	{ "SetQuestComplete", &luaUnit::SetQuestComplete },
	{ "MoveToPlayer", &luaUnit::MoveToPlayer },
	{ "EventCreatureYell", &luaUnit::EventCreatureYell },
	{ "EventCreatureDelete", &luaUnit::EventCreatureDelete },
	{ "EventCastSpell", &luaUnit::EventCastSpell },
	{ "EventCastSpellOnSelf", &luaUnit::EventCastSpellOnSelf },
	{ "EventPlaySound", &luaUnit::EventPlaySound },
	{ "MonsterMove", &luaUnit::MonsterMove },
	{ "SetPosition", &luaUnit::SetPosition },
	{ "SetCurrentAgent", &luaUnit::SetCurrentAgent },
//	{ "AddAISpell", &luaUnit::AddAISpell },
	{ "RegisterAIUpdateEvent", &luaUnit::RegisterAIUpdateEvent },
	{ "ModifyAIUpdateEvent", &luaUnit::ModifyAIUpdateEvent },
	{ "RemoveAIUpdateEvent", &luaUnit::RemoveAIUpdateEvent },
	{ "SetDamageDone", &luaUnit::SetDamageDone },
	{ "GetDamageDone", &luaUnit::GetDamageDone },
	{ "SetAIState", &luaUnit::SetAIState },
	{ "DisableRespawn", &luaUnit::DisableRespawn },
	{ "ModifySpeed", &luaUnit::ModifySpeed },
	{ "SetInvisible", &luaUnit::SetInvisible },
	{ "GetInRangePlayers", &luaUnit::GetInRangePlayers },
	{ "GetInRangeFriends", &luaUnit::GetInRangeFriends },
	{ "RemoveFromWorld", &luaUnit::RemoveFromWorld },
	{ "GetCreatureNearestCoords", &luaUnit::GetCreatureNearestCoords },
	{ "GetGameObjectNearestCoords", &luaUnit::GetGameObjectNearestCoords },
	{ "GetUInt32Value", &luaUnit::GetUInt32Value },
	{ "GetUInt64Value", &luaUnit::GetUInt64Value },
	{ "IsMoving", &luaUnit::IsMoving },
	{ "IsAttacking", &luaUnit::IsAttacking },
	{ "GetDistance", &luaUnit::GetDistance },
	{ "GetCurrentSpellId", &luaUnit::GetCurrentSpellId },
	{ "GetCurrentSpellName", &luaUnit::GetCurrentSpellName },
	{ "ModThreat", &luaUnit::ModThreat },
	{ "RemoveThreat", &luaUnit::RemoveThreat },
	{ "GetThreat", &luaUnit::GetThreat },
	{ "CalcDistance", &luaUnit::CalcDistance },
	{ "GetPowerType", &luaUnit::GetPowerType },
	{ "SetNextTarget", &luaUnit::SetNextTarget },
	{ "GetNextTarget", &luaUnit::GetNextTarget },
	{ "GetSpawnX", &luaUnit::GetSpawnX },
	{ "GetSpawnY", &luaUnit::GetSpawnY },
	{ "GetSpawnZ", &luaUnit::GetSpawnZ },
	{ "GetSpawnO", &luaUnit::GetSpawnO },
	{ "GetInstanceMode", &luaUnit::GetInstanceMode },
	{ "Root", &luaUnit::Root },
	{ "Unroot", &luaUnit::Unroot },
	////////////////////////////////////////
	{ "GetSelection", &luaUnit::GetSelection },
	{ "SendMeetingStoneQueue", &luaUnit::SendMeetingStoneQueue },
	{ "IsInFeralForm", &luaUnit::IsInFeralForm },
	{ "GetStanding", &luaUnit::GetStanding },
	{ "ModStanding", &luaUnit::ModStanding },
	{ "SetStanding", &luaUnit::SetStanding },
	{ "SetAtWar", &luaUnit::SetAtWar },
	//{ "IsAtWar", &luaUnit::IsAtWar },
	{ "GetStandingRank", &luaUnit::GetStandingRank },
	{ "UpdateInRangeSet", &luaUnit::UpdateInRangeSet },
	{ "GetRepRankFromStanding", &luaUnit::GetRepRankFromStanding },
	{ "GetPVPRank", &luaUnit::GetPVPRank },
	{ "SetPVPRank", &luaUnit::SetPVPRank },
	{ "IsGroupLeader", &luaUnit::IsGroupLeader },
	{ "IsGroupMember", &luaUnit::IsGroupMember },
	{ "SetBanned", &luaUnit::SetBanned },
	{ "UnSetBanned", &luaUnit::UnSetBanned },
	{ "SetBindPoint", &luaUnit::SetBindPoint },
	{ "ResetTalents", &luaUnit::ResetTalents },
	{ "GetBindPosition", &luaUnit::GetBindPosition },
	{ "AllowFallDamage", &luaUnit::AllowFallDamage },
	{ "GetSoulStone", &luaUnit::GetSoulStone },
	{ "SetSoulStone", &luaUnit::SetSoulStone },
	{ "SetReincarnate", &luaUnit::SetReincarnate },
	{ "EjectFromInstance", &luaUnit::EjectFromInstance },
	{ "SetPlayerName", &luaUnit::SetPlayerName },
	{ "OnUnitEvent", &luaUnit::OnUnitEvent },
	{ "GetRandomEnemy",& luaUnit::GetRandomEnemy },

	{ NULL, NULL },
};

RegType<GameObject> GOMethods[] = 
{
	{ "GetName", &luaGameObject::GetName },
//	{ "Teleport" , &luaGameObject::Teleport },
    // Begin - GO - Gossip Functions.
    { "GossipCreateMenu", &luaGameObject::GossipCreateMenu },
	{ "GossipMenuAddItem", &luaGameObject::GossipMenuAddItem }, 
	{ "GossipSendMenu", &luaGameObject::GossipSendMenu },
	{ "GossipComplete", &luaGameObject::GossipComplete },
	{ "GossipSendPOI", &luaGameObject::GossipSendPOI },
//	{ "AddItem", &luaGameObject::AddItem },
	{ "GetClosestPlayer", &luaGameObject::GetClosestPlayer },
	{ "GetZoneId", &luaGameObject::GetZoneId },
//	{ "GetItemCount", &luaGameObject::GetItemCount },
	{ "GetSpawnX", &luaGameObject::GetSpawnX },
	{ "GetSpawnY", &luaGameObject::GetSpawnY },
	{ "GetSpawnZ", &luaGameObject::GetSpawnZ },
	{ "GetSpawnO", &luaGameObject::GetSpawnO },
	{ "GetInRangePlayersCount", &luaGameObject::GetInRangePlayersCount },
	{ "GetEntry", &luaGameObject::GetEntry },
	{ "GetX", &luaGameObject::GetX },
	{ "GetY", &luaGameObject::GetY },
	{ "GetZ", &luaGameObject::GetZ },
	{ "GetO", &luaGameObject::GetO },
	{ "GetInRangePlayers", &luaGameObject::GetInRangePlayers },
	{ "GetInRangeGameObjects", &luaGameObject::GetInRangeGameObjects },
	{ "GetInstanceID", &luaGameObject::GetInstanceID },
	{ "GetUInt32Value", &luaGameObject::GetUInt32Value },
	{ "GetUInt64Value", &luaGameObject::GetUInt64Value },
	{ "GetFloatValue", &luaGameObject::GetFloatValue },
	{ "GetGUID", &luaGameObject::GetGUID },
	{ "Despawn", &luaGameObject::Despawn },
	{ "IsInWorld", &luaGameObject::IsInWorld },
	{ "IsInBack", &luaGameObject::IsInBack },
	{ "IsInFront", &luaGameObject::IsInFront },
	{ "SpawnCreature", &luaGameObject::SpawnCreature },
	{ "SpawnGameObject", &luaGameObject::SpawnGameObject },
	{ "CalcDistance", &luaGameObject::CalcDistance },
	{ "SetO", &luaGameObject::SetOrientation },
	{ "RemoveFromWorld", &luaGameObject::RemoveFromWorld },
	{ "CalcRadAngle", &luaGameObject::CalcRadAngle },
	{ "SetUInt32Value", &luaGameObject::SetUInt32Value },
	{ "SetUInt64Value", &luaGameObject::SetUInt64Value },
	{ "SetFloatValue", &luaGameObject::SetFloatValue },
	{ "ModUInt32Value", &luaGameObject::ModUInt32Value },
	{ "CastSpell", &luaGameObject::CastSpell },
	{ "FullCastSpell", &luaGameObject::FullCastSpell },
	{ "CastSpellOnTarget", &luaGameObject::CastSpellOnTarget },
	{ "FullCastSpellOnTarget", &luaGameObject::FullCastSpellOnTarget },
	{ "RegisterAIUpdateEvent", &luaGameObject::RegisterAIUpdateEvent },
	{ "ModifyAIUpdateEvent", &luaGameObject::ModifyAIUpdateEvent },
	{ "RemoveAIUpdateEvent", &luaGameObject::RemoveAIUpdateEvent },
//	{ "Respawn", &luaGameObject::Respawn },
	{ "OnGameObjectEvent", &luaGameObject::OnGameObjectEvent },
	// End - GO - Gossip Functions.
	{ NULL, NULL },
};

template<typename T> RegType<T>* GetMethodTable() { return NULL; }
template<>
RegType<Unit>* GetMethodTable<Unit>() { return UnitMethods; }

template<>
RegType<Item>* GetMethodTable<Item>() { return ItemMethods; }

template<>
RegType<GameObject>* GetMethodTable<GameObject>() { return GOMethods; }

void report(lua_State * L)
{
	const char * msg= lua_tostring(L,-1);
	uint8 count = 0;
	while(msg && count <= 20)
	{
		lua_pop(L,-1);
		printf("\t%s\n", msg);
		msg=lua_tostring(L,-1);
		count++;
	}
}

LuaEngine::LuaEngine()
{
	this->L = lua_open();
}

LuaEngine::~LuaEngine()
{
	lua_close(L);
}

void LuaEngine::LoadScripts()
{
	set<string> luaFiles;
	set<string> luaBytecodeFiles;

#ifdef WIN32
	WIN32_FIND_DATA fd;
	HANDLE h;

	h = FindFirstFile("scripts\\*.*", &fd);
	if(h == INVALID_HANDLE_VALUE)
		return;
	
	do 
	{
		char * fn = strrchr(fd.cFileName, '\\');
		if(!fn)
			fn=fd.cFileName;
        char * ext = strrchr(fd.cFileName, '.');
		if(!stricmp(ext, ".lua"))
			luaFiles.insert(string(fn));
		else if(!stricmp(ext, ".luc"))
			luaBytecodeFiles.insert(string(fn));
	} while(FindNextFile(h, &fd));
	FindClose(h);
#else
	struct dirent ** list;
	int filecount = scandir("./scripts", &list, 0, 0);
	if(filecount <= 0 || !list)
		return;

	while(filecount--)
	{
		char* ext = strrchr(list[filecount]->d_name, '.');
		if(ext != NULL && !strcmp(ext, ".lua"))
			{
				string full_path = string(list[filecount]->d_name);
				luaFiles.insert(string(full_path.c_str()));
		}
		else if(!stricmp(ext, ".luc"))
		{
		string full_path = string(list[filecount]->d_name);
		luaBytecodeFiles.insert(string(full_path.c_str()));
		}

		free(list[filecount]);
	}
	free(list);
#endif

	// we prefer precompiled code.
	for(set<string>::iterator itr = luaBytecodeFiles.begin(); itr != luaBytecodeFiles.end(); ++itr)
	{
		set<string>::iterator it2 = luaFiles.find(*itr);
		if(it2 == luaFiles.end())
			luaFiles.erase(it2);
	}

	luaL_openlibs(L);
	RegisterCoreFunctions();

	if(lua_is_starting_up)
		Log.Notice("Blua Engine", "Loading Scripts... ");

	char filename[200];

	for(set<string>::iterator itr = luaFiles.begin(); itr != luaFiles.end(); ++itr)
	{
#ifdef WIN32
			snprintf(filename, 200, "scripts\\%s", itr->c_str());
#else
			snprintf(filename, 200, "scripts/%s", itr->c_str());
#endif
		if(lua_is_starting_up)
			Log.Notice("Blua Engine", "%s...", itr->c_str());

		if(luaL_loadfile(L, filename) != 0)
		{
			//printf(" %sfailed. (could not load)\n",MSG_COLOR_RED);
			sLog.outColor(TRED, "failed. (could not run)\n");
			const char * msg = lua_tostring(L, -1);
			if(msg!=NULL&&lua_is_starting_up)
				//printf(" %s\t%s\n",msg,MSG_COLOR_RED);
				sLog.outColor(TRED, "\t%s\n",msg);
		}
		else
		{
			if(lua_pcall(L, 0, LUA_MULTRET, 0) != 0)
			{
				//printf("failed. (could not run)\n");
				sLog.outColor(TRED, "failed. (could not run)\n");
				const char * msg = lua_tostring(L, -1);
				if(msg!=NULL&&lua_is_starting_up)
					//printf(" %s\t%s\n",msg,MSG_COLOR_RED);
					sLog.outColor(TRED, "\t%s\n",msg);
			}
		}
	}
}


void LuaEngine::OnUnitEvent(Unit * pUnit, const char * FunctionName, uint32 EventType, Unit * pMiscUnit, uint32 Misc, int32 Misc2, float Misc3, bool Yes, ItemPrototype * Misc4)
{
	if(FunctionName==NULL)
		return;
	size_t pos1,pos2,pos3,pos4,pos5 = 0;
	string pString = string(FunctionName);
	char * key = ".";
	pos1 = pString.find(key);
	pos2 = pString.find(key,pos1+1);
	pos3 = pString.find(key,pos2+1);
	pos4 = pString.find(key,pos3+1);
	pos5 = pString.find(key,pos4+1);
	string tblname1 = pString.substr(0,pos1);
	string tblname2 = pString.substr(pos1+1,(pos2-pos1-1));
	string tblname3 = pString.substr(pos2+1,(pos3-pos2-1));
	string tblname4 = pString.substr(pos3+1,(pos4-pos3-1));
	string tblname5 = pString.substr(pos4+1,string::npos);
	
	if(pos1 != string::npos)
	{
		lua_pushstring(L,tblname1.c_str());
		lua_gettable(L,LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			sLog.outColor(TRED, "Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname1.c_str());
			
			return;
		}
		else if(lua_istable(L,-1))
		{
			if(pos2 != string::npos)
			{
				lua_pushstring(L,tblname2.c_str());
				lua_gettable(L,-2);
				if(lua_isnil(L,-1))
				{
					printf("Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname2);
					
					return;
				}
				else if(lua_istable(L,-1))
				{
					if(pos3 != string::npos)
					{
						lua_pushstring(L,tblname3.c_str());
						lua_gettable(L,-2);
						if(lua_isnil(L,-1))
						{
							sLog.outColor(TRED, "Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname3.c_str());
							
							return;
						}
						else if(lua_istable(L,-1))
						{
							if(pos4 != string::npos)
							{
								lua_pushstring(L,tblname4.c_str());
								lua_gettable(L,-2);
								if(lua_isnil(L,-1))
								{
									sLog.outColor(TRED, "Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname4.c_str());
									
									return;
								}
								if(lua_istable(L,-1))
								{
									if(pos5 != string::npos)
									{
										lua_pushstring(L,tblname5.c_str());
										lua_gettable(L,-2);
										if(lua_isnil(L,-1))
										{
											sLog.outColor(TRED, "Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname5.c_str());
											
											return;
										}
										else if(lua_istable(L,-1))
										{
											printf("Too many tables were specified, Aborting.....\n");
											
											return;
										}
									}
									else
									{
										m_Lock.Acquire();
										string func = pString.substr(pos4+1,string::npos);
										lua_pushstring(L,func.c_str());
										lua_gettable(L,-2);
										Lunar<Unit>::push(L, pUnit);
										lua_pushinteger(L,EventType);
										if(pMiscUnit!=NULL)
											Lunar<Unit>::push(L, pMiscUnit);
										else
											lua_pushnil(L);
										lua_pushinteger(L,Misc);
										lua_pushnumber(L,lua_Number(Misc2));
										lua_pushnumber(L,lua_Number(Misc3));
										( (Yes == true) ? lua_pushboolean(L,1) : lua_pushboolean(L,0) );
										( (Misc4 != NULL) ? lua_pushinteger(L,Misc4->ItemId) : lua_pushnil(L) );

										int r = lua_pcall(L,8,LUA_MULTRET,0);
										if(r)
											report(L);
										m_Lock.Release();
										return;
									}
								}
							}
							else
							{
								m_Lock.Acquire();
								string func = pString.substr(pos3+1,string::npos);
								lua_pushstring(L,func.c_str());
								lua_gettable(L,-2);
								Lunar<Unit>::push(L, pUnit);
								lua_pushinteger(L,EventType);
								if(pMiscUnit!=NULL)
									Lunar<Unit>::push(L, pMiscUnit);
								else
									lua_pushnil(L);
								lua_pushinteger(L,Misc);
								lua_pushnumber(L,lua_Number(Misc2));
								lua_pushnumber(L,lua_Number(Misc3));
								( (Yes == true) ? lua_pushboolean(L,1) : lua_pushboolean(L,0) );
								( (Misc4 != NULL) ? lua_pushinteger(L,Misc4->ItemId) : lua_pushnil(L) );

								int r = lua_pcall(L,8,LUA_MULTRET,0);
								if(r)
									report(L);
								m_Lock.Release();
								
								return;
							}
						}
					}
					else
					{
						m_Lock.Acquire();
						string func1 = pString.substr(pos2+1,string::npos);
						lua_pushstring(L,func1.c_str());
						lua_gettable(L,-2);
						Lunar<Unit>::push(L, pUnit);
						lua_pushinteger(L,EventType);
						if(pMiscUnit!=NULL)
							Lunar<Unit>::push(L, pMiscUnit);
						else
							lua_pushnil(L);
						lua_pushinteger(L,Misc);
						lua_pushnumber(L,lua_Number(Misc2));
						lua_pushnumber(L,lua_Number(Misc3));
						( (Yes == true) ? lua_pushboolean(L,1) : lua_pushboolean(L,0) );
						( (Misc4 != NULL) ? lua_pushinteger(L,Misc4->ItemId) : lua_pushnil(L) );

						int r = lua_pcall(L,8,LUA_MULTRET,0);
						if(r)
							report(L);
						m_Lock.Release();
						
						return;
					}
				}
			}
			else
			{
				m_Lock.Acquire();
				string func = pString.substr(pos1+1,string::npos);
				lua_pushstring(L,func.c_str());
				lua_gettable(L,-2);
				Lunar<Unit>::push(L, pUnit);
				lua_pushinteger(L,EventType);
				if(pMiscUnit!=NULL)
					Lunar<Unit>::push(L, pMiscUnit);
				else
					lua_pushnil(L);
				lua_pushinteger(L,Misc);
				lua_pushnumber(L,lua_Number(Misc2));
				lua_pushnumber(L,lua_Number(Misc3));
				( (Yes == true) ? lua_pushboolean(L,1) : lua_pushboolean(L,0) );
				( (Misc4 != NULL) ? lua_pushinteger(L,Misc4->ItemId) : lua_pushnil(L) );

				int r = lua_pcall(L,8,LUA_MULTRET,0);
				if(r)
					report(L);
				m_Lock.Release();
				
				return;
			}
		}
	}
	else
	{
		m_Lock.Acquire();
		lua_pushstring(L, FunctionName);
		lua_gettable(L, LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to call invalid LUA function '%s' from Arcemu (Unit)!\n", FunctionName);
			
			return;
		}

		Lunar<Unit>::push(L, pUnit);
		lua_pushinteger(L,EventType);
		if(pMiscUnit!=NULL)
			Lunar<Unit>::push(L, pMiscUnit);
		else
			lua_pushnil(L);
		lua_pushinteger(L,Misc);
		lua_pushnumber(L,lua_Number(Misc2));
		lua_pushnumber(L,lua_Number(Misc3));
		( (Yes == true) ? lua_pushboolean(L,1) : lua_pushboolean(L,0) );
		( (Misc4 != NULL) ? lua_pushinteger(L,Misc4->ItemId) : lua_pushnil(L) );

		int r = lua_pcall(L,8,LUA_MULTRET,0);
		if(r) report(L);
		m_Lock.Release();
	}
}

void LuaEngine::OnQuestEvent(Player * QuestOwner, const char * FunctionName, uint32 QuestID, uint32 EventType, Player * QuestStarter,uint32 Misc, uint32 Misc2)
{
	if(FunctionName==NULL) return;
	
	string pString = string(FunctionName);
	size_t pos1,pos2,pos3,pos4,pos5;
	string name1,name2,name3,name4,name5;
	char * key = ".";
	pos1 = pString.find(key);
	pos2 = pString.find(key,pos1+1);
	pos3 = pString.find(key,pos2+1);
	pos4 = pString.find(key,pos3+1);
	pos5 = pString.find(key,pos4+1);
	name1 = pString.substr(0,pos1);
	name2 = pString.substr(pos1+1,pos2-pos1-1);
	name3 = pString.substr(pos2+1,pos3-pos2-1);
	name4 = pString.substr(pos3+1,pos3-pos2-1);
	name5 = pString.substr(pos4+1,string::npos);
	
	if(pos1 != string::npos)
	{
		lua_pushstring(L,name1.c_str());
		lua_gettable(L,LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name1);
			
			return;
		}
		else if(lua_istable(L,-2))
		{
			if(pos2 != string::npos)
			{
				lua_pushstring(L,name2.c_str());
				lua_gettable(L,-2);
				if(lua_isnil(L,-1))
				{
					printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name2);
					
					return;
				}
				else if(lua_istable(L,-1))
				{
					if(pos3 != string::npos)
					{
						lua_pushstring(L,name3.c_str());
						lua_gettable(L,-2);
						if(lua_isnil(L,-1))
						{
							printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name3);
							
							return;
						}
						else if(lua_istable(L,-1))
						{
							if(pos4 != string::npos)
							{
								lua_pushstring(L,name4.c_str());
								lua_gettable(L,-2);
								if(lua_isnil(L,-1))
								{
									printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name4);
									
									return;
								}
								else if(lua_istable(L,-1))
								{
									if(pos5 != string::npos)
									{
										lua_pushstring(L,name5.c_str());
										lua_gettable(L,-2);
										if(lua_isnil(L,-1))
										{
											printf("Tried to access and invalid Lua function %s from Arcemu(GO). \n",name5);
											
											return;
										}
										else if(lua_istable(L,-1))
										{
											printf("Reached maximum number of tables allowed. Aborting..... \n");
											
											return;
										}
									}
									else
									{
										m_Lock.Acquire();
										string func = pString.substr(pos4+1,string::npos);
										lua_pushstring(L,func.c_str());
										lua_gettable(L,-2);
										if (QuestOwner) Lunar<Unit>::push(L, (Unit*)QuestOwner);
										else lua_pushnil(L);
										lua_pushinteger(L,EventType);
										if(QuestStarter!=NULL && QuestStarter->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit*)QuestStarter);
										else lua_pushnil(L);
										int r = lua_pcall(L,3,LUA_MULTRET,0);
										if(r) report(L);
										m_Lock.Release();
										
										return;
									}
								}
							}
							else
							{
								m_Lock.Acquire();
								string func = pString.substr(pos3+1,string::npos);
								lua_pushstring(L,func.c_str());
								lua_gettable(L,-2);
								if (QuestOwner) Lunar<Unit>::push(L, (Unit*)QuestOwner);
								else lua_pushnil(L);
								lua_pushinteger(L,EventType);
								if(QuestStarter!=NULL && QuestStarter->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit*)QuestStarter);
								else lua_pushnil(L);
								int r = lua_pcall(L,3,LUA_MULTRET,0);
								if(r) report(L);
								m_Lock.Release();
								
								return;
							}
						}
					}
					else
					{
						m_Lock.Acquire();
						string func = pString.substr(pos2+1,string::npos);
						lua_pushstring(L,func.c_str());
						lua_gettable(L,-2);
						if (QuestOwner) Lunar<Unit>::push(L, (Unit*)QuestOwner);
						else lua_pushnil(L);
						lua_pushinteger(L,EventType);
						if(QuestStarter!=NULL && QuestStarter->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit*)QuestStarter);
						else lua_pushnil(L);
						int r = lua_pcall(L,3,LUA_MULTRET,0);
						if(r) report(L);
						m_Lock.Release();
						
						return;
					}
				}
			}
			else
			{
				m_Lock.Acquire();
				string func = pString.substr(pos1+1,string::npos);
				lua_pushstring(L,func.c_str());
				lua_gettable(L,-2);
				if (QuestOwner) Lunar<Unit>::push(L, (Unit*)QuestOwner);
				else lua_pushnil(L);
				lua_pushinteger(L,EventType);
				if(QuestStarter!=NULL && QuestStarter->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit*)QuestStarter);
				else lua_pushnil(L);
				int r = lua_pcall(L,3,LUA_MULTRET,0);
				if(r) report(L);
				m_Lock.Release();
				
				return;
			}
		}	
	}
	else
	{
		m_Lock.Acquire();
		lua_pushstring(L, FunctionName);
		lua_gettable(L, LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{	
			printf("Tried to call invalid LUA function '%s' from Arcemu (Quest)!\n", FunctionName);
			
			return;
		}
		if (QuestOwner) Lunar<Unit>::push(L, (Unit*)QuestOwner);
		else lua_pushnil(L);
		lua_pushinteger(L,EventType);
		if(QuestStarter!=NULL && QuestStarter->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit*)QuestStarter);
		else lua_pushnil(L);
		int r = lua_pcall(L,3,LUA_MULTRET,0);
		if(r) report(L);
		m_Lock.Release();
	}
}
void LuaEngine::CallFunction(Unit * pUnit, const char * FuncName)
{
	if(FuncName == NULL) return;
	size_t pos1,pos2,pos3,pos4,pos5 = 0;
	string pString = string(FuncName);
	char * key = ".";
	pos1 = pString.find(key);
	pos2 = pString.find(key,pos1+1);
	pos3 = pString.find(key,pos2+1);
	pos4 = pString.find(key,pos3+1);
	pos5 = pString.find(key,pos4+1);
	string tblname1 = pString.substr(0,pos1);
	string tblname2 = pString.substr(pos1+1,(pos2-pos1-1));
	string tblname3 = pString.substr(pos2+1,(pos3-pos2-1));
	string tblname4 = pString.substr(pos3+1,(pos4-pos3-1));
	string tblname5 = pString.substr(pos4+1, string::npos);
	
	if(pos1 != string::npos)
	{
		lua_pushstring(L,tblname1.c_str());
		lua_gettable(L,LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			sLog.outColor(TRED, "Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname1.c_str());
			
			return;
		}
		else if(lua_istable(L,-1))
		{
			if(pos2 != string::npos) // another table string;
			{
				lua_pushstring(L,tblname2.c_str());
				lua_gettable(L,-2);
				if(lua_isnil(L,-1))
				{
					sLog.outColor(TRED, "Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname2);
					
					return;
				}
				else if(lua_istable(L,-1))
				{
					if(pos3 != string::npos)
					{
						lua_pushstring(L,tblname3.c_str());
						lua_gettable(L,-2);
						if(lua_isnil(L,-1))
						{
							sLog.outColor(TRED, "Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname3.c_str());
							
							return;
						}
						else if(lua_istable(L,-1))
						{
							if(pos4 != string::npos)
							{
								lua_pushstring(L,tblname4.c_str());
								lua_gettable(L,-2);
								if(lua_isnil(L,-1))
								{
									sLog.outColor(TRED, "Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname4.c_str());
									
									return;
								}
								else if(lua_istable(L,-1))
								{
									if(pos5 != string::npos)
									{
										lua_pushstring(L,tblname5.c_str());
										lua_gettable(L,-2);
										if(lua_istable(L,-1))
										{
											printf("Reached maximum tables allowed to be registered. Aborting... \n");
											
											return;
										}
										else if(lua_isnil(L,-1))
										{
											sLog.outColor(TRED, "Tried to access invalid LUA table '%s' from Arcemu (Unit)!\n",tblname5.c_str());
											
											return;
										}
									}
									else
									{
										m_Lock.Acquire();
										string func = pString.substr(pos4+1,string::npos);
										lua_pushstring(L,func.c_str());
										lua_gettable(L,-2);
										Lunar<Unit>::push(L, pUnit);
										int r = lua_pcall(L,1,LUA_MULTRET,0);
										if(r)
											report(L);
										m_Lock.Release();
										
										return;
									}
								}

							}
							else
							{
								m_Lock.Acquire();
								string func = pString.substr(pos3+1,string::npos);
								lua_pushstring(L,func.c_str());
								lua_gettable(L,-2);
								Lunar<Unit>::push(L, pUnit);
								int r = lua_pcall(L,1,LUA_MULTRET,0);
								if(r)
									report(L);
								m_Lock.Release();
								
								return;
							}
						}
					}
					else
					{
						m_Lock.Acquire();
						string func = pString.substr(pos2+1,string::npos);
						lua_pushstring(L,func.c_str());
						lua_gettable(L,-2);
						Lunar<Unit>::push(L, pUnit);
						int r = lua_pcall(L,1,LUA_MULTRET,0);
						if(r)
							report(L);
						m_Lock.Release();
						
						return;
					}
				}
			}
			else
			{
				m_Lock.Acquire();
				string func = pString.substr(pos1+1,string::npos);
				lua_pushstring(L,func.c_str());
				lua_gettable(L,-2);
				Lunar<Unit>::push(L, pUnit);
				int r = lua_pcall(L,1,LUA_MULTRET,0);
				if(r)
					report(L);
				m_Lock.Release();
				
				return;
			}
		}
	}
	else
	{
		m_Lock.Acquire();
		lua_pushstring(L, FuncName);
		lua_gettable(L, LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to call invalid LUA function '%s' from Arcemu (Unit)!\n", FuncName);
			
			return;
		}

		Lunar<Unit>::push(L, pUnit);
		int r = lua_pcall(L,1,LUA_MULTRET,0);
		if(r)
			report(L);
		m_Lock.Release();
	}
}

void LuaEngine::OnGameObjectEvent(GameObject * pGameObject, const char * FunctionName, uint32 EventType, Unit * pMiscUnit, uint32 Misc, ItemPrototype* Misc2)
{
	if(FunctionName==NULL)
		return;
	string pString = string(FunctionName);
	size_t pos1,pos2,pos3,pos4,pos5;
	string name1,name2,name3,name4,name5;
	char * key = ".";
	pos1 = pString.find(key);
	pos2 = pString.find(key,pos1+1);
	pos3 = pString.find(key,pos2+1);
	pos4 = pString.find(key,pos3+1);
	pos5 = pString.find(key,pos4+1);
	name1 = pString.substr(0,pos1);
	name2 = pString.substr(pos1+1,pos2-pos1-1);
	name3 = pString.substr(pos2+1,pos3-pos2-1);
	name4 = pString.substr(pos3+1,pos3-pos2-1);
	name5 = pString.substr(pos4+1,string::npos);
	
	if(pos1 != string::npos)
	{
		lua_pushstring(L,name1.c_str());
		lua_gettable(L,LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name1);
			
			return;
		}
		else if(lua_istable(L,-2))
		{
			if(pos2 != string::npos)
			{
				lua_pushstring(L,name2.c_str());
				lua_gettable(L,-2);
				if(lua_isnil(L,-1))
				{
					printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name2);
					
					return;
				}
				else if(lua_istable(L,-1))
				{
					if(pos3 != string::npos)
					{
						lua_pushstring(L,name3.c_str());
						lua_gettable(L,-2);
						if(lua_isnil(L,-1))
						{
							printf("Tried to access an invalid Lua table/function %s from Arcemu(GO). \n",name3);
							
							return;
						}
						else if(lua_istable(L,-1))
						{
							if(pos4 != string::npos)
							{
								lua_pushstring(L,name4.c_str());
								lua_gettable(L,-2);
								if(lua_isnil(L,-1))
								{
									printf("Tried to access an invalid Lua table/function %s from Arcemu(GO). \n",name4);
									
									return;
								}
								else if(lua_istable(L,-1))
								{
									if(pos5 != string::npos)
									{
										lua_pushstring(L,name5.c_str());
										lua_gettable(L,-2);
										if(lua_isnil(L,-1))
										{
											printf("Tried to access and invalid Lua function/function %s from Arcemu(GO). \n",name5);
											
											return;
										}
										else if(lua_istable(L,-1))
										{
											printf("Reached maximum number of tables allowed. Aborting..... \n");
											
											return;
										}
									}
									else
									{
										m_Lock.Acquire();
										string func = pString.substr(pos4+1,string::npos);
										lua_pushstring(L,func.c_str());
										lua_gettable(L,-2);
										Lunar<GameObject>::push(L, pGameObject);
										lua_pushinteger(L,EventType);
										if(!pMiscUnit)
											lua_pushnil(L);
										else
											Lunar<Unit>::push(L, pMiscUnit);

										int r = lua_pcall(L,3,LUA_MULTRET,0);
										if(r)
											report(L);
										m_Lock.Release();
										
										return;
									}
								}
							}
							else
							{
								m_Lock.Acquire();
								string func = pString.substr(pos3+1,string::npos);
								lua_pushstring(L,func.c_str());
								lua_gettable(L,-2);
								Lunar<GameObject>::push(L, pGameObject);
								lua_pushinteger(L,EventType);
								if(!pMiscUnit)
									lua_pushnil(L);
								else
									Lunar<Unit>::push(L, pMiscUnit);

								int r = lua_pcall(L,3,LUA_MULTRET,0);
								if(r)
									report(L);

								m_Lock.Release();
								return;
							}
						}
					}
					else
					{
						m_Lock.Acquire();
						string func = pString.substr(pos2+1,string::npos);
						lua_pushstring(L,func.c_str());
						lua_gettable(L,-2);
						Lunar<GameObject>::push(L, pGameObject);
						lua_pushinteger(L,EventType);
						if(!pMiscUnit)
							lua_pushnil(L);
						else
							Lunar<Unit>::push(L, pMiscUnit);

						int r = lua_pcall(L,3,LUA_MULTRET,0);
						if(r)
							report(L);
						m_Lock.Release();
						
						return;
					}
				}
			}
			else
			{
				m_Lock.Acquire();
				string func = pString.substr(pos1+1,string::npos);
				lua_pushstring(L,func.c_str());
				lua_gettable(L,-2);
				Lunar<GameObject>::push(L, pGameObject);
				lua_pushinteger(L,EventType);
				if(!pMiscUnit)
					lua_pushnil(L);
				else
					Lunar<Unit>::push(L, pMiscUnit);

				int r = lua_pcall(L,3,LUA_MULTRET,0);
				if(r)
					report(L);
				m_Lock.Release();
				return;
			}
		}	
	}
	else
	{
		m_Lock.Acquire();
		lua_pushstring(L, FunctionName);
		lua_gettable(L, LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to call invalid LUA function '%s' from Arcemu! (GO)\n", FunctionName);
			
			return;
		}

		Lunar<GameObject>::push(L, pGameObject);
		lua_pushinteger(L,EventType);
		if(!pMiscUnit)
			lua_pushnil(L);
		else
			Lunar<Unit>::push(L, pMiscUnit);

		int r = lua_pcall(L,3,LUA_MULTRET,0);
		if(r)
			report(L);
		m_Lock.Release();
		
		return;
	}
}

void LuaEngine::OnGossipEvent(Object * pObject, const char * FunctionName, uint32 EventType, Player * mPlayer, uint32 Id, uint32 IntId, const char * Code)
{
    if(FunctionName==NULL)
		return;

	
	string pString = string(FunctionName);
	size_t pos1,pos2,pos3,pos4,pos5;
	string name1,name2,name3,name4,name5;
	char * key = ".";
	pos1 = pString.find(key);
	pos2 = pString.find(key,pos1+1);
	pos3 = pString.find(key,pos2+1);
	pos4 = pString.find(key,pos3+1);
	pos5 = pString.find(key,pos4+1);
	name1 = pString.substr(0,pos1);
	name2 = pString.substr(pos1+1,pos2-pos1-1);
	name3 = pString.substr(pos2+1,pos3-pos2-1);
	name4 = pString.substr(pos3+1,pos3-pos2-1);
	name5 = pString.substr(pos4+1,string::npos);
	if(pos1 != string::npos)
	{
		lua_pushstring(L,name1.c_str());
		lua_gettable(L,LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name1);
			
			return;
		}
		else if(lua_istable(L,-2))
		{
			if(pos2 != string::npos)
			{
				lua_pushstring(L,name2.c_str());
				lua_gettable(L,-2);
				if(lua_isnil(L,-1))
				{
					printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name2);
					
					return;
				}
				else if(lua_istable(L,-1))
				{
					if(pos3 != string::npos)
					{
						lua_pushstring(L,name3.c_str());
						lua_gettable(L,-2);
						if(lua_isnil(L,-1))
						{
							printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name3);
							
							return;
						}
						else if(lua_istable(L,-1))
						{
							if(pos4 != string::npos)
							{
								lua_pushstring(L,name4.c_str());
								lua_gettable(L,-2);
								if(lua_isnil(L,-1))
								{
									printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name4);
									
									return;
								}
								else if(lua_istable(L,-1))
								{
									if(pos5 != string::npos)
									{
										lua_pushstring(L,name5.c_str());
										lua_gettable(L,-2);
										if(lua_isnil(L,-1))
										{
											printf("Tried to access and invalid Lua function %s from Arcemu(GO). \n",name5);
											
											return;
										}
										else if(lua_istable(L,-1))
										{
											printf("Reached maximum number of tables allowed. Aborting..... \n");
											
											return;
										}
									}
									else
									{
										m_Lock.Acquire();
										string func = pString.substr(pos4+1,string::npos);
										lua_pushstring(L,func.c_str());
										lua_gettable(L,-2);
										if(pObject->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit *)pObject);
										else if(pObject->GetTypeId() == TYPEID_ITEM) Lunar<Item>::push(L, (Item *)pObject);
										else if(pObject->GetTypeId() == TYPEID_GAMEOBJECT) Lunar<GameObject>::push(L, (GameObject *)pObject);
										lua_pushinteger(L, EventType);
										Lunar<Unit>::push(L, (Player *)mPlayer);
										lua_pushinteger(L, Id);
										lua_pushinteger(L, IntId);
										lua_pushstring(L, Code);
										int r = lua_pcall(L, 6, LUA_MULTRET, 0);
										if(r) report(L);
										m_Lock.Release();
										return;
									}
								}
							}
							else
							{
								m_Lock.Acquire();
								string func = pString.substr(pos3+1,string::npos);
								lua_pushstring(L,func.c_str());
								lua_gettable(L,-2);
								if(pObject->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit *)pObject);
								else if(pObject->GetTypeId() == TYPEID_ITEM) Lunar<Item>::push(L, (Item *)pObject);
								else if(pObject->GetTypeId() == TYPEID_GAMEOBJECT) Lunar<GameObject>::push(L, (GameObject *)pObject);
								lua_pushinteger(L, EventType);
								Lunar<Unit>::push(L, (Player *)mPlayer);
								lua_pushinteger(L, Id);
								lua_pushinteger(L, IntId);
								lua_pushstring(L, Code);
								int r = lua_pcall(L, 6, LUA_MULTRET, 0);
								if(r) report(L);
								m_Lock.Release();
								return;
							}
						}
					}
					else
					{
						m_Lock.Acquire();
						string func = pString.substr(pos2+1,string::npos);
						lua_pushstring(L,func.c_str());
						lua_gettable(L,-2);
						if(pObject->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit *)pObject);
						else if(pObject->GetTypeId() == TYPEID_ITEM) Lunar<Item>::push(L, (Item *)pObject);
						else if(pObject->GetTypeId() == TYPEID_GAMEOBJECT) Lunar<GameObject>::push(L, (GameObject *)pObject);
						lua_pushinteger(L, EventType);
						Lunar<Unit>::push(L, (Player *)mPlayer);
						lua_pushinteger(L, Id);
						lua_pushinteger(L, IntId);
						lua_pushstring(L, Code);
						int r = lua_pcall(L, 6, LUA_MULTRET, 0);
						if(r) report(L);
						m_Lock.Release();
						return;
					}
				}
			}
			else
			{
				m_Lock.Acquire();
				string func = pString.substr(pos1+1,string::npos);
				lua_pushstring(L,func.c_str());
				lua_gettable(L,-2);
				if(pObject->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit *)pObject);
				else if(pObject->GetTypeId() == TYPEID_ITEM) Lunar<Item>::push(L, (Item *)pObject);
				else if(pObject->GetTypeId() == TYPEID_GAMEOBJECT) Lunar<GameObject>::push(L, (GameObject *)pObject);
				lua_pushinteger(L, EventType);
				Lunar<Unit>::push(L, (Player *)mPlayer);
				lua_pushinteger(L, Id);
				lua_pushinteger(L, IntId);
				lua_pushstring(L, Code);
				int r = lua_pcall(L, 6, LUA_MULTRET, 0);
				if(r) report(L);
				m_Lock.Release();
				return;
			}
		}	
	}
	else
	{
		m_Lock.Acquire();
		lua_pushstring(L, FunctionName);
		lua_gettable(L, LUA_GLOBALSINDEX);
		if(lua_isnil(L, -1))
		{
			printf("Tried to call invalid LUA function '%s' from Arcemu (Gossip)!\n", FunctionName);
			
			return;
		}
		if(pObject->GetTypeId() == TYPEID_UNIT) Lunar<Unit>::push(L, (Unit *)pObject);
		else if(pObject->GetTypeId() == TYPEID_ITEM) Lunar<Item>::push(L, (Item *)pObject);
		else if(pObject->GetTypeId() == TYPEID_GAMEOBJECT) Lunar<GameObject>::push(L, (GameObject *)pObject);
		lua_pushinteger(L, EventType);
		Lunar<Unit>::push(L, (Player *)mPlayer);
		lua_pushinteger(L, Id);
		lua_pushinteger(L, IntId);
		lua_pushstring(L, Code);
		int r = lua_pcall(L, 6, LUA_MULTRET, 0);
		if(r) report(L);
		m_Lock.Release();
		return;
	}
}
#ifdef ENABLE_LUA_HOOKS
void LuaEngine::OnServerHook(Player * plr, uint32 evt, Object * obj, const char * FunctionName, uint32 Misc = 0, uint32 Misc_ = 0)
{
	if(FunctionName == NULL) return;
	
	string pString = string(FunctionName);
	size_t pos1,pos2,pos3,pos4,pos5;
	string name1,name2,name3,name4,name5;
	char * key = ".";
	pos1 = pString.find(key);
	pos2 = pString.find(key,pos1+1);
	pos3 = pString.find(key,pos2+1);
	pos4 = pString.find(key,pos3+1);
	pos5 = pString.find(key,pos4+1);
	name1 = pString.substr(0,pos1);
	name2 = pString.substr(pos1+1,pos2-pos1-1);
	name3 = pString.substr(pos2+1,pos3-pos2-1);
	name4 = pString.substr(pos3+1,pos3-pos2-1);
	name5 = pString.substr(pos4+1,string::npos);
	if(pos1 != string::npos)
	{
		lua_pushstring(L,name1.c_str());
		lua_gettable(L,LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name1);
			
			return;
		}
		else if(lua_istable(L,-2))
		{
			if(pos2 != string::npos)
			{
				lua_pushstring(L,name2.c_str());
				lua_gettable(L,-2);
				if(lua_isnil(L,-1))
				{
					printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name2);
					
					return;
				}
				else if(lua_istable(L,-1))
				{
					if(pos3 != string::npos)
					{
						lua_pushstring(L,name3.c_str());
						lua_gettable(L,-2);
						if(lua_isnil(L,-1))
						{
							printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name3);
							
							return;
						}
						else if(lua_istable(L,-1))
						{
							if(pos4 != string::npos)
							{
								lua_pushstring(L,name4.c_str());
								lua_gettable(L,-2);
								if(lua_isnil(L,-1))
								{
									printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name4);
									
									return;
								}
								else if(lua_istable(L,-1))
								{
									if(pos5 != string::npos)
									{
										lua_pushstring(L,name5.c_str());
										lua_gettable(L,-2);
										if(lua_isnil(L,-1))
										{
											printf("Tried to access and invalid Lua function %s from Arcemu(GO). \n",name5);
											
											return;
										}
										else if(lua_istable(L,-1))
										{
											printf("Reached maximum number of tables allowed. Aborting..... \n");
											
											return;
										}
									}
									else
									{
										m_Lock.Acquire();
										string func = pString.substr(pos4+1,string::npos);
										lua_pushstring(L,func.c_str());
										lua_gettable(L,-2);
										Lunar<Unit>::push(L, (Unit*)plr);
										lua_pushinteger(L, evt);
										if(obj == NULL) lua_pushnil(L);
										else switch(obj->GetTypeId())
										{
											case TYPEID_UNIT:
											case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
											case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
											default: lua_pushnil(L);
										}
										lua_pushinteger(L, Misc);
										lua_pushinteger(L, Misc_);
										int r = lua_pcall(L, 5, LUA_MULTRET, 0);
										if(r) report(L);
										m_Lock.Release();
										return;
									}
								}
							}
							else
							{
								m_Lock.Acquire();
								string func = pString.substr(pos3+1,string::npos);
								lua_pushstring(L,func.c_str());
								lua_gettable(L,-2);
								Lunar<Unit>::push(L, (Unit*)plr);
								lua_pushinteger(L, evt);
								if(obj == NULL) lua_pushnil(L);
								else switch(obj->GetTypeId())
								{
									case TYPEID_UNIT:
									case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
									case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
									default: lua_pushnil(L);
								}
								lua_pushinteger(L, Misc);
								lua_pushinteger(L, Misc_);
								int r = lua_pcall(L, 5, LUA_MULTRET, 0);
								if(r) report(L);
								m_Lock.Release();
								return;
							}
						}
					}
					else
					{
						m_Lock.Acquire();
						string func = pString.substr(pos2+1,string::npos);
						lua_pushstring(L,func.c_str());
						lua_gettable(L,-2);
						Lunar<Unit>::push(L, (Unit*)plr);
						lua_pushinteger(L, evt);
						if(obj == NULL) lua_pushnil(L);
						else switch(obj->GetTypeId())
						{
							case TYPEID_UNIT:
							case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
							case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
							default: lua_pushnil(L);
						}
						lua_pushinteger(L, Misc);
						lua_pushinteger(L, Misc_);
						int r = lua_pcall(L, 5, LUA_MULTRET, 0);
						if(r) report(L);
						m_Lock.Release();
						return;
					}
				}
			}
			else
			{
				m_Lock.Acquire();
				string func = pString.substr(pos1+1,string::npos);
				lua_pushstring(L,func.c_str());
				lua_gettable(L,-2);
				Lunar<Unit>::push(L, (Unit*)plr);
				lua_pushinteger(L, evt);
				if(obj == NULL) lua_pushnil(L);
				else switch(obj->GetTypeId())
				{
					case TYPEID_UNIT:
					case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
					case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
					default: lua_pushnil(L);
				}
				lua_pushinteger(L, Misc);
				lua_pushinteger(L, Misc_);
				int r = lua_pcall(L, 5, LUA_MULTRET, 0);
				if(r) report(L);
				m_Lock.Release();
				return;
			}
		}	
	}
	else
	{
		m_Lock.Acquire();
		lua_pushstring(L, FunctionName);
		lua_gettable(L, LUA_GLOBALSINDEX);
		if(lua_isnil(L, -1))
		{
			printf("Tried to call invalid LUA function '%s' from Arcemu (Gossip)!\n", FunctionName);
			
			return;
		}
		Lunar<Unit>::push(L, (Unit*)plr);
		lua_pushinteger(L, evt);
		if(obj == NULL) lua_pushnil(L);
		else switch(obj->GetTypeId())
		{
			case TYPEID_UNIT:
			case TYPEID_PLAYER:
				Lunar<Unit>::push(L, (Unit*)obj);
			case TYPEID_GAMEOBJECT:
				Lunar<GameObject>::push(L, (GameObject*)obj);
			default:
				lua_pushnil(L);
		}
		lua_pushinteger(L, Misc);
		lua_pushinteger(L, Misc_);
		int r = lua_pcall(L, 5, LUA_MULTRET, 0);
		if(r) report(L);
		m_Lock.Release();
		return;
	}
}
void LuaEngine::OnServerHook(Player * plr, uint32 evt, Object * obj, const char * FunctionName, uint32 pmisc1, uint32 pmisc2, const char * misc1, const char * misc2)
{
	if(FunctionName==NULL)
		return;
	
	string pString = string(FunctionName);
	size_t pos1,pos2,pos3,pos4,pos5;
	string name1,name2,name3,name4,name5;
	char * key = ".";
	pos1 = pString.find(key);
	pos2 = pString.find(key,pos1+1);
	pos3 = pString.find(key,pos2+1);
	pos4 = pString.find(key,pos3+1);
	pos5 = pString.find(key,pos4+1);
	name1 = pString.substr(0,pos1);
	name2 = pString.substr(pos1+1,pos2-pos1-1);
	name3 = pString.substr(pos2+1,pos3-pos2-1);
	name4 = pString.substr(pos3+1,pos3-pos2-1);
	name5 = pString.substr(pos4+1,string::npos);
	if(pos1 != string::npos)
	{
		lua_pushstring(L,name1.c_str());
		lua_gettable(L,LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name1);
			
			return;
		}
		else if(lua_istable(L,-2))
		{
			if(pos2 != string::npos)
			{
				lua_pushstring(L,name2.c_str());
				lua_gettable(L,-2);
				if(lua_isnil(L,-1))
				{
					printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name2);
					
					return;
				}
				else if(lua_istable(L,-1))
				{
					if(pos3 != string::npos)
					{
						lua_pushstring(L,name3.c_str());
						lua_gettable(L,-2);
						if(lua_isnil(L,-1))
						{
							printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name3);
							
							return;
						}
						else if(lua_istable(L,-1))
						{
							if(pos4 != string::npos)
							{
								lua_pushstring(L,name4.c_str());
								lua_gettable(L,-2);
								if(lua_isnil(L,-1))
								{
									printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name4);
									
									return;
								}
								else if(lua_istable(L,-1))
								{
									if(pos5 != string::npos)
									{
										lua_pushstring(L,name5.c_str());
										lua_gettable(L,-2);
										if(lua_isnil(L,-1))
										{
											printf("Tried to access and invalid Lua function %s from Arcemu(GO). \n",name5);
											
											return;
										}
										else if(lua_istable(L,-1))
										{
											printf("Reached maximum number of tables allowed. Aborting..... \n");
											
											return;
										}
									}
									else
									{
										m_Lock.Acquire();
										string func = pString.substr(pos4+1,string::npos);
										lua_pushstring(L,func.c_str());
										lua_gettable(L,-2);
										Lunar<Unit>::push(L, (Unit*)plr);
										lua_pushinteger(L, evt );
										if(obj == NULL) lua_pushnil(L);
										else switch(obj->GetTypeId())
										{
											case TYPEID_UNIT:
											case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
											case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
											default: lua_pushnil(L);
										}
										lua_pushinteger(L, pmisc1);
										lua_pushinteger(L, pmisc2);
										( (misc1 != NULL) ? lua_pushstring(L, misc1) : lua_pushnil(L) );
										( (misc2 != NULL) ? lua_pushstring(L, misc2) : lua_pushnil(L) );
										int r = lua_pcall(L, 7, LUA_MULTRET, 0);
										if(r)	report(L);
										m_Lock.Release();
										return;
									}
								}
							}
							else
							{
								m_Lock.Acquire();
								string func = pString.substr(pos3+1,string::npos);
								lua_pushstring(L,func.c_str());
								lua_gettable(L,-2);
								Lunar<Unit>::push(L, (Unit*)plr);
								lua_pushinteger(L, evt );
								if(obj == NULL) lua_pushnil(L);
								else switch(obj->GetTypeId())
								{
									case TYPEID_UNIT:
									case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
									case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
									default: lua_pushnil(L);
								}
								lua_pushinteger(L, pmisc1);
								lua_pushinteger(L, pmisc2);
								( (misc1 != NULL) ? lua_pushstring(L, misc1) : lua_pushnil(L) );
								( (misc2 != NULL) ? lua_pushstring(L, misc2) : lua_pushnil(L) );
								int r = lua_pcall(L, 7, LUA_MULTRET, 0);
								if(r)	report(L);
								m_Lock.Release();
								return;
							}
						}
					}
					else
					{
						m_Lock.Acquire();
						string func = pString.substr(pos2+1,string::npos);
						lua_pushstring(L,func.c_str());
						lua_gettable(L,-2);
						Lunar<Unit>::push(L, (Unit*)plr);
						lua_pushinteger(L, evt );
						if(obj == NULL) lua_pushnil(L);
						else switch(obj->GetTypeId())
						{
							case TYPEID_UNIT:
							case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
							case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
							default: lua_pushnil(L);
						}
						lua_pushinteger(L, pmisc1);
						lua_pushinteger(L, pmisc2);
						( (misc1 != NULL) ? lua_pushstring(L, misc1) : lua_pushnil(L) );
						( (misc2 != NULL) ? lua_pushstring(L, misc2) : lua_pushnil(L) );
						int r = lua_pcall(L, 7, LUA_MULTRET, 0);
						if(r)	report(L);
						m_Lock.Release();
						return;
					}
				}
			}
			else
			{
				m_Lock.Acquire();
				string func = pString.substr(pos1+1,string::npos);
				lua_pushstring(L,func.c_str());
				lua_gettable(L,-2);
				Lunar<Unit>::push(L, (Unit*)plr);
				lua_pushinteger(L, evt );
				if(obj == NULL) lua_pushnil(L);
				else switch(obj->GetTypeId())
				{
					case TYPEID_UNIT:
					case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
					case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
					default: lua_pushnil(L);
				}
				lua_pushinteger(L, pmisc1);
				lua_pushinteger(L, pmisc2);
				( (misc1 != NULL) ? lua_pushstring(L, misc1) : lua_pushnil(L) );
				( (misc2 != NULL) ? lua_pushstring(L, misc2) : lua_pushnil(L) );
				int r = lua_pcall(L, 7, LUA_MULTRET, 0);
				if(r)	report(L);
				m_Lock.Release();
				return;
			}
		}	
	}
	else
	{
		m_Lock.Acquire();
		lua_pushstring(L, FunctionName);
		lua_gettable(L, LUA_GLOBALSINDEX);
		if(lua_isnil(L, -1))
		{
			printf("Tried to call invalid LUA function '%s' from Arcemu (Gossip)!\n", FunctionName);
			
			return;
		}
		Lunar<Unit>::push(L, (Unit*)plr);
		lua_pushinteger(L, evt );
		if(obj == NULL) lua_pushnil(L);
		else switch(obj->GetTypeId())
		{
			case TYPEID_UNIT:
			case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
			case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
			default: lua_pushnil(L);
		}
		lua_pushinteger(L, pmisc1);
		lua_pushinteger(L, pmisc2);
		( (misc1 != NULL) ? lua_pushstring(L, misc1) : lua_pushnil(L) );
		( (misc2 != NULL) ? lua_pushstring(L, misc2) : lua_pushnil(L) );
		int r = lua_pcall(L, 7, LUA_MULTRET, 0);
		if(r)	report(L);
		m_Lock.Release();
	}
}
void LuaEngine::OnServerHook(Player * plr, uint32 evt, Object * obj, const char * FunctionName, ArenaTeam * pArena, bool misc1, bool misc2)
{
	if(FunctionName==NULL) return;

	
	string pString = string(FunctionName);
	size_t pos1,pos2,pos3,pos4,pos5;
	string name1,name2,name3,name4,name5;
	char * key = ".";
	pos1 = pString.find(key);
	pos2 = pString.find(key,pos1+1);
	pos3 = pString.find(key,pos2+1);
	pos4 = pString.find(key,pos3+1);
	pos5 = pString.find(key,pos4+1);
	name1 = pString.substr(0,pos1);
	name2 = pString.substr(pos1+1,pos2-pos1-1);
	name3 = pString.substr(pos2+1,pos3-pos2-1);
	name4 = pString.substr(pos3+1,pos3-pos2-1);
	name5 = pString.substr(pos4+1,string::npos);
	if(pos1 != string::npos)
	{
		lua_pushstring(L,name1.c_str());
		lua_gettable(L,LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name1);
			
			return;
		}
		else if(lua_istable(L,-2))
		{
			if(pos2 != string::npos)
			{
				lua_pushstring(L,name2.c_str());
				lua_gettable(L,-2);
				if(lua_isnil(L,-1))
				{
					printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name2);
					
					return;
				}
				else if(lua_istable(L,-1))
				{
					if(pos3 != string::npos)
					{
						lua_pushstring(L,name3.c_str());
						lua_gettable(L,-2);
						if(lua_isnil(L,-1))
						{
							printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name3);
							
							return;
						}
						else if(lua_istable(L,-1))
						{
							if(pos4 != string::npos)
							{
								lua_pushstring(L,name4.c_str());
								lua_gettable(L,-2);
								if(lua_isnil(L,-1))
								{
									printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name4);
									
									return;
								}
								else if(lua_istable(L,-1))
								{
									if(pos5 != string::npos)
									{
										lua_pushstring(L,name5.c_str());
										lua_gettable(L,-2);
										if(lua_isnil(L,-1))
										{
											printf("Tried to access and invalid Lua function %s from Arcemu(GO). \n",name5);
											
											return;
										}
										else if(lua_istable(L,-1))
										{
											printf("Reached maximum number of tables allowed. Aborting..... \n");
											
											return;
										}
									}
									else
									{
										m_Lock.Acquire();
										string func = pString.substr(pos4+1,string::npos);
										lua_pushstring(L,func.c_str());
										lua_gettable(L,-2);
										Lunar<Unit>::push(L, (Unit*)plr);
										lua_pushinteger(L, evt);
										if(obj == NULL) lua_pushnil(L);
										else switch(obj->GetTypeId())
										{
											case TYPEID_UNIT:
											case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
											case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
											default: lua_pushnil(L);
										}
										( (pArena != NULL) ? lua_pushstring(L, pArena->m_name.c_str()) : lua_pushnil(L) );
										lua_pushinteger(L, (misc1 == true) ? 1 : 0);
										lua_pushinteger(L, (misc2 == true) ? 1 : 0);
										int r = lua_pcall(L,6,LUA_MULTRET,0);
										if(r) report(L);
										m_Lock.Release();
										return;
									}
								}
							}
							else
							{
								m_Lock.Acquire();
								string func = pString.substr(pos3+1,string::npos);
								lua_pushstring(L,func.c_str());
								lua_gettable(L,-2);
								Lunar<Unit>::push(L, (Unit*)plr);
								lua_pushinteger(L, evt);
								if(obj == NULL) lua_pushnil(L);
								else switch(obj->GetTypeId())
								{
									case TYPEID_UNIT:
									case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
									case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
									default: lua_pushnil(L);
								}
								( (pArena != NULL) ? lua_pushstring(L, pArena->m_name.c_str()) : lua_pushnil(L) );
								lua_pushinteger(L, (misc1 == true) ? 1 : 0);
								lua_pushinteger(L, (misc2 == true) ? 1 : 0);
								int r = lua_pcall(L,6,LUA_MULTRET,0);
								if(r) report(L);
								m_Lock.Release();
								return;
							}
						}
					}
					else
					{
						m_Lock.Acquire();
						string func = pString.substr(pos2+1,string::npos);
						lua_pushstring(L,func.c_str());
						lua_gettable(L,-2);
						Lunar<Unit>::push(L, (Unit*)plr);
						lua_pushinteger(L, evt);
						if(obj == NULL) lua_pushnil(L);
						else switch(obj->GetTypeId())
						{
							case TYPEID_UNIT:
							case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
							case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
							default: lua_pushnil(L);
						}
						( (pArena != NULL) ? lua_pushstring(L, pArena->m_name.c_str()) : lua_pushnil(L) );
						lua_pushinteger(L, (misc1 == true) ? 1 : 0);
						lua_pushinteger(L, (misc2 == true) ? 1 : 0);
						int r = lua_pcall(L,6,LUA_MULTRET,0);
						if(r) report(L);
						m_Lock.Release();
						return;
					}
				}
			}
			else
			{
				m_Lock.Acquire();
				string func = pString.substr(pos1+1,string::npos);
				lua_pushstring(L,func.c_str());
				lua_gettable(L,-2);
				Lunar<Unit>::push(L, (Unit*)plr);
				lua_pushinteger(L, evt);
				if(obj == NULL) lua_pushnil(L);
				else switch(obj->GetTypeId())
				{
					case TYPEID_UNIT:
					case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
					case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
					default: lua_pushnil(L);
				}
				( (pArena != NULL) ? lua_pushstring(L, pArena->m_name.c_str()) : lua_pushnil(L) );
				lua_pushinteger(L, (misc1 == true) ? 1 : 0);
				lua_pushinteger(L, (misc2 == true) ? 1 : 0);
				int r = lua_pcall(L,6,LUA_MULTRET,0);
				if(r) report(L);
				m_Lock.Release();
				return;
			}
		}	
	}
	else
	{
		m_Lock.Acquire();
		lua_pushstring(L, FunctionName);
		lua_gettable(L, LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to call invalid LUA function '%s' from Arcemu! (GO)\n", FunctionName);
			
			return;
		}
		Lunar<Unit>::push(L, (Unit*)plr);
		lua_pushinteger(L, evt);
		if(obj == NULL) lua_pushnil(L);
		else switch(obj->GetTypeId())
		{
			case TYPEID_UNIT:
			case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
			case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
			default: lua_pushnil(L);
		}
		( (pArena != NULL) ? lua_pushstring(L, pArena->m_name.c_str()) : lua_pushnil(L) );
		lua_pushinteger(L, (misc1 == true) ? 1 : 0);
		lua_pushinteger(L, (misc2 == true) ? 1 : 0);
		int r = lua_pcall(L,6,LUA_MULTRET,0);
		if(r) report(L);
		m_Lock.Release();
	}
}
void LuaEngine::OnServerHook(Player * plr, uint32 evt,Object * obj, const char * FunctionName, Quest * pQuest, Guild * pGuild, SpellEntry * Sp)
{
	if(FunctionName==NULL) return;
	
	string pString = string(FunctionName);
	size_t pos1,pos2,pos3,pos4,pos5;
	string name1,name2,name3,name4,name5;
	char * key = ".";
	pos1 = pString.find(key);
	pos2 = pString.find(key,pos1+1);
	pos3 = pString.find(key,pos2+1);
	pos4 = pString.find(key,pos3+1);
	pos5 = pString.find(key,pos4+1);
	name1 = pString.substr(0,pos1);
	name2 = pString.substr(pos1+1,pos2-pos1-1);
	name3 = pString.substr(pos2+1,pos3-pos2-1);
	name4 = pString.substr(pos3+1,pos3-pos2-1);
	name5 = pString.substr(pos4+1,string::npos);
	if(pos1 != string::npos)
	{
		lua_pushstring(L,name1.c_str());
		lua_gettable(L,LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name1);
			
			return;
		}
		else if(lua_istable(L,-2))
		{
			if(pos2 != string::npos)
			{
				lua_pushstring(L,name2.c_str());
				lua_gettable(L,-2);
				if(lua_isnil(L,-1))
				{
					printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name2);
					
					return;
				}
				else if(lua_istable(L,-1))
				{
					if(pos3 != string::npos)
					{
						lua_pushstring(L,name3.c_str());
						lua_gettable(L,-2);
						if(lua_isnil(L,-1))
						{
							printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name3);
							
							return;
						}
						else if(lua_istable(L,-1))
						{
							if(pos4 != string::npos)
							{
								lua_pushstring(L,name4.c_str());
								lua_gettable(L,-2);
								if(lua_isnil(L,-1))
								{
									printf("Tried to access an invalid Lua table %s from Arcemu(GO). \n",name4);
									
									return;
								}
								else if(lua_istable(L,-1))
								{
									if(pos5 != string::npos)
									{
										lua_pushstring(L,name5.c_str());
										lua_gettable(L,-2);
										if(lua_isnil(L,-1))
										{
											printf("Tried to access and invalid Lua function %s from Arcemu(GO). \n",name5);
											
											return;
										}
										else if(lua_istable(L,-1))
										{
											printf("Reached maximum number of tables allowed. Aborting..... \n");
											
											return;
										}
									}
									else
									{
										m_Lock.Acquire();
										string func = pString.substr(pos4+1,string::npos);
										lua_pushstring(L,func.c_str());
										lua_gettable(L,-2);
										Lunar<Unit>::push(L, (Unit*)plr);
										lua_pushinteger(L, evt);
										if(obj == NULL) lua_pushnil(L);
										else switch(obj->GetTypeId())
										{
											case TYPEID_UNIT:
											case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
											case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
											default: lua_pushnil(L);
										}
										( (pQuest != NULL) ? lua_pushinteger(L, pQuest->id) : lua_pushnil(L));
										( (pGuild != NULL) ? lua_pushstring(L, pGuild->GetGuildName()) : lua_pushnil(L) );
										( (Sp != NULL) ? lua_pushinteger(L, Sp->Id) : lua_pushnil(L) );
										int r = lua_pcall(L,6,LUA_MULTRET,0);
										if(r)	report(L);
										m_Lock.Release();
										return;
									}
								}
							}
							else
							{
								m_Lock.Acquire();
								string func = pString.substr(pos3+1,string::npos);
								lua_pushstring(L,func.c_str());
								lua_gettable(L,-2);
								Lunar<Unit>::push(L, (Unit*)plr);
								lua_pushinteger(L, evt);
								if(obj == NULL) lua_pushnil(L);
								else switch(obj->GetTypeId())
								{
									case TYPEID_UNIT:
									case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
									case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
									default: lua_pushnil(L);
								}
								( (pQuest != NULL) ? lua_pushinteger(L, pQuest->id) : lua_pushnil(L));
								( (pGuild != NULL) ? lua_pushstring(L, pGuild->GetGuildName()) : lua_pushnil(L) );
								( (Sp != NULL) ? lua_pushinteger(L, Sp->Id) : lua_pushnil(L) );
								int r = lua_pcall(L,6,LUA_MULTRET,0);
								if(r)	report(L);
								m_Lock.Release();
								return;
							}
						}
					}
					else
					{
						m_Lock.Acquire();
						string func = pString.substr(pos2+1,string::npos);
						lua_pushstring(L,func.c_str());
						lua_gettable(L,-2);
						Lunar<Unit>::push(L, (Unit*)plr);
						lua_pushinteger(L, evt);
						if(obj == NULL) lua_pushnil(L);
						else switch(obj->GetTypeId())
						{
							case TYPEID_UNIT:
							case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
							case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
							default: lua_pushnil(L);
						}
						( (pQuest != NULL) ? lua_pushinteger(L, pQuest->id) : lua_pushnil(L));
						( (pGuild != NULL) ? lua_pushstring(L, pGuild->GetGuildName()) : lua_pushnil(L) );
						( (Sp != NULL) ? lua_pushinteger(L, Sp->Id) : lua_pushnil(L) );
						int r = lua_pcall(L,6,LUA_MULTRET,0);
						if(r)	report(L);
						m_Lock.Release();
						return;
					}
				}
			}
			else
			{
				m_Lock.Acquire();
				string func = pString.substr(pos1+1,string::npos);
				lua_pushstring(L,func.c_str());
				lua_gettable(L,-2);
				Lunar<Unit>::push(L, (Unit*)plr);
				lua_pushinteger(L, evt);
				if(obj == NULL) lua_pushnil(L);
				else switch(obj->GetTypeId())
				{
					case TYPEID_UNIT:
					case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
					case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
					default: lua_pushnil(L);
				}
				( (pQuest != NULL) ? lua_pushinteger(L, pQuest->id) : lua_pushnil(L));
				( (pGuild != NULL) ? lua_pushstring(L, pGuild->GetGuildName()) : lua_pushnil(L) );
				( (Sp != NULL) ? lua_pushinteger(L, Sp->Id) : lua_pushnil(L) );
				int r = lua_pcall(L,6,LUA_MULTRET,0);
				if(r)	report(L);
				m_Lock.Release();
				return;
			}
		}	
	}
	else
	{
		m_Lock.Acquire();
		lua_pushstring(L, FunctionName);
		lua_gettable(L, LUA_GLOBALSINDEX);
		if(lua_isnil(L,-1))
		{
			printf("Tried to call invalid LUA function '%s' from Arcemu! (GO)\n", FunctionName);
			
			return;
		}

		Lunar<Unit>::push(L, (Unit*)plr);
		lua_pushinteger(L, evt);
		if(obj == NULL) lua_pushnil(L);
		else switch(obj->GetTypeId())
		{
			case TYPEID_UNIT:
			case TYPEID_PLAYER: Lunar<Unit>::push(L, (Unit*)obj);
			case TYPEID_GAMEOBJECT: Lunar<GameObject>::push(L, (GameObject*)obj);
			default: lua_pushnil(L);
		}
		( (pQuest != NULL) ? lua_pushinteger(L, pQuest->id) : lua_pushnil(L));
		( (pGuild != NULL) ? lua_pushstring(L, pGuild->GetGuildName()) : lua_pushnil(L) );
		( (Sp != NULL) ? lua_pushinteger(L, Sp->Id) : lua_pushnil(L) );
		int r = lua_pcall(L,6,LUA_MULTRET,0);
		if(r)	report(L);
		m_Lock.Release();
	}
}
#endif

static int RegisterUnitEvent(lua_State * L);
static int ModifyUnitEvent(lua_State * L);
static int RemoveUnitEvent(lua_State * L);
static int RegisterQuestEvent(lua_State * L);
static int RegisterGameObjectEvent(lua_State * L);
static int RegisterUnitGossipEvent(lua_State * L);
static int RegisterItemGossipEvent(lua_State * L);
static int RegisterGOGossipEvent(lua_State * L);
#ifdef ENABLE_LUA_HOOKS
static int RegisterServerHookEvent(lua_State * L);
static int ModifyServerHookEvent(lua_State * L);
static int RemoveServerHookEvent(lua_State * L);
static int CheckBoolResult(lua_State * L);
#endif
static int WorldQuery(lua_State * L);

void LuaEngine::RegisterCoreFunctions()
{
	// Unit funcs //
	lua_pushcfunction(L, &RegisterUnitEvent);
	lua_setglobal(L, "RegisterUnitEvent");

	lua_pushcfunction(L,&ModifyUnitEvent);
	lua_setglobal(L,"ModifyUnitEvent");

	lua_pushcfunction(L,&RemoveUnitEvent);
	lua_setglobal(L,"RemoveUnitEvent");
	// GameObject funcs//

	lua_pushcfunction(L, &RegisterGameObjectEvent);
	lua_setglobal(L, "RegisterGameObjectEvent");

	// Quest funcs //
	lua_pushcfunction(L, &RegisterQuestEvent);
	lua_setglobal(L, "RegisterQuestEvent");
    // Unit, Item, GO gossip stuff
    lua_pushcfunction(L, &RegisterUnitGossipEvent);
	lua_setglobal(L, "RegisterUnitGossipEvent"); 
 
    lua_pushcfunction(L, &RegisterItemGossipEvent);
	lua_setglobal(L, "RegisterItemGossipEvent"); 

   	lua_pushcfunction(L, &RegisterGOGossipEvent);
	lua_setglobal(L, "RegisterGOGossipEvent");

#ifdef ENABLE_LUA_HOOKS
	lua_pushcfunction(L, &RegisterServerHookEvent);
	lua_setglobal(L, "RegisterServerHookEvent");

	lua_pushcfunction(L, &ModifyServerHookEvent);
	lua_setglobal(L, "ModifyServerHookEvent");

	lua_pushcfunction(L, &RemoveServerHookEvent);
	lua_setglobal(L, "RemoveServerHookEvent");

	lua_pushcfunction(L, &CheckBoolResult);
	lua_setglobal(L, "CheckBoolResult");
#endif

	lua_pushcfunction(L, &WorldQuery);
	lua_setglobal(L, "WorldQuery");
	
	Lunar<Unit>::Register(L);
	Lunar<Item>::Register(L);
	Lunar<GameObject>::Register(L);
	//Lunar<Quest>::Register(L); quest isn't a class
}
static int WorldQuery(lua_State * L)
{
	const char * query = luaL_checkstring(L,1);
	if(!query) return 0;
	QueryResult * qry = g_luaMgr.WorldQuery(query);
	if(qry != NULL) lua_pushboolean(L,1);
	else lua_pushboolean(L,0);
	return 1;
}

static int RegisterUnitEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str || !lua_is_starting_up)
		return 0;

	g_luaMgr.RegisterUnitEvent(entry,ev,str);
	return 0;
}

static int RegisterQuestEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str || !lua_is_starting_up)
		return 0;

	g_luaMgr.RegisterQuestEvent(entry,ev,str);
	return 0;
}

static int RegisterGameObjectEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str || !lua_is_starting_up)
		return 0;

	g_luaMgr.RegisterGameObjectEvent(entry,ev,str);
	return 0;
}
// Gossip stuff
static int RegisterUnitGossipEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str || !lua_is_starting_up)
		return 0;

    g_luaMgr.RegisterUnitGossipEvent(entry, ev, str);
	return 0;
}
static int ModifyUnitEvent(lua_State * L)
{
	int entry = luaL_checkint(L,1);
	int ev = luaL_checkint(L,2);
	const char * str = luaL_checkstring(L,3);
	const char * newstr = luaL_checkstring(L,4);
	if(!entry || !ev) return 0;
	g_luaMgr.ModifyUnitEvent(entry,ev,str,newstr);
	return 0;
}
static int RemoveUnitEvent(lua_State * L)
{
	int entry = luaL_checkint(L,1);
	int ev = luaL_checkint(L,2);
	const char * str = luaL_checkstring(L,3);
	if(!entry || !ev) return 0;
	g_luaMgr.RemoveUnitEvent(entry,ev,str);
	return 0;
}

static int RegisterItemGossipEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str || !lua_is_starting_up)
		return 0;

    g_luaMgr.RegisterItemGossipEvent(entry, ev, str);
	return 0;
}

static int RegisterGOGossipEvent(lua_State * L)
{
	int entry = luaL_checkint(L, 1);
	int ev = luaL_checkint(L, 2);
	const char * str = luaL_checkstring(L, 3);

	if(!entry || !ev || !str || !lua_is_starting_up)
		return 0;

    g_luaMgr.RegisterGOGossipEvent(entry, ev, str);
	return 0;
}
#ifdef ENABLE_LUA_HOOKS
static int RegisterServerHookEvent(lua_State * L)
{
	uint32 evt = luaL_checkint(L,1);
	const char * str = luaL_checkstring(L,2);
	if(!evt || !lua_is_starting_up ) return 0;
	g_luaMgr.RegisterServerHookEvent(evt, str);
	return 0;
}
static int ModifyServerHookEvent(lua_State * L)
{
	uint32 evt = luaL_checkint(L,1);
	const char * str = luaL_checkstring(L,2);
	const char * newfunc = luaL_checkstring(L, 3);
	if(!evt) return 0;
	g_luaMgr.ModifyServerHookEvent(evt, str,newfunc);
	return 0;
}
static int RemoveServerHookEvent(lua_State * L)
{
	uint32 evt = luaL_checkint(L,1);
	const char * str = luaL_checkstring(L,2);
	if(!evt) return 0;
	g_luaMgr.RemoveServerHookEvent(evt, str);
	return 0;
}
static int CheckBoolResult(lua_State * L)
{
	uint32 evt = luaL_checkint(L,1);
	const char * func = luaL_checkstring(L,2);
	if(evt == 0 || func == NULL) return 0;
	bool choice = g_luaMgr.CheckBoolResult(evt,func);
	lua_pushboolean(L, (choice == true) ? 1 : 0);
	return 1;
}
#endif

/************************************************************************/
/* Manager Stuff                                                        */
/************************************************************************/
class LuaCreature : public CreatureAIScript
{
public:
	LuaCreature(Creature* creature) : CreatureAIScript(creature) {};
	~LuaCreature() {};

	void OnCombatStart(Unit* mTarget)
	{
		uint32 evt = CREATURE_EVENT_ON_ENTER_COMBAT;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,0);
			}
	}

	void OnCombatStop(Unit* mTarget)
	{
		uint32 evt = CREATURE_EVENT_ON_LEAVE_COMBAT;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,0);
			}
	}
	void OnTargetDied(Unit* mTarget)
	{
		uint32 evt = CREATURE_EVENT_ON_TARGET_DIED;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,0);
			}
	}

	void OnDied(Unit* mKiller)
	{
		uint32 evt = CREATURE_EVENT_ON_DIED;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mKiller,0);
			}
	}
	void OnTargetParried(Unit* mTarget)
	{
		uint32 evt = CREATURE_EVENT_ON_TARGET_PARRIED;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,0);
			}
	}
	void OnTargetDodged(Unit* mTarget)
	{
		uint32 evt = CREATURE_EVENT_ON_TARGET_DODGED;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,0);
			}
	}
	void OnTargetBlocked(Unit* mTarget, int32 iAmount)
	{
		uint32 evt = CREATURE_EVENT_ON_TARGET_BLOCKED;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,iAmount);
			}
	}
	void OnTargetCritHit(Unit* mTarget, float fAmount)
	{
		uint32 evt = CREATURE_EVENT_ON_TARGET_CRIT_HIT;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,fAmount);
			}
	}
	void OnParried(Unit* mTarget)
	{
		uint32 evt = CREATURE_EVENT_ON_PARRY;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,0);
			}
	}
	void OnDodged(Unit* mTarget)
	{
		uint32 evt = CREATURE_EVENT_ON_DODGED;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,0);
			}
	}
	void OnBlocked(Unit* mTarget, int32 iAmount)
	{
		uint32 evt = CREATURE_EVENT_ON_BLOCKED;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,iAmount);
			}
	}
	void OnCritHit(Unit* mTarget, float fAmount)
	{
		uint32 evt = CREATURE_EVENT_ON_CRIT_HIT;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,fAmount);
			}
	}
	void OnHit(Unit* mTarget, float fAmount)
	{
		uint32 evt = CREATURE_EVENT_ON_HIT;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mTarget,fAmount);
			}
	}
	void OnAssistTargetDied(Unit* mAssistTarget)
	{
		uint32 evt = CREATURE_EVENT_ON_ASSIST_TARGET_DIED;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mAssistTarget,0);
			}
	}
	void OnFear(Unit* mFeared, uint32 iSpellId)
	{
		uint32 evt = CREATURE_EVENT_ON_FEAR;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mFeared,iSpellId);
			}
	}
	void OnFlee(Unit* mFlee)
	{
		uint32 evt = CREATURE_EVENT_ON_FLEE;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mFlee,0);
			}
	}
	void OnCallForHelp()
	{
		uint32 evt = CREATURE_EVENT_ON_CALL_FOR_HELP;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, NULL,0);
			}
	}
	void OnLoad()
	{
		uint32 evt = CREATURE_EVENT_ON_LOAD;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, NULL,0);
			}
	}
	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		uint32 evt = CREATURE_EVENT_ON_REACH_WP;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, NULL,iWaypointId,bForwards);
			}
	}
	void OnLootTaken(Player* pPlayer, ItemPrototype *pItemPrototype)
	{
		uint32 evt = CREATURE_EVENT_ON_LOOT_TAKEN;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, pPlayer,pItemPrototype);
			}
	}
	void AIUpdate()
	{
		uint32 evt = CREATURE_EVENT_ON_AIUPDATE;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, NULL,0);
			}
	}
	void OnEmote(Player* pPlayer, EmoteType Emote)
	{
		uint32 evt = CREATURE_EVENT_ON_EMOTE;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, NULL, uint32(Emote));
			}
	}
	void StringFunctionCall(const char * pFunction)
	{
		g_engine.CallFunction(_unit, pFunction );
	}
	void OnDamageTaken(Unit* mAttacker, float fAmount)
	{
		uint32 evt = CREATURE_EVENT_ON_DAMAGE_TAKEN;
		if( m_binding[evt].size() != NULL)
			for(list<const char*>::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++)
			{
				if( (*itr) != NULL)
					g_engine.OnUnitEvent( _unit, (*itr), evt, mAttacker, fAmount);
			}
	}

	void Destroy()
	{
		delete this;
	}

	LuaUnitBinding * m_binding;
};


class LuaGameObject : public GameObjectAIScript
{
public:
	LuaGameObject(GameObject* go) : GameObjectAIScript(go) {}
	~LuaGameObject() {}

		void OnCreate()
	{
		if( m_binding->Functions[GAMEOBJECT_EVENT_ON_CREATE] != NULL )
			g_engine.OnGameObjectEvent( _gameobject, m_binding->Functions[GAMEOBJECT_EVENT_ON_CREATE], GAMEOBJECT_EVENT_ON_CREATE, NULL, 0, NULL );
	}
	void OnSpawn()
	{
		if( m_binding->Functions[GAMEOBJECT_EVENT_ON_SPAWN] != NULL )
			g_engine.OnGameObjectEvent( _gameobject, m_binding->Functions[GAMEOBJECT_EVENT_ON_SPAWN], GAMEOBJECT_EVENT_ON_SPAWN, NULL, 0, NULL );
	}
	void OnDespawn()
	{
		if( m_binding->Functions[GAMEOBJECT_EVENT_ON_DESPAWN] != NULL )
			g_engine.OnGameObjectEvent( _gameobject, m_binding->Functions[GAMEOBJECT_EVENT_ON_DESPAWN], GAMEOBJECT_EVENT_ON_DESPAWN, NULL, 0, NULL );
	}
	void OnLootTaken(Player* pLooter, ItemPrototype *pItemInfo)
	{
		if( m_binding->Functions[GAMEOBJECT_EVENT_ON_LOOT_TAKEN] != NULL )
			g_engine.OnGameObjectEvent( _gameobject, m_binding->Functions[GAMEOBJECT_EVENT_ON_LOOT_TAKEN], GAMEOBJECT_EVENT_ON_LOOT_TAKEN, pLooter,0, pItemInfo );
	}
	void OnActivate(Player* pPlayer)
	{
		if( m_binding->Functions[GAMEOBJECT_EVENT_ON_USE] != NULL )
			g_engine.OnGameObjectEvent( _gameobject, m_binding->Functions[GAMEOBJECT_EVENT_ON_USE], GAMEOBJECT_EVENT_ON_USE, pPlayer, 0, NULL );
	}
	
	void AIUpdate()
	{
		if( m_binding->Functions[GAMEOBJECT_EVENT_AIUPDATE] != NULL )
			g_engine.OnGameObjectEvent( _gameobject, m_binding->Functions[GAMEOBJECT_EVENT_AIUPDATE], GAMEOBJECT_EVENT_AIUPDATE, NULL, 0, NULL );
	}
	void Destroy ()
	{
		delete this;
	}

	LuaGameObjectBinding * m_binding;
};

class LuaGossip : public GossipScript
{
public:
	LuaGossip() : GossipScript() {}
	~LuaGossip() {}

	void GossipHello(Object* pObject, Player* Plr, bool AutoSend) // Dont need GossipHello for GO's
	{
        if(pObject->GetTypeId() == TYPEID_UNIT)
        {
            if( m_unit_gossip_binding->Functions[GOSSIP_EVENT_ON_TALK] != NULL )
			    g_engine.OnGossipEvent( pObject, m_unit_gossip_binding->Functions[GOSSIP_EVENT_ON_TALK], GOSSIP_EVENT_ON_TALK, Plr, NULL, NULL, NULL );
        }
        else if(pObject->GetTypeId() == TYPEID_ITEM)
        {
            if( m_item_gossip_binding->Functions[GOSSIP_EVENT_ON_TALK] != NULL )
			    g_engine.OnGossipEvent( pObject, m_item_gossip_binding->Functions[GOSSIP_EVENT_ON_TALK], GOSSIP_EVENT_ON_TALK, Plr, NULL, NULL, NULL );
        }
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char * EnteredCode)
	{
        if(pObject->GetTypeId() == TYPEID_UNIT)
        {
            if( m_unit_gossip_binding->Functions[GOSSIP_EVENT_ON_SELECT_OPTION] != NULL )
			    g_engine.OnGossipEvent( pObject, m_unit_gossip_binding->Functions[GOSSIP_EVENT_ON_SELECT_OPTION], GOSSIP_EVENT_ON_SELECT_OPTION, Plr, Id, IntId, EnteredCode);
        }
        else if(pObject->GetTypeId() == TYPEID_ITEM)
        {
            if( m_item_gossip_binding->Functions[GOSSIP_EVENT_ON_SELECT_OPTION] != NULL )
                g_engine.OnGossipEvent( pObject, m_item_gossip_binding->Functions[GOSSIP_EVENT_ON_SELECT_OPTION], GOSSIP_EVENT_ON_SELECT_OPTION, Plr, Id, IntId, EnteredCode);
        }
        else if(pObject->GetTypeId() == TYPEID_GAMEOBJECT)
        {
            if( m_go_gossip_binding->Functions[GOSSIP_EVENT_ON_SELECT_OPTION] != NULL )
                g_engine.OnGossipEvent( pObject, m_go_gossip_binding->Functions[GOSSIP_EVENT_ON_SELECT_OPTION], GOSSIP_EVENT_ON_SELECT_OPTION, Plr, Id, IntId, EnteredCode);
        }
	}

	void GossipEnd(Object* pObject, Player* Plr)
	{
        if(pObject->GetTypeId() == TYPEID_UNIT)
        {
		    if( m_unit_gossip_binding->Functions[GOSSIP_EVENT_ON_END] != NULL )
			    g_engine.OnGossipEvent( pObject, m_unit_gossip_binding->Functions[GOSSIP_EVENT_ON_END], GOSSIP_EVENT_ON_END, Plr, NULL, NULL, NULL );
        }
        else if(pObject->GetTypeId() == TYPEID_ITEM)
        {
            if( m_item_gossip_binding->Functions[GOSSIP_EVENT_ON_END] != NULL )
			    g_engine.OnGossipEvent( pObject, m_item_gossip_binding->Functions[GOSSIP_EVENT_ON_END], GOSSIP_EVENT_ON_END, Plr, NULL, NULL, NULL );
        }
        else if(pObject->GetTypeId() == TYPEID_GAMEOBJECT)
        {
            if( m_go_gossip_binding->Functions[GOSSIP_EVENT_ON_END] != NULL )
			    g_engine.OnGossipEvent( pObject, m_go_gossip_binding->Functions[GOSSIP_EVENT_ON_END], GOSSIP_EVENT_ON_END, Plr, NULL, NULL, NULL );
        }
	}

	LuaUnitGossipBinding * m_unit_gossip_binding;
	LuaItemGossipBinding * m_item_gossip_binding;
    LuaGOGossipBinding * m_go_gossip_binding;
};

class LuaQuest : public QuestScript
{
public:
	LuaQuest() : QuestScript() {}
	~LuaQuest() {}

	void OnQuestStart(Player* mTarget, QuestLogEntry *qLogEntry)
	{
		if( m_binding->Functions[QUEST_EVENT_ON_ACCEPT] != NULL )
			g_engine.OnQuestEvent( mTarget, m_binding->Functions[QUEST_EVENT_ON_ACCEPT], qLogEntry->GetQuest()->id, QUEST_EVENT_ON_ACCEPT, mTarget, 0, 0 );
	}

	void OnQuestComplete(Player* mTarget, QuestLogEntry *qLogEntry)
	{
		if( m_binding->Functions[QUEST_EVENT_ON_COMPLETE] != NULL )
			g_engine.OnQuestEvent( mTarget, m_binding->Functions[QUEST_EVENT_ON_COMPLETE], qLogEntry->GetQuest()->id, QUEST_EVENT_ON_COMPLETE, mTarget, 0, 0 );
	}
	void OnQuestCancel(Player* mTarget)
	{
		if( m_binding->Functions[QUEST_EVENT_ON_CANCEL] != NULL )
			g_engine.OnQuestEvent( mTarget, m_binding->Functions[QUEST_EVENT_ON_CANCEL], 0, QUEST_EVENT_ON_CANCEL, mTarget, 0 , 0 );
	}
	void OnGameObjectActivate(uint32 entry, Player* mTarget, QuestLogEntry *qLogEntry)
	{
		if( m_binding->Functions[QUEST_EVENT_GAMEOBJECT_ACTIVATE] != NULL )
			g_engine.OnQuestEvent( mTarget, m_binding->Functions[QUEST_EVENT_GAMEOBJECT_ACTIVATE], qLogEntry->GetQuest()->id, QUEST_EVENT_GAMEOBJECT_ACTIVATE, mTarget, entry, 0 );
	}
	void OnCreatureKill(uint32 entry, Player* mTarget, QuestLogEntry *qLogEntry)
	{
		if( m_binding->Functions[QUEST_EVENT_ON_CREATURE_KILL] != NULL )
			g_engine.OnQuestEvent( mTarget, m_binding->Functions[QUEST_EVENT_ON_CREATURE_KILL], qLogEntry->GetQuest()->id, QUEST_EVENT_ON_CREATURE_KILL, mTarget, entry , 0 );
	}
	void OnExploreArea(uint32 areaId, Player* mTarget, QuestLogEntry *qLogEntry)
	{
		if( m_binding->Functions[QUEST_EVENT_ON_EXPLORE_AREA] != NULL )
			g_engine.OnQuestEvent( mTarget, m_binding->Functions[QUEST_EVENT_ON_EXPLORE_AREA], qLogEntry->GetQuest()->id, QUEST_EVENT_ON_EXPLORE_AREA, mTarget, areaId, 0 );
	}
	void OnPlayerItemPickup(uint32 itemId, uint32 totalCount, Player* mTarget, QuestLogEntry *qLogEntry)
	{
		if( m_binding->Functions[QUEST_EVENT_ON_PLAYER_ITEMPICKUP] != NULL )
			g_engine.OnQuestEvent( mTarget, m_binding->Functions[QUEST_EVENT_ON_PLAYER_ITEMPICKUP], qLogEntry->GetQuest()->id, QUEST_EVENT_ON_PLAYER_ITEMPICKUP, mTarget, itemId, totalCount );
	}

	LuaQuestBinding * m_binding;
};
#ifdef ENABLE_LUA_HOOKS
class pHookInterface : public LuaHookInterface
{
protected:
	LuaSHBinding * m_binding;
	CompleteMap* compmap;
public:
	pHookInterface() : compmap(new CompleteMap), m_binding(NULL) {}
	friend class LuaEngineMgr; 
	//accessors
	void SetBinding(LuaSHBinding* nBinding ) { m_binding = nBinding; }
	CompleteMap* GetCompleteMap() { return compmap; }
	//LuaSHBinding GetBinding()  { return m_binding[NUM_SERVER_HOOKS]; }
	//end
	bool lOnNewCharacter(uint32 Race, uint32 Class, WorldSession * Session, const char * Name)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_NEW_CHARACTER;
		bool ret = holdbools[evt];
		if( m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook(NULL,evt,NULL,(*itr), Race, Class, Name, NULL); }
		}
		return ret;
	}
	void lOnKillPlayer(Player* pPlayer, Player* pVictim)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_KILL_PLAYER;
		if( m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, pVictim,(*itr)); }
		}
	}
	void lOnFirstEnterWorld(Player* pPlayer)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_FIRST_ENTER_WORLD;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr)); }
		}
	}
	void lOnEnterWorld(Player* pPlayer)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_ENTER_WORLD;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr)); }
		}
	}
	void lOnGuildCreate(Player* pLeader, Guild * pGuild)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_GUILD_CREATE;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pLeader, evt, NULL, (*itr), NULL, pGuild, NULL); }
		}
	}
	void lOnGuildJoin(Player* pPlayer, Guild * pGuild)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_GUILD_JOIN;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr), NULL, pGuild, NULL); }
		}
	}
	void lOnDeath(Player* pPlayer)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_DEATH;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer,evt,NULL, (*itr)); }
		}
	}
	bool lOnRepop(Player* pPlayer)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_REPOP;
		bool ret = holdbools[evt];
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer,evt,NULL, (*itr));
				pHoldBoolsByChar * nmap = &(*compmap)[evt];
				if(nmap != NULL) nmap->insert(make_pair((*itr),ret)); }
		}
		return ret;
	}
	void lOnEmote(Player* pPlayer, uint32 Emote)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_EMOTE;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL,(*itr), Emote); }
		}
	}
	void lOnEnterCombat(Player* pPlayer, Unit* pTarget)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_ENTER_COMBAT;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, pTarget, (*itr)); }
		}
	}
	bool lOnCastSpell(Player* pPlayer, SpellEntry * pSpell)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_CAST_SPELL;
		bool ret = holdbools[evt];
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook(pPlayer, evt, NULL, (*itr), NULL, NULL, pSpell);
				pHoldBoolsByChar * nmap =  &(*compmap)[evt];
				if(nmap != NULL) nmap->insert(make_pair((*itr),ret)); }
		}
		return ret;
	}
	bool lOnLogoutRequest(Player* pPlayer)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_LOGOUT_REQUEST;
		bool ret = holdbools[evt];
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) 
			{
				if( (*itr) != NULL)
				g_engine.OnServerHook(pPlayer, evt, NULL, (*itr));
				pHoldBoolsByChar * nmap =  &(*compmap)[evt];
				if(nmap != NULL) nmap->insert(make_pair((*itr),ret)); }
		}
		return ret;
	}
	void lOnLogout(Player* pPlayer)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_LOGOUT;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook(pPlayer, evt, NULL, (*itr)); }

		}
	}
	void lOnQuestAccept(Player* pPlayer, Quest * pQuest)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_QUEST_ACCEPT;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
					g_engine.OnServerHook(pPlayer, evt, NULL, (*itr), pQuest, NULL, NULL); }
		}
	}
	void lOnZone(Player* pPlayer, uint32 Zone)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_ZONE;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr), Zone); }
		}
	}
	bool lOnChat(Player* pPlayer, uint32 Type, uint32 Lang, const char * Message, const char * Misc)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_CHAT;
		bool ret = holdbools[evt];
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer,evt,NULL,(*itr),Type,Lang,Message,Misc);
				pHoldBoolsByChar * nmap = &(*compmap)[evt];
				if(nmap != NULL) nmap->insert(make_pair((*itr),ret)); }
		}
		return holdbools[evt];
	}
	/*void lOnLoot(Player*  pPlayer, Unit*  pTarget, uint32 Money, uint32 ItemId)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_AREATRIGGER;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, pTarget, (*itr), Money, ItemId); }
		}
	}*/
	void lOnEnterWorld2(Player*  pPlayer)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_ENTER_WORLD_2;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr)); }
		}
	}
	void lOnCharacterCreate(Player*  pPlayer)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_CHARACTER_CREATE;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr)); }
		}
	}
	void lOnQuestCancelled(Player*  pPlayer, Quest * pQuest)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_QUEST_CANCELLED;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr), pQuest, NULL, NULL); }
		}
	}
	void lOnQuestFinished(Player* pPlayer, Quest * pQuest)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_QUEST_FINISHED;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr), pQuest, NULL, NULL); }
		}
	}
	void lOnHonorableKill(Player*  pPlayer, Player*  pKilled)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_HONORABLE_KILL;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, pKilled, (*itr)); }
		}
	}
	void lOnArenaFinish(Player*  pPlayer, ArenaTeam* pTeam, bool victory, bool rated)
	{
		int32 evt = SERVER_HOOK_EVENT_ON_ARENA_FINISH;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr), pTeam, victory, rated); }
		}
	}
	void lOnAreaTrigger(Player* pPlayer, uint32 areaTrigger)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_AREATRIGGER;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
				g_engine.OnServerHook( pPlayer, evt, NULL, (*itr), areaTrigger); }
		}
	}
	void lOnAuraRemove(Player* pPlayer, uint32 spellID)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_AURA_REMOVE;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
					g_engine.OnServerHook(pPlayer,evt,NULL,(*itr),spellID,0);
			}
		}
	}
	void lOnPostSpellCast(Player* pPlayer, SpellEntry * pSpell, Unit* pTarget)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_POST_SPELL_CAST;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
					g_engine.OnServerHook(pPlayer,evt,pTarget,(*itr),NULL,NULL,pSpell);
			}
		}
	}
	void lOnContinentCreate(MapMgr* pMgr)
	{
		uint32 evt = SERVER_HOOK_EVENT_ON_CONTIENT_CREATE;
		if(m_binding[evt].size())
		{
			for(LuaSHBinding::iterator itr = m_binding[evt].begin(); itr != m_binding[evt].end(); itr++) {
				if( (*itr) != NULL)
					g_engine.OnServerHook(NULL,evt,NULL,(*itr),pMgr->GetMapId());
			}
		}
	}
};
#endif
CreatureAIScript * CreateLuaCreature(Creature* src)
{
	LuaUnitBinding * pBinding = g_luaMgr.GetUnitBinding( src->GetEntry() );

	LuaCreature * pLua = new LuaCreature(src);
	pLua->m_binding = pBinding;
	uint32 evt = CREATURE_EVENT_ON_CREATEAISCRIPT;
	for(LuaUnitBinding::iterator itr = pBinding[evt].begin(); itr != pBinding[evt].end(); itr++)
	{
		g_engine.OnUnitEvent( src,(*itr),evt,NULL,0);
	}
	return pLua;
}

GameObjectAIScript * CreateLuaGameObject(GameObject* src)
{
	LuaGameObjectBinding * pBinding = g_luaMgr.GetGameObjectBinding( src->GetEntry() );
	LuaGameObject * pLua = new LuaGameObject(src);
	pLua->m_binding = pBinding;
	return pLua;
}

QuestScript * CreateLuaQuestScript(uint32 id)
{
	LuaQuestBinding * pBinding = g_luaMgr.GetQuestBinding( id );
	LuaQuest * pLua = new LuaQuest();
	pLua->m_binding = pBinding;
	return pLua;
}
// Gossip stuff
GossipScript * CreateLuaUnitGossipScript(uint32 id)
{
    LuaUnitGossipBinding * pBinding = g_luaMgr.GetLuaUnitGossipBinding( id );
	LuaGossip * pLua = new LuaGossip();
	pLua->m_unit_gossip_binding = pBinding;
	return pLua;
}

GossipScript * CreateLuaItemGossipScript(uint32 id)
{
    LuaItemGossipBinding * pBinding = g_luaMgr.GetLuaItemGossipBinding( id );
	if( pBinding == NULL )
		return NULL;

	LuaGossip * pLua = new LuaGossip();
	pLua->m_item_gossip_binding = pBinding;
	return pLua;
}

GossipScript * CreateLuaGOGossipScript(uint32 id)
{
    LuaGOGossipBinding * pBinding = g_luaMgr.GetLuaGOGossipBinding( id );
	LuaGossip * pLua = new LuaGossip();
    pLua->m_go_gossip_binding = pBinding;
	return pLua;
}
/* LuaEngineMgr Constructor */
LuaEngineMgr::LuaEngineMgr() {
#ifdef ENABLE_LUA_HOOKS
	m_shBinding = new LuaSHBinding[NUM_SERVER_HOOKS];
	m_HookInterface = new pHookInterface;
#endif
}

#ifdef ENABLE_LUA_HOOKS
bool LuaEngineMgr::CheckBoolResult(uint32 evt, const char * functionname)
{
	ASSERT( evt < NUM_SERVER_HOOKS);
	pHoldBoolsByChar * nmap;
	switch(evt)
	{
	case 1:
	case 7:
	case 10:
	case 12:
	case 16:
		nmap = &(*m_HookInterface->GetCompleteMap())[evt];
		return (*nmap)[functionname];
	default:
		return true;
	}
}
#endif
void LuaEngineMgr::Startup()
{
	Log.Notice("Lua/BluaEngineMgr", "Spawning Lua Engine...");
	lua_is_starting_up = true;
	g_engine = m_engine;
	m_engine.LoadScripts();
	lua_is_starting_up = false;
#ifdef ENABLE_LUA_HOOKS
	m_HookInterface->SetBinding(m_shBinding);
#endif

	// stuff is registered, so lets go ahead and make our emulated C++ scripted lua classes.
	for(UnitBindingMap::iterator itr = m_unitBinding.begin(); itr != m_unitBinding.end(); ++itr)
	{
		m_scriptMgr->register_creature_script( itr->first, CreateLuaCreature );
	}

	for(GameObjectBindingMap::iterator itr = m_gameobjectBinding.begin(); itr != m_gameobjectBinding.end(); ++itr)
	{
		m_scriptMgr->register_gameobject_script( itr->first, CreateLuaGameObject );
	}

	for(QuestBindingMap::iterator itr = m_questBinding.begin(); itr != m_questBinding.end(); ++itr)
	{
		QuestScript * qs = CreateLuaQuestScript( itr->first );
		if( qs != NULL )
			m_scriptMgr->register_quest_script( itr->first, qs );
	}
    // Register Gossip Stuff
    for(GossipUnitScriptsBindingMap::iterator itr = m_unit_gossipBinding.begin(); itr != m_unit_gossipBinding.end(); ++itr)
	{
		GossipScript * gs = CreateLuaUnitGossipScript( itr->first );
		if( gs != NULL )
			m_scriptMgr->register_gossip_script( itr->first, gs );
    }

    for(GossipItemScriptsBindingMap::iterator itr = m_item_gossipBinding.begin(); itr != m_item_gossipBinding.end(); ++itr)
	{
		GossipScript * gs = CreateLuaItemGossipScript( itr->first );
		if( gs != NULL )
			m_scriptMgr->register_item_gossip_script( itr->first, gs );
    }

    for(GossipGOScriptsBindingMap::iterator itr = m_go_gossipBinding.begin(); itr != m_go_gossipBinding.end(); ++itr)
	{
		GossipScript * gs = CreateLuaGOGossipScript( itr->first );
		if( gs != NULL )
			m_scriptMgr->register_go_gossip_script( itr->first, gs );
    }
#ifdef ENABLE_LUA_HOOKS
	m_scriptMgr->register_lua_hook(m_HookInterface);
#endif
}

QueryResult * LuaEngineMgr::WorldQuery(const char * query)
{
	if(query == NULL) return NULL;
	QueryResult * Qr = WorldDatabase.Query(query);
	if(Qr != NULL) return Qr;
	else return NULL;
}

void LuaEngineMgr::RegisterUnitEvent(uint32 Id, uint32 Event, const char * FunctionName)
{
	ASSERT( Event < CREATURE_EVENT_COUNT);
	UnitBindingMap::iterator itr = m_unitBinding.find(Id);
	if(itr == m_unitBinding.end())
	{
		LuaUnitBinding * ub = new LuaUnitBinding[CREATURE_EVENT_COUNT];
		ub[Event].push_back(strdup(FunctionName));
		m_unitBinding.insert(make_pair(Id,ub));
	}
	else
	{
		if( itr->second[Event].size() != NULL)
		{
			for(LuaUnitBinding::iterator it = itr->second[Event].begin(); it != itr->second[Event].end(); it++)
			{
				if( (*it) == FunctionName)
				{
					printf("LuaEngineMgr::RegisterUnitEvent tried to register duplicate function %s",(*it));
					free( (void*)(*it));
					itr->second[Event].erase( it);
				}
			}
		}
		itr->second[Event].push_back(strdup(FunctionName));
	}
}
void LuaEngineMgr::ModifyUnitEvent(uint32 id, uint32 evt, const char *oldfunc, const char *newfunc)
{
	ASSERT( evt < CREATURE_EVENT_COUNT);
	UnitBindingMap::iterator itr = m_unitBinding.find(id);
	if( itr != m_unitBinding.end())
	{
		uint8 count = 0;
		if(itr->second[evt].size() != 0)
		{
			for(LuaUnitBinding::iterator it = itr->second[evt].begin(); it != itr->second[evt].end(); it++)
			{
				count++;
				if( (*it) != NULL && !strcmp( (*it),oldfunc))
				{
					free((void*)(*it));
					itr->second[evt].erase(it);
					itr->second[evt].push_back(newfunc);
				}
			}
			if(count == itr->second[evt].size())
				itr->second[evt].push_back(newfunc);
		}
	}
}
void LuaEngineMgr::RemoveUnitEvent(uint32 id, uint32 evt, const char * FunctionName)
{
	UnitBindingMap::iterator itr = m_unitBinding.find(id);
	if(itr != m_unitBinding.end())
	{
		uint8 count = 0;
		if(itr->second[evt].size() != 0)
		{
			for(LuaUnitBinding::iterator it = itr->second[evt].begin(); it != itr->second[evt].end(); it++)
			{
				count++;
				if( (*it) != NULL && !strcmp( (*it), FunctionName))
				{
					free( (void*)(*it));
					itr->second[evt].erase(it);
				}
			}
			if(count == itr->second[evt].size())
				printf("LuaEngineMgr::RemoveUnitEvent : Failed to locate function %s in creature id %u and event %u. \n",FunctionName,id,evt);
		}
	}
}

void LuaEngineMgr::RegisterQuestEvent(uint32 Id, uint32 Event, const char * FunctionName)
{
	QuestBindingMap::iterator itr = m_questBinding.find(Id);
	if(itr == m_questBinding.end())
	{
		LuaQuestBinding qb;
		memset(&qb,0,sizeof(LuaQuestBinding));
		qb.Functions[Event] = strdup(FunctionName);
		m_questBinding.insert(make_pair(Id,qb));
	}
	else
	{
		if(itr->second.Functions[Event]!=NULL)
			free((void*)itr->second.Functions[Event]);

		itr->second.Functions[Event]=strdup(FunctionName);
	}
}
void LuaEngineMgr::RegisterGameObjectEvent(uint32 Id, uint32 Event, const char * FunctionName)
{
	GameObjectBindingMap::iterator itr = m_gameobjectBinding.find(Id);
	if(itr == m_gameobjectBinding.end())
	{
		LuaGameObjectBinding ub;
		memset(&ub,0,sizeof(LuaGameObjectBinding));
		ub.Functions[Event] = strdup(FunctionName);
		m_gameobjectBinding.insert(make_pair(Id,ub));
	}
	else
	{
		if(itr->second.Functions[Event]!=NULL)
			free((void*)itr->second.Functions[Event]);

		itr->second.Functions[Event]=strdup(FunctionName);
	}
}
// Gossip Events
void LuaEngineMgr::RegisterUnitGossipEvent(uint32 Id, uint32 Event, const char * FunctionName)
{
    GossipUnitScriptsBindingMap::iterator itr = m_unit_gossipBinding.find(Id);
 
    if(itr == m_unit_gossipBinding.end())
	{
		LuaUnitGossipBinding gb;
		memset(&gb, 0, sizeof(LuaUnitGossipBinding));
		gb.Functions[Event] = strdup(FunctionName);
		m_unit_gossipBinding.insert(make_pair(Id, gb));
	}
	else
	{
		if(itr->second.Functions[Event]!=NULL)
			free((void*)itr->second.Functions[Event]);

		itr->second.Functions[Event]=strdup(FunctionName);
	}
}

void LuaEngineMgr::RegisterItemGossipEvent(uint32 Id, uint32 Event, const char * FunctionName)
{
    GossipItemScriptsBindingMap::iterator itr = m_item_gossipBinding.find(Id);

    if(itr == m_item_gossipBinding.end())
	{
		LuaItemGossipBinding gb;
		memset(&gb, 0, sizeof(LuaItemGossipBinding));
		gb.Functions[Event] = strdup(FunctionName);
		m_item_gossipBinding.insert(make_pair(Id, gb));
	}
	else
	{
		if(itr->second.Functions[Event]!=NULL)
			free((void*)itr->second.Functions[Event]);

		itr->second.Functions[Event]=strdup(FunctionName);
	}
}

#ifdef ENABLE_LUA_HOOKS
void LuaEngineMgr::RegisterServerHookEvent(uint32 evt, const char *FunctionName)
{
	ASSERT( evt < NUM_SERVER_HOOKS);
	if(m_shBinding[evt].size() != 0)
	{
		for(LuaSHBinding::iterator itr = m_shBinding[evt].begin(); itr != m_shBinding[evt].end(); itr++)
			{
			if( (*itr) != NULL && !strcmp( (*itr),FunctionName))
			{
				free( (void*)(*itr));
				(*itr) = NULL;
				m_shBinding[evt].erase(itr);
			}
		}
	}
	m_shBinding[evt].push_back(strdup(FunctionName));
}
void LuaEngineMgr::ModifyServerHookEvent(uint32 evt, const char * func1, const char * func2)
{
	ASSERT( evt < NUM_SERVER_HOOKS);
	if(m_shBinding[evt].size() != 0)
	{
		uint8 count = 0;
		for(LuaSHBinding::iterator itr = m_shBinding[evt].begin(); itr != m_shBinding[evt].end(); itr++)
		{
			count++;
			if( (*itr) != NULL && !strcmp( (*itr), func1))
			{
				free( (void*)(*itr));
				(*itr) = NULL;
				m_shBinding[evt].erase(itr);
				m_shBinding[evt].push_back(strdup(func2));
			}
			if(count == m_shBinding[evt].size())
				m_shBinding[evt].push_back(strdup(func2));
		}
	}
}
void LuaEngineMgr::RemoveServerHookEvent(uint32 evt, const char * func)
{
	ASSERT( evt < NUM_SERVER_HOOKS);
	if(m_shBinding[evt].size() != 0)
	{
		for(LuaSHBinding::iterator itr = m_shBinding[evt].begin(); itr != m_shBinding[evt].end(); itr++)
		{
			if( (*itr) != NULL && !strcmp( (*itr),func))
			{
				delete (*itr);
				(*itr) = NULL;
				m_shBinding[evt].erase(itr);
			}
		}
	}
}
#endif

void LuaEngineMgr::RegisterGOGossipEvent(uint32 Id, uint32 Event, const char * FunctionName)
{
    GossipGOScriptsBindingMap::iterator itr = m_go_gossipBinding.find(Id);

    if(itr == m_go_gossipBinding.end())
	{
		LuaGOGossipBinding gb;
		memset(&gb, 0, sizeof(LuaGOGossipBinding));
		gb.Functions[Event] = strdup(FunctionName);
		m_go_gossipBinding.insert(make_pair(Id, gb));
	}
	else
	{
		if(itr->second.Functions[Event]!=NULL)
			free((void*)itr->second.Functions[Event]);

		itr->second.Functions[Event]=strdup(FunctionName);
	}
}

/*void LuaEngineMgr::ReloadScripts()
{
	m_lock.Acquire();

	// acquire the locks on all the luaengines so they don't do anything.
	for(LuaEngineMap::iterator itr = m_engines.begin(); itr != m_engines.end(); ++itr)
		itr->first->GetLock().Acquire();

	// remove all the function name bindings
	for(UnitBindingMap::iterator itr = m_unitBinding.begin(); itr != m_unitBinding.end(); ++itr)
	{
		for(uint32 i = 0; i < CREATURE_EVENT_COUNT; ++i)
			if(itr->second.Functions[i] != NULL)
				free((void*)itr->second.Functions[i]);
	}
	
	for(GameObjectBindingMap::iterator itr = m_gameobjectBinding.begin(); itr != m_gameobjectBinding.end(); ++itr)
	{
		for(uint32 i = 0; i < GAMEOBJECT_EVENT_COUNT; ++i)
			if(itr->second.Functions[i] != NULL)
				free((void*)itr->second.Functions[i]);
	}

	// clear the maps
	m_gameobjectBinding.clear();
	m_unitBinding.clear();

	// grab the first lua engine in the list, use it to re-create all the binding names.
	LuaEngine * l = m_engines.begin()->first;
	lua_is_starting_up = true;
	l->Restart();
	lua_is_starting_up = false;

	// all our bindings have been re-created, go through the lua engines and restart them all, and then release their locks.
	for(LuaEngineMap::iterator itr = m_engines.begin(); itr != m_engines.end(); ++itr)
	{
		if(itr->first != l)		// this one is already done
		{
			itr->first->Restart();
			itr->first->GetLock().Release();
		}
	}

	// release the big lock
	m_lock.Release();
}*/

void LuaEngineMgr::Unload()
{
	g_engine.GetLock().Acquire();

	for(UnitBindingMap::iterator itr = m_unitBinding.begin(); itr != m_unitBinding.end(); ++itr)
	{
		delete [] itr->second;
	}
	for(GameObjectBindingMap::iterator itr = m_gameobjectBinding.begin(); itr != m_gameobjectBinding.end(); ++itr)
	{
		for(uint32 i = 0; i < GAMEOBJECT_EVENT_COUNT; ++i)
			if(itr->second.Functions[i] != NULL)
				free((void*)itr->second.Functions[i]);
	}
	for(GossipUnitScriptsBindingMap::iterator itr = m_unit_gossipBinding.begin(); itr != m_unit_gossipBinding.end(); ++itr)
	{
		for(uint32 i = 0; i < GOSSIP_EVENT_COUNT; ++i)
			if(itr->second.Functions[i] != NULL)
				free((void*)itr->second.Functions[i]);
	}

	for(GossipItemScriptsBindingMap::iterator itr = m_item_gossipBinding.begin(); itr != m_item_gossipBinding.end(); ++itr)
	{
		for(uint32 i = 0; i < GOSSIP_EVENT_COUNT; ++i)
			if(itr->second.Functions[i] != NULL)
				free((void*)itr->second.Functions[i]);
	}
	for(GossipGOScriptsBindingMap::iterator itr = m_go_gossipBinding.begin(); itr != m_go_gossipBinding.end(); ++itr)
	{
		for(uint32 i = 0; i < GOSSIP_EVENT_COUNT; ++i)
			if(itr->second.Functions[i] != NULL)
				free((void*)itr->second.Functions[i]);
	}
#ifdef ENABLE_LUA_HOOKS
	for(int i = 0; i < NUM_SERVER_HOOKS; i++)
	{
		m_shBinding[i].clear();
	}
	m_scriptMgr->unregister_lua_hook(m_HookInterface);
#endif
	m_gameobjectBinding.clear();
	m_unitBinding.clear();
	m_unit_gossipBinding.clear();
	m_item_gossipBinding.clear();
	m_go_gossipBinding.clear();
	g_engine.Restart();
	ReloadClasses();
	g_engine.GetLock().Release();
}

void LuaEngine::Restart()
{
	sLog.outString("Reloading Scripts....");
	lua_is_starting_up = true;
	g_engine.LoadScripts();
	lua_is_starting_up = false;
}

void LuaEngineMgr::ReloadClasses()
{
#ifdef ENABLE_LUA_HOOKS
	m_HookInterface = new pHookInterface;
	m_HookInterface->SetBinding(m_shBinding);
#endif

	for(UnitBindingMap::iterator itr = m_unitBinding.begin(); itr != m_unitBinding.end(); ++itr)
	{
	m_scriptMgr->register_creature_script( itr->first, CreateLuaCreature );
	}
	for(GameObjectBindingMap::iterator itr = m_gameobjectBinding.begin(); itr != m_gameobjectBinding.end(); ++itr)
	{
	m_scriptMgr->register_gameobject_script( itr->first, CreateLuaGameObject );
	}
	for(QuestBindingMap::iterator itr = m_questBinding.begin(); itr != m_questBinding.end(); ++itr)
	{
		QuestScript * qs = CreateLuaQuestScript( itr->first );
		if( qs != NULL )
			m_scriptMgr->register_quest_script( itr->first, qs );
	}
    for(GossipUnitScriptsBindingMap::iterator itr = m_unit_gossipBinding.begin(); itr != m_unit_gossipBinding.end(); ++itr)
 	{
		GossipScript * gs = CreateLuaUnitGossipScript( itr->first );
 		if( gs != NULL )
 			m_scriptMgr->register_gossip_script( itr->first, gs );
	}
	for(GossipItemScriptsBindingMap::iterator itr = m_item_gossipBinding.begin(); itr != m_item_gossipBinding.end(); ++itr)
	{
		GossipScript * gs = CreateLuaItemGossipScript( itr->first );
		if( gs != NULL )
			m_scriptMgr->register_item_gossip_script( itr->first, gs );
    }

	for(GossipGOScriptsBindingMap::iterator itr = m_go_gossipBinding.begin(); itr != m_go_gossipBinding.end(); ++itr)
	{
		GossipScript * gs = CreateLuaGOGossipScript( itr->first );
		if( gs != NULL )
			m_scriptMgr->register_go_gossip_script( itr->first, gs );
    }
#ifdef ENABLE_LUA_HOOKS
	m_scriptMgr->register_lua_hook(m_HookInterface);
#endif
}

namespace luaGameObject
{
	int GetName(lua_State * L, GameObject * ptr)
	{
		if(!ptr||ptr->GetTypeId()!=TYPEID_GAMEOBJECT||!ptr->GetInfo())
		{
			lua_pushstring(L,"Unknown");
			return 1;
		}

		lua_pushstring(L,ptr->GetInfo()->Name);
		return 1;
	}
	int GetCreatureNearestCoords(lua_State * L, GameObject * ptr)
	{
		if(ptr == NULL) return 0;
		float x = (float)luaL_checkinteger(L,1);
		float y = (float)luaL_checkinteger(L,2);
		float z = (float)luaL_checkinteger(L,3);
		uint32 entryid = luaL_checkint(L,4);
		if(x == 0 || y == 0 || z == 0 || entryid == 0 ) return 0;
		Creature* pC = ptr->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x,y,z,entryid);
		if( pC == NULL) return 0;
		Lunar<Unit>::push(L,(Unit*)(pC));
		return 1;
	}
	int GetGameObjectNearestCoords(lua_State * L, GameObject * ptr)
	{
		if(ptr == NULL) return 0;
		float x = (float)luaL_checkinteger(L,1);
		float y = (float)luaL_checkinteger(L,2);
		float z = (float)luaL_checkinteger(L,3);
		uint32 entryid = luaL_checkint(L,4);
		if(x == 0 || y == 0 || z == 0 || entryid == 0 ) return 0;
		GameObject* Obj = ptr->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(x,y,z,entryid);
		if(Obj == NULL) return 0;
		Lunar<GameObject>::push(L,(Obj));
		return 1;
	}
	int GossipCreateMenu(lua_State * L, GameObject * ptr)
	{
		int text_id = luaL_checkint(L, 1);
		Unit * target = Lunar<Unit>::check(L, 2);
		int autosend = luaL_checkint(L, 3);   
		if(target->GetTypeId() != TYPEID_PLAYER) return 0;
		Player* plr = TO_PLAYER(target);
		objmgr.CreateGossipMenuForPlayer(&Menu, ptr->GetGUID(), text_id, plr);
		if(autosend)
			Menu->SendTo(plr);
		return 1;
	}
	int GossipMenuAddItem(lua_State * L, GameObject * ptr)
	{
		int icon = luaL_checkint(L, 1);
		const char * menu_text = luaL_checkstring(L, 2);
		int IntId = luaL_checkint(L, 3);
		int extra = luaL_checkint(L, 4);
		Menu->AddItem(icon, menu_text, IntId, extra);
		return 1;
	}
	int GossipSendMenu(lua_State * L, GameObject * ptr)
	{
		Unit * target = Lunar<Unit>::check(L, 1);
		if(target->GetTypeId() != TYPEID_PLAYER) return 0;
		Player* plr = TO_PLAYER(target);
		Menu->SendTo(plr);
		return 1;
		}
	int GossipComplete(lua_State * L, GameObject * ptr)
	{
		Unit* target = Lunar<Unit>::check(L, 1);
		if(target->GetTypeId() != TYPEID_PLAYER) return 0;

		Player* plr = TO_PLAYER(target);
		plr->Gossip_Complete();
		return 0;
	}
	int GossipSendPOI(lua_State * L, GameObject * ptr)
	{
		Unit* target = Lunar<Unit>::check(L, 1);
		if(target->GetTypeId() != TYPEID_PLAYER) return 0;
		Player* plr = TO_PLAYER(target);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		int icon = luaL_checkint(L, 4);
		int flags = luaL_checkint(L, 5);
		int data = luaL_checkint(L, 6);
		const char * name = luaL_checkstring(L, 7);

		plr->Gossip_SendPOI(x, y, icon, flags, data, name);
		return 0;
	}
	int GetClosestPlayer(lua_State * L, GameObject * ptr)
	{
		if(!ptr)
			return 0;

		float dist, d2;
		Player * ret = NULL;

		for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
		{
			d2=(*itr)->GetDistanceSq(TO_OBJECT(ptr));
			if(!ret||d2<dist)
			{
				dist=d2;
				ret=(*itr);
			}
		}

		if(ret==NULL)
			lua_pushnil(L);
		else
			Lunar<Unit>::push(L,(Unit*)ret,false);

		return 1;
	}
	int GetDistance(lua_State * L, GameObject * ptr)
	{
		if(!ptr)
			return 0;
		Unit * target = Lunar<Unit>::check(L, 1);
		lua_pushnumber(L,ptr->GetDistance2dSq(TO_OBJECT(target)));
		return 1;
	}
	int IsInWorld(lua_State * L, GameObject * ptr)
	{
		if (ptr)
			if(ptr->IsInWorld())
				lua_pushboolean(L, 1);
			else
				lua_pushboolean(L, 0);
		return 1;
	}
	int GetZoneId(lua_State *L, GameObject * ptr)
	{
		if(!ptr)
			return 0;
		lua_pushinteger(L,(ptr->GetZoneId()));
		return 1;
	}
	int PlaySoundToSet(lua_State * L, GameObject * ptr)
	{
		if(!ptr) return 0;
		int soundid = luaL_checkint(L,1);
		ptr->PlaySoundToSet(soundid);
		return 0;
	}
	int SpawnCreature(lua_State * L, GameObject * ptr)
	{
		if(ptr == NULL) return 0;
		uint32 entry_id = luaL_checkint(L, 1);
		float x = (float)luaL_checkint(L, 2);
		float y = (float)luaL_checkint(L, 3);
		float z = (float)luaL_checkint(L, 4);
		float o = (float)luaL_checkint(L, 5);
		uint32 faction = luaL_checkint(L, 6);
		uint32 duration = luaL_checkint(L, 7);

		if( !x || !y || !z || !entry_id || !faction /*|| !duration*/) //Shady: is it really required?
		{
			lua_pushnil(L);
			return 1;
		}
		CreatureProto* p = CreatureProtoStorage.LookupEntry(entry_id);
	    
		if(p == NULL)
		  return 0;
		Creature* pC = ptr->GetMapMgr()->GetInterface()->SpawnCreature(entry_id,x,y,z,o,false,true,faction,0);
		pC->SetMapId(ptr->GetMapId());
		pC->SetInstanceID(ptr->GetInstanceID());
		pC->PushToWorld(ptr->GetMapMgr());
		if(duration)
		{
//			sEventMgr.AddEvent(pC,&Creature::SafeDelete,false,EVENT_CREATURE_RESPAWN,duration,1,0);
			pC->Despawn(duration,0);
		}
		Lunar<Unit>::push(L,(Unit*)(pC));
		return 1;
	}
	int SpawnGameObject(lua_State * L, GameObject * ptr)
	{
		if(ptr == NULL) return 0;
		uint32 entry_id = luaL_checkint(L, 1);
		float x = (float)luaL_checkint(L, 2);
		float y = (float)luaL_checkint(L, 3);
		float z = (float)luaL_checkint(L, 4);
		float o = (float)luaL_checkint(L, 5);
		uint32 duration = luaL_checkint(L, 6);

		if(!entry_id || !duration)
		{
			lua_pushnil(L);
			return 1;
		}

		GameObjectInfo *goi = GameObjectNameStorage.LookupEntry(entry_id);
		if (goi == NULL) return 0;
		GameObject* pC = ptr->GetMapMgr()->GetInterface()->SpawnGameObject(entry_id,x,y,z,o,false,0,0);
		pC->SetMapId(ptr->GetMapId());
		pC->SetInstanceID(ptr->GetInstanceID());
		pC->Spawn(ptr->GetMapMgr());
		if(duration)
		{
			sEventMgr.AddEvent(pC, &GameObject::_Expire, EVENT_GAMEOBJECT_UPDATE, duration, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}
		Lunar<GameObject>::push(L,(pC));
		return 1;
	}
	int CalcDistance(lua_State * L, GameObject * ptr)
	{
		Unit * desttar = Lunar<Unit>::check(L,1);
		if(desttar)
			lua_pushnumber(L,ptr->CalcDistance(TO_OBJECT(desttar)));
		return 1;
	}
	int GetSpawnX(lua_State * L, GameObject * ptr)
	{
		if(ptr)
			lua_pushnumber(L,ptr->GetSpawnX());
		return 1;
	}
	int GetSpawnY(lua_State * L, GameObject * ptr)
	{
		if(ptr)
			lua_pushnumber(L,ptr->GetSpawnY());
		return 1;
	}
	int GetSpawnZ(lua_State * L, GameObject * ptr)
	{
		if(ptr)
			lua_pushnumber(L,ptr->GetSpawnZ());
		return 1;
	}
	int GetSpawnO(lua_State * L, GameObject * ptr)
	{
		if(ptr)
			lua_pushnumber(L,ptr->GetSpawnO());
		return 1;
	}
	int GetX(lua_State * L, GameObject * ptr)
	{
		if(ptr != NULL)
			lua_pushnumber(L,ptr->GetPositionX());
		return 1;
	}
	int GetY(lua_State * L, GameObject * ptr)
	{
		if(ptr != NULL)
			lua_pushnumber(L,ptr->GetPositionY());
		return 1;
	}
	int GetZ(lua_State * L, GameObject * ptr)
	{
		if(ptr != NULL)
			lua_pushnumber(L,ptr->GetPositionZ());
		return 1;
	}
	int GetO(lua_State * L, GameObject * ptr)
	{
		if(ptr != NULL)
			lua_pushnumber(L,ptr->GetOrientation());
		return 1;
	}

	int GetInRangePlayersCount(lua_State * L, GameObject * ptr)
	{
		if(ptr)
			lua_pushnumber(L,ptr->GetInRangePlayersCount());
		return 1;
	}
	int GetEntry(lua_State * L, GameObject * ptr)
	{
		if(ptr)
			lua_pushnumber(L,ptr->GetEntry());
		return 1;
	}
	int SetOrientation(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		float newo = (float)luaL_checkint(L, 1);
		float x = ptr->GetPosition().x;
		float y = ptr->GetPosition().y;
		float z = ptr->GetPosition().z;
		MapMgr* Mgr = ptr->GetMapMgr();
		ptr->RemoveFromWorld(false);
		ptr->SetPosition(x,y,z,newo,true);
		ptr->PushToWorld(Mgr);
		return 0;
	}
	int CalcRadAngle(lua_State * L, GameObject * ptr)
	{
		float x = (float)luaL_checkint(L,1 );
		float y = (float)luaL_checkint(L, 2);
		float x2 = (float)luaL_checkint(L, 3);
		float y2 = (float)luaL_checkint(L, 4);
		if(!x||!y||!x2||!y2||!ptr)
			return 0;
		lua_pushnumber(L,ptr->calcRadAngle(x,y,x2,y2));
		return 1;
	}
	int GetInstanceID(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		if(ptr->GetMapMgr()->GetMapInfo()->type == INSTANCE_NULL)
			lua_pushnil(L);
		else
		lua_pushinteger(L,ptr->GetInstanceID());
		return 1;
	}
	int GetInRangePlayers(lua_State * L, GameObject * ptr)
	{
		uint32 count = 0;
		lua_newtable(L);
		for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); itr++)
		{
			if( (*itr) ->IsUnit())
			{
				count++,
				lua_pushinteger(L,count);
				Lunar<Unit>::push(L,(Unit*)(*itr));
				lua_rawset(L,-3);
			}
		}
		return 1;
	}

	int GetInRangeGameObjects(lua_State * L, GameObject * ptr)
	{
		uint32 count = 0;
		lua_newtable(L);
		for (ObjectSet::iterator itr = ptr->GetInRangeSetBegin();itr!= ptr->GetInRangeSetEnd();itr++)
		{
			if( (*itr)->GetTypeId() == TYPEID_GAMEOBJECT)
			{
				count++,
				lua_pushinteger(L,count);
				Lunar<GameObject>::push(L,(GameObject*)(*itr));
				lua_rawset(L,-3);
			}
		}
		return 1;
	}
	int IsInFront(lua_State * L, GameObject * ptr)
	{
		Unit * target = Lunar<Unit>::check(L, 1);
		if(ptr != NULL && target != NULL)
		{
			if(ptr->isInFront((ptr)))
				lua_pushboolean(L, 1);
			else
				lua_pushboolean(L, 0);
		}
		return 1;
	}
	int IsInBack(lua_State * L, GameObject * ptr)
	{
		Unit * target = Lunar<Unit>::check(L, 1);
		if(ptr != NULL && target != NULL)
		{
			if(ptr->isInBack((ptr)))
				lua_pushboolean(L, 1);
			else
				lua_pushboolean(L, 0);
		}
		return 1;
	}
	int GetUInt32Value(lua_State * L, GameObject * ptr)
	{
		int field = luaL_checkint(L,1);
		if (ptr)
			lua_pushinteger(L,ptr->GetUInt32Value(field));
		return 1;
	}
	int GetUInt64Value(lua_State * L, GameObject * ptr)
	{
		int field = luaL_checkint(L,1);
		if (ptr && field)
		{
			lua_pushinteger(L,(int)ptr->GetUInt64Value(field));
		}
		return 1;
	}
	int SetUInt32Value(lua_State * L, GameObject * ptr)
	{
		int field = luaL_checkint(L,1);
		int value = luaL_checkint(L,2);
		if(ptr && field && value)
		{
			ptr->SetUInt32Value(field,value);
		}
		return 0;
	}
	int SetUInt64Value(lua_State * L, GameObject * ptr)
	{
		int field = luaL_checkint(L,1);
		int value = luaL_checkint(L,2);
		if(ptr && field && value)
		{
			ptr->SetUInt64Value(field,value);
		}
		return 0;
	}
	int SetFloatValue(lua_State * L, GameObject * ptr)
	{
		int field = luaL_checkint(L,1);
		float value = (float)luaL_checkint(L,2);
		if( ptr && value)
		{
			ptr->SetFloatValue(field,value);
		}
		return 0;
	}
	int GetFloatValue(lua_State * L, GameObject * ptr)
	{
		int field = luaL_checkint(L,1);
		if( ptr && field)
		{
			lua_pushnumber(L,ptr->GetFloatValue(field));
		}
		return 1;
	}
	int ModUInt32Value(lua_State * L, GameObject * ptr)
	{
		int field = luaL_checkint(L,1);
		int value = luaL_checkint(L,2);
		if( ptr && field && value)
		{
			ptr->ModSignedInt32Value(field,value);
		}
		return 0;
	}
	int CastSpell(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		uint32 sp = luaL_checkint(L,1);
		if( !ptr || !sp|| sp == 0) return 0;
		if(dbcSpell.LookupEntry(sp) == NULL) return 0;
		//shared_ptr<Spell> nsp = ptr->CreateSpell(TO_OBJECT(ptr),dbcSpell.LookupEntry(sp),true,NULL);
		//SpellCastTargets tar(TO_OBJECT(ptr));
		//nsp->prepare(&tar);
		ptr->CastSpell(ptr->GetGUID(),sp,true);
		return 0;
	}
	int FullCastSpell(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		uint32 sp = luaL_checkint(L,1);
		if( !ptr || !sp|| sp == 0) return 0;
		if(dbcSpell.LookupEntry(sp) == NULL) return 0;
		//Spell* nsp = objmgr.CreateSpell(TO_OBJECT(ptr),dbcSpell.LookupEntry(sp),false,NULL);
		//SpellCastTargets tar(TO_OBJECT(ptr));
		//nsp->prepare(&tar);
		ptr->CastSpell(ptr->GetGUID(),sp,true);
		return 0;
	}
	int CastSpellOnTarget(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		uint32 sp = luaL_checkint(L,1);
		Unit * target = Lunar<Unit>::check(L,2);
		if( !ptr || !sp || sp == 0) return 0;
		if(dbcSpell.LookupEntry(sp) == NULL) return 0;
		//Spell* nsp = objmgr.CreateSpell(TO_OBJECT(ptr),dbcSpell.LookupEntry(sp),true,NULL);
		//SpellCastTargets tar(TO_OBJECT(target));
		//nsp->prepare(&tar);
		ptr->CastSpell(ptr->GetGUID(),sp,true);
		return 0;
	}
	int FullCastSpellOnTarget(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		uint32 sp = luaL_checkint(L,1);
		Unit * target = Lunar<Unit>::check(L,2);
		if( !ptr || !sp || sp == 0) return 0;
		//Spell* nsp = objmgr.CreateSpell(TO_OBJECT(ptr),dbcSpell.LookupEntry(sp),false,NULLA);
		//SpellCastTargets tar(TO_OBJECT(target));
		//nsp->prepare(&tar);
		ptr->CastSpell(ptr->GetGUID(),sp,true);
		return 0;
	}
	int GetGUID(lua_State * L, GameObject* ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		lua_pushnumber(L,ptr->GetGUID());
		return 1;
	}
	int Despawn(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		uint32 delay = luaL_checkint(L,1);
		uint32 respawnt = luaL_checkint(L,2);
		if(delay)
		{
			sEventMgr.AddEvent( TO_GAMEOBJECT(ptr),&GameObject::Despawn,respawnt,EVENT_GAMEOBJECT_UPDATE, delay, 1, 0);
		}
		return 0;
	}
	int RegisterAIUpdateEvent(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		uint32 time = luaL_checkint(L,1);
		if(!time) return 0;
		sEventMgr.AddEvent(TO_GAMEOBJECT(ptr),&GameObject::CallScriptUpdate,EVENT_GAMEOBJECT_UPDATE,time,0,0);
		return 0;
	}
	int ModifyAIUpdateEvent(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		uint32 ntime = luaL_checkint(L,1);
		if(!ntime) return 0;
		sEventMgr.ModifyEventTime(TO_GAMEOBJECT(ptr),EVENT_GAMEOBJECT_UPDATE,ntime);
		return 0;
	}
	int RemoveAIUpdateEvent(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		sEventMgr.RemoveEvents(TO_GAMEOBJECT(ptr),EVENT_GAMEOBJECT_UPDATE);
		return 0;
	}
	int RemoveFromWorld(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		ptr->RemoveFromWorld(true);
		return 0;
	}
	int OnGameObjectEvent(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		const char * function = luaL_checkstring(L,1);
		uint32 eventnum = luaL_checkint(L,2);
		Unit * pMisc = Lunar<Unit>::check(L,3);
		uint32 Misc = luaL_checkint(L,4);
		if(Misc == 0) Misc = 0;
		g_engine.OnGameObjectEvent(ptr,function,eventnum,pMisc,Misc,0);
		return 0;
	}
	/* Date : 01/09/2009 */
	int SetSpawnPosition(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		float x = luaL_checklong(L,1);
		float y = luaL_checklong(L,2);
		float z = luaL_checklong(L,3);
		float o = luaL_checklong(L,4);
		if(!x || !y || ! z || !o) return 0;
		LocationVector pvect(x,y,z,o);
	//	ptr->SetSpawnPosition(pvect);
		ptr->SetPosition(pvect);
		return 0;
	}
	int IsInArc(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		Unit * target = Lunar<Unit>::check(L,1);
		float degrees = luaL_checklong(L,2);
		if(target == NULL || !degrees) return 0;
		( (ptr->isInArc(TO_OBJECT(target),degrees) == true) ? lua_pushboolean(L,1) : lua_pushboolean(L,0));
		return 1;
	}
	int SaveToDB(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		ptr->SaveToDB();
		return 0;
	}
	int DeleteFromDB(lua_State * L, GameObject * ptr)
	{
		CHECK_TYPEID(TYPEID_GAMEOBJECT);
		ptr->DeleteFromDB();
		return 0;
	}
	int WorldQuery(lua_State * L, GameObject * ptr)
	{
		const char * qry = luaL_checkstring(L,1);
		if(!qry) return 0;
		WorldDatabase.Query(qry);
		return 0;
	}
	/* End Date: 01/09/2009 */
}

namespace luaUnit
{
	int GossipCreateMenu(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		int text_id = luaL_checkint(L, 1);
		Unit * player = Lunar<Unit>::check(L,2);
 		int autosend = luaL_checkint(L, 3);
		if(player->GetTypeId() != TYPEID_PLAYER) return 0;
		Player* plr = TO_PLAYER(player);
		objmgr.CreateGossipMenuForPlayer(&Menu, ptr->GetGUID(), text_id, plr);
		if(autosend)
			Menu->SendTo(plr);
		return 0;
	}
	int GossipMenuAddItem(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		int icon = luaL_checkint(L, 1);
		const char * menu_text = luaL_checkstring(L, 2);
		int IntId = luaL_checkint(L, 3);
		int extra = luaL_checkint(L, 4);

		Menu->AddItem(icon, menu_text, IntId, extra);
		return 0;
	}
	int GossipSendMenu(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Menu->SendTo( TO_PLAYER(ptr));
		return 0;
	}
	int GossipComplete(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		TO_PLAYER(ptr)->Gossip_Complete();
		return 0;
	}

	int GossipSendPOI(lua_State * L, Unit * ptr)
	{
		Unit* target = Lunar<Unit>::check(L, 1);
		if(target->GetTypeId() != TYPEID_PLAYER) return 0;
		Player* plr = TO_PLAYER(target);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		int icon = luaL_checkint(L, 4);
		int flags = luaL_checkint(L, 5);
		int data = luaL_checkint(L, 6);
		const char * name = luaL_checkstring(L, 7);

		plr->Gossip_SendPOI(x, y, icon, flags, data, name);
		return 0;
	}
	int IsPlayer(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL ||( ptr->GetTypeId() != TYPEID_UNIT && ptr->GetTypeId() != TYPE_PLAYER)) return 0;
		lua_pushboolean(L,(ptr->IsPlayer())?1:0);
		return 1;
	}
	int IsCreature(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL ||( ptr->GetTypeId() != TYPEID_UNIT && ptr->GetTypeId() != TYPE_PLAYER)) return 0;
		lua_pushboolean(L,(ptr->IsCreature())?1:0);
		return 1;
	}
	int Emote(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 emote_id = luaL_checkint(L, 1);
		uint32 time = luaL_checkint(L, 2);
		if(emote_id==0) return 0;
		if (time)
			ptr->EventAddEmote((EmoteType)emote_id,time);
		else
			ptr->Emote((EmoteType)emote_id);
		return 0;
	}
	int GetManaPct(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		if (ptr->GetPowerType() == POWER_TYPE_MANA)
			lua_pushnumber(L, (int)(ptr->GetUInt32Value(UNIT_FIELD_POWER1) * 100.0f / ptr->GetUInt32Value(UNIT_FIELD_MAXPOWER1)));
		else
			lua_pushnil(L);
		return 1;
	}
	int GetName(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();

		switch(ptr->GetTypeId())
		{
		case TYPEID_UNIT:
			lua_pushstring(L, TO_CREATURE(ptr)->GetCreatureName() ? TO_CREATURE(ptr)->GetCreatureName()->Name : "Unknown");
			break;

		case TYPEID_PLAYER:
			lua_pushstring(L, TO_PLAYER(ptr)->GetName());
			break;

		default:
			lua_pushstring(L, "Unknown");
			break;
		}

		return 1;
	}
	int SendChatMessage(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 typ = luaL_checkint(L, 1);
		uint32 lang = luaL_checkint(L, 2);
		const char * message = luaL_checklstring(L, 3, NULL);
		if(message == NULL)
			return 0;

		ptr->SendChatMessage(typ, lang, message);
		return 0;
	}
	int MoveTo(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		double x = luaL_checknumber(L, 1);
		double y = luaL_checknumber(L, 2);
		double z = luaL_checknumber(L, 3);
		double o = luaL_checknumber(L, 4);

		if(x == 0 || y == 0 || z == 0)
			return 0;

		ptr->GetAIInterface()->MoveTo( (float)x, (float)y, (float)z, (float)o );
		return 0;
	}

	int SetMovementType(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 typ = luaL_checkint(L, 1);
		ptr->GetAIInterface()->setMoveType(typ);
		return 0;
	}

	int GetX(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushnumber(L, (double)ptr->GetPositionX());
		return 1;
	}

	int GetY(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushnumber(L, (double)ptr->GetPositionY());
		return 1;
	}

	int GetZ(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushnumber(L, (double)ptr->GetPositionZ());
		return 1;
	}

	int GetO(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushnumber(L, (double)ptr->GetOrientation());
		return 1;
	}

	int CastSpell(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 sp = luaL_checkint(L,1);
		if(ptr->GetTypeId() == TYPEID_UNIT)
			TO_CREATURE(ptr)->CastSpell(TO_UNIT(ptr),sp,true);
		else if( ptr->GetTypeId() == TYPEID_PLAYER)
			TO_PLAYER(ptr)->CastSpell(TO_UNIT(ptr),sp,true);
		return 0;
	}

	int FullCastSpell(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 sp = luaL_checkint(L,1);
		if(ptr->GetTypeId() == TYPEID_UNIT)
			TO_CREATURE(ptr)->CastSpell(TO_UNIT(ptr),sp,false);
		else if(ptr->GetTypeId() == TYPEID_PLAYER)
			TO_PLAYER(ptr)->CastSpell(TO_UNIT(ptr),sp,false);
		return 0;
	}
	int CastSpellOnTarget(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 sp = luaL_checkint(L, 1);
		Unit * target = Lunar<Unit>::check(L, 2);

		if(sp==0 || target==NULL) return 0;
		if(ptr->GetTypeId() == TYPEID_UNIT)
			TO_CREATURE(ptr)->CastSpell(TO_UNIT(target),sp,true);
		else if(ptr->GetTypeId() == TYPEID_PLAYER)
			TO_PLAYER(ptr)->CastSpell(TO_UNIT(target),sp,true);
		return 0;
	}
	int FullCastSpellOnTarget(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 sp = luaL_checkint(L, 1);
		Unit * target = Lunar<Unit>::check(L, 2);

		if(sp==0 || target==NULL) return 0;
		if(ptr->GetTypeId() == TYPEID_PLAYER)
			TO_PLAYER(ptr)->CastSpell(TO_UNIT(target),sp,false);
		else if(ptr->GetTypeId() == TYPEID_UNIT)
			TO_CREATURE(ptr)->CastSpell(TO_UNIT(target),sp,false);
		return 0;
	}
	int SpawnCreature(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();

		uint32 entry_id = luaL_checkint(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float z = (float)luaL_checknumber(L, 4);
		float o = (float)luaL_checknumber(L, 5);
		uint32 faction = luaL_checkint(L, 6);
		uint32 duration = luaL_checkint(L, 7);

		if( !x || !y || !z || !entry_id || !faction) return 0;

		CreatureProto * proto = CreatureProtoStorage.LookupEntry(entry_id);
		CreatureInfo * inf = CreatureNameStorage.LookupEntry(entry_id);

		if(!proto || !inf) return 0;

		Creature* pC = ptr->GetMapMgr()->GetInterface()->SpawnCreature(entry_id,x,y,z,o,false,false,0,0);
		if(pC == NULL) return 0;
		pC->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE,faction);
		pC->_setFaction();
		pC->SetInstanceID(ptr->GetInstanceID());
		pC->SetMapId(ptr->GetMapId());
		pC->PushToWorld(ptr->GetMapMgr());
		if(duration)
		{
	//		sEventMgr.AddEvent(pC,&Creature::SafeDelete,false,EVENT_CREATURE_UPDATE,duration,1,0);
			pC->Despawn(duration,0);
		}
		Lunar<Unit>::push(L,((Unit*)(pC)));
		return 1;
	}
	int SpawnGameObject(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();

		uint32 entry_id = luaL_checkint(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float z = (float)luaL_checknumber(L, 4);
		float o = (float)luaL_checknumber(L, 5);
		uint32 duration = luaL_checkint(L, 6);

		if(!entry_id) return 0;

		GameObjectInfo * goi = GameObjectNameStorage.LookupEntry(entry_id);
		if(!goi) return 0;

		GameObject* pC = ptr->GetMapMgr()->GetInterface()->SpawnGameObject(entry_id,x,y,z,o,false,0,0);
		if(pC == NULL) return 0;
		pC->SetMapId(ptr->GetMapId());
		pC->SetInstanceID(ptr->GetInstanceID());
		pC->Spawn(ptr->GetMapMgr());
		if(duration)
		{
			sEventMgr.AddEvent(pC, &GameObject::_Expire, EVENT_GAMEOBJECT_EXPIRE, duration, 1, 0);
		}
		Lunar<GameObject>::push(L,(pC));
		return 1;
	}
	int RegisterEvent(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();

		const char * func_to_call = luaL_checkstring(L,1);
		int delay=luaL_checkint(L,2);
		int repeats=luaL_checkint(L,3);

		if(!func_to_call||!delay)
			return 0;

		Creature* pCreature = TO_CREATURE(ptr);
		string strFunc = string(func_to_call);
		sEventMgr.AddEvent(pCreature, &Creature::TriggerScriptEvent, strFunc, EVENT_CREATURE_UPDATE, (uint32)delay, (uint32)repeats, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		return 0;
	}
	int RemoveEvents(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();

		Creature* pCreature = TO_CREATURE(ptr);
		sEventMgr.RemoveEvents(pCreature);
		return 0;
	}

	int SetFaction(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL || (ptr->GetTypeId() !=  TYPEID_UNIT && ptr->GetTypeId() != TYPEID_PLAYER) ) return 0;
		int faction = luaL_checkint(L,1);
		if(!faction)
			return 0;

		ptr->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE,faction);
		ptr->_setFaction();
		return 0;
	}
	int SetStandState(lua_State * L, Unit * ptr) //states 0..8
	{
		CHECK_PTR();
		int state = luaL_checkint(L,1);
		if(state<=0)
			return 0;
		ptr->SetStandState(state);
		return 0;
	}
	int IsInCombat(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushboolean(L,(ptr->CombatStatus.IsInCombat())?1:0);
		return 1;
	}

	int SetScale(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		double faction = luaL_checknumber(L,1);
		if(faction==0.0)
			return 0;

		ptr->SetFloatValue(OBJECT_FIELD_SCALE_X,(float)faction);
		return 0;
	}

	int SetModel(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();

		int modelid = luaL_checkint(L,1);
		if(modelid==0)
			return 0;

		ptr->SetUInt32Value(UNIT_FIELD_DISPLAYID,modelid);
		return 0;
	}
	int SetCombatCapable(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		int enabled = luaL_checkint(L,1);
		ptr->GetAIInterface()->disable_combat = (enabled > 0) ? true : false;
		//ptr->GetAIInterface()->SetAllowedToEnterCombat(false);
		return 0;
	}

	int SetCombatMeleeCapable(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		int enabled = luaL_checkint(L,1);
		ptr->GetAIInterface()->disable_melee = (enabled > 0) ? true : false;
		return 0;
	}

	int SetCombatRangedCapable(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		int enabled = luaL_checkint(L,1);
		ptr->GetAIInterface()->disable_ranged = (enabled > 0) ? true : false;
		return 0;
	}

	int SetCombatSpellCapable(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		int enabled = luaL_checkint(L,1);
		ptr->GetAIInterface()->disable_spell = (enabled > 0) ? true : false;
		return 0;
	}

	int SetCombatTargetingCapable(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		int enabled = luaL_checkint(L,1);
		ptr->GetAIInterface()->disable_targeting = (enabled > 0) ? true : false;
		return 0;
	}

	int DestroyCustomWaypointMap(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		TO_CREATURE(ptr)->DestroyCustomWaypointMap();
		return 0;
	}

	int CreateCustomWaypointMap(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		Creature* pCreature = TO_CREATURE(ptr);
		if(pCreature->m_custom_waypoint_map)
		{
			for(WayPointMap::iterator itr = pCreature->m_custom_waypoint_map->begin(); itr != pCreature->m_custom_waypoint_map->end(); ++itr)
				delete (*itr);
			delete pCreature->m_custom_waypoint_map;
		}

		pCreature->m_custom_waypoint_map = new WayPointMap;
		pCreature->GetAIInterface()->SetWaypointMap(pCreature->m_custom_waypoint_map);
		return 0;
	}

	int CreateWaypoint(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 wpid = luaL_checkint(L,1);
		float x = luaL_checknumber(L,2);
		float y = luaL_checknumber(L,3);
		float z = luaL_checknumber(L,4);
		float o = luaL_checknumber(L,5);
		int waittime = luaL_checkint(L,6);
		int flags = luaL_checkint(L,7);
		int modelid = luaL_checkint(L,8);
		Creature* pCreature = TO_CREATURE(ptr);
		if(pCreature == NULL) return 0;

		if(!modelid)
			modelid = pCreature->GetUInt32Value(UNIT_FIELD_DISPLAYID);

		WayPoint * wp = pCreature->CreateWaypointStruct();
		wp->backwardemoteid = 0;
		wp->backwardemoteoneshot = 0;
		wp->backwardskinid = 0;
		wp->flags = flags;
		wp->forwardemoteid = 0;
		wp->forwardemoteoneshot = 0;
		wp->forwardskinid = modelid;
		wp->id = wpid;
		wp->o = o;
		wp->waittime = waittime;
		wp->x = x;
		wp->y = y;
		wp->z = z;
		pCreature->GetAIInterface()->addWayPoint(wp);

		return 0;
	}

	int MoveToWaypoint(lua_State * L, Unit * ptr)
	{
		CHECK_PTR(); // players w/ ai enabled can move to wps.
		uint32 id = luaL_checkint(L,1);
		ptr->GetAIInterface()->setWaypointToMove(id);
		return 0;
	}

	int RemoveItem(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		int id = luaL_checkint(L,1);
		int count = luaL_checkint(L,2);

		TO_PLAYER(ptr)->GetItemInterface()->RemoveItemAmt(id,count);
		return 0;
	}

	int AddItem(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		int id = luaL_checkint(L,1);
		int count = luaL_checkint(L,2);

		Player* plr = TO_PLAYER(ptr);
		ItemPrototype * proto = ItemPrototypeStorage.LookupEntry(id);
		if(proto==NULL)
			return 0;

		Item* add = plr->GetItemInterface()->FindItemLessMax(id,count,false);
		if(add==NULL)
		{
			add=objmgr.CreateItem(id,plr);
			add->SetUInt32Value(ITEM_FIELD_STACK_COUNT,count);
			if(plr->GetItemInterface()->AddItemToFreeSlot(add))
				plr->GetSession()->SendItemPushResult(add,false,true,false,true,plr->GetItemInterface()->LastSearchItemBagSlot(),plr->GetItemInterface()->LastSearchItemSlot(),count);
		}
		else
		{
			add->ModUnsigned32Value(ITEM_FIELD_STACK_COUNT,count);
			plr->GetSession()->SendItemPushResult(add,false,true,false,false,plr->GetItemInterface()->GetBagSlotByGuid(add->GetGUID()),0xFFFFFFFF,count);
		}

		return 0;
	}
	int GetInstanceID(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		if( ptr->GetMapMgr()->GetMapInfo()->type == INSTANCE_NULL)
			lua_pushnil(L);
		else
			lua_pushinteger(L,ptr->GetInstanceID());
		return 1;
	}

	int GetClosestPlayer(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();

		float dist, d2;
		Player * ret=NULL;

		for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
		{
			d2=(*itr)->GetDistanceSq(TO_OBJECT(ptr));
			if(!ret||d2<dist)
			{
				dist=d2;
				ret=(*itr);
			}
		}

		if(ret==NULL)
			lua_pushnil(L);
		else
			Lunar<Unit>::push(L,((Unit*)ret));

		return 1;
	}
	int GetRandomPlayer(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();

		int flag = luaL_checkint( L, 1 );

		Player* ret;

		switch( flag )
		{
		case RANDOM_ANY:
			{
				std::vector<Player*>PlayerTable;
				for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
				{
					PlayerTable.push_back(*itr);
				}
				if( PlayerTable.size() != 0 )
					ret = PlayerTable[RandomUInt(PlayerTable.size()-1)];
			}break;
		case RANDOM_IN_SHORTRANGE:
			{
				std::vector<Player*>PlayerTable;
				for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
				{
					if(ptr->CalcDistance( *itr) <= 8)
						PlayerTable.push_back(*itr);
				}
				if(PlayerTable.size() != 0)
					ret = PlayerTable[RandomUInt(PlayerTable.size()-1)];
			}break;
		case RANDOM_IN_MIDRANGE:
			{
				std::vector<Player*>PlayerTable;
				for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
				{
					if( ptr->GetDistanceSq(*itr) > 8 && ptr->GetDistanceSq(*itr) <=20 )
						PlayerTable.push_back(*itr);
				}
				if(PlayerTable.size() != 0)
					ret = PlayerTable[RandomUInt(PlayerTable.size()-1)];
			}break;
		case RANDOM_IN_LONGRANGE:
			{
				std::vector<Player*>PlayerTable;
				for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
				{
					if( ptr->GetDistanceSq(*itr) < 20)
						PlayerTable.push_back(*itr);
				}
				if( PlayerTable.size() != 0 )
					ret = PlayerTable[RandomUInt(PlayerTable.size()-1)];
			}break;
		case RANDOM_WITH_MANA:
			{
				std::vector<Player*>PlayerTable;
				for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
				{
					if( (*itr)->GetPowerType() == POWER_TYPE_MANA )
						PlayerTable.push_back( *itr);
				}
				if( PlayerTable.size() != 0 )
					ret = PlayerTable[RandomUInt(PlayerTable.size()-1)];
			}break;
		case RANDOM_WITH_ENERGY:
			{
				std::vector<Player*>PlayerTable;
				for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
				{
					if ( (*itr)->GetPowerType() == POWER_TYPE_ENERGY)
						PlayerTable.push_back( *itr);
				}
				if (PlayerTable.size() != 0 )
					ret = PlayerTable[RandomUInt(PlayerTable.size()-1)];
			}break;
		case RANDOM_WITH_RAGE:
			{
				std::vector<Player*>PlayerTable;
				for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
				{
					if( (*itr)->GetPowerType() == POWER_TYPE_RAGE )
						PlayerTable.push_back( *itr);
				}
				if( PlayerTable.size() != 0 )
					ret = PlayerTable[RandomUInt(PlayerTable.size()-1)];
			}break;
		case RANDOM_NOT_MAINTANK:
			{
				std::vector<Player*>PlayerTable;
				for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); ++itr)
				{
					if( (*itr) != ptr->GetAIInterface()->GetMostHated() )
						PlayerTable.push_back(*itr);
				}
				if( PlayerTable.size() != 0 )
					ret = PlayerTable[RandomUInt(PlayerTable.size()-1)];
			}break;
		}
		if(ret==NULL)
			lua_pushnil(L);
		else
			Lunar<Unit>::push(L,((Unit*)(ret)));

		return 1;
	}
	int GetRandomFriend(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		std::vector<Unit*>Creatures;
		for(ObjectSet::iterator itr = ptr->GetInRangeSetBegin(); itr != ptr->GetInRangeSetEnd(); ++itr)
		{
			if( (*itr)->IsUnit() && isFriendly(TO_OBJECT(ptr),(*itr)))
			{
				Unit * pTemp = TO_UNIT(*itr);
				Creatures.push_back(pTemp);
			}
		}
		if( Creatures.size() != 0 )
			Lunar<Unit>::push(L,Creatures[RandomUInt(Creatures.size()-1)]);
		return 1;
	}
	int GetRandomEnemy(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		std::vector<Unit*>Enemies;
		for(ObjectSet::iterator itr = ptr->GetInRangeSetBegin(); itr != ptr->GetInRangeSetEnd(); ++itr)
		{
			if( (*itr)->IsUnit() && isHostile(TO_OBJECT(ptr),(*itr)) )
			{
				Unit * pTemp = TO_UNIT(*itr);
				Enemies.push_back( pTemp);
			}
		}
		if( Enemies.size() != 0 )
			Lunar<Unit>::push(L,Enemies[RandomUInt(Enemies.size()-1)]);
		return 1;
	}

	int StopMovement(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		int tim = luaL_checkint(L,1);
		ptr->GetAIInterface()->StopMovement(tim);
		return 0;
	}

	int RemoveAura(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		int auraid = luaL_checkint(L,1);
		ptr->RemoveAura(auraid);
		return 0;
	}

	int PlaySoundToSet(lua_State * L, Unit * ptr)
	{
		if(!ptr) return 0;
		int soundid = luaL_checkint(L,1);
		ptr->PlaySoundToSet(soundid);
		return 0;
	}

	int GetUnitBySqlId(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 sqlid = luaL_checkint(L,1);
		Creature* pC = ptr->GetMapMgr()->GetSqlIdCreature(sqlid);
		CreatureProto * proto = CreatureProtoStorage.LookupEntry(sqlid);
		if(proto == NULL)
			lua_pushnil(L);
		Lunar<Unit>::push(L,((Unit*)(pC)));
		return 1;
	}

	int Despawn(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		int delay = luaL_checkint(L,1);
		int respawntime = luaL_checkint(L,2);
		TO_CREATURE(ptr)->Despawn(delay,respawntime);
		return 0;
	}

	int GetHealthPct(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL)
			lua_pushinteger(L,0);
		else
			lua_pushinteger(L, ptr->GetHealthPct());

		return 1;
	}
	int SetHealthPct(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		if(ptr->GetUInt32Value(UNIT_FIELD_HEALTH) == 0 && ptr->getDeathState() != ALIVE)
			return 0;
		int val = luaL_checkint(L,1);
		if (val>0)
			ptr->SetHealthPct(val);
		return 1;
	}
	int GetItemCount(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID_RET_INT(TYPEID_PLAYER);
		int itemid = luaL_checkint(L,1);
		lua_pushinteger(L, TO_PLAYER(ptr)->GetItemInterface()->GetItemCount(itemid,false));
		return 1;
	}

	int GetMainTank(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID_RET_INT(TYPEID_UNIT);
		Unit* ret = ptr->GetAIInterface()->GetMostHated();
		if(ret==NULL)
			lua_pushnil(L);
		else
			Lunar<Unit>::push(L,(ret),false);
		return 1;
	}
	int GetAddTank(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID_RET_INT(TYPEID_UNIT);
		Unit* ret = ptr->GetAIInterface()->GetSecondHated();
		if(ret==NULL)
			lua_pushnil(L);
		else
			Lunar<Unit>::push(L,(ret),false);
		return 1;
	}
	int ClearThreatList(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID_RET_INT(TYPEID_UNIT);
		ptr->ClearHateList();
		return 1;
	}

	int GetTauntedBy(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT)
		if (!ptr->GetAIInterface()->getTauntedBy())
			lua_pushnil(L);
		else
			Lunar<Unit>::push(L,(ptr->GetAIInterface()->getTauntedBy()),false);
		return 1;
	}
	int SetTauntedBy(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		Unit * target = Lunar<Unit>::check(L,1);
		if (!target || ptr->GetAIInterface()->GetIsTaunted() || target==ptr)
			return 0;
		else
			ptr->GetAIInterface()->taunt(TO_UNIT(target));
		return 1;
	}

	int GetSoulLinkedWith(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		if(ptr->GetAIInterface()->getSoullinkedWith() == NULL)
			lua_pushnil(L);
		else
			Lunar<Unit>::push(L,(ptr->GetAIInterface()->getSoullinkedWith()));
		return 1;
	}
	int SetSoulLinkedWith(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		Unit * target = Lunar<Unit>::check(L, 1);
		if (!target || ptr->GetAIInterface()->GetIsSoulLinked() || target==ptr)
			return 0;
		else
			ptr->GetAIInterface()->SetSoulLinkedWith(TO_UNIT(ptr));;
		return 0;
	}
	int ChangeTarget(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		Unit * target = Lunar<Unit>::check(L,1);
		if (!target || !isHostile(TO_OBJECT(ptr),TO_OBJECT(target)) || ptr==target)
			return 0;
		else
			ptr->GetAIInterface()->SetNextTarget(TO_UNIT(target));
		return 0;
	}

	int HasFinishedQuest(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID_RET(TYPEID_PLAYER);
		int questid = luaL_checkint(L,1);
		if( TO_PLAYER(ptr )->HasFinishedQuest(questid) )
			lua_pushboolean(L,1);
		else
			lua_pushboolean(L,0);

		return 1;
	}

	int UnlearnSpell(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		int spellid = luaL_checkint(L,1);
		TO_PLAYER( ptr )->removeSpell(spellid,false,false,0);
		return 0;
	}

	int LearnSpell(lua_State * L, Unit* ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		int spellid = luaL_checkint(L,1);
		TO_PLAYER( ptr )->addSpell(spellid);
		return 0;
	}

	int MarkQuestObjectiveAsComplete(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		int questid = luaL_checkint(L,1);
		int objective = luaL_checkint(L,2);
		Player* pl = TO_PLAYER( ptr );
		QuestLogEntry * qle = pl->GetQuestLogForEntry(questid);
		qle->SetMobCount(objective, qle->GetQuest()->required_mobcount[objective]);
		qle->SendUpdateAddKill(objective);
		if(qle->CanBeFinished())
			qle->SendQuestComplete();
		qle->UpdatePlayerFields();

		return 0;
	}

	/*int KnockBack(lua_State * L, Unit * ptr)
	{
		if(!ptr) return 0;
		double dx = luaL_checknumber(L,1);
		double dy = luaL_checknumber(L,2);
		double affect1 = luaL_checknumber(L,3);
		double affect2 = luaL_checknumber(L,4);
		WorldPacket data(SMSG_MOVE_KNOCK_BACK, 30);
		data << ptr->GetNewGUID();
		data << getMSTime();
		data << dx << dy << affect1 << affect2;
		ptr->SendMessageToSet(&data, true);

		return 0;
	}*/
	int SendAreaTriggerMessage(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		const char * msg = luaL_checkstring(L,1);
		if(!msg) return 0;
		TO_PLAYER( ptr )->SendAreaTriggerMessage(msg);
		return 0;
	}

	int SendBroadcastMessage(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Player* plr = TO_PLAYER( ptr );
		const char * msg = luaL_checkstring(L,1);
		if(!msg) return 0;
		plr->BroadcastMessage(msg);
		return 0;
	}

	int TeleportUnit(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 mapId = luaL_checkint(L, 1);
		float posX = (float)luaL_checknumber(L, 2);
		float posY = (float)luaL_checknumber(L, 3);
		float posZ = (float)luaL_checknumber(L, 4);
		if(posX == 0 || posY == 0 || posZ == 0)
			return 0;
		LocationVector vec(posX, posY, posZ);
		TO_PLAYER( ptr )->SafeTeleport(mapId, 0, vec);
		return 0;
	}

	int GetHealth(lua_State * L, Unit * ptr)
	{
		if( ptr == NULL )
			lua_pushnil(L);
		else
			lua_pushinteger( L, ptr->GetUInt32Value( UNIT_FIELD_HEALTH ) );
		return 1;
	}

	int GetMaxHealth(lua_State * L, Unit * ptr)
	{
		if( ptr == NULL )
			lua_pushnil(L);
		else
			lua_pushinteger( L, ptr->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) );
		return 1;
	}

	int SetHealth(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		if(ptr->GetUInt32Value(UNIT_FIELD_HEALTH) == 0 && ptr->getDeathState() != ALIVE) return 0;
		int val = luaL_checkint( L, 1 );
		if( ptr != NULL && val > 0 )
		{
			if( (uint32)val > ptr->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
				ptr->SetUInt32Value( UNIT_FIELD_HEALTH, ptr->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) );
			else
				ptr->SetUInt32Value( UNIT_FIELD_HEALTH, val );
		}
		return 0;
	}

	int SetMaxHealth(lua_State * L, Unit * ptr)
	{
		int val = luaL_checkint( L, 1 );
		if( ptr != NULL && val > 0 )
		{
			if( (uint32)val < ptr->GetUInt32Value( UNIT_FIELD_HEALTH ) )
			{
			ptr->SetUInt32Value( UNIT_FIELD_HEALTH, val );
			ptr->SetUInt32Value( UNIT_FIELD_MAXHEALTH, val );
			}
		}
		return 0;
	}

	int WipeHateList(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID_RET_INT(TYPEID_UNIT);
		ptr->WipeHateList();
		return 0;
	}

	int WipeTargetList(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID_RET_INT(TYPEID_UNIT);
		ptr->GetAIInterface()->WipeTargetList();
		return 0;
	}

	int WipeCurrentTarget(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID_RET_INT(TYPEID_UNIT);
		ptr->GetAIInterface()->WipeCurrentTarget();
		return 0;
	}

	int GetPlayerClass(lua_State * L, Unit * ptr)
	{
	   if(ptr == NULL || ptr->GetTypeId()!=TYPEID_PLAYER) 
	   {
		  lua_pushstring(L, "Unknown");
		  return 1;
	   }
	   int plrclass = TO_PLAYER( ptr )->getClass();
	   switch(plrclass) 
	   {
		  case 1:
			 lua_pushstring(L, "Warrior");
			 break;
		  case 2:
			 lua_pushstring(L, "Paladin");
			 break;
		  case 3:
			 lua_pushstring(L, "Hunter");
			 break;
		  case 4:
			 lua_pushstring(L, "Rogue");
			 break;
		  case 5:
			 lua_pushstring(L, "Priest");
			 break;
		  //case 6:
		  case 7:
			 lua_pushstring(L, "Shaman");
			 break;
		  case 8:
			 lua_pushstring(L, "Mage");
			 break;
		  case 9:
			 lua_pushstring(L, "Warlock");
			 break;
		  //case 10:
		  case 11:
			 lua_pushstring(L, "Druid");
			 break;
		  default:
			 lua_pushstring(L, "Unknown");
			 break;
	   }
	   return 1;
	}
	int ClearHateList(lua_State * L, Unit * ptr)
	{
 		CHECK_TYPEID_RET_INT(TYPEID_UNIT);
 		ptr->ClearHateList();
 		return 1;
	}
	int PvPFlagged(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushboolean(L,( TO_PLAYER( ptr )->IsPvPFlagged())?1:0);
		return 1;
	}
	int GetRunSpeed(lua_State *  L, Unit * ptr)
	{
		CHECK_PTR();
		if(ptr->GetTypeId() == TYPEID_PLAYER || ptr->GetTypeId() == TYPEID_UNIT)
			lua_pushnumber(L,(float)ptr->m_runSpeed);
		return 1;
	}
	int GetFlySpeed(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		if(ptr->GetTypeId() == TYPEID_UNIT || ptr->GetTypeId() == TYPEID_PLAYER)
			lua_pushnumber(L,(float)ptr->m_flySpeed);
		return 1;
	}
	int GetModel(lua_State * L, Unit * ptr)
	{
		if( ptr == NULL )
			lua_pushnil(L);
		else
			lua_pushinteger( L, ptr->GetUInt32Value( UNIT_FIELD_DISPLAYID ) );

		return 1;
	}
	int Disconnect(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		TO_PLAYER( ptr )->GetSession()->Disconnect();
		return 0;
	}
	int GetZone(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushinteger(L,ptr->GetZoneId());
		return 1;
	}
	int GetMapId(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushinteger(L,ptr->GetMapId());
		return 1;
	}
	int SendWideBroadcastMessage(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		const char * msg = luaL_checkstring(L,1);
		if(!msg) return 0;
		sWorld.SendWorldWideScreenText(msg, 0);
		return 0;
	}
	int IsBehind(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		Unit * target = Lunar<Unit>::check(L,1);
		if(target == NULL) return 0;
		lua_pushboolean(L,(ptr->isInBack( TO_UNIT( target )))?1:0);
		return 1;
	}
	int RemoveFlag(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		int newflag = luaL_checkint( L, 1 );
		int oldflag = luaL_checkint( L, 2 );
		ptr->RemoveFlag(newflag, oldflag);
		return 0;
	}
	int IsFlying(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL || ptr->GetTypeId() !=  TYPEID_PLAYER && ptr->GetTypeId() != TYPEID_UNIT) return 0;
		if(ptr->GetTypeId() == TYPEID_PLAYER)
			lua_pushboolean(L,( TO_PLAYER( ptr )->m_setflycheat)?1:0);
		else if(ptr->GetTypeId() == TYPEID_UNIT)
			lua_pushboolean(L,( TO_CREATURE( ptr )->GetAIInterface()->IsFlying())?1:0);
			return 1;
	}
	int SetFactionStanding(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		int faction = luaL_checkint( L, 1 );
		int val = luaL_checkint( L, 2 );
		if( val != 0 )
			TO_PLAYER( ptr )->SetStanding(faction,val);
		return 0;
	}
	int GetLevel(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL || ptr->GetTypeId() != TYPEID_UNIT && ptr->GetTypeId() != TYPEID_PLAYER) return 0;
		lua_pushinteger(L,ptr->getLevel());
		return 1;
	}
	int IsAlive(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL || ptr->GetTypeId() != TYPEID_UNIT && ptr->GetTypeId() != TYPEID_PLAYER) return 0;
		lua_pushboolean(L,(ptr->isAlive())?1:0);
		return 1;
	}
	int IsStealthed(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushboolean(L,( ((Player*)ptr)->InStealth())?1:0);
		return 1;
	}
	int IsGM(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushboolean(L,( ((Player*)ptr)->GetSession()->HasGMPermissions())?1:0);
		return 1;
	}
	int IsAlliance(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushboolean(L,( ((Player*)ptr)->GetTeam() == 1)?1:0);
		return 1;
	}
	int IsHorde(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushboolean(L,( ((Player*)ptr)->GetTeam() == 2)?1:0);
		return 1;
	}
	int HasAmountOfPlayers(lua_State * L, Unit * ptr)
	{
		int Amount = luaL_checkint( L, 1 );
		if (Amount == 0) return 0;
		lua_pushboolean(L, (sWorld.AlliancePlayers+sWorld.HordePlayers == Amount)?1:0);
		return 1;
	}
	int HasGMTagOn(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushboolean(L,( ((Player*)ptr)->bGMTagOn)?1:0);
		return 1;
	}
	int CastSpellAoF(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 sp = luaL_checkint(L, 4);
		float x = (float)luaL_checknumber(L,1);
		float y = (float)luaL_checknumber(L,2);
		float z = (float)luaL_checknumber(L,3);
		if(!sp | !x | !y | !z)
			return 0;
		ptr->CastSpellAoF(x,y,z,dbcSpell.LookupEntry(sp), true);
		return 0;
	}
	int RemoveAllAuras(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		if(ptr->GetTypeId() != TYPEID_UNIT || ptr->GetTypeId() != TYPEID_PLAYER )
			return 0;
		ptr->RemoveAllAuras();
		return 0;
	}
	int TogglePvP(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		((Player*)ptr)->PvPToggle();
		return 0;
	}
	int ApplyRestState(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Player * plr = (Player*)ptr;
		uint32 rs = luaL_checkint(L, 1);
		plr->ApplyPlayerRestState( (rs >0)?true:false);
		return 0;
	}
	int ResurrectPlayer(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Player * Plr = (Player*)ptr;
		//Plr->ResurrectPlayer();
		Plr->ResurrectPlayer(Plr);
		return 0;
	}
	int SetEmoteState(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		uint32 emote = luaL_checkint(L, 1);
		ptr->setEmoteState(emote);
		return 0;
	}
	int GetPlayerAccountName(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushstring(L,((Player*)ptr)->GetSession()->GetAccountNameS());
		return 1;
	}
	int RemoveStealth(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		((Player*)ptr)->RemoveStealth();
		return 0;
	}
	int Die(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		ptr->DealDamage(TO_UNIT( ptr ),ptr->GetUInt32Value(UNIT_FIELD_HEALTH),0,0,0);
		return 0;
	}
	int SetStealth(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 id = luaL_checkint(L, 1);
		if(id == 0) return 0;
		((Player*)ptr)->SetStealth(id);
		return 0;
	}
	int WorldQuery(lua_State * L, Unit * ptr)
	{
		const char * query = luaL_checkstring(L, 1);
		if(query == 0) return 0;
		WorldDatabase.Query(query);
		return 0;
	}
	int AddCreatureLoot(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		int entry = luaL_checkint(L, 1);
		int item = luaL_checkint(L, 2);
		int perc = luaL_checkint(L, 3);
		int hper = luaL_checkint(L, 4);
		int min = luaL_checkint(L, 5);
		int max = luaL_checkint(L, 6);
		int ffa = luaL_checkint(L, 7);
		WorldDatabase.Query("INSERT INTO `creatureloot` VALUES ('','%i','%i','%i','%i','%i','%i','%i')", entry, item, perc, hper, min, max, ffa);
		return 0;
	}

	int SystemMessageToPlr(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Unit * pTemp = Lunar<Unit>::check(L, 1);
		const char * msg = luaL_checkstring(L, 2);
		int color = luaL_checkint(L, 3);
		Player* target = TO_PLAYER(pTemp);
		if(color == 0)
			sChatHandler.SystemMessageToPlr(target, msg);
		else if(color == 1)
			sChatHandler.RedSystemMessageToPlr(target, msg);
		else if(color == 2)
			sChatHandler.BlueSystemMessageToPlr(target, msg);
		else if(color == 3)
			sChatHandler.GreenSystemMessageToPlr(target, msg);
		else
			sLog.outColor(TRED, "Error You specified a non existent interger for the function");
		return 0;
	}

	int CharacterQuery(lua_State * L, Unit * ptr)
	{
		const char * query = luaL_checkstring(L, 1);
		if(query == 0) return 0;
		CharacterDatabase.Query(query);
		return 0;
	}

	int IsInvincible(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		if(ptr->GetTypeId() != TYPEID_PLAYER && ptr->GetTypeId() != TYPEID_UNIT ) return 0;
		lua_pushboolean(L,(ptr->bInvincible)?1:0);
		return 1;
	}
	int SaveToDB(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		if(ptr->GetTypeId() == TYPEID_UNIT)
			((Creature*)ptr)->SaveToDB();
		else if(ptr->GetTypeId() == TYPEID_PLAYER)
			((Player*)ptr)->SaveToDB(false);
		return 0;
	}

	int IsMoving(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		if(ptr->GetTypeId() == TYPEID_UNIT)
			lua_pushboolean(L,(ptr->GetAIInterface()->m_creatureState == MOVING)?1:0);
		else if(ptr->GetTypeId() == TYPEID_PLAYER)
			lua_pushboolean(L,( ((Player*)ptr)->m_isMoving)?1:0);
		return 1;
	}
	int IsAttacking(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		if(ptr->GetTypeId() == TYPEID_UNIT)
			lua_pushboolean(L,( ((Player*)ptr)->GetAIInterface()->m_creatureState == ATTACKING)?1:0);
		else if( ptr->GetTypeId() == TYPEID_PLAYER)
			lua_pushboolean(L,( ((Player*)ptr)->IsAttacking())?1:0);
		return 1;
	}
			
	int SetInvincible(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 choice = luaL_checkint(L,1);
		ptr->bInvincible = ( (choice > 0)? true : false );
		return 0;
	}
	bool IsInrangeSQ( Object *t1, Object *t2,float sq_r)
	{
		if( !t1 || !t2 )
			return false;

		float distx=t1->GetPositionX()-t2->GetPositionX();
		float disty=t1->GetPositionY()-t2->GetPositionY();
		float dist = distx*distx + disty*disty; 
		return dist <= sq_r;
	}
	int IsInRange(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Player * plr = (Player*)ptr;
		float range = (float)luaL_checknumber(L,1);
		( (IsInrangeSQ(plr, ptr, range) == true)?lua_pushboolean(L,1) : lua_pushboolean(L,0) );
		return 1;
	}
	int FinishQuest(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		QuestLogEntry * qle;
		uint32 questid = luaL_checkint(L, 1);
		if(questid == 0) return 0;
		qle = ((Player*)ptr)->GetQuestLogForEntry(questid);
		( (qle != NULL) ? qle->Finish() : lua_pushnil(L) );
		return 0;
	}
		
	int IfQuestCanBeFinished(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		QuestLogEntry * qle;
		uint32 questid = luaL_checkint(L, 1);
		if(questid == 0) return 0;
		qle = ((Player*)ptr)->GetQuestLogForEntry(questid);
		if(qle != NULL)
		lua_pushboolean(L, (qle->CanBeFinished())?1:0);
		return 1;
	}
	int SetQuestComplete(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		QuestLogEntry * qle;
		uint32 questid = luaL_checkint(L, 1);
		if(questid == 0) return 0;
		qle = ((Player*)ptr)->GetQuestLogForEntry(questid);
		if(qle == 0) return 0;
		qle->SendQuestComplete();
		return 0;
	}

	int SubtractTime(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		QuestLogEntry * qle;
		uint32 time = luaL_checkint(L, 2);
		uint32 questid = luaL_checkint(L, 1);
		if(questid == 0) return 0;
		qle = ((Player*)ptr)->GetQuestLogForEntry(questid);
		if(qle == 0 ) return 0;
		qle->SubtractTime(time);
		return 0;
	}

	int MoveToPlayer(lua_State * L, Unit * ptr)
	{
		Unit * plr = Lunar<Unit>::check(L,1);
		if( plr->IsPlayer())
			ptr->GetAIInterface()->MoveTo(plr->GetPositionX(),plr->GetPositionY(),plr->GetPositionZ(),ptr->GetOrientation());
		return 0;
	}

	int EventCreatureYell(lua_State * L, Unit * ptr)
	{
		Creature * cre = (Creature*)ptr;
		uint32 time = luaL_checkint(L, 2);
		string msg = luaL_checkstring(L, 1);
		sEAS.EventCreatureYell(cre, msg, time);
		return 0;
	}

	int EventCreatureDelete(lua_State * L, Unit * ptr)
	{
		Creature * cre = (Creature*)ptr;
		uint32 time = luaL_checkint(L, 1);
		sEAS.EventCreatureDelete(cre, time);
		return 0;
	}

	int EventCastSpell(lua_State * L, Unit * ptr)
	{
		Creature * cre = (Creature*)ptr;
		uint32 time = luaL_checkint(L, 2);
		uint32 spellid = luaL_checkint(L, 1);
		Player * target = Lunar<Player>::check(L, 3);
		sEAS.EventCastSpell(ptr, target, spellid, time);
		return 0;
	}

	int EventCastSpellOnSelf(lua_State * L, Unit * ptr)
	{
		Creature * cre = (Creature*)ptr;
		uint32 time = luaL_checkint(L, 2);
		uint32 spellid = luaL_checkint(L, 1);
		sEAS.EventCastSpell(ptr, ptr, spellid, time);
		return 0;
	}

	int EventPlaySound(lua_State * L, Unit * ptr)
	{
		Creature * cre = (Creature*)ptr;
		uint32 time = luaL_checkint(L, 2);
		uint32 soundid = luaL_checkint(L, 1);
		sEAS.EventPlaySound(cre, soundid, time);
		return 0;
	}
	int MonsterMove(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL || (ptr->GetTypeId() != TYPEID_UNIT && ptr->GetTypeId() != TYPEID_PLAYER)) return 0;
		float x = (float)luaL_checkint(L,1);
		float y = (float)luaL_checkint(L,2);
		float z = (float)luaL_checkint(L,3);
		uint32 time = luaL_checkint(L,4);
		uint32 moveflags = luaL_checkint(L,5);
		if(!x || !y || !z || !time) return 0;

		WorldPacket data(SMSG_MONSTER_MOVE,(sizeof(float)*6)+(sizeof(uint32)*4)+sizeof(WoWGuid));
		data << ptr->GetNewGUID();
		data << ptr->GetPosition();
		data << getMSTime();
		if(ptr->GetOrientation())
		{
			data << uint8(4);
			data << ptr->GetOrientation();
		}
		else
			data << uint8(0);
		data << moveflags;
		data << time;
		data << uint32(1);
		data << x << y << z;
		if(ptr->GetTypeId() == TYPEID_UNIT)
			ptr->SendMessageToSet(&data, false);
		else if(ptr->GetTypeId() == TYPEID_PLAYER)
			((Player*)ptr)->GetSession()->SendPacket(&data);
		return 0;
	}
	int SetPosition(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		float x = (float)luaL_checkint(L,1);
		float y = (float)luaL_checkint(L,2);
		float z = (float)luaL_checkint(L,3);
		if(!x ||!y||!z) return 0;
		LocationVector vec(x,y,z);
		ptr->SetPosition(vec,true);
		return 0;
	}
	int SetCurrentAgent(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 agent = luaL_checkint(L,1);
		if(agent == NULL) return 0;
		ptr->GetAIInterface()->setCurrentAgent(AI_Agent(agent));
		return 0;
	}
	/*int AddAISpell(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 spellid = luaL_checkint(L,1);
		uint32 agent	= luaL_checkint(L,2);
		uint32 cd	= luaL_checkint(L,3);
		uint32 spelltype = luaL_checkint(L,4);
		uint32 targetype = luaL_checkint(L,5);
		uint32 procchance = luaL_checkint(L,6);
		uint32 autocast = luaL_checkint(L,7);
		if(!spellid) return 0;
		SpellEntry * spp = dbcSpell.LookupEntry(spellid);
		AI_Spell * sp = new AI_Spell();
		sp->agent = agent;
		sp->autocast_type = autocast;
		sp->cooldown = cd;
		sp->cooldowntime = 0;
		sp->custom_pointer = true;
		sp->entryId = ptr->GetEntry();
		sp->floatMisc1 = 0;
		sp->maxrange = GetMaxRange(dbcSpellRange.LookupEntry(spp->rangeIndex));
		sp->minrange = GetMinRange(dbcSpellRange.LookupEntry(spp->rangeIndex));
		sp->Misc2 = 0;
		sp->procChance = procchance;
		sp->procCount = 0;
		sp->procCounter = 0;
		sp->spell = spp;
		sp->spelltargetType = targetype;
		sp->spellType = spelltype;
		if( agent == AGENT_RANGED)
			ptr->GetAIInterface()->m_canRangedAttack = true;
		else if( agent == AGENT_SPELL)
			ptr->GetAIInterface()->addSpellToList(sp);
		return 0;
	}*/
	int RegisterAIUpdateEvent(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 time = luaL_checkint(L,1);
		if(!time) return 0;
		sEventMgr.AddEvent( TO_CREATURE(ptr ),&Creature::CallScriptUpdate,EVENT_CREATURE_UPDATE,time,0,0);
		return 0;
	}
	int ModifyAIUpdateEvent(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 newtime = luaL_checkint(L,1);
		if(!newtime) return 0;
		sEventMgr.ModifyEventTime( TO_CREATURE( ptr ),EVENT_CREATURE_UPDATE,newtime);
		return 0;
	}
	int RemoveAIUpdateEvent(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		sEventMgr.RemoveEvents( TO_CREATURE( ptr ),EVENT_CREATURE_UPDATE);
		return 0;
	}
	int SetDamageDone(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 school = luaL_checkint(L,1);
		uint32 coeff = luaL_checkint(L,2);

		((Creature*)ptr)->ModDamageDone[school] = coeff;
		return 0;
	}
	int GetDamageDone(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 school = luaL_checkint(L,1);
		lua_pushnumber(L,((Creature*)ptr)->ModDamageDone[school]);
		return 1;
	}
	int SetAIState(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 typ = luaL_checkint(L,1);
		((Creature*)ptr)->GetAIInterface()->SetAIState(AI_State(typ));
		return 0;
	}
	int DisableRespawn(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		((Creature*)ptr)->m_noRespawn = true;
		return 0;
	}
	int ModifySpeed(lua_State  * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		uint32 speed = luaL_checkint(L,1);
		if(speed == 0) return 0;
		ptr->m_speedModifier = (float)speed;
		ptr->UpdateSpeed();
		return 0;
	}
	int SetInvisible(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		uint32 choice = luaL_checkint(L,1);
		//if( choice > 0 ) ptr->m_auracount[18]++;
		//else ptr->m_auracount[18]--;
		if( choice > 0 )
		{
			ptr->m_invisFlag = (uint8)choice;
			ptr->m_invisible = true;
		}
		else
		{
			ptr->m_invisFlag = INVIS_FLAG_NORMAL;
			ptr->m_invisible = false;
		}
		ptr->UpdateVisibility();
		return 0;
	}
	int GetInRangePlayers(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		uint32 count = NULL;
		lua_newtable(L);
		for(PlayerSet::iterator itr = ptr->GetInRangePlayerSetBegin(); itr != ptr->GetInRangePlayerSetEnd(); itr++)
		{
			count++;
			lua_pushinteger(L,count);
			Lunar<Unit>::push(L, TO_UNIT(*itr));
			lua_rawset(L,-3);
		}
		return 1;
	}
	int GetInRangeFriends(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		uint32 count = NULL;
		lua_newtable(L);
		for(ObjectSet::iterator itr = ptr->GetInRangeSetBegin(); itr != ptr->GetInRangeSetEnd(); itr++)
		{
			if( (*itr)->IsUnit() && isFriendly(TO_OBJECT(ptr),(*itr)) )
			{
				count++;
				lua_pushinteger(L,count);
				Lunar<Unit>::push(L, TO_UNIT(*itr) );
				lua_rawset(L,-3);
			}
		}
		return 1;
	}
	int GetInRangeUnits(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 count = 0;
		lua_newtable(L);
		for(ObjectSet::iterator itr = ptr->GetInRangeSetBegin(); itr != ptr->GetInRangeSetEnd(); itr++)
		{
			if( (*itr)->GetTypeId() == TYPEID_UNIT  )
			{
				count++;
				lua_pushinteger(L,count);
				Lunar<Unit>::push(L,(TO_UNIT(*itr) ));
				lua_rawset(L,-3);
			}
		}
		return 1;
	}
	int RemoveFromWorld(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		if( ptr->GetTypeId() != TYPEID_UNIT && ptr->GetTypeId() != TYPEID_PLAYER ) return 0;
		ptr->RemoveFromWorld(true);
		return 0;
	}
	int GetCreatureNearestCoords(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		float x = (float)luaL_checkinteger(L,1);
		float y = (float)luaL_checkinteger(L,2);
		float z = (float)luaL_checkinteger(L,3);
		uint32 entryid = luaL_checkint(L,4);
		if(x == 0 || y == 0 || z == 0 || entryid == 0 ) return 0;
		Creature* pC = ptr->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x,y,z,entryid);
		if( pC == NULL) return 0;
		Lunar<Unit>::push(L,TO_UNIT(pC) );
		return 1;
	}
	int GetGameObjectNearestCoords(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		float x = (float)luaL_checkinteger(L,1);
		float y = (float)luaL_checkinteger(L,2);
		float z = (float)luaL_checkinteger(L,3);
		uint32 entryid = luaL_checkint(L,4);
		if(x == 0 || y == 0 || z == 0 || entryid == 0 ) return 0;
		GameObject* Obj = ptr->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(x,y,z,entryid);
		if(Obj == NULL) return 0;
		Lunar<GameObject>::push(L,(Obj) );
		return 1;
	}
	int GetUInt32Value(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL || (ptr->GetTypeId() != TYPEID_UNIT && ptr->GetTypeId() != TYPEID_PLAYER)) return 0;
		uint32 field = luaL_checkint(L,1);
		lua_pushinteger(L,ptr->GetUInt32Value(field));
		return 1;
	}
	int GetUInt64Value(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL || (ptr->GetTypeId() != TYPEID_UNIT && ptr->GetTypeId() != TYPEID_PLAYER)) return 0;
		uint32 field = luaL_checkint(L,1);
		lua_pushnumber(L,ptr->GetUInt64Value(field));
		return 1;
	}
	int GetDistance(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL ) return 0;
		Unit * tar = Lunar<Unit>::check(L,1);
		if( tar == NULL) return 0;
		lua_pushnumber(L,ptr->CalcDistance(tar->GetPositionX(),tar->GetPositionY(),tar->GetPositionZ()));
		return 1;
	}
	int CalcDistance(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		float x = (float)luaL_checkint(L,1);
		float y = (float)luaL_checkint(L,2);
		float z = (float)luaL_checkint(L,3);
		if(x == 0 || y == 0 || z == 0 ) return 0;
		lua_pushnumber(L,ptr->CalcDistance(x,y,z));
		return 1;
	}
	int GetCurrentSpellId(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		if(ptr->GetCurrentSpell() != 0)
			lua_pushinteger(L,ptr->GetCurrentSpell()->m_spellInfo->Id);
		return 1;
	}
	int GetCurrentSpellName(lua_State * L, Unit * ptr)
	{
		if(ptr == NULL) return 0;
		if(ptr->GetCurrentSpell() != 0 )
			lua_pushstring(L,ptr->GetCurrentSpell()->m_spellInfo->Name);
		return 1;
	}
	int ModThreat(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		Unit * target = Lunar<Unit>::check(L,1);
		uint32 threattomod = luaL_checkint(L,2);
		if(target == NULL) return 0;
		ptr->GetAIInterface()->modThreatByPtr(TO_UNIT( target ),threattomod);
		return 0;
	}
	int RemoveThreat(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		Unit * target = Lunar<Unit>::check(L,1);
		if(target == NULL) return 0;
		ptr->GetAIInterface()->RemoveThreatByPtr(TO_UNIT( target ));
		return 0;
	}
	int GetThreat(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		Unit * target = Lunar<Unit>::check(L,1);
		if(target == NULL) return 0;
		lua_pushinteger(L,(uint32)ptr->GetAIInterface()->getThreatByPtr(TO_UNIT( target )));
		return 1;
	}
	int GetPowerType(lua_State * L, Unit * ptr)
	{
		if( ptr == NULL ||(ptr->GetTypeId() != TYPEID_PLAYER && ptr->GetTypeId() != TYPEID_UNIT)) return 0;
		switch(ptr->GetPowerType())
		{
		case POWER_TYPE_HEALTH:
			lua_pushstring(L,"Health");
			break;
		case POWER_TYPE_MANA:
			lua_pushstring(L,"Mana");
			break;
		case POWER_TYPE_FOCUS:
			lua_pushstring(L,"Focus");
			break;
		case POWER_TYPE_ENERGY:
			lua_pushstring(L,"Energy");
			break;
		case POWER_TYPE_RAGE:
			lua_pushstring(L,"Rage");
			break;
		default:
			lua_pushstring(L,"Unknown");
			break;
		}
		return 1;
	}
	int SetNextTarget(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		Unit * tar = Lunar<Unit>::check(L,1);
		if( tar == NULL) return 0;
		ptr->GetAIInterface()->SetNextTarget(TO_UNIT( tar ));
		return 0;
	}
	int GetNextTarget(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		Lunar<Unit>::push(L,(ptr->GetAIInterface()->GetNextTarget()) );
		return 1;
	}
	int GetSpawnX(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		if(ptr->GetSpawnX() != 0)
			lua_pushnumber(L,(float)ptr->GetSpawnX());
		return 1;
	}
	int GetSpawnY(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		if(ptr->GetSpawnY() != 0)
			lua_pushnumber(L,(float)ptr->GetSpawnY());
		return 1;
	}
	int GetSpawnZ(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		if(ptr->GetSpawnZ() != 0)
			lua_pushnumber(L,(float)ptr->GetSpawnZ());
		return 1;
	}
	int GetSpawnO(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		if(ptr->GetSpawnO() != 0)
			lua_pushnumber(L,(float)ptr->GetSpawnO());
		return 1;
	}
	int GetInstanceMode(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Player * plr = ((Player*)ptr);
		if(plr->GetMapMgr()->GetMapInfo()->type != INSTANCE_NULL)
		{
			switch(plr->iInstanceType)
			{
			case MODE_EPIC_5MEN:
				lua_pushstring(L,"Epic");
			case MODE_NORMAL_5MEN:
				lua_pushstring(L,"Normal");
			case MODE_HEROIC_5MEN:
				lua_pushstring(L,"Heroic");
			default:
				lua_pushstring(L,"Unknown");
			}
		}
		return 1;
	}
	/*int KnockBack(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		float distance = (float)luaL_checkint(L,1);
		float height = (float)luaL_checkint(L,2);
		Player * plr = ((Player*)ptr);
		WorldPacket data(SMSG_MOVE_KNOCK_BACK,50);
		data << plr->GetNewGUID();
		data << getMSTime();
		data << cosf(plr->GetOrientation()) << sinf(ptr->GetOrientation());
		data << distance;
		data << (-height);
		plr->blinked = true;
		plr->DelaySpeedHack(5000);
		plr->GetSession()->SendPacket(&data);
		return 0;
	}*/
	int Root(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		ptr->m_canMove = false;
		return 0;
	}
	int Unroot(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		ptr->m_canMove = true;
		return 0;
	}
	int GetSelection(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Player * plr =  ((Player*)ptr);
		if( plr->GetSelection() != 0)
			Lunar<Unit>::push(L,(plr->GetMapMgr()->GetUnit(plr->GetSelection())) );
		return 1;
	}
	int SetSelection(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Unit * tar = Lunar<Unit>::check(L,1);
		if(tar == NULL) return 0;
		((Player*)ptr)->SetSelection(tar->GetGUID());
		return 0;
	}
	int SendMeetingStoneQueue(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 dungeon_id = luaL_checkint(L,1);
		uint32 status = luaL_checkint(L,2);
		((Player*)ptr)->SendMeetingStoneQueue(dungeon_id,status);
		return 0;
	}
	int IsInFeralForm(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Player * plr = ((Player*)ptr);
		lua_pushboolean(L,(plr->IsInFeralForm() != 0)?1:0);
		return 1;
	}
	int GetStanding(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 faction = luaL_checkint(L,1);
		Player * plr = ((Player*)ptr);
		lua_pushinteger(L,( plr->GetStanding(faction) != 0)?plr->GetStanding(faction) : 0);
		return 1;
	}
	int SetStanding(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 faction = luaL_checkint(L,1);
		int32 value = luaL_checkint(L,2);
		((Player*)ptr)->SetStanding(faction,value);
		return 0;
	}
	int ModStanding(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 faction = luaL_checkint(L,1);
		int32 value = luaL_checkint(L,2);
		((Player*)ptr)->ModStanding(faction,value);
		return 0;
	}
	int SetAtWar(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 faction = luaL_checkint(L,1);
		uint32 set = luaL_checkint(L,2);
		((Player*)ptr)->SetAtWar(faction,(set > 0)?true:false);
		return 0;
	}
	/*int IsAtWar(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 faction = luaL_checkint(L,1);
		Player * plr = static_cast<Player*>(ptr);
		if( plr->IsAtWar(faction) == true)
			lua_pushboolean(L,1);
		else
			lua_pushboolean(L,0);
		return 1;
	}*/
	int GetStandingRank(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 faction = luaL_checkint(L,1);
		switch( ((Player*)ptr)->GetStandingRank(faction))
		{
		case STANDING_HATED:
			lua_pushstring(L,"Hated");
		case STANDING_HOSTILE:
			lua_pushstring(L,"Hostile");
		case STANDING_UNFRIENDLY:
			lua_pushstring(L,"Unfriendly");
		case STANDING_NEUTRAL:
			lua_pushstring(L,"Neutral");
		case STANDING_FRIENDLY:
			lua_pushstring(L,"Friendly");
		case STANDING_HONORED:
			lua_pushstring(L,"Honored");
		case STANDING_REVERED:
			lua_pushstring(L,"Revered");
		case STANDING_EXALTED:
			lua_pushstring(L,"Exalted");
		default:
			lua_pushstring(L,"Unknown");
		}
		return 1;
	}
	int UpdateInRangeSet(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		((Player*)ptr)->UpdateInrangeSetsBasedOnReputation();
		return 0;
	}
	int GetRepRankFromStanding(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 value = luaL_checkint(L,1);
		switch( ((Player*)ptr)->GetReputationRankFromStanding(value))
		{
		case STANDING_HATED:
			lua_pushstring(L,"Hated");
		case STANDING_HOSTILE:
			lua_pushstring(L,"Hostile");
		case STANDING_UNFRIENDLY:
			lua_pushstring(L,"Unfriendly");
		case STANDING_NEUTRAL:
			lua_pushstring(L,"Neutral");
		case STANDING_FRIENDLY:
			lua_pushstring(L,"Friendly");
		case STANDING_HONORED:
			lua_pushstring(L,"Honored");
		case STANDING_REVERED:
			lua_pushstring(L,"Revered");
		case STANDING_EXALTED:
			lua_pushstring(L,"Exalted");
		default:
			lua_pushstring(L,"Unknown");
		}
		return 1;
	}
	int GetPVPRank(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushinteger(L, ((Player*)ptr)->GetPVPRank());
		return 1;
	}
	int SetPVPRank(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		int32 newrank = luaL_checkint(L,1);
		((Player*)ptr)->SetPVPRank(newrank);
		return 0;
	}
	int IsGroupLeader(lua_State* L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushboolean(L,( ((Player*)ptr)->IsGroupLeader() == true)?1:0);
		return 1;
	}
	int IsGroupMember(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushboolean(L,( TO_PLAYER(ptr )->IsGroupMember( TO_PLAYER(ptr )) == true)?1:0);
		return 1;
	}
	int SetBanned(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		const char * msg = luaL_checklstring(L,1,NULL);
		if(msg)
			((Player*)ptr)->SetBanned(string(msg));
		else
			((Player*)ptr)->SetBanned();
		return 0;
	}
	int UnSetBanned(lua_State  * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		((Player*)ptr)->UnSetBanned();
		return 0;
	}
	int SetBindPoint(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		float x = (float)luaL_checkint(L,1);
		float y = (float)luaL_checkint(L,2);
		float z = (float)luaL_checkint(L,3);
		uint32 mapid = luaL_checkint(L,4);
		uint32 zoneid = luaL_checkint(L,5);
		((Player*)ptr)->SetBindPoint(x,y,z,mapid,zoneid);
		return 0;
	}
	int ResetTalents(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		((Player*)ptr)->Reset_Talents();
		return 0;
	}
	int GetBindPosition(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_newtable(L);
		Player * plr = ((Player*)ptr);
		lua_pushstring(L,"x");
		lua_pushnumber(L,(float)plr->GetBindPositionX());
		lua_rawset(L,-3);
		lua_pushstring(L,"y");
		lua_pushnumber(L,(float)plr->GetBindPositionY());
		lua_rawset(L,-3);
		lua_pushstring(L,"z");
		lua_pushnumber(L,(float)plr->GetBindPositionZ());
		lua_rawset(L,-3);
		lua_pushstring(L,"mapid");
		lua_pushnumber(L,(float)plr->GetBindMapId());
		lua_rawset(L,-3);
		lua_pushstring(L,"zoneid");
		lua_pushnumber(L,(float)plr->GetBindZoneId());
		lua_rawset(L,-3);
		
		return 1;
	}
	int AllowFallDamage(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 choice = luaL_checkint(L,1);
		((Player*)ptr)->m_noFallDamage = (choice > 0)?true:false;
		return 0;
	}
	int GetSoulStone(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		lua_pushinteger(L,((Player*)ptr)->GetSoulStone());
		return 1;
	}
	int SetSoulStone(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 id = luaL_checkint(L,1);
		if(id != 0)
			((Player*)ptr)->SetSoulStone(id);
		return 0;
	}
	int SetReincarnate(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 choice = luaL_checkint(L,1);
		((Player*)ptr)->bReincarnation = (choice >0)?true:false;
		return 0;
	}
	int EjectFromInstance(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		((Player*)ptr)->EjectFromInstance();
		return 0;
	}
	int SetPlayerName(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		const char * name = luaL_checkstring(L,1);
		if(name == 0 ) return 0;
		((Player*)ptr)->SetName(string(name));
		return 0;
	}
	int OnUnitEvent(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		const char * func_to_call = luaL_checkstring(L,1);
		uint32 eventnum = luaL_checkint(L,2);
		Unit * pMisc = Lunar<Unit>::check(L,3);
		uint32 Misc  = luaL_checkint(L,4);
		g_engine.OnUnitEvent(ptr,func_to_call,eventnum,pMisc,Misc);
		return 0;
	}
	/* Date : 01/05/2009 */
	int AbsorbDamage(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 school = luaL_checkint(L,1);
		uint32 dmg = luaL_checkint(L,2);
	//	Unit * pMisc = Lunar<Unit>::check(L,3);
		if(school == 0) return 0;
	//	ptr->AbsorbDamage(pMisc,school, &dmg);
		return 0;
	}
	int GetEntry(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		( (ptr != NULL) ? lua_pushinteger(L, ptr->GetEntry()) : lua_pushnil(L));
		return 1;
	}
	int Energize(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		Unit * target = Lunar<Unit>::check(L,1);
		uint32 spellid = luaL_checkint(L,2);
		uint32 amt = luaL_checkint(L,3);
		uint32 type = luaL_checkint(L,4);
		if(target == NULL || spellid == 0) return 0;
		ptr->Energize( TO_UNIT(target), spellid, amt, type);
		return 0;
	}
	int Heal(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		Unit * target = Lunar<Unit>::check(L,1);
		uint32 spellid = luaL_checkint(L,2);
		uint32 amt = luaL_checkint(L,3);
		if(target == NULL || !spellid) return 0;
		ptr->Heal( TO_UNIT(target), spellid, amt);
		return 0;
	}
	int GetAP(lua_State * L, Unit * ptr)
	{
		bool ranged = ( (luaL_checkint(L,1) != 0) ? true : false );
		if(ptr == NULL) lua_pushnil(L);
		( (ranged == true) ? lua_pushinteger(L, ptr->GetRAP()) : lua_pushinteger(L,ptr->GetAP()) );
		return 1;
	}
	int GetPlayerRace(lua_State * L, Unit * ptr) {
		char * s;
		switch( ptr->getRace()) {
			case RACE_HUMAN: s = "Human"; break;
			case RACE_BLOODELF: s = "BloodElf"; break;
			case RACE_TROLL: s = "Troll"; break;
			case RACE_NIGHTELF: s = "NightElf"; break;
			case RACE_UNDEAD_PLAYER: s = "Undead"; break;
			case RACE_ORC: s = "Orc"; break;
			case RACE_DWARF: s = "Dwarf"; break;
			case RACE_GNOME: s = "Gnome"; break;
			case RACE_DRAENEI: s = "Draenei"; break;
			case RACE_TAUREN: s = "Tauren"; break;
			default: s = "Unknown"; break;
		}
		lua_pushstring(L,s);
		return 1;
	}
	int GetSummon(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Pet* pPet = TO_PLAYER(ptr)->GetSummon();
		( (pPet != NULL) ? Lunar<Unit>::push(L, (Unit*)(pPet)) : lua_pushnil(L) );
		return 1;
	}
	int IsInParty(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		Player* plr = TO_PLAYER(ptr);
		if(plr->GetGroup() == NULL) return 0;
		Group * party = plr->GetGroup();
		if(party->GetGroupType() == GROUP_TYPE_PARTY)
			lua_pushboolean(L,1);
		else
			lua_pushboolean(L,0);
	//	( (ptr->InParty( TO_UNIT(ptr)) == true) ? lua_pushboolean(L,1) : lua_pushboolean(L, 0) );
		return 1;
	}
	int IsInRaid(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
	//	( (ptr->InRaid( TO_UNIT(ptr)) == true) ? lua_pushboolean(L, 1) : lua_pushboolean(L, 0) );
		Player* plr = TO_PLAYER(ptr);
		if(plr->GetGroup() == NULL) return 0;
		Group * party = plr->GetGroup();
		if(party->GetGroupType() == GROUP_TYPE_RAID)
			lua_pushboolean(L,1);
		else
			lua_pushboolean(L,0);
		return 1;
	}
	int IsCasting(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		( (ptr->isCasting() == true) ? lua_pushboolean(L,1) : lua_pushboolean(L, 0) );
		return 1;
	}
	int SetAttackTimer(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		int32 timer = luaL_checkint(L,1);
		bool offhand = ( (luaL_checkint(L,2)) ? true : false );
		ptr->setAttackTimer(timer, offhand);
		return 0;
	}
	int SetDeathState(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 deathstate = luaL_checkint(L,1);
		if(deathstate > 3) return 0;
		ptr->setDeathState( DeathState(deathstate) );
		return 0;
	}
	int GetDeathState(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushinteger(L, uint32(ptr->getDeathState()) );
		return 1;
	}
	int ShareHealth(lua_State * L, Unit * ptr)
	{
		Unit * target = Lunar<Unit>::check(L,1);
		if(target == NULL) return 0;
	//	ptr->ShareHealthWithUnit( TO_UNIT(target) );
		return 0;
	}
	int GetStandState(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushinteger(L, uint32(ptr->GetStandState()));
		return 1;
	}
	/* End Date : 01/05/2009 */
	/* Date : 01/07/2009 */
	int SetUInt32Value(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 field = luaL_checkint(L,1);
		uint32 valu = luaL_checkint(L,2);
		if(!field || !valu) return 0;
		ptr->SetUInt32Value(field,valu);
		return 0;
	}
	int SetUInt64Value(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 field = luaL_checkint(L,1);
		uint32 valu = luaL_checkint(L,2);
		if(!field || !valu) return 0;
		ptr->SetUInt64Value(field, uint64(valu));
		return 0;
	}
	int GetGUID(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		( (ptr->GetGUID()) ? lua_pushinteger(L, (uint32)ptr->GetGUID()) : lua_pushnil(L) );
		return 1;
	}
	int CalcRadAngle(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 x1 = luaL_checkint(L,1);
		uint32 y1 = luaL_checkint(L,2);
		uint32 x2 = luaL_checkint(L,3);
		uint32 y2 = luaL_checkint(L,4);
		if(!x1 || !y1 || !x2 || !y2) return 0;
		lua_pushnumber(L, ptr->calcRadAngle(x1,y1,x2,y2) );
		return 1;
	}
	int EnableFlight(lua_State * L, Unit *ptr)
	{
		CHECK_PTR();
		WorldPacket data(835,13);
		if(ptr->IsUnit())
		{
			data << ptr->GetGUID();
			data << uint32(2);
			ptr->SendMessageToSet(&data, false);
			return 0;
		}
		else if(ptr->IsPlayer())
		{
			data << ptr->GetGUID();
			data << uint32(2);
		//	((Player*)ptr)->m_canfly = true;
			((Player*)ptr)->m_setflycheat = true;
			((Player*)ptr)->SendMessageToSet(&data,true);
			return 0;
		}
		else return 0;
	}
	int DisableFlight(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		WorldPacket data(836,13);
		if(ptr->IsUnit())
		{
			data << ptr->GetGUID();
			data << uint32(5);
			ptr->SendMessageToSet(&data, false);
		}
		else if(ptr->IsPlayer())
		{
			data << ptr->GetGUID();
			data << uint32(5);
		//	((Player*)ptr)->m_canfly = false;
			((Player*)ptr)->m_setflycheat = false;
			((Player*)ptr)->SendMessageToSet(&data,true);
		}
		else 
			return 0;

	return 0;
	}
	int AttackReaction(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		Unit * target = Lunar<Unit>::check(L,1);
		uint32 amt = luaL_checkint(L,2);
		if(target == NULL) return 0;
		((Creature*)ptr)->GetAIInterface()->AttackReaction(TO_UNIT(target),amt);
		return 0;
	}
	int IsInWorld(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		if(ptr->IsInWorld() == true)
				lua_pushboolean(L,1);
		else
				lua_pushboolean(L,0);
		return 1;
	}
	int PlaySpellVisual(lua_State * L, Unit *ptr)
	{
		CHECK_PTR();
		uint32 visualid = luaL_checkint(L,2);
		Unit * target = Lunar<Unit>::check(L,1);
		if(target == NULL || !visualid) return 0;
		ptr->PlaySpellVisual(target->GetGUID(),visualid);
		return 0;
	}
	int ImmuneMechanic(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 mechanic = luaL_checkint(L,1);
		uint32 choice = luaL_checkint(L,2);
		if(!mechanic|| !choice) return 0;
	//	( (choice > 0 ) ? ptr->m_mechanicscount[mechanic]++ : ptr->m_mechanicscount[mechanic] = 0);
		( (choice > 0 ) ? ptr->MechanicsDispels[mechanic]++ : ptr->MechanicsDispels[mechanic] = 0);
		return 0;
	}
	/* End Date : 01/07/2008 */
	/* Date : 01/13/2009 */
	int GetCurrentWaypoint(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		lua_pushinteger(L,ptr->GetAIInterface()->m_currentWaypoint);
		return 1;
	}
	int SetAllowedToEnterCombat(lua_State * L, Unit *  ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 choice = luaL_checkint(L,1);
		( (choice > 0) ? ptr->GetAIInterface()->SetAllowedToEnterCombat(true) : ptr->GetAIInterface()->SetAllowedToEnterCombat(false));
		return 0;
	}
	int GetDistanceSq(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		Unit * tar = Lunar<Unit>::check(L,1);
		if( tar == NULL) return 0;
		lua_pushnumber(L,(float)ptr->GetDistanceSq(TO_OBJECT( tar )));
		return 1;
	}
	int SetOutOfCombatRange(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		uint32 nrange = luaL_checkint(L,1);
		ptr->GetAIInterface()->setOutOfCombatRange(nrange);
		return 0;
	}
	int SetSpawnLocation(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_UNIT);
		double x = luaL_checknumber(L,1);
		double y = luaL_checknumber(L,2);
		double z = luaL_checknumber(L,3);
		double o = luaL_checknumber(L,4);
		LocationVector pVect(x,y,z,o);
	//	ptr->SetSpawnPosition(pVect);
		ptr->SetPosition(pVect);
		return 0;
	}
	int DeleteAllWaypoints(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		ptr->GetAIInterface()->deleteWaypoints();
		return 0;
	}
	int ChangeWaypoint(lua_State * L , Unit * ptr)
	{
		CHECK_PTR();
		uint32 oldwp = luaL_checkint(L,1);
		uint32 newwp = luaL_checkint(L,2);
		ptr->GetAIInterface()->changeWayPointID(oldwp,newwp);
		return 0;
	}
	int DeleteWaypoint(lua_State * L, Unit * ptr)
	{
		CHECK_PTR();
		uint32 wp = luaL_checkint(L,1);
		ptr->GetAIInterface()->deleteWayPoint(wp);
		return 0;
	}
	int AddHonorToPlayer(lua_State * L, Unit * ptr)
	{
		CHECK_TYPEID(TYPEID_PLAYER);
		uint32 points = luaL_checkint(L,1);
		Player* pPlayer = TO_PLAYER(ptr);
		if(pPlayer->m_honorPoints + points >= 75000)
			points = 75000 - pPlayer->m_honorPoints;
		pPlayer->m_honorPoints += points;
		pPlayer->SetUInt32Value(PLAYER_FIELD_KILLS, pPlayer->m_killsToday);
		pPlayer->SetUInt32Value(PLAYER_FIELD_TODAY_CONTRIBUTION, pPlayer->m_honorToday);
		pPlayer->SetUInt32Value(PLAYER_FIELD_YESTERDAY_CONTRIBUTION, pPlayer->m_killsYesterday | ( (pPlayer->m_honorYesterday * 10) << 16));
	//	pPlayer->SetUInt32Value(PLAYER_FIELD_LIFETIME_HONORBALE_KILLS, pPlayer->m_killsLifetime);
		pPlayer->SetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS, pPlayer->m_killsLifetime);
		pPlayer->SetUInt32Value(PLAYER_FIELD_HONOR_CURRENCY, pPlayer->m_honorPoints);
		pPlayer->SetUInt32Value(PLAYER_FIELD_ARENA_CURRENCY, pPlayer->m_arenaPoints);
		return 0;
	}
}

namespace luaItem
{
	int GossipCreateMenu(lua_State * L, Item * ptr)
	{
		int text_id = luaL_checkint(L, 1);
		Unit* target = Lunar<Unit>::check(L, 2);
 		int autosend = luaL_checkint(L, 3);
		if(target->GetTypeId() != TYPEID_PLAYER) return 0;

		Player* plr = TO_PLAYER( target );
	    
		objmgr.CreateGossipMenuForPlayer(&Menu, ptr->GetGUID(), text_id, plr);
		if(autosend)
			Menu->SendTo(plr);
		return 1;
	}
	int GossipMenuAddItem(lua_State * L, Item * ptr)
	{
		int icon = luaL_checkint(L, 1);
		const char * menu_text = luaL_checkstring(L, 2);
		int IntId = luaL_checkint(L, 3);
		int extra = luaL_checkint(L, 4);

		Menu->AddItem(icon, menu_text, IntId, extra);
		return 1;
	}
	int GossipSendMenu(lua_State * L, Item * ptr)
	{
		Unit* target = Lunar<Unit>::check(L, 1);
		if(target->GetTypeId() != TYPEID_PLAYER) return 0;
		Player* plr = TO_PLAYER( target );
		Menu->SendTo(plr);
		return 1;
	}
	int GossipComplete(lua_State * L, Item * ptr)
	{
		Unit* target = Lunar<Unit>::check(L, 1);
		if(target->GetTypeId() != TYPEID_PLAYER) return 0;
		Player* plr = TO_PLAYER( target );
		plr->Gossip_Complete();
		return 1;
	}
	int GossipSendPOI(lua_State * L, Item * ptr)
	{
		Unit* target = Lunar<Unit>::check(L, 1);
		Player * plr = (Player*)target;
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		int icon = luaL_checkint(L, 4);
		int flags = luaL_checkint(L, 5);
		int data = luaL_checkint(L, 6);
		const char * name = luaL_checkstring(L, 7);
		if(target->GetTypeId() != TYPEID_PLAYER) return 0;

		plr->Gossip_SendPOI(x, y, icon, flags, data, name);
		return 1;
	}
}
