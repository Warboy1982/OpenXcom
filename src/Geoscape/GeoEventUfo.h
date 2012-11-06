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
#ifndef OPENXCOM_GEOEVENTUFO_H
#define OPENXCOM_GEOEVENTUFO_H
#include "GeoscapeEvents.h"

namespace OpenXcom
{
class Ufo;

/**
 * A new UFO is on the map.
 * It is not yet detected by XCOM.
 */
class UfoSpawned: public GeoEvent<UfoSpawned>
{
public:
	/// Remember the UFO.
	UfoSpawned(const Ufo &theUfo) : _ufo(theUfo) { /* Empty by design. */ }
	/// Provide read-only access to the UFO information.
	const Ufo &ufo() const { return _ufo; }
private:
	/// The UFO we care about.
	const Ufo &_ufo;
};

/**
 * A UFO was detected.
 */
class UfoDetected: public GeoEvent<UfoDetected>
{
public:
	/// Remember the UFO.
	UfoDetected(const Ufo &theUfo) : _ufo(theUfo) { /* Empty by design. */ }
	/// Provide read-only access to the UFO information.
	const Ufo &ufo() const { return _ufo; }
private:
	/// The UFO we care about.
	const Ufo &_ufo;
};

/**
 * A previously detected UFO has become hidden again.
 */
class UfoLost: public GeoEvent<UfoDetected>
{
public:
	/// Remember the UFO.
	UfoLost(const Ufo &theUfo) : _ufo(theUfo) { /* Empty by design. */ }
	/// Provide read-only access to the UFO information.
	const Ufo &ufo() const { return _ufo; }
private:
	/// The UFO we care about.
	const Ufo &_ufo;
};
}
#endif