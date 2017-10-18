#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> pinball_struct;
	p2List<PhysBody*> balls;
	SDL_Texture* ball;

	//Test
	SDL_Rect rect_bg;
	SDL_Rect rect_ball;
	SDL_Texture* bg;
	//Test

	PhysBody* sensor;
	bool sensed;

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
};
