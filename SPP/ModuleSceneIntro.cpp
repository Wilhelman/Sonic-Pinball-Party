#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	pinball_spritesheet = NULL;

	// Here we set up all animations in the scene

	// M icon

	m_icon.PushBack({ 344, 1144, 60, 36 });
	m_icon.PushBack({ 1826, 555, 60, 36 });
	m_icon.loop = true;
	m_icon.speed = 0.07f;

	//Start canon

	start_canon.PushBack({ 575, 1499, 62, 64 });
	start_canon.PushBack({ 676, 1499, 62, 64 });
	start_canon.PushBack({ 801, 1499, 62, 64 });
	start_canon.PushBack({ 575, 1499, 62, 64 });
	start_canon.loop = false;
	start_canon.speed = 0.0f;

	// Bouncing triangles

	triangle_L_anim.PushBack({ 474, 1100, 42, 80 });
	triangle_L_anim.PushBack({ 526, 1100, 42, 80 });
	triangle_L_anim.loop = true;
	triangle_L_anim.speed = 0.1f;

	triangle_R_anim.PushBack({ 578, 1100, 42, 80 });
	triangle_R_anim.PushBack({ 630, 1100, 42, 80 });
	triangle_R_anim.loop = true;
	triangle_R_anim.speed = 0.1f;

	// Arrows

	blue_arrow_cave.PushBack({ 163, 1475, 46, 38 });
	blue_arrow_cave.PushBack({ 163, 1517, 46, 38 });
	blue_arrow_cave.loop = true;
	blue_arrow_cave.speed = 0.07f;

	three_red_arrows.PushBack({ 243, 1529, 70, 24 });
	three_red_arrows.PushBack({ 243, 1555, 70, 24 });
	three_red_arrows.loop = true;
	three_red_arrows.speed = 0.07f;

	blue_arrow_top_right.PushBack({ 350, 1456, 18, 24 });
	blue_arrow_top_right.PushBack({ 350, 1485, 18, 24 });
	blue_arrow_top_right.loop = true;
	blue_arrow_top_right.speed = 0.07f;

	yellow_arrow_1.PushBack({ 348, 1590, 24, 36 });
	yellow_arrow_1.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_1.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_1.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_1.loop = true;
	yellow_arrow_1.speed = 0.07f;

	yellow_arrow_2.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_2.PushBack({ 348, 1590, 24, 36 });
	yellow_arrow_2.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_2.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_2.loop = true;
	yellow_arrow_2.speed = 0.07f;

	yellow_arrow_3.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_3.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_3.PushBack({ 348, 1590, 24, 36 });
	yellow_arrow_3.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_3.loop = true;
	yellow_arrow_3.speed = 0.07f;

	yellow_arrow_4.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_4.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_4.PushBack({ 348, 1630, 24, 36 });
	yellow_arrow_4.PushBack({ 348, 1590, 24, 36 });
	yellow_arrow_4.loop = true;
	yellow_arrow_4.speed = 0.07f;

	left_purple_arrow.PushBack({ 28, 1676, 30, 28 });
	left_purple_arrow.PushBack({ 28, 1624, 30, 28 });
	left_purple_arrow.loop = true;
	left_purple_arrow.speed = 0.07f;

	right_purple_arrow.PushBack({ 382, 1676, 30, 28 });
	right_purple_arrow.PushBack({ 28, 1624, 30, 28 });
	right_purple_arrow.loop = true;
	right_purple_arrow.speed = 0.07f;

	// Side canons

	side_canon_L.PushBack({ 109, 1246, 34, 42 });
	side_canon_L.PushBack({ 39, 1246, 34, 42 });
	side_canon_L.PushBack({ 109, 1246, 34, 42 });
	side_canon_L.loop = false;
	side_canon_L.speed = 0.0f;

	side_canon_R.PushBack({ 109, 1246, 34, 42 });
	side_canon_R.PushBack({ 39, 1246, 34, 42 });
	side_canon_R.PushBack({ 109, 1246, 34, 42 });
	side_canon_R.loop = false;
	side_canon_R.speed = 0.0f;

	//Map Letters

	map_M.PushBack({ 40, 1728, 38, 30 });
	map_M.PushBack({ 91, 1730, 38, 30 });
	map_M.PushBack({ 91, 1730, 38, 30 });
	map_M.PushBack({ 91, 1730, 38, 30 });
	map_M.PushBack({ 40, 1728, 38, 30 });
	map_M.PushBack({ 91, 1730, 38, 30 });
	map_M.PushBack({ 40, 1728, 38, 30 });
	map_M.PushBack({ 91, 1730, 38, 30 });
	map_M.loop = true;
	map_M.speed = 0.04f;

	map_A.PushBack({ 91, 1730, 38, 30 });
	map_A.PushBack({ 40, 1760, 38, 30 });
	map_A.PushBack({ 91, 1730, 38, 30 });
	map_A.PushBack({ 91, 1730, 38, 30 });
	map_A.PushBack({ 40, 1760, 38, 30 });
	map_A.PushBack({ 91, 1730, 38, 30 });
	map_A.PushBack({ 40, 1760, 38, 30 });
	map_A.PushBack({ 91, 1730, 38, 30 });
	map_A.loop = true;
	map_A.speed = 0.04f;

	// Chip letters

	map_P.PushBack({ 91, 1730, 38, 30 });
	map_P.PushBack({ 91, 1730, 38, 30 });
	map_P.PushBack({ 40, 1792, 38, 30 });
	map_P.PushBack({ 91, 1730, 38, 30 });
	map_P.PushBack({ 40, 1792, 38, 30 });
	map_P.PushBack({ 91, 1730, 38, 30 });
	map_P.PushBack({ 40, 1792, 38, 30 });
	map_P.PushBack({ 91, 1730, 38, 30 });
	map_P.loop = true;
	map_P.speed = 0.04f;

	chip_C.PushBack({ 0, 1458, 32, 32 });
	chip_C.PushBack({ 74, 1562, 32, 32 });
	chip_C.PushBack({ 74, 1562, 32, 32 });
	chip_C.PushBack({ 74, 1562, 32, 32 });
	chip_C.PushBack({ 74, 1562, 32, 32 });
	chip_C.PushBack({ 0, 1458, 32, 32 });
	chip_C.PushBack({ 74, 1562, 32, 32 });
	chip_C.PushBack({ 0, 1458, 32, 32 });
	chip_C.PushBack({ 74, 1562, 32, 32 });
	chip_C.loop = true;
	chip_C.speed = 0.04f;

	chip_H.PushBack({ 74, 1562, 32, 32 });
	chip_H.PushBack({ 6, 1494, 32, 32 });
	chip_H.PushBack({ 74, 1562, 32, 32 });
	chip_H.PushBack({ 74, 1562, 32, 32 });
	chip_H.PushBack({ 74, 1562, 32, 32 });
	chip_H.PushBack({ 6, 1494, 32, 32 });
	chip_H.PushBack({ 74, 1562, 32, 32 });
	chip_H.PushBack({ 6, 1494, 32, 32 });
	chip_H.PushBack({ 74, 1562, 32, 32 });
	chip_H.loop = true;
	chip_H.speed = 0.04f;

	chip_I.PushBack({ 74, 1562, 32, 32 });
	chip_I.PushBack({ 74, 1562, 32, 32 });
	chip_I.PushBack({ 18, 1528, 32, 32 });
	chip_I.PushBack({ 74, 1562, 32, 32 });
	chip_I.PushBack({ 74, 1562, 32, 32 });
	chip_I.PushBack({ 18, 1528, 32, 32 });
	chip_I.PushBack({ 74, 1562, 32, 32 });
	chip_I.PushBack({ 18, 1528, 32, 32 });
	chip_I.PushBack({ 74, 1562, 32, 32 });
	chip_I.loop = true;
	chip_I.speed = 0.04f;

	chip_P.PushBack({ 74, 1562, 32, 32 });
	chip_P.PushBack({ 74, 1562, 32, 32 });
	chip_P.PushBack({ 74, 1562, 32, 32 });
	chip_P.PushBack({ 32, 1560, 32, 32 });
	chip_P.PushBack({ 74, 1562, 32, 32 });
	chip_P.PushBack({ 32, 1560, 32, 32 });
	chip_P.PushBack({ 74, 1562, 32, 32 });
	chip_P.PushBack({ 32, 1560, 32, 32 });
	chip_P.PushBack({ 74, 1562, 32, 32 });
	chip_P.loop = true;
	chip_P.speed = 0.04f;

	// Orange bar

	orange_bar.PushBack({ 555, 1710, 62, 62 });
	orange_bar.PushBack({ 453, 1698, 62, 62 });
	orange_bar.loop = true;
	orange_bar.speed = 0.07f;

	// Ball

	ball_anim.PushBack({ 0, 1418, 28, 28 });
	ball_anim.PushBack({ 38, 1418, 28, 28 });
	ball_anim.PushBack({ 76, 1418, 28, 28 });
	ball_anim.PushBack({ 114, 1418, 28, 28 });
	ball_anim.loop = true;
	ball_anim.speed = 0.0f;

	// Dots and circles

	yellow_dot.PushBack({ 348, 1630, 21, 22 });
	yellow_dot.PushBack({ 962, 1050, 21, 22 });
	yellow_dot.loop = false;
	yellow_dot.speed = 0.1f;

	white_circle.PushBack({ 348, 1630, 28, 28 });
	white_circle.PushBack({ 248, 1138, 28, 28 });
	white_circle.loop = false;
	white_circle.speed = 0.1f;

	yellow_circle.PushBack({ 348, 1630, 28, 28 });
	yellow_circle.PushBack({ 292, 1108, 28, 28 });
	yellow_circle.loop = false;
	yellow_circle.speed = 0.1f;

	red_circle.PushBack({ 348, 1630, 28, 28 });
	red_circle.PushBack({ 276, 1150, 28, 28 });
	red_circle.loop = false;
	red_circle.speed = 0.1f;

	blue_circle.PushBack({ 348, 1630, 28, 28 });
	blue_circle.PushBack({ 304, 1138, 28, 28 });
	blue_circle.loop = false;
	blue_circle.speed = 0.1f;

	green_circle.PushBack({ 348, 1630, 28, 28 });
	green_circle.PushBack({ 260, 1108, 28, 28 });
	green_circle.loop = false;
	green_circle.speed = 0.1f;

	// Explosion

	explosion.PushBack({ 234, 1263, 30, 30 });
	explosion.PushBack({ 270, 1258, 30, 30 });
	explosion.loop = false;
	explosion.speed = 0.05f;

	// Green rhombus

	green_rhombus_1.PushBack({ 348, 1630, 32, 30 });
	green_rhombus_1.PushBack({ 162, 1700, 32, 30 });
	green_rhombus_1.loop = false;
	green_rhombus_1.speed = 0.1f;

	green_rhombus_2.PushBack({ 348, 1630, 32, 30 });
	green_rhombus_2.PushBack({ 162, 1700, 32, 30 });
	green_rhombus_2.loop = false;
	green_rhombus_2.speed = 0.1f;

	green_rhombus_3.PushBack({ 348, 1630, 32, 30 });
	green_rhombus_3.PushBack({ 162, 1700, 32, 30 });
	green_rhombus_3.loop = false;
	green_rhombus_3.speed = 0.1f;

	// Boss

	boss.PushBack({ 0, 874, 116, 126 });
	boss.PushBack({ 116, 874, 116, 126 });
	boss.PushBack({ 226, 874, 116, 126 });
	boss.loop = true;
	boss.speed = 0.1f;

	//Boss explosion

	big_explosion.PushBack({ 662, 1656, 94, 94 });
	big_explosion.PushBack({ 815, 1656, 94, 94 });
	big_explosion.PushBack({ 984, 1656, 94, 94 });
	big_explosion.PushBack({ 1138, 1656, 94, 94 });
	big_explosion.loop = true;
	big_explosion.speed = 0.1f;

	// Boss hitted

	bossHit.PushBack({ 352, 874, 116, 126 });
	bossHit.loop = true;
	bossHit.speed = 0.1f;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
	balls_left = boss_live = 3;
	App->ui->score = 0;
	current_time = hole_timer = bush_timer = yellow_dots_timer = circle_timer = hit_timer
		= rhombus_count = rhombus_timer = boss_timer = color_circles = monster_roar_fx = hit_wall_fx = 0;

	if (!App->audio->IsEnabled() && App->audio->isAudioDeviceOpened) {
		App->audio->Enable();
		App->audio->Init();
	}

	if (!App->textures->IsEnabled()) {
		App->textures->Enable();
		App->textures->Init();
	}

	if (!App->ui->IsEnabled()) {
		App->ui->Enable();
		App->ui->Start();
	}

	LOG("Loading Intro assets");
	bool ret = true;
	blit_tunnel_control = inside_side_canon = canon_R_done = canon_L_done = in_mid_rail = dot_1 = dot_2 = dot_3 = dot_4 = bossAlive = spawned
		= ball_lost = inside_start_canon = ball_created = ball_in_rail = in_cave_hole = in_mid_hole = in_right_hole = boss_defeated = false;


	App->renderer->camera.x = App->renderer->camera.y = 0;

	if (App->audio->isAudioDeviceOpened) 
	{
		hole_in_fx = App->audio->LoadFx("audio/sound_fx/hole_in.wav");
		hole_out_fx = App->audio->LoadFx("audio/sound_fx/hole_out.wav");
		triangle_fx = App->audio->LoadFx("audio/sound_fx/bouncing_triangle.wav");
		start_canon_fx = App->audio->LoadFx("audio/sound_fx/canon_shot.wav");
		lose_fx = App->audio->LoadFx("audio/sound_fx/lose.wav");
		five_colors_fx = App->audio->LoadFx("audio/sound_fx/five_colors.wav");
		bonus_fx = App->audio->LoadFx("audio/sound_fx/yellow_dot.wav");
		win_fx = App->audio->LoadFx("audio/sound_fx/win.wav");
		monster_roar_fx = App->audio->LoadFx("audio/sound_fx/monster_roar.wav");
		hit_wall_fx = App->audio->LoadFx("audio/sound_fx/hit_wall.wav");
		four_dots_fx = App->audio->LoadFx("audio/sound_fx/four_dots.wav");

		if (!App->audio->PlayMusic("audio/music/Nightmaren.ogg"))
			ret = false;
	}

	pinball_spritesheet = App->textures->Load("pinball/pinball_sonic_spritesheet.png");

	if (pinball_spritesheet == nullptr) 
	{
		LOG("Cannot load the animations spritesheet in SceneIntro");
		ret = false;
	}

	// ---- Setting up SDL_Rect attributes ----

	rect_bg.h = SCREEN_HEIGHT;
	rect_bg.w = SCREEN_WIDTH;
	rect_bg.x = 0;
	rect_bg.y = 0;

	rect_tunnel.h = 428;
	rect_tunnel.w = 512;
	rect_tunnel.x = 522;
	rect_tunnel.y = 0;

	rect_plunge_struct.h = 384;
	rect_plunge_struct.w = 48;
	rect_plunge_struct.x = 990;
	rect_plunge_struct.y = 464;

	rect_rail.h = 632;
	rect_rail.w = 308;
	rect_rail.x = 1248;
	rect_rail.y = 138;

	rect_bush.h = 40;
	rect_bush.w = 42;
	rect_bush.x = 186;
	rect_bush.y = 1248;

	rect_piece_rail.h = 84;
	rect_piece_rail.w = 64;
	rect_piece_rail.x = 1147;
	rect_piece_rail.y = 458;

	rect_central_piece.h = 110;
	rect_central_piece.w = 112;
	rect_central_piece.x = 872;
	rect_central_piece.y = 1348;

	rect_cave.x = 949;
	rect_cave.y = 1137;
	rect_cave.w = 84;
	rect_cave.h = 44;

	// ------- Setting up wall chains -------
	setWalls();

	// ----- Creating sensors for the ball -----
	setSensors();

	App->player->Enable();
	
	// Spawning ball
	spawnBall();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	for (p2List_item<PhysBody*>* ball_item = balls.getFirst(); ball_item != NULL; ball_item = ball_item->next)
	{
		App->physics->world->DestroyBody(ball_item->data->body);
	}

	for (p2List_item<PhysBody*>* wall_item = pinball_walls.getFirst(); wall_item != NULL; wall_item = wall_item->next)
	{
		App->physics->world->DestroyBody(wall_item->data->body);
	}

	for (p2List_item<PhysBody*>* tunnel_item = tunnel_walls.getFirst(); tunnel_item != NULL; tunnel_item = tunnel_item->next)
	{
		App->physics->world->DestroyBody(tunnel_item->data->body);
	}

	for (p2List_item<PhysBody*>* sensors_item = sensors.getFirst(); sensors_item != NULL; sensors_item = sensors_item->next)
	{
		App->physics->world->DestroyBody(sensors_item->data->body);
	}

	if (triangle_L != NULL)
	{
		App->physics->world->DestroyBody(triangle_L->body);
		triangle_L = NULL;
	}

	if (triangle_R != NULL)
	{
		App->physics->world->DestroyBody(triangle_R->body);
		triangle_R = NULL;
	}

	if (rail != NULL)
	{
		App->physics->world->DestroyBody(rail->body);
		rail = NULL;
	}

	if (rail_mini_sensor!= NULL)
	{
		App->physics->world->DestroyBody(rail_mini_sensor->body);
		rail_mini_sensor = NULL;
	}
	

	App->player->CleanUp();
	App->player->Disable();

	App->ui->CleanUp();
	App->ui->Disable();

	App->audio->CleanUp();
	App->audio->Disable();

	App->textures->CleanUp();
	App->textures->Disable();

	balls.clear();
	pinball_walls.clear();
	sensors.clear();
	tunnel_walls.clear();

	return true;
}

