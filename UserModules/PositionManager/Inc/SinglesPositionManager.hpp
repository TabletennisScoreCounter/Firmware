/*
 * SinglesPositionManager.hpp
 *
 *  Created on: 2017/09/17
 *      Author: Shuji
 */

#ifndef SINGLESPOSITIONMANAGER_HPP_
#define SINGLESPOSITIONMANAGER_HPP_

#include "../Inc/PlayerPositionManager.hpp"

class SinglesPositionManger : public PlayerPositionManager{
public:
	SinglesPositionManger(PlayerPositionManager::POSITION_t initialPosition) : PlayerPositionManager(initialPosition){};
	void rotatePosition();
	void rotatePositionInverse();
};


#endif /* SINGLESPOSITIONMANAGER_HPP_ */
