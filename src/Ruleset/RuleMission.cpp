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

namespace OpenXcom
{

/**
 * Creates a blank ruleset for a certain
 * type of Mission.
 * @param type String defining the type.
 */
RuleMission::RuleMission(const std::string &type)
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
		else if (key == "month1")
		{
			i.second() >> _month1;
		}
		else if (key == "month2")
		{
			i.second() >> _month2;
		}
		else if (key == "month3")
		{
			i.second() >> _month3;
		}
		else if (key == "month4")
		{
			i.second() >> _month4;
		}
		else if (key == "month5")
		{
			i.second() >> _month5;
		}
		else if (key == "month6")
		{
			i.second() >> _month6;
		}
		else if (key == "month7")
		{
			i.second() >> _month7;
		}
		else if (key == "month8")
		{
			i.second() >> _month8;
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
	out << YAML::Key << "month1" << YAML::Value << _month1;
	out << YAML::Key << "month2" << YAML::Value << _month2;
	out << YAML::Key << "month3" << YAML::Value << _month3;
	out << YAML::Key << "month4" << YAML::Value << _month4;
	out << YAML::Key << "month5" << YAML::Value << _month5;
	out << YAML::Key << "month6" << YAML::Value << _month6;
	out << YAML::Key << "month7" << YAML::Value << _month7;
	out << YAML::Key << "month8" << YAML::Value << _month8;
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
 * Returns the probability of a given race being in charge of a mission
 * @param month The month dataset to use (value > 8 = 8)
 * @param race The Alien race we want the numbers on
 * @return The probability of a given alien race being in charge.
 */
int RuleMission::getRace(int month, AlienRace *race) const
{
	switch(month)
	{
	case 1:
		return _month1.find(race->getId())->second;
	case 2:
		return _month2.find(race->getId())->second;
	case 3:
		return _month3.find(race->getId())->second;
	case 4:
		return _month4.find(race->getId())->second;
	case 5:
		return _month5.find(race->getId())->second;
	case 6:
		return _month6.find(race->getId())->second;
	case 7:
		return _month7.find(race->getId())->second;
	default:
		return _month8.find(race->getId())->second;
	}
}

}
