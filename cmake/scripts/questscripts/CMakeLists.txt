if(NOT BUILD_QUESTSCRIPTS )
  message("\tQuestScripts was skipped because BUILD_QUESTSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_QUESTSCRIPTS)

PROJECT(QuestScripts)

SET( prefix ${SCRIPTS_PATH}/${PROJECT_NAME} )

SET( sources
Setup.cpp 
../Common/Base.cpp 
ArathiHighlands.cpp 
Azshara.cpp 
Azuremyst_Isle.cpp 
BladeEdge_Mountains.cpp 
BlastedLands.cpp 
BloodmystIsle.cpp 
Darkshore.cpp 
#DeathKnight.cpp 
Desolace.cpp 
Dragonblight.cpp 
Druid.cpp 
Duskwood.cpp 
Dustwallow_Marsh.cpp 
Eastern_Plaguelands.cpp 
EversongWoods.cpp 
FirstAid.cpp 
Ghostlands.cpp 
Hellfire_Peninsula.cpp 
HillsbradFoothills.cpp 
Howling_Fjord.cpp 
Isle_of_QuelDanas.cpp 
LochModan.cpp 
Mage.cpp 
Mulgore.cpp 
Nagrand.cpp 
Netherstorm.cpp 
Old_Hillsbrad.cpp 
Paladin.cpp 
QuestGossip.cpp 
QuestHooks.cpp 
RedridgeMountains.cpp 
ShadowMoon.cpp 
SholazarBasin.cpp 
SilvermoonCity.cpp 
Silverpine_Forest.cpp 
Stormwind.cpp 
StranglethornVale.cpp 
Tanaris.cpp 
Teldrassil.cpp 
Terrokar_Forest.cpp 
The_Barrens.cpp 
ThousandNeedles.cpp 
TirisfalGlades.cpp 
Undercity.cpp 
UnGoro.cpp 
Unsorted.cpp 
Warrior.cpp 
Westfall.cpp 
Zangarmarsh.cpp )

SET( headers
Setup.h
../Common/Base.h
../Common/EasyFunctions.h
../Common/Instance_Base.h )

foreach(src IN ITEMS ${sources} )
  SET( SRCS ${SRCS} ${prefix}/${src} )
endforeach(src)
foreach(src IN ITEMS ${headers} )
  SET( HEADERS ${HEADERS} ${prefix}/${src} )
endforeach(src)

include_directories( ${include_dirs} ${prefix} )
add_library( ${PROJECT_NAME} SHARED ${SRCS} )
add_dependencies( ${PROJECT_NAME} ${dependancies} )
target_link_libraries( ${PROJECT_NAME} ${linkages} )

include(PCHSupport)
IF( CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${prefix}/Setup.cpp)
ENDIF()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${SCRIPTLIB_PATH} LIBRARY DESTINATION ${SCRIPTLIB_PATH})
#Cleap up our variables(Not required.)
unset( prefix)
unset( SRCS )
unset( sources )
