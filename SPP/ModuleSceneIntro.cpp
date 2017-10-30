#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ray_on = sensed = false;
	bg = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	ball_lost = false;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	bg = App->textures->Load("pinball/pinball_sonic_spritesheet.png");

	rect_bg.h = SCREEN_HEIGHT;
	rect_bg.w = SCREEN_WIDTH;
	rect_bg.x = 0;
	rect_bg.y = 0;

	rect_ball.h = 28;
	rect_ball.w = 28;
	rect_ball.x = 0;
	rect_ball.y = 1418;



	// ------- Setting up wall chains -------

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

	triangle_L = App->physics->CreateChain(0, 0, points_triangle_L, 14, groupIndex::RIGID_PINBALL, 1.0f);

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

	triangle_R = App->physics->CreateChain(0, 0, points_triangle_R, 14, groupIndex::RIGID_PINBALL, 1.0f);


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

	pinball_walls.add(App->physics->CreateChain(0, 0, points_top_wall, 160, groupIndex::RIGID_PINBALL, 0.01f));
	
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
		34, 840,
		54, 840,
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
		477, 832,
		499, 832,
		504, 825,
		504, 433,
		500, 425,
		494, 420,
		482, 417,
		468, 427,
		465, 426,
		475, 411
	};


	pinball_walls.add(App->physics->CreateChain(0, 0, points_bottom_wall, 108, groupIndex::RIGID_PINBALL, 0.01f));

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

	pinball_walls.add(App->physics->CreateChain(0, 0, points_right_L, 28, groupIndex::RIGID_PINBALL, 0.01f));

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

	pinball_walls.add(App->physics->CreateChain(0, 0, points_left_L, 28, groupIndex::RIGID_PINBALL, 0.01f));


	//upper map
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

	tunnel_walls.add(App->physics->CreateChain(0, 0, points_upper_tunnel, 68, groupIndex::BALL, 0.01f));


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

	tunnel_walls.add(App->physics->CreateChain(0, 0, points_bottom_tunnel_1, 44, groupIndex::BALL, 0.01f));


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

	tunnel_walls.add(App->physics->CreateChain(0, 0, points_bottom_tunnel_2, 38, groupIndex::BALL, 0.01f));


	int points_rail[156] = 
	{
		138, 282,
		113, 257,
		101, 244,
		85, 228,
		71, 211,
		63, 184,
		63, 130,
		73, 97,
		85, 77,
		111, 52,
		139, 40,
		161, 35,
		199, 34,
		232, 40,
		242, 45,
		256, 47,
		266, 49,
		273, 53,
		279, 59,
		285, 75,
		296, 101,
		301, 128,
		301, 175,
		289, 219,
		272, 254,
		230, 298,
		148, 340,
		59, 384,
		33, 409,
		32, 534,
		34, 539,
		39, 544,
		66, 557,
		82, 564,
		94, 575,
		102, 590,
		103, 621,
		108, 629,
		108, 636,
		107, 644,
		103, 649,
		96, 652,
		85, 653,
		76, 647,
		72, 639,
		72, 632,
		76, 623,
		76, 602,
		73, 595,
		66, 589,
		47, 580,
		25, 570,
		9, 558,
		2, 546,
		2, 404,
		11, 390,
		35, 367,
		210, 280,
		245, 244,
		259, 216,
		270, 185,
		270, 115,
		265, 101,
		253, 88,
		244, 80,
		240, 74,
		227, 67,
		203, 62,
		160, 62,
		135, 69,
		119, 79,
		104, 96,
		96, 115,
		92, 132,
		92, 178,
		100, 204,
		117, 224,
		154, 261
	};

	tunnel_walls.add(App->physics->CreateChain(0, 0, points_rail, 156, groupIndex::BALL, 0.01f));


	// ----- Dead sensor for lost balls -----

	sensors.add(App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT + 80, 150, 80));

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

	for (p2List_item<PhysBody*>* rail_item = rail_walls.getFirst(); rail_item != NULL; rail_item = rail_item->next)
	{
		App->physics->world->DestroyBody(rail_item->data->body);
	}

	if (triangle_L != NULL)
	{
		delete triangle_L;
		triangle_L = NULL;
	}

	balls.clear();
	pinball_walls.clear();
	sensors.clear();
	tunnel_walls.clear();
	rail_walls.clear();

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//Blitting background
	App->renderer->Blit(bg, 0, 0, &rect_bg, 1.0f);

	// ----- Ball creation -----
	//TODO: balls we'll be created at Start() and every time you lose one
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		balls.add(App->physics->CreateBall(App->input->GetMouseX(), App->input->GetMouseY(), 14));
		balls.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	// ----- Blitting ------
	p2List_item<PhysBody*>* ball_item = balls.getFirst();

	while (ball_item != NULL)
	{
		int x, y;
		ball_item->data->GetPosition(x, y);

		//TODO: control sprite according to ball velocity
		float vel = ball_item->data->body->GetAngularVelocity();

		App->renderer->Blit(bg, x, y, &rect_ball, 1.0f, ball_item->data->GetRotation());

		ball_item = ball_item->next;
	}
	
	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------


	if (ball_lost) {
		for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next) {
			App->physics->world->DestroyBody(bc->data->body);
		}
		balls.clear();

		balls.add(App->physics->CreateBall(488, 800, 14));
		balls.getLast()->data->listener = this;
		ball_lost = false;
	}

	/*c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}*/

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	//App->audio->PlayFx(bonus_fx);

	if (bodyA == sensor || bodyB == sensor) {
		
	}
	for (p2List_item<PhysBody*>* bc = balls.getFirst(); bc != NULL; bc = bc->next) {
		if (bodyA == bc->data)
		{
			
			if (bodyB->physType == DEAD_SENSOR) {
				ball_lost = true;

				for (p2List_item<PhysBody*>* t_w = tunnel_walls.getFirst(); t_w != NULL; t_w = t_w->next) {
					
					b2Fixture* fixture = t_w->data->body->GetFixtureList();

					while (fixture != NULL)
					{
						b2Filter newFilter;
						newFilter.groupIndex = groupIndex::RIGID_PINBALL;
						fixture->SetFilterData(newFilter);
						fixture = fixture->GetNext();
					}
				}

				break;
				
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