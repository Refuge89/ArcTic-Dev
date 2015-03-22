PROJECT(world)
SET( prefix ${ROOT_PATH}/src/world )
SET(sources
#  DBC/dbcfile.cpp
#  DBC/DBCStores.cpp
    Main.cpp 
    Master.cpp 
#    CConsole.cpp 
    ConsoleCommands.cpp 
    ConsoleListener.cpp
    AchievementInterface.cpp 
    AddonMgr.cpp 
    AIInterface.cpp 
#    AIEvents.cpp
    AlteracValley.cpp 
    ArathiBasin.cpp 
    AreaTrigger.cpp 
    Arenas.cpp 
    ArenaTeam.cpp 
    AuctionHouse.cpp 
    AuctionMgr.cpp 
    BattlegroundCommands.cpp 
    BattlegroundHandler.cpp 
    BattlegroundMgr.cpp 
    ChainAggroEntity.cpp 
    Channel.cpp 
    ChannelHandler.cpp 
    CharacterHandler.cpp 
    Chat.cpp 
    ChatHandler.cpp 
    ClusterInterface.cpp 
    CollideInterface.cpp 
    CombatHandler.cpp 
    Container.cpp 
    Corpse.cpp 
    Creature.cpp 
    CalendarHandler.cpp 
    Entities/Summons/Summon.cpp
    Entities/Summons/CompanionSummon.cpp
    Entities/Summons/GuardianSummon.cpp
    Entities/Summons/PossessedSummon.cpp
    Entities/Summons/TotemSummon.cpp
    Entities/Summons/WildSummon.cpp
    DayWatcherThread.cpp 
    debugcmds.cpp 
    DuelHandler.cpp 
    DynamicObject.cpp 
    EventableObject.cpp 
    EventMgr.cpp 
    EyeOfTheStorm.cpp 
    faction.cpp 
    GameObject.cpp 
    GMTicket.cpp 
 #   GMTicketCommands.cpp 
 #   Gossip.cpp
    Group.cpp 
    GroupHandler.cpp 
    Guild.cpp 
    GuildHandler.cpp 
    HonorHandler.cpp 
 #   INGEvents.cpp 
    Item.cpp 
    ItemHandler.cpp 
    ItemInterface.cpp 
    Level0.cpp 
    Level1.cpp 
    Level2.cpp 
    Level3.cpp 
    LfgHandler.cpp 
    LfgMgr.cpp 
  #  LocalizationMgr.cpp 
    LogonCommClient.cpp 
    LogonCommHandler.cpp 
    LootMgr.cpp 
    MailSystem.cpp 
    Map.cpp 
    MapCell.cpp 
    MapMgr.cpp 
    MapScriptInterface.cpp 
    MiscHandler.cpp 
    MovementHandler.cpp 
    NPCHandler.cpp 
    Object.cpp 
    ObjectMgr.cpp 
    ObjectStorage.cpp 
    Opcodes.cpp 
    Pet.cpp 
    PetHandler.cpp 
    Player.cpp 
    PlayerPacketWrapper.cpp 
    QueryHandler.cpp 
    Quest.cpp 
    QuestCommands.cpp 
    QuestHandler.cpp 
    QuestMgr.cpp 
    RaidHandler.cpp 
    RecallCommands.cpp 
    ReputationHandler.cpp 
    ScriptMgr.cpp 
 #   ServerPlayedCharacters.cpp 
    SkillHandler.cpp 
    SocialHandler.cpp 
    Spell.cpp 
    SpellAuras.cpp 
    SpellEffects.cpp 
    SpellFixes.cpp 
    SpellHandler.cpp 
    SpellTarget.cpp 
    Stats.cpp 
    StdAfx.cpp 
    SummonHandler.cpp
    StrandOfTheAncients.cpp 
    TaxiHandler.cpp 
    TaxiMgr.cpp 
    TerrainMgr.cpp 
 #   TheBattleForTroia.cpp 
    IsleOfConquest.cpp 
    TradeHandler.cpp 
    TransporterHandler.cpp 
    Unit.cpp 
    VehicleHandler.cpp 
    Vehicle.cpp 
#    VoiceChatClientSocket.cpp 
    VoiceChatHandler.cpp 
#    WarnSystem.cpp 
#    WarnSystem_Punishments.cpp 
    WarsongGulch.cpp 
    WayPoints.cpp 
    WeatherMgr.cpp 
    Wintergrasp.cpp 
    WintergraspInternal.cpp
    WordFilter.cpp 
    WorldSocketCluster.cpp 
    WorkerServerClient.cpp 
    World.cpp 
    World.rc 
    WorldCreator.cpp 
    WorldRunnable.cpp 
    WorldSession.cpp 
    WorldSocket.cpp 
    WorldStateManager.cpp )

