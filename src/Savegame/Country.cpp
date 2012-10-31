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
#include "Country.h"
#include "../Ruleset/RuleCountry.h"
#include "../Engine/RNG.h"
#include "../Engine/Game.h"
#include "Region.h"
#include "../Ruleset/Ruleset.h"
#include "../Ruleset/RuleRegion.h"
#include "SavedGame.h"

namespace OpenXcom
{

/**
 * Initializes a country of the specified type.
 * @param rules Pointer to ruleset.
 * @param gen Generate new funding.
 */
Country::Country(RuleCountry *rules, bool gen) : _rules(rules), _funding(0), _change(0), _activityXcom(0), _activityAlien(0)
{
	if (gen)
	{
		_funding = RNG::generate(rules->getMinFunding(), rules->getMaxFunding()) * 1000;
	}
}

/**
 *
 */
Country::~Country()
{
}

/**
 * Loads the country from a YAML file.
 * @param node YAML node.
 */
void Country::load(const YAML::Node &node)
{
	node["funding"] >> _funding;
	node["change"] >> _change;
	node["activityXcom"] >> _activityXcom;
	node["activityAlien"] >> _activityAlien;
}

/**
 * Saves the country to a YAML file.
 * @param out YAML emitter.
 */
void Country::save(YAML::Emitter &out) const
{
	out << YAML::BeginMap;
	out << YAML::Key << "type" << YAML::Value << _rules->getType();
	out << YAML::Key << "funding" << YAML::Value << _funding;
	out << YAML::Key << "change" << YAML::Value << _change;
	out << YAML::Key << "activityXcom" << YAML::Value << _activityXcom;
	out << YAML::Key << "activityAlien" << YAML::Value << _activityAlien;
	out << YAML::EndMap;
}

/**
 * Returns the ruleset for the country's type.
 * @return Pointer to ruleset.
 */
RuleCountry *const Country::getRules() const
{
	return _rules;
}

/**
 * Returns the country's current monthly funding.
 * @return Monthly funding.
 */
int Country::getFunding() const
{
	return _funding;
}

/**
 * Changes the country's current monthly funding.
 * @param funding Monthly funding.
 */
void Country::setFunding(int funding)
{
	_change += funding;
	_funding = funding;
}

/**
 * Returns the country's funding change since last month.
 * @return Funding change.
 */
int Country::getChange() const
{
	return _change;
}

/**
 * Resets the country's funding change since last month.
 */
void Country::resetChange()
{
	_change = 0;
}
/*
 * Keith Richards would be so proud
 */
int Country::getSatisfaction()
{
	for (std::vector<std::string>::iterator i = getRules()->getRegions()->begin(); i != getRules()->getRegions()->end(); ++i)
	{
		for (std::vector<Region*>::iterator r = _game->getSavedGame()->getRegions()->begin(); r != _game->getSavedGame()->getRegions()->end(); ++r)
		{
			_activityXcom += (*r)->getActivityXcom();
			_activityAlien += (*r)->getActivityAlien();
		}
	}

	return _activityXcom - _activityAlien;
}

void Country::setActivityXcom(int activity)
{
	_activityXcom += activity;
}

void Country::setActivityAlien(int activity)
{
	_activityAlien += activity;
}

int Country::getActivityXcom() const
{
	return _activityXcom;
}

int Country::getActivityAlien() const
{
	return _activityAlien;
}
}
