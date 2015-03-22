/*

 */

#ifndef __LUAENGINE_H
#define __LUAENGINE_H

#include "StdAfx.h"
//#include "LUAFunctions.h"
#define SKIP_ALLOCATOR_SHARING 1
#include "EAS/EasyFunctions.h"

extern "C" {		// we're C++, and LUA is C, so the compiler needs to know to use C function names.
#include "../../lualib/lua.h"
#include "../../lualib/lauxlib.h"
#include "../../lualib/lualib.h"
};
class GossipMenu;
class LuaEngine;
class LuaEngineMgr;
#ifdef ENABLE_LUA_HOOKS
class pHookInterface;
#endif ENABLE_LUA_HOOKS

extern LuaEngineMgr g_luaMgr;
extern LuaEngine g_engine;

GossipMenu * Menu;

bool lua_is_starting_up = false;
bool questexist;
ScriptMgr * m_scriptMgr;

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_SCRIPT_ENGINE | SCRIPT_TYPE_SCRIPT_ENGINE_LUA;
}


template<typename T> const char * GetTClassName() { return "UNKNOWN"; }

template<>
const char * GetTClassName<Unit>()
{
	return "Unit";
}

template<>
const char * GetTClassName<Item>()
{
	return "Item";
}

template<>
const char * GetTClassName<GameObject>()
{
	return "GameObject";
}


template<typename T>
struct RegType
{
	const char * name;
//	int(*mfunc)(lua_State*,shared_ptr<T>);
	int(*mfunc)(lua_State*, T*);
};

