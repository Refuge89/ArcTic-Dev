PROJECT(shared)

SET( prefix ${ROOT_PATH}/src/shared )
SET( sources
    CThreads.cpp 
    CThreads.h 
    CrashHandler.h 
    CrashHandler.cpp 
    Log.cpp 
    MersenneTwister.cpp 
    MersenneTwister.h 
    PreallocatedQueue.h 
    BufferPool.cpp 
    BufferPool.h 
    ByteBuffer.h 
    Common.h 
    Config.h 
    Errors.h 
    Log.h 
    NGLog.h 
#    printStackTrace.cpp 
#    printStackTrace.h 
    Singleton.h 
    Utilities/Timer.h 
    #UnixThreading.h 
    Utilities/Utility.h 
    Utilities/Utility.cpp 
	Collision/vmap/AABSPTree.h
	Collision/vmap/BaseModel.cpp
	Collision/vmap/BaseModel.h
	Collision/vmap/CoordModelMapping.cpp
	Collision/vmap/CoordModelMapping.h
	Collision/vmap/IVMapManager.h
	Collision/vmap/ManagedModelContainer.cpp
	Collision/vmap/ManagedModelContainer.h
	Collision/vmap/ModelContainer.cpp
	Collision/vmap/ModelContainer.h
	Collision/vmap/NodeValueAccess.h
	Collision/vmap/RayIntersectionIterator.h
	Collision/vmap/ShortBox.h
	Collision/vmap/ShortVector.h
	Collision/vmap/SubModel.cpp
	Collision/vmap/SubModel.h
	Collision/vmap/TileAssembler.cpp
	Collision/vmap/TileAssembler.h
	Collision/vmap/TreeNode.cpp
	Collision/vmap/TreeNode.h
	Collision/vmap/VMapManager.cpp
	Collision/vmap/VMapManager.h
	Collision/g3dlite/AABox.cpp
	Collision/g3dlite/Box.cpp
	Collision/g3dlite/Crypto.cpp
	Collision/g3dlite/Matrix3.cpp
	Collision/g3dlite/Plane.cpp
	Collision/g3dlite/System.cpp
	Collision/g3dlite/Triangle.cpp
	Collision/g3dlite/Vector3.cpp
	Collision/g3dlite/Vector4.cpp
	Collision/g3dlite/format.cpp
	Collision/LocationVector.h
	Collision/Interface.cpp 
    Console/BaseConsole.h 
    Console/CConsole.cpp 
    Console/CConsole.h 
    Console/ConsoleListener.cpp 
   # WinThreading.h RealmPacket
    RealmPacket.h 
    WorldPacket.h 
    crc32.cpp 
    crc32.h 
    getopt.cpp 
    getopt.h 
    hashmap.cpp 
    hashmap.h 
    FastQueue.h 
    PacketLog.cpp 
    PacketLog.h 
    SmartPointer.h 
    svn_revision.h 
    Threading/Mutex.cpp
    Threading/Threading.h  
    Threading/ThreadPool.cpp 
    Storage.h 
    Utilities/Arctic.h 
    Utilities/Arctic.cpp 
    Auth/BigNumber.cpp 
    Auth/BigNumber.h 
    Auth/HMAC.cpp 
    Auth/HMAC.h 
    Auth/MD5.cpp 
    Auth/MD5.h 
    Auth/Sha1.cpp 
    Auth/Sha1.h 
    Auth/WowCrypt.cpp 
    Auth/WowCrypt.h 
    Config/Config.cpp 
    Config/Config.h 
    Config/ConfigEnv.h 
    Database/DBC.cpp 
    Database/Database.cpp 
    Database/DBC.h 
    Database/Database.h 
    Database/DBCStores.cpp 
    Database/DatabaseEnv.h 
    Database/DBCStores.h 
    Database/Field.h 
    Database/DataStore.h 
    Database/dbcfile.cpp 
    Database/dbcfile.h 
    Database/PostgresDatabase.cpp 
    Database/PostgresDatabase.h 
    Database/SQLiteDatabase.cpp 
    Database/SQLiteDatabase.h 
    Database/MySQLDatabase.cpp 
    Database/MySQLDatabase.h 
    Database/CreateInterface.cpp 
    Network/CircularBuffer.h 
    Network/CircularBuffer.cpp 
    Network/ListenSocketLinux.h 
    Network/ListenSocketFreeBSD.h 
    Network/ListenSocketPoll.h 
    Network/ListenSocketSelect.h 
    Network/Network.h 
    Network/Socket.cpp 
    Network/Socket.h 
    Network/SocketDefines.h 
    Network/SocketLinux.cpp 
    Network/SocketOpsPoll.cpp 
    Network/SocketOpsSelect.cpp 
    Network/SocketFreeBSD.cpp 
    Network/SocketMgrLinux.cpp 
    Network/SocketMgrLinux.h 
    Network/SocketMgrFreeBSD.cpp 
    Network/SocketMgrFreeBSD.h 
    Network/SocketOps.h 
    Network/SocketOpsLinux.cpp 
    Network/SocketPoll.cpp 
    Network/SocketSelect.cpp 
    Network/SocketOpsFreeBSD.cpp )



IF(WIN32)
	SET( sources ${sources} Network/SocketMgrWin32.cpp  Network/SocketOpsWin32.cpp  Network/SocketWin32.cpp StackWalker.cpp )
ELSEIF(IS_FREEBSD OR APPLE)
	SET( sources ${sources}  Network/SocketMgrFreeBSD.cpp  Network/SocketFreeBSD.cpp  Network/SocketOpsFreeBSD.cpp )
ELSE(WIN32)
	SET( sources ${sources}  Network/SocketMgrLinux.cpp  Network/SocketLinux.cpp  Network/SocketOpsLinux.cpp )
ENDIF(WIN32)

foreach(src IN ITEMS ${sources} )
  SET( SRCS ${SRCS} ${prefix}/${src} )
endforeach(src)

include_directories( ${GLOBAL_INCLUDE_DIRS} )
IF( IS_64BIT )
	link_directories( ${DEPENDENCY_DLLS64} )
ELSE()
	link_directories( ${DEPENDENCY_DLLS} )
ENDIF()
link_directories( ${DEPENDENCY_LIBS} )

ADD_LIBRARY( ${PROJECT_NAME} STATIC ${SRCS} ${HEADERS} )

target_link_libraries( ${PROJECT_NAME} ${ZLIB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${MYSQL_LIBRARY} ${OPENSSL_LIBRARIES} ${EXTRA_LIBS} )

