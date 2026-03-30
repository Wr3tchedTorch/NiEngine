#pragma once

#include "Component.h"

namespace ni {

class UpdateComponent : public Component
{
public:
	virtual void update() = 0;
};

}