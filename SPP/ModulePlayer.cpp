#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"

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

	//player_ball = App->physics->CreateBall(435, 50, 14);

	right_flipper = App->physics->CreateRightFlipper();
	left_flipper = App->physics->CreateLeftFlipper();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//Blitting ball texture
	//App->renderer->Blit(ball_tex, player_ball->body->GetPosition().x, player_ball->body->GetPosition().y, NULL, 1.0f, player_ball->body->GetAngle());

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



