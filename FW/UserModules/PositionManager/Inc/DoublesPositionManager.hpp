/*
 * PositionManager.hpp
 *
 *  Created on: 2017/09/16
 *      Author: Shuji
 */

#ifndef DOUBLESPOSITIONMANAGER_HPP_
#define DOUBLESPOSITIONMANAGER_HPP_

#include "PlayerPositionManager.hpp"

class DoublesPositionManger : public PlayerPositionManager{
public:
	DoublesPositionManger(PlayerPositionManager::POSITION_t initialPosition) : PlayerPositionManager(initialPosition){};
	void rotatePosition();
	void rotatePositionInverse();
};


#endif /* DOUBLESPOSITIONMANAGER_HPP_ */
