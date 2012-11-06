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
#ifndef OPENXCOM_GEOSCAPEEVENTS_H
#define OPENXCOM_GEOSCAPEEVENTS_H

#ifndef NDEBUG
#include <string>
#include <typeinfo>
#endif

namespace OpenXcom
{

class SavedGame;
class Ufo;

// IMPORTANT
// The following list SHOULD contain every GeoEvent class defined.
class GeoEvent30Minutes;
class TerrorSiteExpired;
class UfoSpawned;
class UfoDetected;
class UfoLost;

/**
 * Helper functions and namespacing.
 */
struct GeoscapeEvents
{
	class Base;
};

/**
 * Abstract class to set the API for handling GeoEvents.
 * This class, together with the nested template GeoEvent<> and all the event
 * classes use double dispatch to get the proper event handler called.
 * All event consumers must extend this class.
 */
class GeoscapeEventHandler
{
protected:
	// Important: A handle() virtual member function MUST exist for every
	// class in the list above, and it SHOULD do nothing.
	// Derived classes should implement the handlers for the events they
	// care about.

	/// Handle unknown events.
	virtual void handle(const GeoscapeEvents::Base &);
	/// Called every 30 game minutes.
	virtual void handle(const GeoEvent30Minutes &) { /* default version does nothing. */ }
	/// Called when a terror site expires.
	virtual void handle(const TerrorSiteExpired &) { /* default version does nothing. */ }
	/// Called when a new UFO has spawned.
	virtual void handle(const UfoSpawned &) { /* default version does nothing. */ }
	/// Called when a UFO has been detected.
	virtual void handle(const UfoDetected &) { /* default version does nothing. */ }
	/// Called when a detected UFO becomes hidden again.
	virtual void handle(const UfoLost &) { /* default version does nothing. */ }

protected:
	virtual ~GeoscapeEventHandler() { /* Empty by design. */ }

// This allows actual handling of the events.
template <class D> friend class GeoEvent;
};

//Implementation details
#include "GeoscapeEventsImpl.h"

//
// Actual events
//
class TerrorSite; // Forward declaration

/**
 * A terror site has expired.
 */
class TerrorSiteExpired: public GeoEvent<TerrorSiteExpired>
{
public:
	/// Create the event for a given Terror site.
	TerrorSiteExpired(const TerrorSite &ts) : _site(ts) { /* Empty by design. */ }
	/// Provide read-only access to the site information.
	const TerrorSite &terrorSite() const { return _site; }
private:
	/// The terror site that expired
	const TerrorSite &_site;
};

}
#endif