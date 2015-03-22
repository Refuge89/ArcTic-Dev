/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2012 Arctic Server Team
 * See COPYING for license details.
 */

#include "StdAfx.h"
#include "Setup.h"
#ifdef WIN32
#pragma warning(disable:4305)		// warning C4305: 'argument' : truncation from 'double' to 'float'
#endif

/************************************************************************/
/* Arximag Teleport  Azshara                                            */
/************************************************************************/

class ArximagTeleportDown : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
	void GossipHello(Object* pObject, Player* plr, bool AutoSend)
	{
		GossipMenu *Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1994, plr);

		Menu->AddItem(0, "[i am, ready]", 1);

		if(AutoSend)
			Menu->SendTo(plr);
	}
	void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char * Code)
	{
		Creature*  pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?(TO_CREATURE(pObject)):NULL;
		if(pCreature==NULL)
		{
			return;
		}

		GossipMenu * Menu;
		switch(IntId)
		{
		case 0:
			GossipHello(pObject, plr, true);
			break;
		case 1:
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1994, plr);
			 plr->EventTeleport(1, 3649.567627, -4705.155762, 120.966309);
			break;
		}
	}
};

class ArximagTeleportUp : public GossipScript
{
public:
	void Destroy()
	{
		delete this;
	}
	void GossipHello(Object* pObject, Player* plr, bool AutoSend)
	{
		GossipMenu *Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, plr);

		Menu->AddItem(0, "[i am, ready]", 1);

		if(AutoSend)
			Menu->SendTo(plr);
	}

	void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char * Code)
	{
		Creature*  pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?(TO_CREATURE(pObject)):NULL;
		if(pCreature==NULL)
		{
			return;
		}

		GossipMenu * Menu;
		switch(IntId)
		{
		case 0:
			GossipHello(pObject, plr, true);
			break;
		case 1:
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, plr);
			 plr->EventTeleport(1, 3778.438721, -4612.299805, 227.253922);
			break;
		}
	}
};

void SetupAzshara(ScriptMgr * mgr)
{
	GossipScript * axtd = (GossipScript*) new ArximagTeleportDown();
	GossipScript * axtu = (GossipScript*) new ArximagTeleportUp();

	mgr->register_gossip_script(8399, axtd); 
	mgr->register_gossip_script(8395, axtu); 
}