template <typename T> class Lunar {
	typedef struct { T *pT; } userdataType;
public:
	typedef int (*mfp)(lua_State *L, T* ptr);
	typedef struct { const char *name; mfp mfunc; } RegType;

	static void Register(lua_State *L) {
		lua_newtable(L);
		int methods = lua_gettop(L);

		luaL_newmetatable(L, GetTClassName<T>());
		int metatable = lua_gettop(L);

		// store method table in globals so that
		// scripts can add functions written in Lua.
		lua_pushvalue(L, methods);
		set(L, LUA_GLOBALSINDEX, GetTClassName<T>());

		// hide metatable from Lua getmetatable()
		lua_pushvalue(L, methods);
		set(L, metatable, "__metatable");

		lua_pushvalue(L, methods);
		set(L, metatable, "__index");

		lua_pushcfunction(L, tostring_T);
		set(L, metatable, "__tostring");

		lua_pushcfunction(L, gc_T);
		set(L, metatable, "__gc");

		lua_newtable(L);                // mt for method table
		lua_pushcfunction(L, new_T);
		lua_pushvalue(L, -1);           // dup new_T function
		set(L, methods, "new");         // add new_T to method table
		set(L, -3, "__call");           // mt.__call = new_T
		lua_setmetatable(L, methods);

		// fill method table with methods from class T
		for (RegType *l = ((RegType*)GetMethodTable<T>()); l->name; l++) {
			lua_pushstring(L, l->name);
			lua_pushlightuserdata(L, (void*)l);
			lua_pushcclosure(L, thunk, 1);
			lua_settable(L, methods);
		}

		lua_pop(L, 2);  // drop metatable and method table
	}

	// call named lua method from userdata method table
	static int call(lua_State *L, const char *method,
		int nargs=0, int nresults=LUA_MULTRET, int errfunc=0)
	{
		int base = lua_gettop(L) - nargs;  // userdata index
		if (!luaL_checkudata(L, base, T::className)) {
			lua_settop(L, base-1);           // drop userdata and args
			lua_pushfstring(L, "not a valid %s userdata", T::className);
			return -1;
		}

		lua_pushstring(L, method);         // method name
		lua_gettable(L, base);             // get method from userdata
		if (lua_isnil(L, -1)) {            // no method?
			lua_settop(L, base-1);           // drop userdata and args
			lua_pushfstring(L, "%s missing method '%s'", T::className, method);
			return -1;
		}
		lua_insert(L, base);               // put method under userdata, args

		int status = lua_pcall(L, 1+nargs, nresults, errfunc);  // call method
		if (status) {
			const char *msg = lua_tostring(L, -1);
			if (msg == NULL) msg = "(error with no message)";
			lua_pushfstring(L, "%s:%s status = %d\n%s",
				T::className, method, status, msg);
			lua_remove(L, base);             // remove old message
			return -1;
		}
		return lua_gettop(L) - base + 1;   // number of results
	}

	// push onto the Lua stack a userdata containing a pointer to T object
	static int push(lua_State *L, T *obj, bool gc=false) {
		if (!obj) { lua_pushnil(L); return 0; }
		luaL_getmetatable(L, GetTClassName<T>());  // lookup metatable in Lua registry
		if (lua_isnil(L, -1)) luaL_error(L, "%s missing metatable", GetTClassName<T>());
		int mt = lua_gettop(L);
		subtable(L, mt, "userdata", "v");
		userdataType *ud =
			static_cast<userdataType*>(pushuserdata(L, obj, sizeof(userdataType)));
		if (ud) {
			ud->pT = obj;  // store pointer to object in userdata
			lua_pushvalue(L, mt);
			lua_setmetatable(L, -2);
			if (gc == false) {
				lua_checkstack(L, 3);
				subtable(L, mt, "do not trash", "k");
				lua_pushvalue(L, -2);
				lua_pushboolean(L, 1);
				lua_settable(L, -3);
				lua_pop(L, 1);
			}
		}
		lua_replace(L, mt);
		lua_settop(L, mt);
		return mt;  // index of userdata containing pointer to T object
	}

	// get userdata from Lua stack and return pointer to T object
	static T *check(lua_State *L, int narg) {
		userdataType *ud =
			static_cast<userdataType*>(luaL_checkudata(L, narg, GetTClassName<T>()));
		if(!ud) { luaL_typerror(L, narg, GetTClassName<T>()); return NULL; }
		return ud->pT;  // pointer to T object
	}

private:
	Lunar();  // hide default constructor

	// member function dispatcher
	static int thunk(lua_State *L) {
		// stack has userdata, followed by method args
		T *obj = check(L, 1);  // get 'self', or if you prefer, 'this'
		lua_remove(L, 1);  // remove self so member function args start at index 1
		// get member function from upvalue
		RegType *l = static_cast<RegType*>(lua_touserdata(L, lua_upvalueindex(1)));
		//return (obj->*(l->mfunc))(L);  // call member function
		return l->mfunc(L,obj);
	}

	// create a new T object and
	// push onto the Lua stack a userdata containing a pointer to T object
	static int new_T(lua_State *L) {
		lua_remove(L, 1);   // use classname:new(), instead of classname.new()
		T *obj = NULL/*new T(L)*/;  // call constructor for T objects
		assert(false);
		push(L, obj, true); // gc_T will delete this object
		return 1;           // userdata containing pointer to T object
	}

	// garbage collection metamethod
	static int gc_T(lua_State *L) {
		if (luaL_getmetafield(L, 1, "do not trash")) {
			lua_pushvalue(L, 1);  // dup userdata
			lua_gettable(L, -2);
			if (!lua_isnil(L, -1)) return 0;  // do not delete object
		}
		userdataType *ud = static_cast<userdataType*>(lua_touserdata(L, 1));
		T *obj = ud->pT;
		if (obj) delete obj;  // call destructor for T objects
		return 0;
	}

	static int tostring_T (lua_State *L) {
		char buff[32];
		userdataType *ud = static_cast<userdataType*>(lua_touserdata(L, 1));
		T *obj = ud->pT;
		sprintf(buff, "%p", obj);
		lua_pushfstring(L, "%s (%s)", GetTClassName<T>(), buff);
		return 1;
	}

	static void set(lua_State *L, int table_index, const char *key) {
		lua_pushstring(L, key);
		lua_insert(L, -2);  // swap value and key
		lua_settable(L, table_index);
	}

	static void weaktable(lua_State *L, const char *mode) {
		lua_newtable(L);
		lua_pushvalue(L, -1);  // table is its own metatable
		lua_setmetatable(L, -2);
		lua_pushliteral(L, "__mode");
		lua_pushstring(L, mode);
		lua_settable(L, -3);   // metatable.__mode = mode
	}

	static void subtable(lua_State *L, int tindex, const char *name, const char *mode) {
		lua_pushstring(L, name);
		lua_gettable(L, tindex);
		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);
			lua_checkstack(L, 3);
			weaktable(L, mode);
			lua_pushstring(L, name);
			lua_pushvalue(L, -2);
			lua_settable(L, tindex);
		}
	}

	static void *pushuserdata(lua_State *L, void *key, size_t sz) {
		void *ud = 0;
		lua_pushlightuserdata(L, key);
		lua_gettable(L, -2);     // lookup[key]
		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);         // drop nil
			lua_checkstack(L, 3);
			ud = lua_newuserdata(L, sz);  // create new userdata
			lua_pushlightuserdata(L, key);
			lua_pushvalue(L, -2);  // dup userdata
			lua_settable(L, -4);   // lookup[key] = userdata
		}
		return ud;
	}
};

