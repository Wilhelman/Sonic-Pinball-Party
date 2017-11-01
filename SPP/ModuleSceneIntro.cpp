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
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
	balls_left = 3;
	App->ui->score = 0;
	LOG("Loading Intro assets");
	bool ret = true;
	blit_tunnel_control = in_mid_rail = ball_lost = inside_start_canon = ball_created = ball_in_rail = false;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav"); // TODO : this is not being UNLOAD in Cleanup!

	triangle_fx = App->audio->LoadFx("audio/sound_fx/bouncing_triangle.wav");

	start_canon_fx = App->audio->LoadFx("audio/sound_fx/canon_shot.wav");

	if (!App->audio->PlayMusic("audio/music/Nightmaren.ogg"))
		ret = false;

	pinball_spritesheet = App->textures->Load("pinball/pinball_sonic_spritesheet.png");

	if (pinball_spritesheet == nullptr) 
	{
		LOG("Cannot load the animations spritesheet in SceneIntro");
		ret = false;
	}

	// Animations settings

	m_icon.PushBack({ 344, 1144, 60, 36 });
	m_icon.PushBack({ 1826, 555, 60, 36 });
	m_icon.loop = true;
	m_icon.speed = 0.07f;

	start_canon.PushBack({ 575, 1499, 62, 64 });
	start_canon.PushBack({ 676, 1499, 62, 64 });
	start_canon.PushBack({ 801, 1499, 62, 64 });
	start_canon.PushBack({ 575, 1499, 62, 64 });
	start_canon.loop = false;
	start_canon.speed = 0.0f;

	triangle_L_anim.PushBack({ 474, 1100, 42, 80 });
	triangle_L_anim.PushBack({ 526, 1100, 42, 80 });
	triangle_L_anim.loop = true;
	triangle_L_anim.speed = 0.1f;

	triangle_R_anim.PushBack({ 578, 1100, 42, 80 });
	triangle_R_anim.PushBack({ 630, 1100, 42, 80 });
	triangle_R_anim.loop = true;
	triangle_R_anim.speed = 0.1f;

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

	// ---- Setting up SDL_Rect attributes ----

	rect_bg.h = SCREEN_HEIGHT;
	rect_bg.w = SCREEN_WIDTH;
	rect_bg.x = 0;
	rect_bg.y = 0;

	rect_ball.h = 28;
	rect_ball.w = 28;
	rect_ball.x = 0;
	rect_ball.y = 1418;

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

	balls.clear();
	pinball_walls.clear();
	sensors.clear();
	tunnel_walls.clear();

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//Blitting 

	//BG
	App->renderer->Blit(pinball_spritesheet, 0, 0, &rect_bg, 1.0f);
	
	// Bouncing triangles
	App->renderer->Blit(pinball_spritesheet, 113, 621, &triangle_L_anim.GetCurrentFrame(), 1.0f);
	App->renderer->Blit(pinball_spritesheet, 325, 621, &triangle_R_anim.GetCurrentFrame(), 1.0f);

	// Arrows
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
	
	//Tunnels
	if (blit_tunnel_control)//in tunnel
	{
		App->renderer->Blit(pinball_spritesheet, 0, 27, &rect_rail, 1.0f);
		App->renderer->Blit(pinball_spritesheet, 0, 0, &rect_tunnel, 1.0f);

		p2List_item<PhysBody*>* ball_item = balls.getFirst();

		while (ball_item != NULL)
		{
			int x, y;
			ball_item->data->GetPosition(x, y);

			//TODO: control sprite according to ball velocity
			float vel = ball_item->data->body->GetAngularVelocity();

			App->renderer->Blit(pinball_spritesheet, x, y, &rect_ball, 1.0f);

			ball_item = ball_item->next;
		}
		App->renderer->Blit(pinball_spritesheet, 0, 347, &rect_piece_rail, 1.0f);
	}
	else //not in tunnel
	{
		if (ball_in_rail) {
			App->renderer->Blit(pinball_spritesheet, 0, 27, &rect_rail, 1.0f);
			p2List_item<PhysBody*>* ball_item = balls.getFirst();
			while (ball_item != NULL)
			{
				int x, y;
				ball_item->data->GetPosition(x, y);

				//TODO: control sprite according to ball velocity
				float vel = ball_item->data->body->GetAngularVelocity();

				App->renderer->Blit(pinball_spritesheet, x, y, &rect_ball, 1.0f);

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

				//TODO: control sprite according to ball velocity
				float vel = ball_item->data->body->GetAngularVelocity();

				App->renderer->Blit(pinball_spritesheet, x, y, &rect_ball, 1.0f);

				ball_item = ball_item->next;
			}
		}

		if (!ball_in_rail) {
			p2List_item<PhysBody*>* ball_item = balls.getFirst();
			while (ball_item != NULL)
			{
				int x, y;
				ball_item->data->GetPosition(x, y);

				//TODO: control sprite according to ball velocity
				float vel = ball_item->data->body->GetAngularVelocity();

				App->renderer->Blit(pinball_spritesheet, x, y, &rect_ball, 1.0f);

				ball_item = ball_item->next;
			}
			App->renderer->Blit(pinball_spritesheet, 0, 27, &rect_rail, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 0, 0, &rect_tunnel, 1.0f);
			App->renderer->Blit(pinball_spritesheet, 0, 347, &rect_piece_rail, 1.0f);
		}
			
	}

	// Plunge
	App->renderer->Blit(pinball_spritesheet, 467, 463, &rect_plunge_struct, 1.0f);
	
	/*if (!ball_in_rail) {
		// Rail piece
		App->renderer->Blit(pinball_spritesheet, 0, 27, &rect_rail, 1.0f);
		
	}*/

	// Central piece
	App->renderer->Blit(pinball_spritesheet, 184, 327, &rect_central_piece, 1.0f);

	// Cave
	App->renderer->Blit(pinball_spritesheet, 171, 162, &rect_cave, 1.0f);

	//Animations
	App->renderer->Blit(pinball_spritesheet, 452, 559, &start_canon.GetCurrentFrame(), 1.0f);

	

	// ----- Ball creation -----
	//TODO: balls we'll be created at Start() and every time you lose one
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		balls.add(App->physics->CreateBall(App->input->GetMouseX(), App->input->GetMouseY(), 14));
		balls.getLast()->data->listener = this;
	}

	// ----- Blitting ------

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------

	if (start_canon.GetCurrentFrame().x == 801 && ball_created == false)
	{
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
	}

	if (ball_lost || inside_start_canon && (ball_created == false))
	{
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next) 
		{
			App->physics->world->DestroyBody(bc->data->body);
		}
		balls.clear();
		
		if (inside_start_canon)
			inside_start_canon = false;

		if (ball_lost)
		{
			balls_left--;

			if (balls_left > 0) {
				spawnBall();
			}

			ball_lost = false;
		}
	}

	//Game is over!
	if (balls_left == 0 && App->fade->FadeIsOver()) 
	{
		App->fade->FadeToBlack(this, this, 7.0f);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	//App->audio->PlayFx(bonus_fx);

	for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next) 
	{
		if (bodyA == bc->data)
		{
			if (bodyB->physType == TRIANGLE)
			{
				App->ui->score += 200;
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
				ball_created = false;
				start_canon.Reset();
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
		

			if (bodyB->physType == DEAD_SENSOR) 
			{
				ball_lost = true;

				//balls.getLast()->data->listener = this;
			}
		}
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}
}

