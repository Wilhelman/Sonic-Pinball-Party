#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"

class PhysBody;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	p2List<PhysBody*> balls;
	PhysBody* left_flipper;
	PhysBody* right_flipper;


	//SDL_Rect rect_ball;
	//SDL_Texture* bg;
};