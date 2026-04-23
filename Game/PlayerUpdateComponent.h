#pragma once

#include <string>

#include <NiEngine/UpdateComponent.h>
#include <NiEngine/ComponentLocator.h>
#include <NiEngine/GameObjectTag.h>
#include <NiEngine/Id.h>
#include <NiEngine/AnimatedGraphicsComponent.h>

class PlayerUpdateComponent : public ni::UpdateComponent
{
public:
	PlayerUpdateComponent(ni::ComponentLocator& component_locator, ni::AnimatedGraphicsComponent& graphics, ni::Id<ni::GameObjectTag> owner_id);
	void Update() override;

private:
	inline static const int kAnimationRow = 12;
	inline static const std::string kJumpAnimationKey = "jump";
	inline static const std::string kWalkAnimationKey = "walk";

	void Jump();
};