/** Macros for calling lua-based events
 */
#define LUA_ON_UNIT_EVENT(unit,eventtype,miscunit,misc) if(unit->GetTypeId()==TYPEID_UNIT && unit->IsInWorld()) { unit->GetMapMgr()->GetScriptEngine()->OnUnitEvent(unit,eventtype,miscunit,misc); }
#define LUA_ON_QUEST_EVENT(plr,quest,eventtype,miscobject) if(plr->IsPlayer() && plr->IsInWorld() && miscobject->IsInWorld() && !miscobject->IsPlayer()) { plr->GetMapMgr()->GetScriptEngine()->OnQuestEvent(plr,quest,eventtype,miscobject); } 
#define LUA_ON_GO_EVENT(unit,evtype,miscunit) if(unit->GetTypeId()==TYPEID_GAMEOBJECT && unit->IsInWorld()) { unit->GetMapMgr()->GetScriptEngine()->OnGameObjectEvent(unit,evtype,miscunit); }
#define LUA_ON_GOSSIP_EVENT(object, evtype, player, id, intid, code) if(object->IsInWorld()) { object->GetMapMgr()->GetScriptEngine()->OnGossipEvent(object, evtype, player, id, intid, code); }
#define LUA_CALL_FUNC(unit,funcname) if(unit->GetTypeId()==TYPEID_UNIT && unit->IsInWorld()) { unit->GetMapMgr()->GetScriptEngine()->CallFunction(unit,funcname); }

/** Quest Events
 */
enum QuestEvents
{
	QUEST_EVENT_ON_ACCEPT = 1,
	QUEST_EVENT_ON_COMPLETE = 2,
	QUEST_EVENT_ON_CANCEL = 3,
	QUEST_EVENT_GAMEOBJECT_ACTIVATE = 4,
	QUEST_EVENT_ON_CREATURE_KILL  = 5,
	QUEST_EVENT_ON_EXPLORE_AREA = 6,
	QUEST_EVENT_ON_PLAYER_ITEMPICKUP = 7,
	QUEST_EVENT_COUNT,
};

/** Creature Events
 */
