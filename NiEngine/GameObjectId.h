#pragma once

#include <cstdint>

struct GameObjectId
{
	uint32_t id_;

	bool operator==(const GameObjectId& other) const
	{
		return id_ == other.id_;
	}
};

