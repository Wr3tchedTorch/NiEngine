#pragma once

#include <NiEngine/UpdateComponent.h>
#include <NiEngine/GameObjectTag.h>
#include <NiEngine/Id.h>
#include <NiEngine/PlatformerCharacterPhysicsComponent.h>

class PlayerUpdateComponent : public ni::UpdateComponent
{
public:
	PlayerUpdateComponent(ni::Id<GameObjectTag> owner_id, ni::PlatformerCharacterPhysicsComponent& physics_comp);

	void Update() override;
};