enum CreatureEvents
{
	CREATURE_EVENT_ON_ENTER_COMBAT		= 1,
	CREATURE_EVENT_ON_LEAVE_COMBAT		= 2,
	CREATURE_EVENT_ON_TARGET_DIED		= 3,
	CREATURE_EVENT_ON_DIED		= 4,
	CREATURE_EVENT_ON_TARGET_PARRIED		= 5,
	CREATURE_EVENT_ON_TARGET_DODGED		= 6,
	CREATURE_EVENT_ON_TARGET_BLOCKED		= 7,
	CREATURE_EVENT_ON_TARGET_CRIT_HIT		= 8,
	CREATURE_EVENT_ON_PARRY		= 9,
	CREATURE_EVENT_ON_DODGED		= 10,
	CREATURE_EVENT_ON_BLOCKED		= 11,
	CREATURE_EVENT_ON_CRIT_HIT		= 12,
	CREATURE_EVENT_ON_HIT		= 13,
	CREATURE_EVENT_ON_ASSIST_TARGET_DIED		= 14,
	CREATURE_EVENT_ON_FEAR		= 15,
	CREATURE_EVENT_ON_FLEE		= 16,
	CREATURE_EVENT_ON_CALL_FOR_HELP		= 17,
	CREATURE_EVENT_ON_LOAD		= 18,
	CREATURE_EVENT_ON_REACH_WP		= 19,
	CREATURE_EVENT_ON_LOOT_TAKEN		= 20,
	CREATURE_EVENT_ON_AIUPDATE		= 21,
	CREATURE_EVENT_ON_EMOTE		= 22,
	CREATURE_EVENT_USER_DEFINED = 23,
	CREATURE_EVENT_ON_DAMAGE_TAKEN = 24,
	CREATURE_EVENT_ON_CREATEAISCRIPT = 25,
	CREATURE_EVENT_COUNT,
};

/** GameObject Events
 */
enum GameObjectEvents
{
	GAMEOBJECT_EVENT_ON_CREATE			= 1,
	GAMEOBJECT_EVENT_ON_SPAWN			= 2,
	GAMEOBJECT_EVENT_ON_LOOT_TAKEN		= 3,
	GAMEOBJECT_EVENT_ON_USE				= 4,
	GAMEOBJECT_EVENT_AIUPDATE			= 5,
	GAMEOBJECT_EVENT_ON_DESPAWN			= 6,
	GAMEOBJECT_EVENT_USER_DEFINED = 7,
	GAMEOBJECT_EVENT_COUNT,
};

/** Gossip Events
*/
enum GossipEvents
{
	GOSSIP_EVENT_ON_TALK			= 1,
	GOSSIP_EVENT_ON_SELECT_OPTION	= 2,
	GOSSIP_EVENT_ON_END             = 3,
	GOSSIP_EVENT_COUNT,
};

enum RandomFlags
{
	RANDOM_ANY           = 0,
	RANDOM_IN_SHORTRANGE = 1,
	RANDOM_IN_MIDRANGE   = 2,
	RANDOM_IN_LONGRANGE  = 3,
	RANDOM_WITH_MANA     = 4,
	RANDOM_WITH_RAGE     = 5,
	RANDOM_WITH_ENERGY   = 6,
	RANDOM_NOT_MAINTANK  = 7
};
class LuaEngine
{
private:
	lua_State * L;
	Mutex m_Lock;

public:
	LuaEngine();
	~LuaEngine();

	void LoadScripts();
	void Shutdown();
	void Restart();
	void RegisterCoreFunctions();
	ARCEMU_INLINE Mutex& GetLock() { return m_Lock; }

