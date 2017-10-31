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
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	
	right_flipper = App->physics->CreateRightFlipper();
	left_flipper = App->physics->CreateLeftFlipper();
	plunge = App->physics->CreatePlunge();
	
	flippers_tex = App->textures->Load("pinball/pinball_sonic_spritesheet.png");
	

	rect_rFlipper.h = 20;
	rect_rFlipper.w = 60;
	rect_rFlipper.x = 398;
	rect_rFlipper.y = 1314;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	

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

	



	//TODO: postions are not well obtained for some reason
	/*int right_flipper_x, right_flipper_y;
	right_flipper->GetPosition(right_flipper_x, right_flipper_y);
	App->renderer->Blit(flippers_tex, 450, 500, &rect_rFlipper);*/

	b2Vec2 anchorVec = right_flipper->joint->GetAnchorB();
	App->renderer->Blit(flippers_tex, 258, 760 ,&rect_rFlipper, 1.0f, right_flipper->GetRotation(), anchorVec.x + 48, anchorVec.y-4);


	//TODO: control sprite according to ball velocity

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		
		plunge->body->ApplyForceToCenter(b2Vec2(0, 250),true);
	}
	else {
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