update_status ModuleSceneIntro::Update()
{
	// Here we update EVERYTHING that happens in scene

	// Blitting background
	App->renderer->Blit(pinball_spritesheet, 0, 0, &rect_bg, 1.0f);
	
	// Blitting Bouncing triangles
	App->renderer->Blit(pinball_spritesheet, 113, 621, &triangle_L_anim.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 325, 621, &triangle_R_anim.GetCurrentFrame(), 1.0f);

	// Blitting Arrows
	App->renderer->Blit(pinball_spritesheet, 191, 227, &blue_arrow_cave.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 271, 280, &three_red_arrows.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 378, 208, &blue_arrow_top_right.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 376, 342, &yellow_arrow_1.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 392, 306, &yellow_arrow_2.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 408, 270, &yellow_arrow_3.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 424, 234, &yellow_arrow_4.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 56, 428, &left_purple_arrow.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 410, 428, &right_purple_arrow.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 210, 722, &m_icon.GetCurrentFrame(), 1.0f);

	// Blitting Dots
	if (dot_1) {
		App->renderer->Blit(pinball_spritesheet, 38, 606, &yellow_dot.GetCurrentFrame(), 1.0f);
	}

	if (dot_2) {
		App->renderer->Blit(pinball_spritesheet, 86, 612, &yellow_dot.GetCurrentFrame(), 1.0f);
	}

	if (dot_3) {
		App->renderer->Blit(pinball_spritesheet, 374, 612, &yellow_dot.GetCurrentFrame(), 1.0f);
	}

	if (dot_4) {
		App->renderer->Blit(pinball_spritesheet, 422, 606, &yellow_dot.GetCurrentFrame(), 1.0f);
	}

	if (dot_1 && dot_2 && dot_3 && dot_4 && yellow_dots_timer == 0) {
		yellow_dot.loop = true;
		yellow_dots_timer = SDL_GetTicks();
		yellow_dot.speed = 0.01f;
		App->audio->PlayFx(four_dots_fx);
	}

	if (yellow_dots_timer + 2000 > current_time && (dot_1 && dot_2 && dot_3 && dot_4)) {
		App->renderer->Blit(pinball_spritesheet, 38, 606, &yellow_dot.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 86, 612, &yellow_dot.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 374, 612, &yellow_dot.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 422, 606, &yellow_dot.GetCurrentFrame(), 1.0f);
	}
	else if (yellow_dots_timer + 2000 < current_time && (dot_1 && dot_2 && dot_3 && dot_4)) {
		App->ui->score += 2500;
		dot_1 = dot_2 = dot_3 = dot_4 = false;
		yellow_dot.loop = false;
		yellow_dots_timer = 0;
	}

	//Blitting Rhombus
	switch (rhombus_count)
	{
	case 0:
		break;
	case 1:
		App->renderer->Blit(pinball_spritesheet, 190, 452, &green_rhombus_1.GetCurrentFrame(), 1.0f);
		break;
	case 2:
		App->renderer->Blit(pinball_spritesheet, 190, 452, &green_rhombus_1.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 224, 460, &green_rhombus_2.GetCurrentFrame(), 1.0f);
		break;
	case 3:
		App->renderer->Blit(pinball_spritesheet, 190, 452, &green_rhombus_1.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 224, 460, &green_rhombus_2.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 258, 452, &green_rhombus_3.GetCurrentFrame(), 1.0f);
		break;
	default:
		break;
	}

	// Blitting Circle Colors

	switch (color_circles)
	{
	case 0:
		break;
	case 1:
		App->renderer->Blit(pinball_spritesheet, 198, 672, &white_circle.GetCurrentFrame(), 1.0f);
		break;
	case 2:
		App->renderer->Blit(pinball_spritesheet, 198, 672, &white_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 210, 642, &green_circle.GetCurrentFrame(), 1.0f);
		break;
	case 3:
		App->renderer->Blit(pinball_spritesheet, 198, 672, &white_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 210, 642, &green_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 242, 642, &yellow_circle.GetCurrentFrame(), 1.0f);
		break;
	case 4:
		App->renderer->Blit(pinball_spritesheet, 198, 672, &white_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 210, 642, &green_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 242, 642, &yellow_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 254, 672, &blue_circle.GetCurrentFrame(), 1.0f);
		break;
	case 5:
		App->renderer->Blit(pinball_spritesheet, 198, 672, &white_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 210, 642, &green_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 242, 642, &yellow_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 254, 672, &blue_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 226, 684, &red_circle.GetCurrentFrame(), 1.0f);
		break;
	default:
		break;
	}

	if (color_circles == 5 && circle_timer + 2000 > current_time) {
		white_circle.loop = yellow_circle.loop = red_circle.loop = blue_circle.loop = green_circle.loop = true;
		App->renderer->Blit(pinball_spritesheet, 198, 672, &white_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 210, 642, &green_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 242, 642, &yellow_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 254, 672, &blue_circle.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 226, 684, &red_circle.GetCurrentFrame(), 1.0f);
	}
	else if (color_circles == 5 && circle_timer + 2000 < current_time) {
		balls_left++;
		App->ui->score += 2500;
		color_circles = 0;
		circle_timer = 0;
		white_circle.loop = yellow_circle.loop = red_circle.loop = blue_circle.loop = green_circle.loop = false;
	}

	// Blitting Map Letters
	App->renderer->Blit(pinball_spritesheet, 68, 480, &map_M.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 68, 512, &map_A.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 68, 544, &map_P.GetCurrentFrame(), 1.0f);

	// Blitting Chip letters
	App->renderer->Blit(pinball_spritesheet, 28, 210, &chip_C.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 34, 246, &chip_H.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 46, 280, &chip_I.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 60, 312, &chip_P.GetCurrentFrame(), 1.0f);

	//Blitting Orange bar
	App->renderer->Blit(pinball_spritesheet, 410, 450, &orange_bar.GetCurrentFrame(), 1.0f);
	
	//Blitting Tunnels

	if (blit_tunnel_control) //in tunnel
	{
		App->renderer->Blit(pinball_spritesheet, 0, 27, &rect_rail, 1.0f);
		App->renderer->Blit(pinball_spritesheet, 0, 0, &rect_tunnel, 1.0f);

		p2List_item<PhysBody*>* ball_item = balls.getFirst();

		while (ball_item != NULL)
		{
			int x, y;
			ball_item->data->GetPosition(x, y);

			float vel = ball_item->data->body->GetLinearVelocity().Length();
			ball_anim.speed = vel / 15;

			App->renderer->Blit(pinball_spritesheet, x, y, &ball_anim.GetCurrentFrame(), 1.0f);
			
			ball_item = ball_item->next;
		}
		App->renderer->Blit(pinball_spritesheet, 0, 347, &rect_piece_rail, 1.0f);
	}
	else //not in tunnel
	{
		if (ball_in_rail) {
			//bushes
			App->renderer->Blit(pinball_spritesheet, 74, 162, &rect_bush, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 104, 130, &rect_bush, 1.0f);

			App->renderer->Blit(pinball_spritesheet, 0, 27, &rect_rail, 1.0f);
			p2List_item<PhysBody*>* ball_item = balls.getFirst();
			while (ball_item != NULL)
			{
				int x, y;
				ball_item->data->GetPosition(x, y);

				float vel = ball_item->data->body->GetLinearVelocity().Length();
				ball_anim.speed = vel / 15;

				App->renderer->Blit(pinball_spritesheet, x, y, &ball_anim.GetCurrentFrame(), 1.0f);

				ball_item = ball_item->next;
			}
			App->renderer->Blit(pinball_spritesheet, 0, 0, &rect_tunnel, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 0, 347, &rect_piece_rail, 1.0f);
		}

		if (in_mid_rail) {
			App->renderer->Blit(pinball_spritesheet, 0, 27, &rect_rail, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 0, 0, &rect_tunnel, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 0, 347, &rect_piece_rail, 1.0f);
			p2List_item<PhysBody*>* ball_item = balls.getFirst();
			while (ball_item != NULL)
			{
				int x, y;
				ball_item->data->GetPosition(x, y);

				float vel = ball_item->data->body->GetLinearVelocity().Length();
				ball_anim.speed = vel / 15;

				App->renderer->Blit(pinball_spritesheet, x, y, &ball_anim.GetCurrentFrame(), 1.0f);

				ball_item = ball_item->next;
			}
		}

		if (!ball_in_rail) {
			p2List_item<PhysBody*>* ball_item = balls.getFirst();
			while (ball_item != NULL)
			{
				int x, y;
				ball_item->data->GetPosition(x, y);

				float vel = ball_item->data->body->GetLinearVelocity().Length();
				ball_anim.speed = vel / 15;

				App->renderer->Blit(pinball_spritesheet, x, y, &ball_anim.GetCurrentFrame(), 1.0f);

				ball_item = ball_item->next;
			}
			//Blitting bushes
			App->renderer->Blit(pinball_spritesheet, 74, 162, &rect_bush, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 104, 130, &rect_bush, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 0, 27, &rect_rail, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 0, 0, &rect_tunnel, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 0, 347, &rect_piece_rail, 1.0f);
		}
			
	}

	// Blitting Plunge
	App->renderer->Blit(pinball_spritesheet, 467, 463, &rect_plunge_struct, 1.0f);

	// Blitting Central piece
	App->renderer->Blit(pinball_spritesheet, 184, 327, &rect_central_piece, 1.0f);

	// Blitting boss control and green rhombus

	if (rhombus_count == 3 && rhombus_timer + 2000 < current_time && bossAlive && !(hit_timer + 1000 > current_time)) {
		App->renderer->Blit(pinball_spritesheet, 188, 326, &boss.GetCurrentFrame(), 1.0f);
		rhombus_count = 3;
		rhombus_timer = 0;
		green_rhombus_1.loop = green_rhombus_2.loop = green_rhombus_3.loop = true;
		spawned = true;
	}

	if (hit_timer + 1000 > current_time && bossAlive ){

		App->renderer->Blit(pinball_spritesheet, 188, 326, &bossHit.GetCurrentFrame(), 1.0f);
	}

	if (rhombus_count == 3 && rhombus_timer + 2000 > current_time) {
		bossAlive = true;
		green_rhombus_1.loop = green_rhombus_2.loop = green_rhombus_3.loop = true;
		App->renderer->Blit(pinball_spritesheet, 190, 452, &green_rhombus_1.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 224, 460, &green_rhombus_2.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 258, 452, &green_rhombus_3.GetCurrentFrame(), 1.0f);

		App->renderer->Blit(pinball_spritesheet, 195, 350, &big_explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 170, 370, &big_explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 220, 370, &big_explosion.GetCurrentFrame(), 1.0f);
	}

	if (boss_timer + 3000 > current_time && boss_defeated) {
		App->renderer->Blit(pinball_spritesheet, 188, 326, &bossHit.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 195, 350, &big_explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 170, 370, &big_explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 220, 370, &big_explosion.GetCurrentFrame(), 1.0f);
	}
	

	// Blitting Cave
	App->renderer->Blit(pinball_spritesheet, 171, 162, &rect_cave, 1.0f);

	// Blitting Cannons
	App->renderer->Blit(pinball_spritesheet, 452, 559, &start_canon.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 29, 788, &side_canon_L.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 419, 788, &side_canon_R.GetCurrentFrame(), 1.0f);
	

	// ----- Ball creation -----
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		balls.add(App->physics->CreateBall(App->input->GetMouseX(), App->input->GetMouseY(), 14));
		balls.getLast()->data->listener = this;
	}

	// Start canon control
	if (start_canon.GetCurrentFrame().x == 801 && !ball_created && inside_start_canon)
	{
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			App->physics->world->DestroyBody(bc->data->body);
		}
		balls.clear();
		
		balls.add(App->physics->CreateBall(485, 608, 14));
		balls.getLast()->data->listener = this;
		ball_created = true;

		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			int x, y;
			bc->data->GetPosition(x, y);
			bc->data->body->ApplyLinearImpulse(b2Vec2(-2.3f, -2.9f), b2Vec2(x, y), true);
		}
		App->audio->PlayFx(start_canon_fx);

		if (inside_start_canon)
			inside_start_canon = false;
	}

	//Left Canon control
	if (side_canon_L.GetCurrentFrame().x == 39 && !ball_created && inside_side_canon)
	{
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			App->physics->world->DestroyBody(bc->data->body);
		}
		balls.clear();
		explosion.loop = false;
		App->renderer->Blit(pinball_spritesheet, 30, 743, &explosion.GetCurrentFrame(), 1.0f);

		balls.add(App->physics->CreateBall(45, 807, 14));
		balls.getLast()->data->listener = this;
		ball_created = true;

		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			int x, y;
			bc->data->GetPosition(x, y);
			bc->data->body->ApplyLinearImpulse(b2Vec2(0.0f, -2.9f), b2Vec2(x, y), true);
		}
		App->audio->PlayFx(start_canon_fx);

		inside_side_canon = false;
	}

	// Right Canon control
	if (side_canon_R.GetCurrentFrame().x == 39 && !ball_created && inside_side_canon)
	{
		explosion.loop = false;
		App->renderer->Blit(pinball_spritesheet, 420, 743, &explosion.GetCurrentFrame(), 1.0f);

		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			App->physics->world->DestroyBody(bc->data->body);
		}
		balls.clear();

		balls.add(App->physics->CreateBall(434, 807, 14));
		balls.getLast()->data->listener = this;
		ball_created = true;

		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			int x, y;
			bc->data->GetPosition(x, y);
			bc->data->body->ApplyLinearImpulse(b2Vec2(0.0f, -2.9f), b2Vec2(x, y), true);
		}
		App->audio->PlayFx(start_canon_fx);

		inside_side_canon = false;
	}

	//Hole Teleport Cave control 
	if (in_cave_hole) {
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			App->physics->world->DestroyBody(bc->data->body);
		}
		balls.clear();
		App->renderer->Blit(pinball_spritesheet, 198, 190, &explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 196, 193, &explosion.GetCurrentFrame(), 1.0f);
	}

	if (in_cave_hole && hole_timer + 500 < current_time)
	{
		App->audio->PlayFx(hole_out_fx);
		App->ui->score += 1000;
		
		balls.add(App->physics->CreateBall(260, 72, 14));
		balls.getLast()->data->listener = this;
		ball_created = true;

		in_cave_hole = false;
	}

	//Hole Teleport Mid control 
	if (in_mid_hole) {
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			App->physics->world->DestroyBody(bc->data->body);
		}
		balls.clear();
		App->renderer->Blit(pinball_spritesheet, 292, 248, &explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 292, 248, &explosion.GetCurrentFrame(), 1.0f);
	}

	if (in_mid_hole && hole_timer + 500 < current_time)
	{
		App->audio->PlayFx(hole_out_fx);
		App->ui->score += 1000;

		balls.add(App->physics->CreateBall(ball_x + 5, ball_y + 2, 14));
		balls.getLast()->data->listener = this;
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			int x, y;
			bc->data->GetPosition(x, y);
			bc->data->body->ApplyLinearImpulse(b2Vec2(-0.7f, 1.4f), b2Vec2(x, y), true);
		}
		ball_created = true;

		in_mid_hole = false;
	}


	//Hole Teleport Cave right 
	if (in_right_hole) {
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			App->physics->world->DestroyBody(bc->data->body);
		}
		balls.clear();
		App->renderer->Blit(pinball_spritesheet, 472, 426, &explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 472, 426, &explosion.GetCurrentFrame(), 1.0f);
	}

	if (in_right_hole && hole_timer + 500 < current_time)
	{
		App->audio->PlayFx(hole_out_fx);
		App->ui->score += 1000;

		balls.add(App->physics->CreateBall(ball_x + 20, ball_y + 2, 14));
		balls.getLast()->data->listener = this;
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next)
		{
			int x, y;
			bc->data->GetPosition(x, y);
			bc->data->body->ApplyLinearImpulse(b2Vec2(0.1f, 0.0f), b2Vec2(x, y), true);
		}
		ball_created = true;

		in_right_hole = false;
	}

	//Blitting explosion bushes
	if (bush_timer + 500 > current_time) {
		explosion.loop = true;
		App->renderer->Blit(pinball_spritesheet, 110, 130, &explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 123, 133, &explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 109, 156, &explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 79, 160, &explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 75, 171, &explosion.GetCurrentFrame(), 1.0f);
		App->renderer->Blit(pinball_spritesheet, 101, 174, &explosion.GetCurrentFrame(), 1.0f);
	}

	// Ball lost control
	if (ball_lost)
	{
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next) 
		{
			App->physics->world->DestroyBody(bc->data->body);
		}
		balls.clear();

		balls_left--;

		if (balls_left > 0) {
			spawnBall();
		}

		ball_lost = false;
	}

	//Game is over!
	if (balls_left == 0 && App->fade->FadeIsOver()) 
	{
		App->audio->PlayFx(win_fx);
		App->fade->FadeToBlack(this, this, 7.0f);
	}

	current_time = SDL_GetTicks();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Here we control every collision in scene

	for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next) 
	{
		if (bodyA == bc->data)
		{
			if (bodyB->physType == TRIANGLE)
			{
				App->ui->score += 400;
				App->audio->PlayFx(triangle_fx);
			}

			if (bodyB->physType == ENTRY_RAIL)
			{
				ball_in_rail = true;
			
				b2Fixture* fixture = rail->body->GetFixtureList();

				while (fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::RIGID_PINBALL;
					fixture->SetFilterData(newFilter);
					fixture = fixture->GetNext();
				}

				b2Fixture* fixture_m = rail_mini_sensor->body->GetFixtureList();

				while (fixture_m != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::RIGID_PINBALL;
					fixture_m->SetFilterData(newFilter);
					fixture_m = fixture_m->GetNext();
				}
				

				b2Fixture* r_flipper_fixture = App->player->right_flipper->body->GetFixtureList();

				while (r_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::BALL;
					r_flipper_fixture->SetFilterData(newFilter);
					r_flipper_fixture = r_flipper_fixture->GetNext();
				}

				b2Fixture* l_flipper_fixture = App->player->left_flipper->body->GetFixtureList();

				while (l_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::BALL;
					l_flipper_fixture->SetFilterData(newFilter);
					l_flipper_fixture = l_flipper_fixture->GetNext();
				}

				for (p2List_item<PhysBody*>* p_w = pinball_walls.getFirst(); p_w != NULL; p_w = p_w->next)
				{
					b2Fixture* fixture = p_w->data->body->GetFixtureList();

					while (fixture != NULL)
					{
						b2Filter newFilter;
						newFilter.groupIndex = groupIndex::BALL;
						fixture->SetFilterData(newFilter);
						fixture = fixture->GetNext();
					}
				}

				break;
			}

			if (bodyB->physType == MID_RAIL)
			{
				in_mid_rail = true;
			}

			if (bodyB->physType == EXIT_RAIL)
			{

				ball_in_rail = in_mid_rail = false;

				b2Fixture* fixture = rail->body->GetFixtureList();

				while (fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::BALL;
					fixture->SetFilterData(newFilter);
					fixture = fixture->GetNext();
				}

				b2Fixture* fixture_m = rail_mini_sensor->body->GetFixtureList();

				while (fixture_m != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::BALL;
					fixture_m->SetFilterData(newFilter);
					fixture_m = fixture_m->GetNext();
				}


				b2Fixture* r_flipper_fixture = App->player->right_flipper->body->GetFixtureList();

				while (r_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::RIGID_PINBALL;
					r_flipper_fixture->SetFilterData(newFilter);
					r_flipper_fixture = r_flipper_fixture->GetNext();
				}

				b2Fixture* l_flipper_fixture = App->player->left_flipper->body->GetFixtureList();

				while (l_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::RIGID_PINBALL;
					l_flipper_fixture->SetFilterData(newFilter);
					l_flipper_fixture = l_flipper_fixture->GetNext();
				}

				for (p2List_item<PhysBody*>* p_w = pinball_walls.getFirst(); p_w != NULL; p_w = p_w->next)
				{
					b2Fixture* fixture = p_w->data->body->GetFixtureList();

					while (fixture != NULL)
					{
						b2Filter newFilter;
						newFilter.groupIndex = groupIndex::RIGID_PINBALL;
						fixture->SetFilterData(newFilter);
						fixture = fixture->GetNext();
					}
				}

				break;
			}


			if (bodyB->physType == ENTRY_TUNNEL && !ball_in_rail)
			{
				blit_tunnel_control = true;
				for (p2List_item<PhysBody*>* t_w = tunnel_walls.getFirst(); t_w != NULL; t_w = t_w->next)
				{
					b2Fixture* fixture = t_w->data->body->GetFixtureList();

					while (fixture != NULL)
					{
						b2Filter newFilter;
						newFilter.groupIndex = groupIndex::RIGID_PINBALL;
						fixture->SetFilterData(newFilter);
						fixture = fixture->GetNext();
					}
				}

				b2Fixture* r_flipper_fixture = App->player->right_flipper->body->GetFixtureList();

				while (r_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::BALL;
					r_flipper_fixture->SetFilterData(newFilter);
					r_flipper_fixture = r_flipper_fixture->GetNext();
				}

				b2Fixture* l_flipper_fixture = App->player->left_flipper->body->GetFixtureList();

				while (l_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::BALL;
					l_flipper_fixture->SetFilterData(newFilter);
					l_flipper_fixture = l_flipper_fixture->GetNext();
				}

				for (p2List_item<PhysBody*>* p_w = pinball_walls.getFirst(); p_w != NULL; p_w = p_w->next)
				{
					b2Fixture* fixture = p_w->data->body->GetFixtureList();

					while (fixture != NULL)
					{
						b2Filter newFilter;
						newFilter.groupIndex = groupIndex::BALL;
						fixture->SetFilterData(newFilter);
						fixture = fixture->GetNext();
					}
				}
				break;
			}

			if (bodyB->physType == EXIT_TUNNEL && !ball_in_rail)
			{
				blit_tunnel_control = false;
				for (p2List_item<PhysBody*>* t_w = tunnel_walls.getFirst(); t_w != NULL; t_w = t_w->next)
				{
					b2Fixture* fixture = t_w->data->body->GetFixtureList();

					while (fixture != NULL)
					{
						b2Filter newFilter;
						newFilter.groupIndex = groupIndex::BALL;
						fixture->SetFilterData(newFilter);
						fixture = fixture->GetNext();
					}
				}

				b2Fixture* r_flipper_fixture = App->player->right_flipper->body->GetFixtureList();

				while (r_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::RIGID_PINBALL;
					r_flipper_fixture->SetFilterData(newFilter);
					r_flipper_fixture = r_flipper_fixture->GetNext();
				}

				b2Fixture* l_flipper_fixture = App->player->left_flipper->body->GetFixtureList();

				while (l_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::RIGID_PINBALL;
					l_flipper_fixture->SetFilterData(newFilter);
					l_flipper_fixture = l_flipper_fixture->GetNext();
				}

				for (p2List_item<PhysBody*>* p_w = pinball_walls.getFirst(); p_w != NULL; p_w = p_w->next)
				{
					b2Fixture* fixture = p_w->data->body->GetFixtureList();

					while (fixture != NULL)
					{
						b2Filter newFilter;
						newFilter.groupIndex = groupIndex::RIGID_PINBALL;
						fixture->SetFilterData(newFilter);
						fixture = fixture->GetNext();
					}
				}
				break;
			}

			if (bodyB->physType == EXIT_CANON)
			{
				ball_created = false;
				balls.getLast()->data->listener = this;
				for (p2List_item<PhysBody*>* p_w = pinball_walls.getFirst(); p_w != NULL; p_w = p_w->next)
				{
					b2Fixture* fixture = p_w->data->body->GetFixtureList();

					while (fixture != NULL)
					{
						b2Filter newFilter;
						newFilter.groupIndex = groupIndex::RIGID_PINBALL;
						fixture->SetFilterData(newFilter);
						fixture = fixture->GetNext();
					}
				}

				b2Fixture* r_flipper_fixture = App->player->right_flipper->body->GetFixtureList();

				while (r_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::RIGID_PINBALL;
					r_flipper_fixture->SetFilterData(newFilter);
					r_flipper_fixture = r_flipper_fixture->GetNext();
				}

				b2Fixture* l_flipper_fixture = App->player->left_flipper->body->GetFixtureList();

				while (l_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::RIGID_PINBALL;
					l_flipper_fixture->SetFilterData(newFilter);
					l_flipper_fixture = l_flipper_fixture->GetNext();
				}
				break;
			}

			if (bodyB->physType == START_CANON && !ball_created)
			{
				start_canon.Reset();
				for (p2List_item<PhysBody*>* p_w = pinball_walls.getFirst(); p_w != NULL; p_w = p_w->next)
				{
					b2Fixture* fixture = p_w->data->body->GetFixtureList();

					while (fixture != NULL)
					{
						b2Filter newFilter;
						newFilter.groupIndex = groupIndex::BALL;
						fixture->SetFilterData(newFilter);
						fixture = fixture->GetNext();
					}
				}

				for (p2List_item<PhysBody*>* ball_item = balls.getFirst(); ball_item != NULL; ball_item = ball_item->next)
				{
					int x, y;
					bc->data->GetPosition(x, y);
					bc->data->body->SetGravityScale(0.0f);
					bc->data->body->SetLinearVelocity(b2Vec2(0, 0));
					bc->data->body->SetAngularVelocity(0);
				}

				inside_start_canon = true;
				start_canon.speed = 0.06f;

				b2Fixture* r_flipper_fixture = App->player->right_flipper->body->GetFixtureList();

				while (r_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::BALL;
					r_flipper_fixture->SetFilterData(newFilter);
					r_flipper_fixture = r_flipper_fixture->GetNext();
				}

				b2Fixture* l_flipper_fixture = App->player->left_flipper->body->GetFixtureList();

				while (l_flipper_fixture != NULL)
				{
					b2Filter newFilter;
					newFilter.groupIndex = groupIndex::BALL;
					l_flipper_fixture->SetFilterData(newFilter);
					l_flipper_fixture = l_flipper_fixture->GetNext();
				}
				break;
			}

			if (bodyB->physType == ENTRY_SIDE_CANON_L && !ball_created)
			{
				side_canon_L.Reset();
				for (p2List_item<PhysBody*>* ball_item = balls.getFirst(); ball_item != NULL; ball_item = ball_item->next)
				{
					int x, y;
					bc->data->GetPosition(x, y);
					bc->data->body->SetGravityScale(0.0f);
					bc->data->body->SetLinearVelocity(b2Vec2(0, 0));
					bc->data->body->SetAngularVelocity(0);
				}

				side_canon_L.speed = 0.06f;
				canon_L_done = inside_side_canon  = true;
			}

			if (bodyB->physType == ENTRY_SIDE_CANON_R && !ball_created)
			{
				side_canon_R.Reset();
				for (p2List_item<PhysBody*>* ball_item = balls.getFirst(); ball_item != NULL; ball_item = ball_item->next)
				{
					int x, y;
					bc->data->GetPosition(x, y);
					bc->data->body->SetGravityScale(0.0f);
					bc->data->body->SetLinearVelocity(b2Vec2(0, 0));
					bc->data->body->SetAngularVelocity(0);
				}

				side_canon_R.speed = 0.06f;
				canon_R_done = inside_side_canon = true;
			}

			if (bodyB->physType == CAVE_HOLE && !in_cave_hole)
			{
				color_circles++;
				App->audio->PlayFx(hole_in_fx);
				in_cave_hole = true;
				hole_timer = SDL_GetTicks();
				if (color_circles == 5) {
					circle_timer = SDL_GetTicks();
					App->audio->PlayFx(five_colors_fx);
				}
			}

			if (bodyB->physType == MID_HOLE && !in_mid_hole && hole_timer + 1500 < current_time)
			{
				color_circles++;
				for (p2List_item<PhysBody*>* ball_item = balls.getFirst(); ball_item != NULL; ball_item = ball_item->next)
				{
					bc->data->GetPosition(ball_x, ball_y);
				}
				App->audio->PlayFx(hole_in_fx);
				in_mid_hole = true;
				hole_timer = SDL_GetTicks();
				if (color_circles == 5) {
					circle_timer = SDL_GetTicks();
					App->audio->PlayFx(five_colors_fx);
				}
			}

			if (bodyB->physType == RIGHT_HOLE && !in_right_hole && hole_timer + 1500 < current_time)
			{
				color_circles++;
				for (p2List_item<PhysBody*>* ball_item = balls.getFirst(); ball_item != NULL; ball_item = ball_item->next)
				{
					bc->data->GetPosition(ball_x, ball_y);
				}
				App->audio->PlayFx(hole_in_fx);
				in_right_hole = true;
				hole_timer = SDL_GetTicks();
				if (color_circles == 5) {
					circle_timer = SDL_GetTicks();
					App->audio->PlayFx(five_colors_fx);
				}
			}

			if (bodyB->physType == BUSH && !ball_in_rail)
			{
				bush_timer = SDL_GetTicks();
				App->renderer->Blit(pinball_spritesheet, 420, 743, &explosion.GetCurrentFrame(), 1.0f);
				App->ui->score += 350;
				App->audio->PlayFx(hole_in_fx);
			}

			if (bodyB->physType == DOT_1 && !dot_1)
			{
				dot_1 = true;
				App->ui->score += 100;
				App->audio->PlayFx(bonus_fx);
			}

			if (bodyB->physType == DOT_2 && !dot_2)
			{
				dot_2 = true;
				App->ui->score += 100;
				App->audio->PlayFx(bonus_fx);
			}

			if (bodyB->physType == DOT_3 && !dot_3)
			{
				dot_3 = true;
				App->ui->score += 100;
				App->audio->PlayFx(bonus_fx);
			}

			if (bodyB->physType == DOT_4 && !dot_4)
			{
				dot_4 = true;
				App->ui->score += 100;
				App->audio->PlayFx(bonus_fx);
			}

			if (bodyB->physType == RHOMBUS && rhombus_count < 3)
			{
				rhombus_count++;
				App->audio->PlayFx(hit_wall_fx);
				if (rhombus_count == 3) {

					App->ui->score += 2500;
					rhombus_timer = SDL_GetTicks();
					App->audio->PlayFx(monster_roar_fx);
				}
			}

			if (bodyB->physType == BOSS && bossAlive && spawned && boss_live > 0)
			{
				App->audio->PlayFx(hit_wall_fx);
				boss_live--;
				hit_timer = SDL_GetTicks();
				if (boss_live == 0) {
					boss_defeated = true;
					bossAlive = false;
					App->ui->score += 10000;
					boss_timer = SDL_GetTicks();
					App->audio->PlayFx(monster_roar_fx);
				}
			}
		

			if (bodyB->physType == DEAD_SENSOR) 
			{
				App->audio->PlayFx(lose_fx);
				ball_lost = true;
			}
		}
	}
}

