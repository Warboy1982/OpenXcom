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
#ifndef OPENXCOM_GEOSCAPEEVENTSIMPL_H
#define OPENXCOM_GEOSCAPEEVENTSIMPL_H
#ifndef NDEBUG
#include <string>
#include <typeinfo>
#endif

/** @file Implementation details for the GeoEvent system. */

/**
 * The root class of GeoEvents.
 * It works together with the GeoEvent<> template to ease the
 * implementation of conforming GeoEvent subclasses.
 */ 
class GeoscapeEvents::Base
{
public:
	virtual ~Base() { /* Empty by design */ }

	// Only the GeoEvent class must implement these.
	/// Send event to proper handler.
	virtual void inform(GeoscapeEventHandler *) const = 0;
#ifndef NDEBUG
	virtual std::string className() const = 0;
#endif

private:
	Base() { /* Empty by design */ }
	/* Disable copy and assignment. */
	Base(const Base &);
	Base &operator=(const Base &);
template <class D> friend class GeoEvent;
};

/**
 * Base class template for events happening on the Geoscape.
 * All GeoEvent subclasses must be defined as inheriting this.
 * It uses the Curious Recurring Template Pattern to take care
 * of the dynamic dispatch to the proper event handler of GeoscapeAI.
 * @sa GeoEvent30Minutes
 * @note The protected constructor stops the creation of naked Event<Some>
 * objects.
 */
template <class D>
class GeoEvent: public GeoscapeEvents::Base
{
public:
	/// Allow the event consumer to handle the actual event type.
	void inform(GeoscapeEventHandler *alien) const { alien->handle(static_cast<const D&>(*this)); }
#ifndef NDEBUG
	/// Return the derived class name.
	std::string className() const { return typeid(*static_cast<const D*>(this)).name(); }
#endif
protected:
	GeoEvent() : Base() { /* Empty by design. */ }

};

#endif