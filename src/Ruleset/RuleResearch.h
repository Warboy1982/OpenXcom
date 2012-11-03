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
#ifndef OPENXCOM_RULERESEARCH_H
#define OPENXCOM_RULERESEARCH_H

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace OpenXcom
{
/**
   Represent one research project.
   Dependency and unlock. Dependency is the list of RuleResearch which must be discovered before a RuleResearch became available. 
   Unlock are used to immediately unlock a RuleResearch(even if not all dependency have been researched).
   Free is what research you gain from this project (ie: ship types from engineers) one will be added at random

   Fake ResearchProject. A RuleResearch is fake one, if t's cost is 0. They are used to to create check point in the dependency tree.
   For example if we have a Research E which need either A & B or C & D. We create 2 fake research project:
   * F which need A & B
   * G which need C & D
   both F and G can unlock E.
*/
class RuleResearch
{
 private:
	std::string _name;
	int _cost, _points;
	std::vector<std::string> _dependencies, _unlocks, _free, _requirement;
	bool _needItem;
public:
	RuleResearch(const std::string & name);
	/// Loads the research from YAML.
	void load(const YAML::Node& node);
	/// Saves the research to YAML.
	void save(YAML::Emitter& out) const;
	/// Get time needed to discover this ResearchProject
	int getCost() const;
	/// Get points gained for this ResearchProject
	int getPoints() const;
	/// Get the research name
	const std::string & getName () const;
	/// Get the research dependencies
	const std::vector<std::string> & getDependencies () const;
	/// Does this ResearchProject need a corresponding Item to be researched ?
	bool needItem() const;
	/// Get the list of ResearchProjects unlocked by this research
	const std::vector<std::string> & getUnlocked () const;
	/// get the list of ResearcgProjects granted by this research
	const std::vector<std::string> & getFree() const;
	const std::vector<std::string> & getRequirement() const;
};
}

#endif
