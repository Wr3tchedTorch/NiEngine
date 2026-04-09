#pragma once

#include <NiEngine/Component.h>

namespace ni {

class UpdateComponent : public Component
{
public:
	virtual void Update() = 0;
};

}