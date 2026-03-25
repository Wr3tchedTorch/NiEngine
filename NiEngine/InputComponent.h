#pragma once

#include "Component.h"

namespace ni {

class InputComponent : public Component
{
public:	
	virtual void update() = 0;
};

}