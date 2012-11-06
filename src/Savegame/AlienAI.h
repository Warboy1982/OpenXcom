/*
 * Copyright 2012 OpenXcom Developers.
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
#ifndef OPENXCOM_ALIENAI_H
#define OPENXCOM_ALIENAI_H

#include <yaml-cpp/yaml.h>

namespace OpenXcom
{

class SavedGame;

/**
 * Store the information the GeoscapeAI requires.
 * This is a POD (plain old data) that only GeoscapeAI should touch directly.
 * The SavedGame should only use the YAML related parts, and constructor and
 * detructor.
 */
class AlienAI
{
public:
	/// Create an AlienAI with default data.
	AlienAI();
	/// Free resources used by the AlienAI.
	~AlienAI();
	/// Loads the data from YAML.
	void load(SavedGame &theGame, const YAML::Node& node);
	/// Saves the data to YAML.
	void save(YAML::Emitter& out) const;

	/* ONLY GeoscapeAI should access these */
	/// The number of minutes before each attempt at terror missions.
	int _terrorCountdown;

private:
	// Disable copy and assignments.
	AlienAI(const AlienAI &);
	AlienAI &operator=(const AlienAI &);
};

}

#endif