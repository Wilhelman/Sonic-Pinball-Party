#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleRender.h"




ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//player_ball = ball_tex = NULL;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	right_flipper = App->physics->CreateRightFlipper();
	left_flipper = App->physics->CreateLeftFlipper();

	/*rect_ball.h = 28;
	rect_ball.w = 28;
	rect_ball.x = 0;
	rect_ball.y = 1418;*/

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	balls.clear();

	if (left_flipper != NULL)
	{
		delete left_flipper;
		left_flipper = NULL;
	}
	
	if (right_flipper != NULL)
	{
		delete right_flipper;
		right_flipper = NULL;
	}

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//Blitting ball texture
	//App->renderer->Blit(ball_tex, player_ball->body->GetPosition().x, player_ball->body->GetPosition().y, NULL, 1.0f, player_ball->body->GetAngle());

	// ----- Blitting ball textures ------
	p2List_item<PhysBody*>* ball_item = balls.getFirst();

	while (ball_item != NULL)
	{
		int x, y;
		ball_item->data->GetPosition(x, y);

		//if (ball_item->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			//App->renderer->Blit(bg, x, y, &rect_ball, 1.0f, ball_item->data->GetRotation());

		ball_item = ball_item->next;
	}


	// ----- Ball creation -----
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		balls.add(App->physics->CreateBall(App->input->GetMouseX(), App->input->GetMouseY(), 14));
		balls.getLast()->data->listener = this;
	}

	// ----- Flipper input control -----

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		left_flipper->body->ApplyTorque(-60.0f, true);
	}
	else {
		left_flipper->body->ApplyTorque(10.0f, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		right_flipper->body->ApplyTorque(60.0f, true);
	}
	else {
		right_flipper->body->ApplyTorque(-10.0f, true);
	}

	return UPDATE_CONTINUE;
}



