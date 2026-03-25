#pragma once

#include "GameObjectId.h"

namespace ni {

class Component
{
protected:
	GameObjectId owner_id_;

public:
	Component(GameObjectId owner) : owner_id_(owner)
	{
	};
};

}