void ModuleSceneIntro::setWalls() {

	// Here we create all chains of the scene

	// Bouncing triangles

	int points_triangle_R_sensor[8] =
	{
		359, 629,
		331, 689,
		340, 688,
		362, 640
	};

	triangle_R = App->physics->CreateChain(0, 0, points_triangle_R_sensor, 8, groupIndex::RIGID_PINBALL, 1.5f, TRIANGLE);

	int points_triangle_L_sensor[8] =
	{
		121, 628,
		148, 687,
		140, 684,
		119, 639
	};

	triangle_L = App->physics->CreateChain(0, 0, points_triangle_L_sensor, 8, groupIndex::RIGID_PINBALL, 1.5f, TRIANGLE);

	int points_triangle_L[14] =
	{
		114, 679,
		114, 624,
		119, 624,
		150, 690,
		150, 696,
		144, 696,
		116, 681
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, points_triangle_L, 14, groupIndex::RIGID_PINBALL, 0.1f, NO_DEF_));

	int points_triangle_R[14] =
	{
		366, 624,
		367, 678,
		365, 681,
		336, 696,
		330, 696,
		330, 690,
		362, 624
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, points_triangle_R, 14, groupIndex::RIGID_PINBALL, 0.1f, NO_DEF_));


	// Static walls

	int points_top_wall[160] =
	{
		431, 396,
		427, 403,
		423, 407,
		418, 407,
		421, 401,
		427, 391,
		434, 385,
		440, 374,
		462, 307,
		465, 291,
		470, 267,
		483, 227,
		492, 189,
		497, 165,
		497, 133,
		488, 107,
		475, 88,
		461, 75,
		440, 66,
		419, 58,
		385, 58,
		360, 67,
		337, 82,
		320, 104,
		314, 121,
		310, 128,
		310, 142,
		308, 143,
		308, 182,
		314, 198,
		321, 220,
		329, 237,
		334, 240,
		341, 248,
		341, 260,
		332, 260,
		328, 255,
		328, 246,
		316, 236,
		298, 236,
		291, 244,
		284, 244,
		280, 240,
		281, 234,
		282, 228,
		284, 218,
		285, 211,
		286, 196,
		286, 180,
		285, 164,
		285, 148,
		278, 126,
		267, 116,
		259, 109,
		252, 104,
		244, 99,
		237, 96,
		216, 85,
		175, 77,
		155, 77,
		125, 82,
		95, 90,
		74, 99,
		53, 118,
		37, 140,
		31, 151,
		28, 159,
		26, 167,
		24, 177,
		23, 196,
		23, 234,
		29, 268,
		38, 294,
		54, 327,
		60, 352,
		59, 366,
		74, 411,
		72, 411,
		69, 406,
		65, 398
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, points_top_wall, 160, groupIndex::RIGID_PINBALL, 0.01f, NO_DEF_));

	int points_bottom_wall[108] =
	{
		24, 415,
		32, 432,
		44, 454,
		48, 467,
		44, 472,
		36, 480,
		36, 559,
		38, 565,
		43, 568,
		47, 572,
		47, 580,
		33, 595,
		31, 600,
		29, 614,
		27, 632,
		25, 659,
		24, 665,
		24, 832,
		34, 835,
		54, 835,
		64, 832,
		64, 774,
		71, 775,
		184, 832,
		184, 962,
		296, 962,
		296, 832,
		408, 776,
		416, 774,
		416, 834,
		427, 840,
		446, 840,
		456, 834,
		456, 668,
		453, 638,
		451, 617,
		447, 595,
		433, 579,
		433, 574,
		457, 517,
		457, 511,
		449, 504,
		472, 484,
		472, 825,
		477, 840,
		499, 840,
		504, 825,
		504, 433,
		500, 425,
		494, 420,
		481, 418,
		469, 424,
		469, 420,
		475, 411
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, points_bottom_wall, 108, groupIndex::RIGID_PINBALL, 0.01f, NO_DEF_));

	int points_right_L[28] =
	{
		310, 758,
		310, 774,
		320, 774,
		407, 730,
		416, 722,
		416, 643,
		413, 636,
		408, 636,
		408, 691,
		403, 704,
		394, 715,
		367, 731,
		327, 750,
		310, 758
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, points_right_L, 28, groupIndex::RIGID_PINBALL, 0.01f, NO_DEF_));

	int points_left_L[28] =
	{
		170, 758,
		169, 774,
		160, 774,
		108, 748,
		72, 730,
		63, 721,
		64, 642,
		66, 636,
		72, 636,
		72, 691,
		80, 708,
		89, 718,
		97, 722,
		170, 758
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, points_left_L, 28, groupIndex::RIGID_PINBALL, 0.01f, NO_DEF_));

	int points_top_U[46]
	{
		415, 127,
		422, 170,
		420, 202,
		434, 197,
		449, 183,
		455, 163,
		455, 145,
		450, 132,
		443, 122,
		434, 113,
		418, 107,
		403, 106,
		390, 109,
		379, 115,
		369, 123,
		360, 135,
		356, 151,
		356, 167,
		363, 179,
		369, 188,
		373, 192,
		382, 166,
		380, 135
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, points_top_U, 46, groupIndex::RIGID_PINBALL, 0.01f, NO_DEF_));

	int points_left_U[30] = 
	{
		131, 286,
		115, 299,
		108, 305,
		102, 300,
		105, 292,
		108, 283,
		110, 244,
		114, 232,
		125, 225,
		140, 226,
		154, 234,
		167, 247,
		183, 263,
		176, 271,
		160, 259
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, points_left_U, 30, groupIndex::RIGID_PINBALL, 0.01f, NO_DEF_));

	// Tunnel walls

	int points_upper_tunnel[68] =
	{
		27, 412,
		13, 382,
		2, 354,
		-4, 323,
		-11, 280,
		-14, 242,
		-17, 199,
		-16, 157,
		-6, 113,
		17, 72,
		38, 51,
		65, 33,
		94, 20,
		132, 8,
		175, 0,
		219, -5,
		254, -5,
		301, -3,
		343, 3,
		380, 14,
		418, 27,
		453, 48,
		474, 67,
		488, 86,
		500, 110,
		508, 136,
		508, 169,
		508, 217,
		509, 252,
		506, 282,
		500, 320,
		492, 358,
		480, 392,
		471, 417
	};

	tunnel_walls.add(App->physics->CreateChain(0, 0, points_upper_tunnel, 68, groupIndex::BALL, 0.01f, NO_DEF_));

	int points_bottom_tunnel_1[44] =
	{
		58, 392,
		48, 364,
		39, 330,
		31, 292,
		25, 252,
		23, 210,
		23, 173,
		29, 140,
		44, 108,
		63, 84,
		80, 68,
		107, 56,
		143, 46,
		184, 39,
		229, 38,
		272, 38,
		312, 42,
		338, 56,
		355, 75,
		366, 92,
		374, 113,
		381, 133
	};

	tunnel_walls.add(App->physics->CreateChain(0, 0, points_bottom_tunnel_1, 44, groupIndex::BALL, 0.01f, NO_DEF_));

	int points_bottom_tunnel_2[38] =
	{
		413, 121,
		407, 100,
		399, 78,
		392, 59,
		410, 63,
		424, 74,
		440, 90,
		450, 106,
		461, 125,
		467, 146,
		472, 173,
		471, 198,
		470, 226,
		470, 252,
		466, 284,
		458, 324,
		447, 359,
		439, 385,
		432, 406
	};

	tunnel_walls.add(App->physics->CreateChain(0, 0, points_bottom_tunnel_2, 38, groupIndex::BALL, 0.01f, NO_DEF_));

	int points_rail[154] =
	{
		124, 277,
		113, 266,
		100, 253,
		86, 239,
		74, 226,
		63, 208,
		57, 191,
		55, 175,
		54, 144,
		59, 118,
		71, 88,
		80, 72,
		102, 50,
		126, 38,
		159, 29,
		175, 27,
		200, 27,
		236, 34,
		255, 42,
		272, 45,
		282, 52,
		289, 67,
		294, 76,
		303, 103,
		307, 131,
		308, 168,
		302, 200,
		291, 228,
		276, 260,
		231, 304,
		104, 368,
		63, 387,
		50, 398,
		38, 412,
		38, 531,
		45, 541,
		84, 559,
		100, 573,
		105, 581,
		109, 591,
		109, 620,
		114, 628,
		114, 639,
		109, 650,
		101, 657,
		84, 656,
		73, 650,
		66, 640,
		66, 629,
		71, 620,
		71, 604,
		60, 593,
		41, 585,
		22, 575,
		5, 563,
		0, 552,
		0, 402,
		3, 391,
		29, 366,
		37, 359,
		207, 276,
		242, 239,
		263, 186,
		266, 173,
		266, 126,
		261, 103,
		249, 93,
		241, 85,
		237, 78,
		208, 67,
		169, 67,
		141, 72,
		111, 95,
		98, 136,
		98, 181,
		106, 204,
		154, 251
	};

	rail = App->physics->CreateChain(0, 0, points_rail, 154, groupIndex::BALL, 0.01f, NO_DEF_);

	int points_mini_rail[8] =
	{
		78, 650,
		101, 650,
		100, 656,
		77, 655
	};

	rail_mini_sensor = App->physics->CreateChain(0, 0, points_mini_rail, 8, groupIndex::BALL, 0.01f, EXIT_RAIL);

	int left_U_top_points[36] = 
	{
		70, 190,
		72, 176,
		78, 166,
		87, 152,
		100, 142,
		109, 135,
		127, 127,
		141, 125,
		142, 121,
		140, 118,
		125, 118,
		104, 126,
		87, 140,
		74, 156,
		67, 168,
		63, 182,
		62, 190,
		64, 193
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, left_U_top_points, 36, groupIndex::RIGID_PINBALL, 0.01f, NO_DEF_));

	int right_U_top_points[38] =
	{
		182, 127,
		203, 131,
		219, 137,
		233, 152,
		239, 166,
		242, 184,
		243, 191,
		246, 192,
		250, 189,
		250, 174,
		244, 158,
		237, 144,
		226, 133,
		216, 126,
		204, 122,
		192, 119,
		181, 118,
		176, 120,
		176, 124
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, right_U_top_points, 38, groupIndex::RIGID_PINBALL, 0.01f, NO_DEF_));
	
}

