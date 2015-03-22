/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2012 Arctic Server Team
 * See COPYING for license details.
 */

#pragma once

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
// #include <fstream>

#include "Common.h"
#include <Network/Network.h>

#include "../shared/Log.h"
#include "../shared/Utilities/Utility.h"
#include "../shared/ByteBuffer.h"
#include "../shared/Config/ConfigEnv.h"

#include <zlib.h>

#include "../shared/DataBase/DatabaseEnv.h"
#include "../shared/DataBase/DBCStores.h"
#include "../shared/DataBase/dbcfile.h"

#include "../shared/Auth/BigNumber.h"
#include "../shared/Auth/Sha1.h"
#include "../shared/Auth/WowCrypt.h"
#include "../shared/CrashHandler.h"

#include "LogonOpcodes.h"
#include "../logonServer/Main.h"
#include "../World/NameTables.h"
#include "AccountCache.h"
#include "PeriodicFunctionCall_Thread.h"
#include "../logonServer/AutoPatcher.h"
#include "../logonServer/AuthSocket.h"
#include "../logonServer/AuthStructs.h"
#include "../logonServer/LogonOpcodes.h"
#include "../logonServer/LogonCommServer.h"
#include "../logonServer/LogonConsole.h"
#include "../shared/WorldPacket.h"

// database decl
extern Database* sLogonSQL;