	void OnUnitEvent(Unit * pUnit, const char * FunctionName, uint32 EventType, Unit * pMiscUnit, uint32 Misc, int32 Misc2, float Misc3, bool Yes, ItemPrototype * Misc4);
	void OnUnitEvent(Unit * pUnit, const char * FunctionName, uint32 EventType, Unit * pMiscUnit, uint32 Misc) { OnUnitEvent(pUnit,FunctionName,EventType,pMiscUnit,Misc,0,0,false,NULL); }
	void OnUnitEvent(Unit * pUnit, const char * FunctionName ,uint32 EventType, Unit * pMiscUnit, int32 Misc2){ OnUnitEvent(pUnit,FunctionName,EventType,pMiscUnit,0,Misc2,0,false,NULL); }
	void OnUnitEvent(Unit * pUnit, const char * FunctionName, uint32 EventType, Unit * pMiscUnit, float Misc3) { OnUnitEvent(pUnit,FunctionName,EventType,pMiscUnit,0,0,Misc3,false,NULL); }
	void OnUnitEvent(Unit * pUnit, const char * FunctionName, uint32 EventType, Unit * pMiscUnit, uint32 Misc, bool Yes) { OnUnitEvent(pUnit,FunctionName,EventType,pMiscUnit,Misc,0,0,Yes,NULL); }
	void OnUnitEvent(Unit * pUnit, const char * FunctionName, uint32 EventType, Unit * pMiscUnit, ItemPrototype * Proto){ OnUnitEvent(pUnit,FunctionName, EventType,pMiscUnit,0,0,0,false,Proto); }
	void OnQuestEvent(Player * QuestOwner, const char * FunctionName, uint32 QuestID, uint32 EventType, Player * QuestStarter,uint32 Misc, uint32 Misc2);
	void OnGameObjectEvent(GameObject * pGameObject, const char * FunctionName, uint32 EventType, Unit * pMiscUnit, uint32 Misc, ItemPrototype* Misc2);
    void OnGossipEvent(Object * pObject, const char * FunctionName, uint32 EventType, Player * mPlayer, uint32 Id, uint32 IntId, const char * Code);
	void CallFunction(Unit * pUnit, const char * FuncName);
#ifdef ENABLE_LUA_HOOKS
	void OnServerHook(Player *, uint32,Object *, const char *, uint32, uint32);
	void OnServerHook(Player *, uint32, Object *, const char *, Quest *, Guild *, SpellEntry *);
	void OnServerHook(Player *, uint32, Object *, const char *, uint32, uint32, const char *, const char*);
	void OnServerHook(Player *, uint32, Object *, const char *, ArenaTeam *, bool, bool);
#endif
};

typedef list<const char * > LuaUnitBinding;
struct LuaQuestBinding { const char * Functions[QUEST_EVENT_COUNT]; };
struct LuaGameObjectBinding { const char * Functions[GAMEOBJECT_EVENT_COUNT]; };
struct LuaUnitGossipBinding { const char * Functions[GOSSIP_EVENT_COUNT]; };
struct LuaItemGossipBinding { const char * Functions[GOSSIP_EVENT_COUNT]; };
struct LuaGOGossipBinding { const char * Functions[GOSSIP_EVENT_COUNT]; };

#ifdef ENABLE_LUA_HOOKS
typedef list<const char*> LuaSHBinding;
typedef unordered_map<const char*, bool> pHoldBoolsByChar;
typedef unordered_map<uint32,pHoldBoolsByChar> CompleteMap;
#endif

class LuaEngineMgr
{
private:
	typedef unordered_map<uint32, LuaUnitBinding*> UnitBindingMap;
	typedef unordered_map<uint32, LuaQuestBinding> QuestBindingMap;
	typedef unordered_map<uint32, LuaGameObjectBinding> GameObjectBindingMap;
	typedef unordered_map<uint32, LuaUnitGossipBinding> GossipUnitScriptsBindingMap;
	typedef unordered_map<uint32, LuaItemGossipBinding> GossipItemScriptsBindingMap;
	typedef unordered_map<uint32, LuaGOGossipBinding> GossipGOScriptsBindingMap;
	UnitBindingMap m_unitBinding;
	QuestBindingMap m_questBinding;
	GameObjectBindingMap m_gameobjectBinding;
	GossipUnitScriptsBindingMap m_unit_gossipBinding;
	GossipItemScriptsBindingMap m_item_gossipBinding;
	GossipGOScriptsBindingMap m_go_gossipBinding;
#ifdef ENABLE_LUA_HOOKS
	LuaSHBinding * m_shBinding;
#endif

public:
#ifdef ENABLE_LUA_HOOKS
	pHookInterface * m_HookInterface;
#endif
	LuaEngine m_engine;
	LuaEngineMgr();
	void Startup();
	void ReloadClasses();
	void Unload();
	// Unit Event Functions //
	void RegisterUnitEvent(uint32 Id, uint32 Event, const char * FunctionName);
	void ModifyUnitEvent(uint32 id, uint32 evt, const char * oldfunc, const char * newfunc);
	void RemoveUnitEvent(uint32 id, uint32 evt, const char * FunctionName);
	// Quest Event Functions //
	void RegisterQuestEvent(uint32 Id, uint32 Event, const char * FunctionName);
	// GO Event Functions //
	void RegisterGameObjectEvent(uint32 Id, uint32 Event, const char * FunctionName);
	// Unit Gossip Functions //
    void RegisterUnitGossipEvent(uint32 Id, uint32 Event, const char * FunctionName);
	// Item Gossip Functions //
    void RegisterItemGossipEvent(uint32 Id, uint32 Event, const char * FunctionName);
	// GO Gossip Functions //
    void RegisterGOGossipEvent(uint32 Id, uint32 Event, const char * FunctionName);