void ModuleSceneIntro::setSensors() 
{
	// Here we create all sensors in the scene

	sensors.add(App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT + 80, 150, 80, DEAD_SENSOR));

	int points_exit_right[8] =
	{
		406, 438,
		461, 462,
		462, 445,
		419, 428
	};

	b2Vec2 exit_vec_R[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		exit_vec_R[i].Set(PIXEL_TO_METERS(points_exit_right[i * 2 + 0]), PIXEL_TO_METERS(points_exit_right[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, exit_vec_R, EXIT_TUNNEL));

	int points_entry_right[8] =
	{
		438, 391,
		473, 399,
		476, 386,
		444, 378
	};

	b2Vec2 entry_vec_R[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		entry_vec_R[i].Set(PIXEL_TO_METERS(points_entry_right[i * 2 + 0]), PIXEL_TO_METERS(points_entry_right[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, entry_vec_R, ENTRY_TUNNEL));

	int points_entry_left[8] = 
	{
		23, 401,
		56, 393,
		49, 379,
		16, 388
	};

	b2Vec2 entry_vec_L[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		entry_vec_L[i].Set(PIXEL_TO_METERS(points_entry_left[i * 2 + 0]), PIXEL_TO_METERS(points_entry_left[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, entry_vec_L, ENTRY_TUNNEL));

	int points_exit_left[8] = 
	{
		42, 459,
		104, 435,
		80, 427,
		43, 441
	};

	b2Vec2 exit_vec_L[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		exit_vec_L[i].Set(PIXEL_TO_METERS(points_exit_left[i * 2 + 0]), PIXEL_TO_METERS(points_exit_left[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, exit_vec_L, EXIT_TUNNEL));

	int points_entry_center[8] = 
	{
		378, 124,
		410, 112,
		412, 120,
		380, 131
	};

	b2Vec2 entry_vec_center[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		entry_vec_center[i].Set(PIXEL_TO_METERS(points_entry_center[i * 2 + 0]), PIXEL_TO_METERS(points_entry_center[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, entry_vec_center, ENTRY_TUNNEL));


	int points_exit_center[8] = 
	{
		381, 168,
		426, 158,
		430, 177,
		375, 178
	};

	b2Vec2 exit_vec_center[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		exit_vec_center[i].Set(PIXEL_TO_METERS(points_exit_center[i * 2 + 0]), PIXEL_TO_METERS(points_exit_center[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, exit_vec_center, EXIT_TUNNEL));

	int points_start_canon[8] =
	{
		472, 594,
		505, 593,
		505, 569,
		471, 569
	};

	b2Vec2 start_vec_canon[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		start_vec_canon[i].Set(PIXEL_TO_METERS(points_start_canon[i * 2 + 0]), PIXEL_TO_METERS(points_start_canon[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, start_vec_canon, START_CANON));

	int points_exit_canon[8] =
	{
		504, 466,
		43, 457,
		48, 514,
		512, 522
	};

	b2Vec2 exit_vec_canon[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		exit_vec_canon[i].Set(PIXEL_TO_METERS(points_exit_canon[i * 2 + 0]), PIXEL_TO_METERS(points_exit_canon[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, exit_vec_canon, EXIT_CANON));


	int points_entry_rail_1[8] = 
	{
		113, 260,
		133, 239,
		139, 244,
		117, 266
	};

	b2Vec2 entry_vec_rail[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		entry_vec_rail[i].Set(PIXEL_TO_METERS(points_entry_rail_1[i * 2 + 0]), PIXEL_TO_METERS(points_entry_rail_1[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, entry_vec_rail, ENTRY_RAIL));

	int points_exit_rail_1[8] = 
	{
		137, 294,
		168, 263,
		178, 275,
		141, 304
	};

	b2Vec2 exit_vec_rail[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		exit_vec_rail[i].Set(PIXEL_TO_METERS(points_exit_rail_1[i * 2 + 0]), PIXEL_TO_METERS(points_exit_rail_1[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, exit_vec_rail, EXIT_RAIL));

	int points_mid_rail_1[8] = 
	{
		237, 255,
		256, 270,
		267, 260,
		247, 242
	};

	b2Vec2 mid_vec_rail[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		mid_vec_rail[i].Set(PIXEL_TO_METERS(points_mid_rail_1[i * 2 + 0]), PIXEL_TO_METERS(points_mid_rail_1[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, mid_vec_rail, MID_RAIL));

	int left_points_side_canon[8] = 
	{
		28, 847,
		60, 847,
		60, 825,
		28, 825
	};

	b2Vec2 entry_vec_left_canon[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		entry_vec_left_canon[i].Set(PIXEL_TO_METERS(left_points_side_canon[i * 2 + 0]), PIXEL_TO_METERS(left_points_side_canon[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, entry_vec_left_canon, ENTRY_SIDE_CANON_L));

	int right_points_side_canon[8] =
	{
		417, 830,
		417, 845,
		451, 845,
		451, 831
	};

	b2Vec2 entry_vec_right_canon[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		entry_vec_right_canon[i].Set(PIXEL_TO_METERS(right_points_side_canon[i * 2 + 0]), PIXEL_TO_METERS(right_points_side_canon[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, entry_vec_right_canon, ENTRY_SIDE_CANON_R));

	int right_points_side_exit[8] =
	{
		420, 750,
		420, 767,
		447, 768,
		446, 752
	};

	b2Vec2 exit_vec_right_canon[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		exit_vec_right_canon[i].Set(PIXEL_TO_METERS(right_points_side_exit[i * 2 + 0]), PIXEL_TO_METERS(right_points_side_exit[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, exit_vec_right_canon, EXIT_CANON));


	int left_points_side_exit[8] =
	{
		27, 732,
		27, 747,
		61, 748,
		60, 731
	};

	b2Vec2 exit_vec_left_canon[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		exit_vec_left_canon[i].Set(PIXEL_TO_METERS(left_points_side_exit[i * 2 + 0]), PIXEL_TO_METERS(left_points_side_exit[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, exit_vec_left_canon, EXIT_CANON));


	int cave_hole[8] =
	{
		203, 195,
		203, 214,
		220, 214,
		220, 195
	};

	b2Vec2 vec_cave_hole[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		vec_cave_hole[i].Set(PIXEL_TO_METERS(cave_hole[i * 2 + 0]), PIXEL_TO_METERS(cave_hole[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, vec_cave_hole, CAVE_HOLE));

	int points_entry_rail_3[8] = 
	{
		249, 65,
		252, 85,
		274, 85,
		273, 63
	};

	b2Vec2 entry_vec_rail2[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		entry_vec_rail2[i].Set(PIXEL_TO_METERS(points_entry_rail_3[i * 2 + 0]), PIXEL_TO_METERS(points_entry_rail_3[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, entry_vec_rail2, ENTRY_RAIL));


	int mid_hole[8] =
	{
		298, 257,
		298, 265,
		314, 265,
		314, 257
	};

	b2Vec2 vec_mid_hole[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		vec_mid_hole[i].Set(PIXEL_TO_METERS(mid_hole[i * 2 + 0]), PIXEL_TO_METERS(mid_hole[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, vec_mid_hole, MID_HOLE));
	
	int right_hole[8] =
	{
		477, 435,
		477, 444,
		496, 444,
		496, 436
	};

	b2Vec2 vec_right_hole[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		vec_right_hole[i].Set(PIXEL_TO_METERS(right_hole[i * 2 + 0]), PIXEL_TO_METERS(right_hole[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, vec_right_hole, RIGHT_HOLE));

	int left_bush[8] =
	{
		86, 168,
		81, 189,
		115, 189,
		113, 173
	};

	b2Vec2 vec_left_bush[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		vec_left_bush[i].Set(PIXEL_TO_METERS(left_bush[i * 2 + 0]), PIXEL_TO_METERS(left_bush[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, vec_left_bush, BUSH));

	int right_bush[8] =
	{
		117, 140,
		140, 140,
		141, 162,
		118, 164
	};

	b2Vec2 vec_right_bush[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		vec_right_bush[i].Set(PIXEL_TO_METERS(right_bush[i * 2 + 0]), PIXEL_TO_METERS(right_bush[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, vec_right_bush, BUSH));

	int yellow_dot_1[8] =
	{
		36, 611,
		36, 628,
		60, 628,
		60, 609
	};

	b2Vec2 yellow_vec_dot_1[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		yellow_vec_dot_1[i].Set(PIXEL_TO_METERS(yellow_dot_1[i * 2 + 0]), PIXEL_TO_METERS(yellow_dot_1[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, yellow_vec_dot_1, DOT_1));

	int yellow_dot_2[8] =
	{
		85, 614,
		85, 634,
		107, 634,
		107, 613
	};

	b2Vec2 yellow_vec_dot_2[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		yellow_vec_dot_2[i].Set(PIXEL_TO_METERS(yellow_dot_2[i * 2 + 0]), PIXEL_TO_METERS(yellow_dot_2[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, yellow_vec_dot_2, DOT_2));

	int yellow_dot_3[8] =
	{
		375, 617,
		375, 634,
		394, 634,
		394, 614
	};

	b2Vec2 yellow_vec_dot_3[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		yellow_vec_dot_3[i].Set(PIXEL_TO_METERS(yellow_dot_3[i * 2 + 0]), PIXEL_TO_METERS(yellow_dot_3[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, yellow_vec_dot_3, DOT_3));

	int yellow_dot_4[8] =
	{
		422, 607,
		423, 627,
		441, 627,
		441, 608
	};

	b2Vec2 yellow_vec_dot_4[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		yellow_vec_dot_4[i].Set(PIXEL_TO_METERS(yellow_dot_4[i * 2 + 0]), PIXEL_TO_METERS(yellow_dot_4[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, yellow_vec_dot_4, DOT_4));


	int rhombus_trigger_p[8] =
	{
		190, 375,
		194, 436,
		286, 437,
		284, 378
	};

	b2Vec2 rhombus_vec_dot_4[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		rhombus_vec_dot_4[i].Set(PIXEL_TO_METERS(rhombus_trigger_p[i * 2 + 0]), PIXEL_TO_METERS(rhombus_trigger_p[i * 2 + 1]));
	}
	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, rhombus_vec_dot_4, RHOMBUS));

	
	int boss_points[14] =
	{
		230, 379,
		195, 377,
		190, 421,
		219, 441,
		258, 442,
		281, 422,
		279, 383
	};

	b2Vec2 boss_vec_dot_4[7];

	for (uint i = 0; i < 14 / 2; ++i)
	{
		boss_vec_dot_4[i].Set(PIXEL_TO_METERS(boss_points[i * 2 + 0]), PIXEL_TO_METERS(boss_points[i * 2 + 1]));
	}

	boss_hitbox = App->physics->CreatePolygonSensor(0, 0, 7, boss_vec_dot_4, BOSS);
}

void ModuleSceneIntro::spawnBall() 
{
	balls.add(App->physics->CreateBall(488, 800, 14));
	balls.getLast()->data->listener = this;
}