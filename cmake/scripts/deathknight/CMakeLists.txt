if(NOT BUILD_DEATHKNIGHT )
  message("\tDeathKnight was skipped because BUILD_DEATHKNIGHT is unchecked.")
  return()
endif(NOT BUILD_DEATHKNIGHT)

PROJECT(DeathKnight)

SET( prefix ${SCRIPTS_PATH}/${PROJECT_NAME} )

SET( sources
Setup.cpp 
../Common/Base.cpp 
Quest_DeathKnight.cpp )

SET( headers
Setup.h
../Common/Base.h
../Common/EasyFunctions.h )

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
