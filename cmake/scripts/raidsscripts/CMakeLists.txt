if(NOT BUILD_RAIDSSCRIPTS )
  message("\tRaidsScripts was skipped because BUILD_RAIDSSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_RAIDSSCRIPTS)

PROJECT(RaidsScripts)

SET( prefix ${SCRIPTS_PATH}/RaidsScripts )

set(sources
Raid_BlackTemple.cpp 
BlackTemple/ShadeOfAkama.cpp 
Raid_BlackwingLair.cpp 
Raid_CoT_BattleOfMountHyjal.cpp 
Raid_GruulsLair.cpp 
Raid_Karazhan.cpp 
Raid_Magtheridons_Lair.cpp 
Raid_MoltenCore.cpp 
Raid_Naxxramas.cpp 
Raid_OnyxiasLair.cpp 
Raid_SerpentshrineCavern.cpp 
Raid_TheEye.cpp 
Raid_TheObsidianSanctum.cpp 
Raid_Ulduar.cpp 
Raid_ZulGurub.cpp 
SunwellPlateau/Raid_SunwellPlateau.cpp 
Raid_WorldBosses.cpp 
Raid_ZulAman.cpp 
Raid_ZulGurub.cpp 
../Common/Instance_Base.cpp 
../Common/Base.cpp 
Setup.cpp )

SET( headers
Raid_Naxxramas.h
Raid_Ulduar.h
Setup.h
../Common/Base.h
../Common/EasyFunctions.h
../Common/Instance_Base.h)

foreach(src IN ITEMS ${sources} )
  SET( SRCS ${SRCS} ${prefix}/${src} )
endforeach(src)
foreach(src IN ITEMS ${headers} )
  SET( HEADERS ${HEADERS} ${prefix}/${src} )
endforeach(src)


include_directories( ${include_dirs} ${prefix} )
add_library( ${PROJECT_NAME} SHARED ${SRCS} ${HEADERS} )
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