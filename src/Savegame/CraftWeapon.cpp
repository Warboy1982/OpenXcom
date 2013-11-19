/*
 * Copyright 2010-2013 OpenXcom Developers.
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
#include "CraftWeapon.h"
#include "../Ruleset/RuleCraftWeapon.h"
#include "CraftWeaponProjectile.h"

namespace OpenXcom
{

/**
 * Initializes a craft weapon of the specified type.
 * @param rules Pointer to ruleset.
 * @param ammo Initial ammo.
 */
CraftWeapon::CraftWeapon(RuleCraftWeapon *rules, int ammo) : _rules(rules), _ammo(ammo), _rearming(false)
{
}

/**
 *
 */
CraftWeapon::~CraftWeapon()
{
}

/**
 * Loads the craft weapon from a YAML file.
 * @param node YAML node.
 */
void CraftWeapon::load(const YAML::Node &node)
{
	_ammo = node["ammo"].as<int>(_ammo);
	_rearming = node["rearming"].as<bool>(_rearming);
}

/**
 * Saves the base to a YAML file.
 * @return YAML node.
 */
YAML::Node CraftWeapon::save() const
{
	YAML::Node node;
	node["type"] = _rules->getType();
	node["ammo"] = _ammo;
	if (_rearming)
		node["rearming"] = _rearming;
	return node;
}

/**
 * Returns the ruleset for the craft weapon's type.
 * @return Pointer to ruleset.
 */
RuleCraftWeapon *CraftWeapon::getRules() const
{
	return _rules;
}

/**
 * Returns the ammo contained in this craft weapon.
 * @return Weapon ammo.
 */
int CraftWeapon::getAmmo() const
{
	return _ammo;
}

/**
 * Changes the ammo contained in this craft weapon.
 * @param ammo Weapon ammo.
 */
bool CraftWeapon::setAmmo(int ammo)
{
	_ammo = ammo;
	if (_ammo < 0)
	{
		_ammo = 0;
		return false;
	}
	if (_ammo > _rules->getAmmoMax())
	{
		_ammo = _rules->getAmmoMax();
	}
	return true;
}

/**
 * Returns whether this craft weapon needs rearming.
 * @return Rearming status.
 */
bool CraftWeapon::isRearming() const
{
	return _rearming;
}

/**
 * Changes whether this craft weapon needs rearming
 * (for example, in case there's no more ammo).
 * @param rearming Rearming status.
 */
void CraftWeapon::setRearming(bool rearming)
{
	_rearming = rearming;
}

/**
 * Rearms this craft weapon's ammo.
 * @param available number of clips available.
 * @param clipSize number of rounds in said clips.
 * @return number of clips used.
 */
int CraftWeapon::rearm(const int available, const int clipSize)
{
	int used = 0;

	if (clipSize > 0)
	{
		const int needed = std::max(1, (_rules->getAmmoMax() - _ammo) / clipSize);
		used = std::min(_rules->getRearmRate() / clipSize, needed);
	}

	if (available >= used)
	{
		setAmmo(_ammo + _rules->getRearmRate());
	}
	else
	{
		setAmmo(_ammo + (clipSize * available));
	}

	if (_ammo >= _rules->getAmmoMax())
	{
		_ammo = _rules->getAmmoMax();
		_rearming = false;
	}

	return used;
}

/*
 * Fires a projectile from crafts weapon.
 * @return Pointer to the new projectile.
 */
CraftWeaponProjectile* CraftWeapon::fire() const
{
	CraftWeaponProjectile *p = new CraftWeaponProjectile();
	p->setType(this->getRules()->getProjectileType());
	p->setSpeed(this->getRules()->getProjectileSpeed());
	p->setAccuracy(this->getRules()->getAccuracy());
	p->setDamage(this->getRules()->getDamage());
	p->setRange(this->getRules()->getRange());
	return p;
}

}
