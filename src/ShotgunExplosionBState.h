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
#ifndef OPENXCOM_SHOTGUNEXPLOSIONBSTATE_H
#define OPENXCOM_SHOTGUNEXPLOSIONBSTATE_H

#include "Battlescape\BattleState.h"
#include "Battlescape\Position.h"
#include "Battlescape\ProjectileFlyBState.h"

namespace OpenXcom
{

class BattlescapeGame;
class BattleUnit;
class BattleItem;
class Tile;

/* Explosion state not only handles explosions, but also bullet impacts! */
/* Refactoring tip : ImpactBState */

class ShotgunExplosionBState : public BattleState
{
private:
	BattleUnit *_unit;
	Position _center;
	BattleItem *_item;
	Tile *_tile;
	int _buckshotCounter;
	Position *_centera;
	Position *_centerb;
	Position *_centerc;
	Position *_centerd;
	Position *_centere;
public:
	/// Creates a new ExplosionBState class
	ShotgunExplosionBState(BattlescapeGame *parent, Position center, BattleItem *item, BattleUnit *unit, Tile *tile = 0);
	/// Cleans up the ExplosionBState.
	~ShotgunExplosionBState();
	/// Initializes the state.
	void init();
	/// Handles a cancels request.
	void cancel();
	/// Runs state functionality every cycle.
	void think();
	/// Get the result of the state.
	std::string getResult() const;

};

}

#endif
