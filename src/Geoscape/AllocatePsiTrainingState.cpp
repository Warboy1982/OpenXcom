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
#include <sstream>
#include "PsiTrainingState.h"
#include "AllocatePsiTrainingState.h"
#include "../Engine/Game.h"
#include "../Resource/ResourcePack.h"
#include "../Engine/Language.h"
#include "../Engine/Palette.h"
#include "../Interface/TextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/Base.h"
#include "../Interface/TextList.h"
#include "GeoscapeState.h"
#include "../Savegame/Soldier.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the Psi Training screen.
 * @param game Pointer to the core game.
 */
AllocatePsiTrainingState::AllocatePsiTrainingState(Game *game, Base *base) : State(game)
{
	// Create objects
	_window = new Window(this, 320, 200, 0, 0);
	_txtTitle = new Text(300, 16, 16, 8);
	_txtTraining = new Text(32, 16, 34, 180);
	_btnOk = new TextButton(120, 16, 100, 176);
	_lstSoldiers = new TextList(287, 128, 8, 40);
	
	// Set palette
	_game->setPalette(_game->getResourcePack()->getPalette("PALETTES.DAT_1")->getColors());
	_game->setPalette(_game->getResourcePack()->getPalette("BACKPALS.DAT")->getColors(Palette::blockOffset(7)), Palette::backPos, 16);

	add(_window);
	add(_btnOk);
	add(_txtTitle);
	add(_txtTraining);
	add(_lstSoldiers);

	// Set up objects
	_window->setColor(Palette::blockOffset(15)+8);
	_window->setBackground(_game->getResourcePack()->getSurface("BACK01.SCR"));

	_btnOk->setColor(Palette::blockOffset(8)+5);
	_btnOk->setText(_game->getLanguage()->getString("STR_OK"));
	_btnOk->onMouseClick((ActionHandler)&PsiTrainingState::btnOkClick);
	
	_txtTitle->setColor(Palette::blockOffset(8)+5);
	_txtTitle->setBig();
	_txtTitle->setText(base->getName());

	_txtTraining->setColor(Palette::blockOffset(8)+5);
	_txtTraining->setText(_game->getLanguage()->getString("STR_IN_TRAINING"));
	
	_lstSoldiers->setColor(Palette::blockOffset(15)+1);
	_lstSoldiers->setArrowColor(Palette::blockOffset(13)+10);
	_lstSoldiers->setArrowColumn(193, ARROW_VERTICAL);
	_lstSoldiers->setColumns(4, 162, 58, 40, 20);
	_lstSoldiers->setSelectable(true);
	_lstSoldiers->setBackground(_window);
	_lstSoldiers->setMargin(2);
	_lstSoldiers->onLeftArrowPress((ActionHandler)&AllocatePsiTrainingState::lstItemsLeftArrowPress);
	_lstSoldiers->onLeftArrowRelease((ActionHandler)&AllocatePsiTrainingState::lstItemsLeftArrowRelease);
	_lstSoldiers->onLeftArrowClick((ActionHandler)&AllocatePsiTrainingState::lstItemsLeftArrowClick);
	_lstSoldiers->onRightArrowPress((ActionHandler)&AllocatePsiTrainingState::lstItemsRightArrowPress);
	_lstSoldiers->onRightArrowRelease((ActionHandler)&AllocatePsiTrainingState::lstItemsRightArrowRelease);
	_lstSoldiers->onRightArrowClick((ActionHandler)&AllocatePsiTrainingState::lstItemsRightArrowClick);
	for(std::vector<Soldier*>::const_iterator s = base->getSoldiers()->begin(); s != base->getSoldiers()->end(); ++s)
	{
		if ((*s)->getWoundRecovery() == 0)
		{
			_soldiers.push_back(*s);
			std::string _training = "STR_NO";
			if((*s)->isInPsiTraining())
				_training = "STR_YES";
			_lstSoldiers->addRow(4, (*s)->getName().c_str(),"" ,"" ,_training);
		}
	}
}
/**
 *
 */
AllocatePsiTrainingState::~AllocatePsiTrainingState()
{

}

/**
 * Resets the palette.
 */
void AllocatePsiTrainingState::init()
{
	_game->setPalette(_game->getResourcePack()->getPalette("BACKPALS.DAT")->getColors(Palette::blockOffset(7)), Palette::backPos, 16);
}

/**
 * Returns to the previous screen.
 * @param action Pointer to an action.
 */
void AllocatePsiTrainingState::btnOkClick(Action *action)
{
	_game->popState();
	_game->pushState (new PsiTrainingState(_game));
}

}
