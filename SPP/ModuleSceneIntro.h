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

	//Main functionals calls
	void spawnBall();
	void setWalls();
	void setSensors();

public:

	//PhysBody variables
	p2List<PhysBody*> balls;
	p2List<PhysBody*> pinball_walls;
	p2List<PhysBody*> tunnel_walls;
	p2List<PhysBody*> sensors;
	PhysBody* rail;
	PhysBody* rail_mini_sensor;
	PhysBody* triangle_L;
	PhysBody* triangle_R;

	//Textures and SDL_Rects
	SDL_Rect rect_ball;
	SDL_Rect rect_bg;
	SDL_Rect rect_tunnel;
	SDL_Rect rect_plunge_struct;
	SDL_Rect rect_rail;
	SDL_Rect rect_piece_rail;
	SDL_Rect rect_central_piece;
	SDL_Rect rect_cave;

	SDL_Texture* pinball_spritesheet;

	//Pinball sounds
	uint bonus_fx;
	uint triangle_fx;
	uint start_canon_fx;

	// Controls
	bool sensed, ball_lost, blit_tunnel_control, inside_start_canon, ball_in_rail;
	bool in_mid_rail, ball_created, inside_side_canon, canon_R_done, canon_L_done;

	//Animations
	Animation m_icon;
	Animation start_canon;
	Animation triangle_R_anim;
	Animation triangle_L_anim;
	Animation blue_arrow_cave;
	Animation blue_arrow_top_right;
	Animation three_red_arrows;
	Animation yellow_arrow_1;
	Animation yellow_arrow_2;
	Animation yellow_arrow_3;
	Animation yellow_arrow_4;
	Animation left_purple_arrow;
	Animation right_purple_arrow;
	Animation side_canon_L;
	Animation side_canon_R;

	//Win_Fail_Conditions
	uint balls_left;
};
