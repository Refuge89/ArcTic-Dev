/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2012 Arctic Server Team
 * See COPYING for license details.
 */

#include "StdAfx.h"

initialiseSingleton( WeatherMgr );

void BuildWeatherPacket(WorldPacket * data, uint32 Effect, float Density )
{
	data->Initialize(SMSG_WEATHER);
	if(Effect == 0 ) // set all parameter to 0 for sunny.
		*data << uint32(0) << float(0) << uint32(0) << uint8(0);
	else if (Effect == 1) // No sound/density for fog
		*data << Effect << float(0) << uint32(0) << uint8(0);
	else
		*data << Effect << Density << GetSound(Effect,Density) << uint8(0) ;
}

uint32 GetSound(uint32 Effect, float Density)
{
	uint32 sound;
	if(Density<=0.20f)
		return WEATHER_NOSOUND;

	switch(Effect)
	{
		case 2: // rain
		case 4:
			if(Density  <0.40f)
				 sound = WEATHER_RAINLIGHT;
			else if(Density  <0.70f)
				sound = WEATHER_RAINMEDIUM;
			else
				sound = WEATHER_RAINHEAVY;
			break;
		case 8: // snow
			if(Density  <0.40f)
				sound = WEATHER_SNOWLIGHT;
			else if(Density  <0.70f)
				sound = WEATHER_SNOWMEDIUM;
			else
				sound = WEATHER_SNOWHEAVY;
			break;
		case 16: // storm
			if(Density  <0.40f)
				sound = WEATHER_SANDSTORMLIGHT;
			else if(Density  <0.70f)
				sound = WEATHER_SANDSTORMMEDIUM;
			else
				sound = WEATHER_SANDSTORMHEAVY;
			break;
		default: // no sound
			sound = WEATHER_NOSOUND;
			break;
	}
	return sound;
}

WeatherMgr::WeatherMgr()
{
}

WeatherMgr::~WeatherMgr()
{
	map<uint32, WeatherInfo*>::iterator itr;
	for( itr = m_zoneWeathers.begin(); itr != m_zoneWeathers.end(); itr++)
		delete itr->second;

	m_zoneWeathers.clear();
}

void WeatherMgr::LoadFromDB()
{
	QueryResult *result = WorldDatabase.Query( "SELECT zoneId,high_chance,high_type,med_chance,med_type,low_chance,low_type FROM weather" );
	if( !result )
		return;

	Field *fields = result->Fetch();
	WeatherInfo* wi = NULL;
	do
	{
		fields = result->Fetch();
		wi = new WeatherInfo();
		wi->m_zoneId = fields[0].GetUInt32();
		wi->m_effectValues[0] = fields[1].GetUInt32(); // high_chance
		wi->m_effectValues[1] = fields[2].GetUInt32(); // high_type
		wi->m_effectValues[2] = fields[3].GetUInt32(); // med_chance
		wi->m_effectValues[3] = fields[4].GetUInt32(); // med_type
		wi->m_effectValues[4] = fields[5].GetUInt32(); // low_chance
		wi->m_effectValues[5] = fields[6].GetUInt32(); // low_type
		m_zoneWeathers[wi->m_zoneId] = wi;

		wi->_GenerateWeather();
	} while( result->NextRow() );
	Log.Notice("WeatherMgr", "Loaded weather information for %u zones.", result->GetRowCount());

	delete result;
}

void WeatherMgr::SendWeather(Player* plr) // Update weather when player has changed zone (WorldSession::HandleZoneUpdateOpcode)
{
	std::map<uint32, WeatherInfo* >::iterator itr;
	itr = m_zoneWeathers.find(plr->GetZoneId());

	if(itr == m_zoneWeathers.end())
	{
		WorldPacket data(SMSG_WEATHER, 9);
		BuildWeatherPacket(&data, 0, 0);
		plr->GetSession()->SendPacket( &data );
		plr->m_lastSeenWeather = 0;

		return;
	}
	else
	{
		itr->second->SendUpdate(plr);
	}
}

