if(NOT BUILD_INSTANCESCRIPTS )
  message("\tInstanceScripts was skipped because BUILD_INSTANCESCRIPTS is unchecked.")
  return()
endif(NOT BUILD_INSTANCESCRIPTS)

PROJECT(InstanceScripts)

SET( prefix ${SCRIPTS_PATH}/InstanceScripts )

set(sources
Battleground_AlteracValley.cpp 
Instance_Arcatraz.cpp 
Instance_AuchenaiCrypts.cpp 
Instance_AzjolNerub.cpp 
Instance_BlackfathomDeeps.cpp 
Instance_BlackMorass.cpp 
Instance_BlackrockDepths.cpp 
Instance_BlackrockSpire.cpp 
Instance_BloodFurnace.cpp 
Instance_Botanica.cpp 
Instance_CullingOfStratholme.cpp 
Instance_Deadmines.cpp 
Instance_DireMaul.cpp 
Instance_DrakTharonKeep.cpp 
Instance_HallsOfLightning.cpp 
Instance_HallsOfStone.cpp 
Instance_HellfireRamparts.cpp 
Instance_MagistersTerrace.cpp 
Instance_ManaTombs.cpp 
Instance_Mauradon.cpp 
Instance_Nexus.cpp 
Instance_OldHillsbradFoothills.cpp 
Instance_RagefireChasm.cpp 
Instance_RazorfenDowns.cpp 
Instance_ScarletMonastery.cpp 
Instance_Scholomance.cpp 
Instance_SethekkHalls.cpp 
Instance_ShadowfangKeep.cpp 
Instance_ShadowLabyrinth.cpp 
Instance_TheMechanar.cpp 
Instance_TheShatteredHalls.cpp 
Instance_TheSlavePens.cpp 
Instance_TheSteamvault.cpp 
Instance_TheStockade.cpp 
Instance_TheUnderbog.cpp 
Instance_Uldaman.cpp 
Instance_UtgardeKeep.cpp 
Instance_WailingCaverns.cpp 
Instance_TheStockade.cpp 
Instance_ZulFarrak.cpp 
../Common/Instance_Base.cpp 
../Common/Base.cpp 
Setup.cpp )

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