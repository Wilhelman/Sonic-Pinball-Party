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
	PhysBody* boss_hitbox;
	PhysBody* triangle_L;
	PhysBody* triangle_R;

	//Textures and SDL_Rects
	SDL_Rect rect_bg;
	SDL_Rect rect_tunnel;
	SDL_Rect rect_plunge_struct;
	SDL_Rect rect_rail;
	SDL_Rect rect_piece_rail;
	SDL_Rect rect_central_piece;
	SDL_Rect rect_cave;
	SDL_Rect rect_bush;
	SDL_Texture* pinball_spritesheet;

	//Pinball sounds
	uint hole_in_fx;
	uint hole_out_fx;
	uint triangle_fx;
	uint start_canon_fx;
	uint bonus_fx;
	uint lose_fx;
	uint five_colors_fx;
	uint four_dots_fx;
	uint win_fx;

	// Controls
	bool sensed, ball_lost, blit_tunnel_control, inside_start_canon, ball_in_rail, dot_1, dot_2, dot_3, dot_4, bossAlive, spawned;
	bool in_mid_rail, ball_created, inside_side_canon, canon_R_done, canon_L_done, in_cave_hole, in_mid_hole, in_right_hole , boss_defeated;

	//Ball position to teleport
	int ball_x, ball_y;

	//Animations
	Animation m_icon, start_canon, triangle_R_anim, triangle_L_anim, blue_arrow_cave , yellow_dot, white_circle, boss, bossHit, big_explosion;
	Animation blue_arrow_top_right, three_red_arrows, yellow_arrow_1, yellow_arrow_2, yellow_circle, red_circle, blue_circle, green_circle;
	Animation yellow_arrow_3, yellow_arrow_4, left_purple_arrow, right_purple_arrow, ball_anim, explosion, green_rhombus_3;
	Animation side_canon_L, side_canon_R, map_M, map_A, map_P, chip_C, chip_H, chip_I, chip_P, orange_bar, green_rhombus_1, green_rhombus_2;


	//Win_Fail_Conditions
	uint balls_left;

	//Time controls
	int current_time, hole_timer, bush_timer, yellow_dots_timer, circle_timer, color_circles, rhombus_count, hit_timer,
		rhombus_timer, boss_live, boss_timer;
};
