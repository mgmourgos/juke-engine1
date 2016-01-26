#include "Game.h"
#include <SDL.h>
#include <math.h>
#include "Graphics.h"
#include "Sprite.h"
#include <iostream>
#include "InputHandler.h"
#include "EnvironmentEntity.h"


namespace {
	const int FPS = 60;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	eventLoop();
	AllSprites.clear();
}

Game::~Game() {
	delete player;
	SDL_Quit();
}

void Game::eventLoop() {

	Graphics graphics;
	InputHandler input;
	Command* command;
	
	Sprite BackGround(graphics, "Files/Background.bmp", 0, 0, 640, 432);
	//player = new Player(graphics, 320, 240);
	std::shared_ptr<Player> player = std::make_shared<Player>(graphics, 320, 240);
	entity_queue.push_back(player);
	gameActor_queue.push_back(player);
	std::shared_ptr<EnvironmentEntity> platform = std::make_shared<EnvironmentEntity>(graphics, 350, 350, 50, 20);
	entity_queue.push_back(platform);
	platform = std::make_shared<EnvironmentEntity>(graphics, 400, 240, 100, 20);
	entity_queue.push_back(platform);

	AllSprites.push_back(BackGround);
	
	bool running = true;
	int last_update_time = SDL_GetTicks();

	while (running) {
		const int start_time_ms = SDL_GetTicks();
		input.beginNewFrame();
		command = NULL;





		running = input.getCommandsFromInput(command_queue);
		//give commands the id of gameactor to execute
		//ai.getCmds(command_queue)
		//command_queue.push_back()

		executeCommands();

		const int current_time_ms = SDL_GetTicks();
		update(current_time_ms - last_update_time);
		last_update_time = current_time_ms;

		draw(graphics);
		





		const int ms_per_frame = 1000/*ms*/ / FPS;
		const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
		if (elapsed_time_ms < ms_per_frame) {
			SDL_Delay(ms_per_frame - elapsed_time_ms);   //delays for 1/60th of a second //10 ms or less of granularity
		}
	}//while running
}

void Game::executeCommands() {
	for (auto command : command_queue) {

		command->execute(*gameActor_queue[0]);
	}
	command_queue.clear();
}

void Game::draw(Graphics& graphics) {
	graphics.clear();
	for (int i = 0; i < AllSprites.size(); i++) {
		AllSprites[i].draw(graphics, 0, 0);
	}
	for (auto &entity : entity_queue) {
		entity->draw(graphics);
	}
	//player->draw(graphics);
	graphics.flip();
}

void Game::update(int elapsed_time_ms) {
	for (auto &entity : entity_queue) {
		entity->update(elapsed_time_ms);
	}
	//player->update(elapsed_time_ms);
}
