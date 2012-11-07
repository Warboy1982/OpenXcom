/*
 * Copyright 2010-2012 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <cmath>
#include "RuleMission.h"
#include "AlienRace.h"
#include "RuleUfo.h"
#include "RuleCraft.h"
#include "../Savegame/Ufo.h"
#include "../Savegame/Craft.h"

namespace OpenXcom
{
	
void operator >> (const YAML::Node& node, RuleFlightPattern& s)
{
	node[0] >> s.a;
	node[1] >> s.b;
	node[2] >> s.c;
	node[3] >> s.d;
	node[4] >> s.e;
	node[5] >> s.f;
	node[6] >> s.g;
	node[7] >> s.h;
}
YAML::Emitter& operator << (YAML::Emitter& out, const RuleFlightPattern& s)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << s.a << s.b << s.c << s.d << s.e << s.f << s.g << s.h << YAML::EndSeq;
	return out;
}

void operator >> (const YAML::Node& node, RaceSet& s)
{
	node >> s.races;
}

YAML::Emitter& operator << (YAML::Emitter& out, const RaceSet& s)
{
	out << s.races;
	return out;
}

/**
 * Creates a blank ruleset for a certain
 * type of Mission.
 * @param type String defining the type.
 */
RuleMission::RuleMission(const std::string &type) : _type(""), _spawnOnComplete(""), _races(0), _scoutList(0), _missionShip(0), _minScouts(0),
	_maxScouts(0), _minScoutTime(0), _maxScoutTime(0), _minMissionTime(0), _maxMissionTime(0), _points(0), _maxMissionShips(0), _minMissionShips(0)
{
}

RuleMission::~RuleMission()
{
}

/**
 * Loads the Mission from a YAML file.
 * @param node YAML node.
 */
void RuleMission::load(const YAML::Node &node)
{
	int a = 0;
	for (YAML::Iterator i = node.begin(); i != node.end(); ++i)
	{
		std::string key;
		i.first() >> key;
		if (key == "type")
		{
			i.second() >> _type;
		}
		if (key == "scoutList")
		{
			i.second() >> _scoutList;
		}
		if (key == "minScouts")
		{
			i.second() >> _minScouts;
		}
		if (key == "maxScouts")
		{
			i.second() >> _maxScouts;
		}
		if (key == "minScoutTime")
		{
			i.second() >> _minScoutTime;
		}
		if (key == "maxScoutTime")
		{
			i.second() >> _maxScoutTime;
		}
		if (key == "scoutFlightPattern")
		{
			i.second() >> _scoutFlightPattern;
		}
		if (key == "missionShip")
		{
			i.second() >> _missionShip;
		}
		if (key == "minMissionShips")
		{
			i.second() >> _minMissionShips;
		}
		if (key == "minMissionShips")
		{
			i.second() >> _minMissionShips;
		}
		if (key == "minMissionTime")
		{
			i.second() >> _minMissionTime;
		}
		if (key == "maxMissionTime")
		{
			i.second() >> _maxMissionTime;
		}
		if (key == "missionFlightPattern")
		{
			i.second() >> _missionFlightPattern;
		}
		if (key == "spawnOnComplete")
		{
			i.second() >> _spawnOnComplete;
		}
		if (key == "points")
		{
			i.second() >> _points;
		}
		else if (key == "races")
		{
			i.second() >> _races;
		}
	}
}

/**
 * Saves the Mission to a YAML file.
 * @param out YAML emitter.
 */
void RuleMission::save(YAML::Emitter &out) const
{
	out << YAML::BeginMap;
	out << YAML::Key << "type" << YAML::Value << _type;
	out << YAML::Key << "scoutList" << YAML::Value << _scoutList;
	out << YAML::Key << "minScouts" << YAML::Value << _minScouts;
	out << YAML::Key << "maxScouts" << YAML::Value << _maxScouts;
	out << YAML::Key << "minScoutTime" << YAML::Value << _minScoutTime;
	out << YAML::Key << "maxScoutTime" << YAML::Value << _maxScoutTime;
	out << YAML::Key << "scoutFlightPattern" << YAML::Value << _scoutFlightPattern;
	out << YAML::Key << "missionShip" << YAML::Value << _missionShip;
	out << YAML::Key << "minMissionShips" << YAML::Value << _minMissionShips;
	out << YAML::Key << "maxMissionShips" << YAML::Value << _maxMissionShips;
	out << YAML::Key << "minMissionTime" << YAML::Value << _minMissionTime;
	out << YAML::Key << "maxMissionTime" << YAML::Value << _maxMissionTime;
	out << YAML::Key << "missionFlightPattern" << YAML::Value << _missionFlightPattern;
	out << YAML::Key << "spawnOnComplete" << YAML::Value << _spawnOnComplete;
	out << YAML::Key << "points" << YAML::Value << _points;
	out << YAML::Key << "races" << YAML::Value << _races;
	out << YAML::EndMap;
}

/**
 * Returns the language string that names
 * this mission type.
 * @return Mission name.
 */
std::string RuleMission::getType() const
{
	return _type;
}

/**
 * Returns the probability tables of a given race being in charge of a mission
 * @return The probability tables of a given alien race being in charge of this mission.
 * note: i'm not 100% sure this is how this should be handled.
 */
const std::vector<RaceSet> RuleMission::getRaceSet() const
{
	return _races;
}

std::vector<std::string> RuleMission::getScoutList() const
{
	return _scoutList;
}
std::vector<std::string> RuleMission::getMissionShipList() const
{
	return _missionShip;
}

int RuleMission::getMinScouts() const
{
	return _minScouts;
}
int RuleMission::getMaxScouts() const
{
	return _maxScouts;
}
int RuleMission::getMinScoutTime() const
{
	return _minScoutTime;
}
int RuleMission::getMaxScoutTime() const
{
	return _maxScoutTime;
}
int RuleMission::getMinMissionTime() const
{
	return _minMissionTime;
}
int RuleMission::getMaxMissionTime() const
{
	return _maxMissionTime;
}
int RuleMission::getPoints() const
{
	return _points;
}
int RuleMission::getMinMissionShips() const
{
	return _minMissionShips;
}
int RuleMission::getMaxMissionShips() const
{
	return _maxMissionShips;
}
RuleFlightPattern RuleMission::getScoutFlightPattern() const
{
	return _scoutFlightPattern;
}
RuleFlightPattern RuleMission::getMissionFlightPattern() const
{
	return _missionFlightPattern;
}
std::string RuleMission::getSpawnOnComplete() const
{
	return _spawnOnComplete;
}
}
