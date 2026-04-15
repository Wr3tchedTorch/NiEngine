#include "PlayerUpdateComponent.h"

#include <NiEngine/GameObjectTag.h>
#include <NiEngine/Id.h>
#include <NiEngine/PlatformerCharacterPhysicsComponent.h>
#include <NiEngine/ServiceLocator.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

PlayerUpdateComponent::PlayerUpdateComponent(ni::Id<GameObjectTag> owner_id, ni::PlatformerCharacterPhysicsComponent& physics_comp)
{
	owner_id_ = owner_id;	

	ni::ServiceLocator::Instance().GetEventDispatcher().OnKeyPressed([&physics_comp](const sf::Event::KeyPressed& event) 
	{
		float throttle = (int)(event.scancode == sf::Keyboard::Scancode::D) - (int)(event.scancode == sf::Keyboard::Scancode::A);
		
		physics_comp.SolveMove(throttle);

		if (event.scancode == sf::Keyboard::Scancode::Space)
		{
			physics_comp.Jump();
		}
	});
}

void PlayerUpdateComponent::Update()
{
}