WeatherInfo::WeatherInfo()
{
	m_currentDensity = 0;
	m_currentEffect = 0;
	m_currentTime = 0;
	m_maxDensity = 0;
	m_totalTime = 0;
	m_zoneId = 0;
}

WeatherInfo::~WeatherInfo()
{
	m_effectValues.clear();
	sEventMgr.RemoveEvents(this);
}

void WeatherInfo::_GenerateWeather()
{
	m_currentTime = 0;
	m_currentEffect = 0;
	m_currentDensity = 0.20f; // Starting Offset (don't go below, it's annoying fog)
	float fd = RandomFloat();
	m_maxDensity = fd+1; // 1-2
	m_totalTime = (RandomUInt(11) + 5)*1000*120; // update approx. every 1-2 minutes

	uint32 rv = RandomUInt(100);

	std::map<uint32, uint32>::iterator itr;

	if(rv <= m_effectValues[4]) // %chance on changing weather from sunny to m_effectValues[5]
	{
		m_currentEffect = m_effectValues[5];
	}
	else if(rv <= m_effectValues[2]) // %chance on changing weather from sunny to m_effectValues[3]
	{
		m_currentEffect = m_effectValues[3];
	}
	else if(rv <= m_effectValues[0]) // %chance on changing weather from sunny to m_effectValues[1]
	{
		m_currentEffect = m_effectValues[1];
	}

	SendUpdate();

	sEventMgr.AddEvent(this, &WeatherInfo::BuildUp, EVENT_WEATHER_UPDATE, (uint32)(m_totalTime/ceil(m_maxDensity/WEATHER_DENSITY_UPDATE)*2), 0,0);
	DEBUG_LOG("WeatherMgr", "Forecast for zone:%d new type:%d new interval:%d ms",m_zoneId,m_currentEffect,(uint32)(m_totalTime/ceil(m_maxDensity/WEATHER_DENSITY_UPDATE)*2));
}

void WeatherInfo::BuildUp()
{
	// Increase until 0.5, start random counter when reached
	if (m_currentDensity >= 0.50f)
	{
		sEventMgr.RemoveEvents(this, EVENT_WEATHER_UPDATE);
		sEventMgr.AddEvent(this, &WeatherInfo::Update, EVENT_WEATHER_UPDATE, (uint32)(m_totalTime/ceil(m_maxDensity/WEATHER_DENSITY_UPDATE)*4), 0,0);
	}
	else
	{
		m_currentDensity += WEATHER_DENSITY_UPDATE;
		SendUpdate();
	}
}
void WeatherInfo::Update()
{
	// There will be a 66% the weather density decreases. If Sunny, use as currentDensity as countdown
	if (m_currentEffect == 0 || RandomUInt(100) < 66)
	{
		m_currentDensity -= WEATHER_DENSITY_UPDATE;
		if (m_currentDensity < 0.20f) // 0.20 is considered fog, lower values are anoying
		{
			m_currentDensity = 0.0f;
			m_currentEffect = 0;
			sEventMgr.RemoveEvents(this, EVENT_WEATHER_UPDATE);
			_GenerateWeather();
			return;
		}
	}
	else
	{
		m_currentDensity += WEATHER_DENSITY_UPDATE;
		if (m_currentDensity >= m_maxDensity)
		{
			m_currentDensity = m_maxDensity;
			return;
		}
	}
	SendUpdate();
}

void WeatherInfo::SendUpdate()
{
	WorldPacket data(SMSG_WEATHER, 9);
	BuildWeatherPacket(&data, m_currentEffect, m_currentDensity);

	sWorld.SendZoneMessage(&data, m_zoneId, 0);
}

void WeatherInfo::SendUpdate(Player* plr) // Updates weather for player's zone-change only if new zone weather differs
{
	if(plr->m_lastSeenWeather == m_currentEffect) // return if weather is same as previous zone
		return;

	plr->m_lastSeenWeather = m_currentEffect;

	WorldPacket data(SMSG_WEATHER, 9);
	BuildWeatherPacket(&data, m_currentEffect, m_currentDensity);
	plr->GetSession()->SendPacket( &data );
}
