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
#include "GeoscapeEvents.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/TerrorSite.h"
#include "../Savegame/Ufo.h"
#include "GeoEventUfo.h"
#ifndef NDEBUG
#include <iostream>
#endif

namespace OpenXcom
{

/**
 * This gets called only when a better match was not found.
 * This could mean we have an error somewhere, unless you really don't care for
 * the event.
 * If you wanted the actual event make sure that the proper event class forward
 * declaration is in GeoEvents.h and an appropriate handle(ProperEvent*) is
 * declared in GeoscapeEventHandler.
 * @param event An event of unknown type.
 */
void GeoscapeEventHandler::handle(const GeoscapeEvents::Base &event)
{
#ifndef NDEBUG
	std::cerr << "Got base object for class " << event.className() << std::endl;
#endif
}

}