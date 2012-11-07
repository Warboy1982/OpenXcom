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
#ifndef OPENXCOM_GEOSCAPEAI_H
#define OPENXCOM_GEOSCAPEAI_H

#include "GeoscapeEvents.h"
#ifndef NDEBUG
#include <string>
#include <typeinfo>
#endif

namespace OpenXcom
{

class GeoscapeState;
class Game;
class Country;

/**
 * Handle Geoscape game events.
 * Use them to react to XCOM acts and initiate Alien actions.
 * This class, together with the nested template GeoEvent<> and all the event
 * classes use double dispatch to get the proper event handler called.
 */
class GeoscapeAI: public GeoscapeEventHandler
{
public:
	/// Create a mission generator.
	GeoscapeAI(Game &game, GeoscapeState &state);
	/// Process the information from an event.
	void process(const GeoscapeEvents::Base &event);
	void SpawnUFO();

protected:
	/// Called every 30 game minutes.
	void handle(GeoEvent30Minutes *);

private:
	int _angerlevel;
	/// Access to data and rules.
	Game &_game;
	/// This is who can display our messages.
	GeoscapeState &_state;

	// Immitate existing behaviour.
	void fakeUFOSpawn();
	void fakeTerrorSpawn();

	#define M_PI 3.14159265358979323846
	#define M_PI_2 1.57079632679489661923
};

}

#endif