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
#ifndef OPENXCOM_RULEMISSION_H
#define OPENXCOM_RULEMISSION_H

#include <string>
#include <vector>
#include <map>
#include <yaml-cpp/yaml.h>

namespace OpenXcom
{

class AlienRace;

/**
 * Represents an Alien Mission
 * containing information on racial appearance ratios
 */
class RuleMission
{
private:
	std::string _type;
	std::map<std::string, int> _month1, _month2, _month3, _month4, _month5, _month6, _month7, _month8;
public:
	/// Creates a blank mission ruleset
	RuleMission(const std::string &type);
	/// Cleans up the mission ruleset.
	~RuleMission();
	/// Loads mission data from YAML.
	void load(const YAML::Node& node);
	/// Saves the mission data to YAML.
	void save(YAML::Emitter& out) const;
	/// Gets the mission's type.
	std::string getType() const;
	/// Gets a mission's racial appearance ratios.
	int getRace(int month, AlienRace *race) const;
};

}

#endif
