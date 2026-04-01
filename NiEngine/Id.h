#pragma once

#include <cstdint>
#include <type_traits>

template <typename Tag>
struct Id
{
	uint32_t id_ = 0;

	bool operator==(const Id& other) const
	{
		return id_ == other.id_;
	}

	Id& operator++()
	{
		id_++;
		return *this;
	}
};

template<typename Tag>
struct std::hash<Id<Tag>>
{
	size_t operator()(const Id<Tag>& id) const
	{
		return std::hash<uint32_t>{}(id.id_);
	}
};