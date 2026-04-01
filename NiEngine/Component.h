#pragma once

#include "Id.h"
#include "GameObjectTag.h"

namespace ni {

class Component
{
protected:
	Id<GameObjectTag> owner_id_;
};

}