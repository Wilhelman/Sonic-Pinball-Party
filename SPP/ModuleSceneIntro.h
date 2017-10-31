#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

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

	//PhysBody variables
	p2List<PhysBody*> balls;
	p2List<PhysBody*> pinball_walls;
	p2List<PhysBody*> tunnel_walls;
	p2List<PhysBody*> sensors;
	PhysBody* rail;
	PhysBody* triangle_L;
	PhysBody* triangle_R;

	//Textures and SDL_Rects
	SDL_Texture* pinball_spritesheet;

	SDL_Rect rect_ball;
	SDL_Rect rect_bg;
	SDL_Rect rect_triangle_R;
	SDL_Rect rect_triangle_L;
	SDL_Rect rect_tunnel;
	SDL_Rect rect_plunge_struct;
	SDL_Rect rect_rail;
	SDL_Rect rect_piece_rail;
	SDL_Rect rect_central_piece;
	
	// Controls and other stuff

	uint bonus_fx;
	p2Point<int> ray;

	bool ray_on;
	bool sensed;
	bool ball_lost;
	bool blit_tunnel_control;

	//Animations
	Animation m_icon;

	//Win_Fail_Conditions
	uint balls_left;
};