	QueryResult * WorldQuery(const char *);
#ifdef ENABLE_LUA_HOOKS
	// ServerHook evts //
	void RegisterServerHookEvent(uint32,const char *);
	void RemoveServerHookEvent(uint32 id, const char * funcName);
	void ModifyServerHookEvent(uint32 evt, const char * func1, const char * func2);
	bool CheckBoolResult(uint32,const char*);
#endif


	LuaUnitBinding * GetUnitBinding(uint32 Id)
	{
		UnitBindingMap::iterator itr = m_unitBinding.find(Id);
		return (itr == m_unitBinding.end()) ? NULL : itr->second;
	}

	LuaQuestBinding * GetQuestBinding(uint32 Id)
	{
		QuestBindingMap::iterator itr = m_questBinding.find(Id);
		return (itr == m_questBinding.end()) ? NULL : &itr->second;
	}

	LuaGameObjectBinding * GetGameObjectBinding(uint32 Id)
	{
		GameObjectBindingMap::iterator itr =m_gameobjectBinding.find(Id);
		return (itr == m_gameobjectBinding.end()) ? NULL : &itr->second;
	}
    // Gossip Stuff
    LuaUnitGossipBinding * GetLuaUnitGossipBinding(uint32 Id)
	{
		GossipUnitScriptsBindingMap::iterator itr = m_unit_gossipBinding.find(Id);
		return (itr == m_unit_gossipBinding.end()) ? NULL : &itr->second;
	}

    LuaItemGossipBinding * GetLuaItemGossipBinding(uint32 Id)
	{
		GossipItemScriptsBindingMap::iterator itr = m_item_gossipBinding.find(Id);
		return (itr == m_item_gossipBinding.end()) ? NULL : &itr->second;
	}

    LuaGOGossipBinding * GetLuaGOGossipBinding(uint32 Id)
	{
		GossipGOScriptsBindingMap::iterator itr = m_go_gossipBinding.find(Id);
		return (itr == m_go_gossipBinding.end()) ? NULL : &itr->second;
	}
#ifdef ENABLE_LUA_HOOKS
	LuaSHBinding *GetLuaHookBinding() { return m_shBinding; }
#endif
};

//#include "LUAEngine.cpp"

/************************************************************************/
/* SCRIPT FUNCTION IMPLEMENTATION                                       */
/************************************************************************/
#define CHECK_TYPEID(expected_type) if(!ptr || !ptr->IsInWorld() || ptr->GetTypeId() != expected_type) { return 0; }
#define CHECK_TYPEID_RET(expected_type) if(!ptr || !ptr->IsInWorld() || ptr->GetTypeId() != expected_type) { lua_pushboolean(L,0); return 0; }
#define CHECK_TYPEID_RET_INT(expected_type) if(!ptr || !ptr->IsInWorld() || ptr->GetTypeId() != expected_type) { lua_pushinteger(L,0); return 0; }
#define CHECK_PTR() if( ptr == NULL ||!ptr->IsInWorld() ) { return 0; }
//#include "..\object_functions\GameObjectFunctions.cpp"
//#include "..\object_functions\UnitFunctions.cpp"
//#include "..\object_functions\ItemFunctions.cpp"

#endif







