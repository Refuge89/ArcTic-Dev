/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2012 Arctic Server Team
 * See COPYING for license details.
 */

#pragma once

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

//#define DEG2RAD (M_PI/180.0)
#ifdef M_PI
#undef M_PI
#endif

#define M_PI		3.14159265358979323846f
#define M_H_PI		1.57079632679489661923f
#define M_Q_PI		0.785398163397448309615f
#define M_PI_FLOAT 3.14159f

#define _GAME

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <fstream>

#ifdef WIN32
#include <array>
#else
#include <tr1/array>
#endif

#include "../shared/AuthCodes.h"
#include "../shared/Common.h"
#include "../shared/MersenneTwister.h"
#include "../shared/WorldPacket.h"
#include "../shared/Log.h"
#include "../shared/NGLog.h"
#include "../shared/ByteBuffer.h"
#include "../shared/StackBuffer.h"
#include "../shared/Config/ConfigEnv.h"
#include "../shared/crc32.h"
#include "../shared/LocationVector.h"
#include "../shared/hashmap.h"

#include "../shared/Collision/vmap/IVMapManager.h"
#include "../shared/Collision/vmap/VMapManager.h"

#include <zlib.h>

#include <DataBase/DatabaseEnv.h>
#include <DataBase/DBCStores.h>
#include <DataBase/dbcfile.h>

#include <Network/Network.h>

#include "../shared/Auth/MD5.h"
#include "../shared/Auth/BigNumber.h"
#include "../shared/Auth/Sha1.h"
#include "../shared/Auth/WowCrypt.h"
#include "../shared/CrashHandler.h"
#include "../shared/FastQueue.h"
#include "../shared/CircularQueue.h"
#include "../shared/Threading/RWLock.h"
#include "../shared/Threading/Condition.h"
#include "../shared/Getopt.h"
#include "../shared/BufferPool.h"

#include "Const.h"
#include "NameTables.h"
#include "UpdateFields.h"
#include "UpdateMask.h"
#include "Opcodes.h"
#include "WorldStates.h"

#ifdef CLUSTERING
	#include "../ClusterServer/WorkerOpcodes.h"
#endif

#include "Packets.h"

#include "../shared/CallBack.h"
#include "WordFilter.h"
#include "EventMgr.h"
#include "EventableObject.h"
#include "Object.h"
#include "LootMgr.h"
#include "SummonHandler.h"
#include "Unit.h"

#include "../shared/Utilities/Arctic.h"

#include "AddonMgr.h"
#include "AIInterface.h"
#include "AreaTrigger.h"
#include "BattlegroundMgr.h"
#include "AlteracValley.h"
#include "ArathiBasin.h"
#include "EyeOfTheStorm.h"
#include "Arenas.h"
#include "CellHandler.h"
#include "Chat.h"
#include "Corpse.h"
#include "Quest.h"
#include "QuestMgr.h"
#include "Creature.h"
#include "Entities/Summons/Summon.h"
#include "Entities/Summons/CompanionSummon.h"
#include "Entities/Summons/GuardianSummon.h"
#include "Entities/Summons/PossessedSummon.h"
#include "Entities/Summons/TotemSummon.h"
#include "Entities/Summons/WildSummon.h"
#include "DynamicObject.h"
#include "GameObject.h"
#include "Group.h"
#include "Guild.h"
#include "HonorHandler.h"
#include "ItemPrototype.h"
#include "Item.h"
#include "Container.h"
#include "AuctionHouse.h"
#include "AuctionMgr.h"
#include "LfgMgr.h"
#include "MailSystem.h"
#include "Map.h"
#include "MapCell.h"
#include "TerrainMgr.h"
#include "MiscHandler.h"
#include "NPCHandler.h"
#include "Pet.h"
#include "WorldSocket.h"
#include "World.h"
#include "WorldSession.h"
#include "WorldStateManager.h"
#include "MapMgr.h"
#include "MapScriptInterface.h"
#include "WintergraspInternal.h"
#include "Wintergrasp.h"
#include "Player.h"
#include "faction.h"
#include "Skill.h"
#include "SkillNameMgr.h"
#include "SpellNameHashes.h"
#include "SpellDefines.h"
#include "Spell.h"
#include "MapMgr.h"
#include "SpellAuras.h"
#include "TaxiMgr.h"
#include "TransporterHandler.h"
#include "WarsongGulch.h"
#include "WeatherMgr.h"
#include "ItemInterface.h"
#include "Stats.h"
#include "ObjectMgr.h"
#include "GuildDefines.h"
#include "WorldCreator.h"
#include "ScriptMgr.h"
#include "Channel.h"
#include "ChannelMgr.h"
#include "ArenaTeam.h"
#include "LogonCommClient.h"
#include "LogonCommHandler.h"
#include "MainServerDefines.h"
#include "WorldRunnable.h"
#include "../shared/Storage.h"
#include "ObjectStorage.h"
#include "DayWatcherThread.h"
#include "Vehicle.h"
#include "AchievementInterface.h"
#include "AchievementDefines.h"
#include "ChainAggroEntity.h"
#include "StrandOfTheAncients.h"
#include "IsleOfConquest.h"
#include "Wintergrasp.h"

#ifdef CLUSTERING
	#include "WorkerServerClient.h"
	#include "ClusterInterface.h"
#endif

#include "CollideInterface.h"

#include "Master.h"
#include "BaseConsole.h"