void ModuleSceneIntro::setWalls() {
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
		440, 401,
		438, 407,
		430, 412,
		416, 412,
		416, 403,
		423, 383,
		440, 384,
		440, 380,
		462, 290,
		464, 290,
		464, 266,
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
		282, 229,
		284, 226,
		284, 215,
		286, 214,
		286, 187,
		284, 186,
		282, 175,
		278, 158,
		278, 67,
		268, 56,
		252, 56,
		243, 66,
		242, 94,
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
		67, 357,
		59, 366,
		74, 411,
		68, 412,
		64, 410,
		62, 401
	};

	pinball_walls.add(App->physics->CreateChain(0, 0, points_top_wall, 160, groupIndex::RIGID_PINBALL, 0.01f, NO_DEF_));

	int points_bottom_wall[108] =
	{
		29, 412,
		37, 428,
		50, 459,
		50, 472,
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
		482, 417,
		468, 427,
		465, 426,
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

	int points_left_U[30] = {
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
}

void ModuleSceneIntro::setSensors() {

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

	int points_entry_left[8] = {
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

	int points_exit_left[8] = {
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

	int points_entry_center[8] = {
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


	int points_exit_center[8] = {
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
		472, 624,
		505, 623,
		505, 599,
		471, 599
	};

	b2Vec2 start_vec_canon[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		start_vec_canon[i].Set(PIXEL_TO_METERS(points_start_canon[i * 2 + 0]), PIXEL_TO_METERS(points_start_canon[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, start_vec_canon, START_CANON));

	int points_exit_canon[8] =
	{
		401, 455,
		344, 511,
		364, 532,
		425, 472
	};

	b2Vec2 exit_vec_canon[4];

	for (uint i = 0; i < 8 / 2; ++i)
	{
		exit_vec_canon[i].Set(PIXEL_TO_METERS(points_exit_canon[i * 2 + 0]), PIXEL_TO_METERS(points_exit_canon[i * 2 + 1]));
	}

	sensors.add(App->physics->CreatePolygonSensor(0, 0, 4, exit_vec_canon, EXIT_CANON));


	int points_entry_rail_1[8] = {
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

	int points_exit_rail_1[8] = {
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

	int points_mid_rail_1[8] = {
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


	int left_points_side_exit[8] =
	{
		420, 750,
		420, 767,
		447, 768,
		446, 752
	};

}

void ModuleSceneIntro::spawnBall() {
	balls.add(App->physics->CreateBall(488, 800, 14));
	balls.getLast()->data->listener = this;
}