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
#ifndef OPENXCOM_TIMERGEOEVENTS_H
#define OPENXCOM_TIMERGEOEVENTS_H

#include "GeoscapeEvents.h"

namespace OpenXcom
{

/**
 * Send this every 30 game minutes.
 * This is a simple event, all the information is it's type.
 */
class GeoEvent30Minutes: public GeoEvent<GeoEvent30Minutes> { /* Empty by design. */ };

}
#endif