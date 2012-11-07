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
#include "GeoscapeAI.h"
#include "AlienTerrorState.h"
#include "../Engine/Game.h"
#include "../Engine/RNG.h"
#include "GeoscapeState.h"
#include "GeoEventUfo.h"
#include "../Ruleset/City.h"
#include "../Ruleset/RuleRegion.h"
#include "../Ruleset/Ruleset.h"
#include "../Ruleset/RuleUfo.h"
#include "../Ruleset/RuleMission.h"
#include "../Ruleset/RuleCountry.h"
#include "../Savegame/Country.h"
#include "../Savegame/AlienAI.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/TerrorSite.h"
#include "../Savegame/Ufo.h"
#include "../Savegame/Waypoint.h"
#include "../Savegame/GameTime.h"
#include <cmath>
#include <algorithm>

namespace OpenXcom
{

/**
 * Create a mission generator with the information stored in @a game.
 * @param game The game object provides access to all the data and rules.
 * @param parent The Geoscape state, because some state classes require it.
 */
GeoscapeAI::GeoscapeAI(Game &game, GeoscapeState &parent)
: _game(game), _state(parent)
{
	// Empty by design!
}

/**
 * Add events to our processing queue.
 * After calling this function, we own and control the lifetime of the event.
 * @param event The pointer to the event.
 */
void GeoscapeAI::process(const GeoscapeEvents::Base &event)
{
	event.inform(this);
}

/**
 * Temporary code to spawn a UFO, code moved from GeoscapeState.
 * @todo get help with YAML interpretation, and move these tables to a ruleset.
 */
void GeoscapeAI::SpawnUFO()
{
	std::vector<std::string> ufos = _game.getRuleset()->getUfosList();
	std::vector<std::string> missions = _game.getRuleset()->getMissionList();
	int chance = RNG::generate(1, 100);
	if (chance <= 40)
	{		
		int _pick = RNG::generate(0, missions.size()-2);
		RuleMission* mission = _game.getRuleset()->getMission(missions.at(_pick)); // -2 because alien retaliation is a special case
		int set = ((_game.getSavedGame()->getTime()->getTotalDays())+1)/60;
		if(set > mission->getRaceSet().size()-1) set = mission->getRaceSet().size()-1;
		RaceSet probabilites = mission->getRaceSet().at(set);
		int ships = RNG::generate(1, _pick+1); // 1 for research, 1+ for other types (so we can send scouts)
		//Country _target(0); // base on activity levels
		int _period(0); //time period - how long until mission expires - base on type?
		unsigned int _type = 0; // should depend on mission type, role in mission based on number of ships and anger towards player
		                // make race based on ruleset variables and a function of totaldays
		// Makes smallest UFO the more likely, biggest UFO the least likely
		// eg. 0 - 0..6, 1 - 6..10, etc.
		unsigned int range = RNG::generate(1, (ufos.size()*(ufos.size()+1))/2);
		unsigned int type = 0;
		for (unsigned int i = 0, j = 1; i < ufos.size(); ++i, j += ufos.size()-i)
		{
			if (j <= range && range < j + ufos.size()-i)
			{
				type = i;
				break;
			}
		}
		Ufo *u = new Ufo(_game.getRuleset()->getUfo(ufos[type]));
		u->setLongitude(RNG::generate(0.0, 2*M_PI));
		u->setLatitude(RNG::generate(-M_PI_2, M_PI_2));
		Waypoint *w = new Waypoint();
		w->setLongitude(RNG::generate(0.0, 2*M_PI));
		w->setLatitude(RNG::generate(-M_PI_2, M_PI_2));
		u->setDestination(w);
		u->setSpeed(RNG::generate(u->getRules()->getMaxSpeed() / 4, u->getRules()->getMaxSpeed() / 2));
		int race = RNG::generate(1, 2);
		if(_game.getSavedGame()->getTime()->getTotalDays() > 45)
			race += RNG::generate(0, 1);
		if(_game.getSavedGame()->getTime()->getTotalDays() > 90)
			race += RNG::generate(0, 1);
		if(_game.getSavedGame()->getTime()->getTotalDays() > 135)
			race += RNG::generate(0, 2);
		if (race == 1)
			u->setAlienRace("STR_SECTOID");
		else if (race == 2)
			u->setAlienRace("STR_FLOATER");
		else if (race == 3)
			u->setAlienRace("STR_SNAKEMAN");
		else if (race == 4)
			u->setAlienRace("STR_MUTON");
		else if (race == 5)
			u->setAlienRace("STR_ETHERIAL");
		else
			u->setAlienRace("STR_MIXED");
		_game.getSavedGame()->getUfos()->push_back(u);
	}
}

/**
 * Temporary code to spawn a Terror Site, code moved from GeoscapeState.
 * @todo Write proper missions and remove this function.
 */
void GeoscapeAI::fakeTerrorSpawn()
{
	// Spawn terror sites
	int chance = RNG::generate(1, 20);
	if (chance <= 2)
	{
		// Pick a city
		RuleRegion* region = 0;
		std::vector<std::string> regions = _game.getRuleset()->getRegionsList();
		do
		{
			region = _game.getRuleset()->getRegion(regions[RNG::generate(0, regions.size()-1)]);
		}
		while (region->getCities()->empty());
		City *city = (*region->getCities())[RNG::generate(0, region->getCities()->size()-1)];

		TerrorSite *t = new TerrorSite();
		t->setLongitude(city->getLongitude());
		t->setLatitude(city->getLatitude());
		t->setId(_game.getSavedGame()->getId("STR_TERROR_SITE"));
		t->setHoursActive(24 + RNG::generate(0, 24));
		int race = RNG::generate(1, 2);
		if (race == 1)
			t->setAlienRace("STR_SECTOID");
		else
			t->setAlienRace("STR_FLOATER");
		_game.getSavedGame()->getTerrorSites()->push_back(t);
		_game.pushState(new AlienTerrorState(&_game, city, &_state));
	}
}

/**
 * Try to spawn UFOs and reduce the countdown for new terror sites.
 * Each timer event means 30 minutes have passed in the game world.
 * @param event A timer event.
 */
void GeoscapeAI::handle(GeoEvent30Minutes *event)
{
	(void)event; //Keep both gcc and Doxygen happy
	SpawnUFO();
	/*
	 * Count down until a new terror mission can begin.
	 * The time passes in 30 minute increments.
	 * Once the count down finishes, a new one begins.
	 */
	int terrorMinutes = _game.getSavedGame()->accessAlienAI()._terrorCountdown - 30;
	if (terrorMinutes <= 0)
	{
		fakeTerrorSpawn();
		terrorMinutes = 24 * 60; // Another day
	}
	_game.getSavedGame()->accessAlienAI()._terrorCountdown = terrorMinutes;
	
}

}