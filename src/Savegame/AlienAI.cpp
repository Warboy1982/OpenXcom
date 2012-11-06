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
#include "AlienAI.h"
#include "SavedGame.h"

namespace OpenXcom
{

/**
 * Create an AlienAI with default values.
 */
AlienAI::AlienAI() : _terrorCountdown(24 * 60)
{
	// Empty by design!
}

/**
 * Free all resources used by this AlienAI.
 */
AlienAI::~AlienAI()
{
	// Empty by design!
}

/**
 * Loads the data from a YAML file.
 * @param node YAML node.
 */
void AlienAI::load(SavedGame &theGame, const YAML::Node &node)
{
	node["terrorCountdown"] >> _terrorCountdown;
}

/**
 * Saves the alien data to a YAML file.
 * @param out YAML emitter.
 */
void AlienAI::save(YAML::Emitter &out) const
{
	out << YAML::BeginMap;
	out << YAML::Key << "terrorCountdown" << YAML::Value << _terrorCountdown;
	out << YAML::EndMap;
}

}