SET( headers
#DBC/dbcfile.h
#DBC/DBCStores.h
Master.h
BaseConsole.h
#CConsole.h
ConsoleCommands.h
AchievementInterface.h 
AddonMgr.h 
AIInterface.h 
#AIEvents.h
AlteracValley.h 
ArathiBasin.h 
AreaTrigger.h 
Arenas.h 
ArenaTeam.h 
AuctionHouse.h 
AuctionMgr.h 
BattlegroundMgr.h 
CellHandler.h 
ChainAggroEntity.h 
Channel.h 
ChannelMgr.h 
Chat.h 
ClassSpells.h 
ClusterInterface.h 
CollideInterface.h 
Entities/Summons/CompanionSummon.h
Const.h 
Container.h 
Corpse.h 
Creature.h 
DayWatcherThread.h 
DynamicObject.h 
EventableObject.h 
EventMgr.h 
EyeOfTheStorm.h 
faction.h 
GameObject.h
#Gossip.h 
Group.h 
Entities/Summons/GuardianSummon.h
Guild.h 
HonorHandler.h 
Item.h 
ItemInterface.h 
ItemPrototype.h 
LfgMgr.h 
#LocalizationMgr.h 
LogonCommClient.h 
LogonCommHandler.h 
LootMgr.h 
MailSystem.h 
MainServerDefines.h 
Map.h 
MapCell.h 
MapMgr.h 
MapScriptInterface.h 
MiscHandler.h 
NameTables.h 
NPCHandler.h 
Object.h 
ObjectMgr.h 
ObjectStorage.h 
Opcodes.h 
Packets.h 
Pet.h 
Player.h 
Entities/Summons/PossessedSummon.h
Quest.h 
QuestMgr.h 
ScriptMgr.h 
ScriptSetup.h 
#ServerPlayedCharacters.h 
SkillNameMgr.h 
Spell.h 
SpellAuras.h 
#SpellFailure.h 
SpellNameHashes.h 
Stats.h 
StdAfx.h 
Entities/Summons/Summon.h
StrandOfTheAncients.h 
TaxiMgr.h 
TerrainMgr.h 
Entities/Summons/TotemSummon.h
#TheBattleForTroia.h 
IsleOfConquest.h 
TransporterHandler.h 
Unit.h 
UpdateFields.h 
UpdateMask.h 
Vehicle.h 
#VoiceChatClientSocket.h 
#VoiceChatHandler.h 
#WarnSystem.h 
WarsongGulch.h 
WeatherMgr.h 
Wintergrasp.h 
WintergraspInternal.h
WordFilter.h 
WorkerServerClient.h 
Entities/Summons/WildSummon.h
World.h 
WorldCreator.h 
WorldRunnable.h 
WorldSession.h 
WorldSocket.h 
WorldStateManager.h 
WorldStates.h 
)
	

foreach(src IN ITEMS ${sources} )
  SET( SRCS ${SRCS} ${prefix}/${src} )
endforeach(src)
foreach(src IN ITEMS ${headers} )
  SET( HEADERS ${HEADERS} ${prefix}/${src} )
endforeach(src)

include(PCHSupport)
include_directories( ${GLOBAL_INCLUDE_DIRS} )
link_directories( ${DEPENDENCY_LIBS} ${EXTRA_LIBS_PATH} )

add_executable( ${PROJECT_NAME} ${SRCS} ${HEADERS} )

IF( CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} StdAfx.h ${prefix}/StdAfx.cpp)
ENDIF()
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS TRUE)

add_dependencies( ${PROJECT_NAME} shared )
target_link_libraries( ${PROJECT_NAME} shared ${PCRE_LIBRARIES} )
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)





