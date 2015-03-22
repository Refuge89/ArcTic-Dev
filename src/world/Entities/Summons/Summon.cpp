/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2011 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../../StdAfx.h"

Summon::Summon(uint64 GUID) : Creature(GUID)
{
	summonslot = -1;
}

Summon::~Summon()
{
}

void Summon::Load(CreatureProto* proto, Unit* owner, LocationVector & position, uint32 spellid, int32 summonslot)
{
	ASSERT(owner != NULL);

	Creature::Load(proto, position.x, position.y, position.z, position.o);

	SetFaction( owner->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	SetPhase( owner->GetPhase());
	SetZoneId(owner->GetZoneId());
	SetUInt32Value(UNIT_CREATED_BY_SPELL,spellid);
	this->summonslot = summonslot;

	if(owner->IsPvPFlagged())
		SetPvPFlag();
	else
		RemovePvPFlag();

	if(owner->IsFFAPvPFlagged())
		SetFFAPvPFlag();
	else
		RemoveFFAPvPFlag();

	if(owner->IsSanctuaryFlagged())
		SetSanctuaryFlag();
	else
		RemoveSanctuaryFlag();

	SetUInt64Value(UNIT_FIELD_CREATEDBY,owner->GetGUID());

	if(owner->GetUInt64Value(UNIT_FIELD_SUMMONEDBY) == 0)
		SetUInt64Value(UNIT_FIELD_SUMMONEDBY,owner->GetGUID());
	else
		SetUInt64Value(UNIT_FIELD_SUMMONEDBY,owner->GetUInt64Value(UNIT_FIELD_SUMMONEDBY));

	this->owner = owner;

	if(owner->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
		SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);

}

void Summon::OnPushToWorld()
{
	if(summonslot != -1)
		owner->summonhandler.AddSummonToSlot(this, summonslot);
	else
		owner->summonhandler.AddSummon(this);

	Creature::OnPushToWorld();

}

void Summon::OnPreRemoveFromWorld()
{
	if(owner == NULL)
		return;

	if(GetUInt32Value(UNIT_CREATED_BY_SPELL) != 0)
		owner->RemoveAura(GetUInt32Value(UNIT_CREATED_BY_SPELL));

	if(summonslot != -1)
		owner->summonhandler.RemoveSummonFromSlot(summonslot, false);
	else
		owner->summonhandler.RemoveSummon(this);

	summonslot = -1;
	owner = NULL;

	SendDestroyObject();

}

Object* Summon::GetPlayerOwner()
{
	// owner is nulled on death
	if(owner == NULL)
		return NULL;

	if(owner->IsPlayer())
		return owner;
	else
		return NULL;
}

void Summon::Die(Unit* pAttacker, uint32 damage, uint32 spellid)
{
	if(owner->IsTotem())
		owner->Die(pAttacker, damage, spellid);

	Creature::Die(pAttacker, damage, spellid);

	if(summonslot != -1)
		owner->summonhandler.RemoveSummonFromSlot(summonslot, false);
	else
		owner->summonhandler.RemoveSummon(this);

	summonslot = -1;
	owner = NULL;
}

void Summon::OnRemoveInRangeObject(Object* object)
{

	if((owner != NULL) && (object->GetGUID() == owner->GetGUID()))
		Despawn(1, 0);

	Creature::OnRemoveInRangeObject(object);
}