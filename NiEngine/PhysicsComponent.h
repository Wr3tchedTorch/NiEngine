#pragma once

#include "Component.h"

namespace ni {

class PhysicsComponent : public Component
{
public:
	virtual void update() = 0;
};

}