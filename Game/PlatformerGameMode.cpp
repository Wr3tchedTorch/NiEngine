#include "PlatformerGameMode.h"

#include <types.h>
#include <memory>
#include <utility>
#include <format>
#include <string>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <NiEngine/Converter.h>
#include <NiEngine/BitmapStore.h>
#include <NiEngine/GameMode.h>
#include <NiEngine/WipeScreenTransition.h>
#include <NiEngine/GameModeController.h>
#include <NiEngine/TextFadeScreenTransition.h>
#include <NiEngine/Text.h>
#include <NiEngine/HUDComponent.h>

#include "PlatformerObjectFactory.h"


PlatformerGameMode::PlatformerGameMode() : hud_(sf::Color::Transparent, { {64, 64}, {100, 50} }, {0, 0}, { 10, 10 }, false, 3)
{
	auto level_text = std::make_unique<ni::Text>("fonts/ARCADECLASSIC.TTF", "Level 1", sf::Color::White, 40);
	level_text->SetTextOutline(2, sf::Color::Black);
	int text_component_index = hud_.AddComponent(std::move(level_text));

	ni::Converter::pixels_per_meters_ = 16;

	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = { 0.0f, 9.8f };
	GetPhysicsEngine().CreateWorld(world_def);
	
	auto factory = std::make_unique<PlatformerObjectFactory>();
	level_.RegisterObjectFactory(std::move(factory));

	level_.LoadNextLevel(*this);
	world_camera_.FitTo(level_.GetCurrentTilemap().GetBounds());

	engine_title_transition_.Init(2, "\t\t NI   Engine\nPor  Eric  Moura", "fonts/ARCADECLASSIC.TTF", 50, sf::Color::White, sf::Color::Black, transitions_camera_.GetView().getSize());
	engine_title_transition_.OnTransitionFinished([this]() {
		current_transition_->Play(true);
	});
	engine_title_transition_.Play();
	
	current_transition_ = std::make_unique<ni::WipeScreenTransition>(.8f, transitions_camera_.GetView().getSize(), false, sf::Color::Black);
	current_transition_->OnTransitionCoveredScreen([this, text_component_index]() {
		if (restart_level_)
		{
			level_.ReloadLevel(*this);
			restart_level_ = false;
		}
		else if (load_next_level_)
		{
			level_.LoadNextLevel(*this);
			load_next_level_ = false;

			auto text_component = GetLevelTextHUD(text_component_index);
			if (text_component)
			{
				std::string level_string = std::format("Level {}", level_.GetCurrentLevelIndex());
				text_component->SetTextString(level_string);
			}
		}
	});	

	current_transition_->OnTransitionFinished([this]() {
		transitioning_ = false;
	});
}

void PlatformerGameMode::PrepareToLoadNextLevel()
{
	load_next_level_ = true;
}

void PlatformerGameMode::RestartLevel()
{
	restart_level_ = true;
}

void PlatformerGameMode::Update(ni::GameModeController& controller)
{
	if ((restart_level_ || load_next_level_) && !transitioning_)
	{
		current_transition_->Play();
		transitioning_ = true;
		return;
	}
	GameMode::Update(controller);
}

void PlatformerGameMode::Render(sf::RenderTarget& target, sf::RenderStates states, BitmapStore& store)
{
	world_camera_.ApplyTo(target);

	level_.RenderTilemap(target, states, store);
	component_store_.Render(target, states, store);

	hud_camera_.ApplyTo(target);
	hud_.Render(target, states, store);

	transitions_camera_.ApplyTo(target);

	if (current_transition_)
	{
		current_transition_->Render(target, states, store);
	}
	engine_title_transition_.Render(target, states, store);
}

ni::Text* PlatformerGameMode::GetLevelTextHUD(int component_index) const
{
	ni::HUDComponent* hud_component = hud_.GetComponentByIndex(component_index);
	if (!hud_component)
	{
		return nullptr;
	}
	auto text_component = static_cast<ni::Text*>(hud_component);
	if (!text_component)
	{
		return nullptr;
	}
	return text_component;
}
