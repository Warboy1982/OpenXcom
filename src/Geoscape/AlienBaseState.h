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
#ifndef OPENXCOM_ALIENBASESTATE_H
#define OPENXCOM_ALIENBASESTATE_H

#include "../Engine/State.h"

namespace OpenXcom
{

class Region;
class TextButton;
class Window;
class Text;
class GeoscapeState;
class AlienBase;

/**
 * Displays info on a terror site.
 */
class AlienBaseState : public State
{
private:
	Region *_region;
	GeoscapeState *_state;
	AlienBase *_base;

	TextButton *_btnCentre, *_btnCancel;
	Window *_window;
	Text *_txtTitle, *_txtRegion;
public:
	/// Creates the Ufo Detected state.
	AlienBaseState(Game *game, AlienBase *base, GeoscapeState *state);
	/// Cleans up the Ufo Detected state.
	~AlienBaseState();
	/// Updates the palette.
	void init();
	/// Handler for clicking the Centre on UFO button.
	void btnCentreClick(Action *action);
	/// Handler for clicking the Cancel button.
	void btnCancelClick(Action *action);
};

}

#endif
