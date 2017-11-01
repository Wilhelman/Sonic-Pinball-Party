#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"

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

	flipper_hit_fx = App->audio->LoadFx("audio/sound_fx/flipper_hit.wav");
	plunge_fx = App->audio->LoadFx("audio/sound_fx/fire_ball.wav");

	rect_rFlipper.h = 20;
	rect_rFlipper.w = 60;
	rect_rFlipper.x = 398;
	rect_rFlipper.y = 1314;

	rect_lFlipper.h = 20;
	rect_lFlipper.w = 60;
	rect_lFlipper.x = 398;
	rect_lFlipper.y = 1342;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	if (left_flipper != NULL)
	{
		App->physics->world->DestroyBody(left_flipper->body);
		left_flipper = NULL;
	}
	
	if (right_flipper != NULL)
	{
		App->physics->world->DestroyBody(right_flipper->body);
		right_flipper = NULL;
	}

	if (plunge != NULL)
	{
		App->physics->world->DestroyBody(plunge->body);
		plunge = NULL;
	}

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	// ----- Blitting flippers -----

	b2Vec2 anchorRVec = right_flipper->joint->GetAnchorB();
	App->renderer->Blit(flippers_tex, 258, 760 ,&rect_rFlipper, 1.0f, right_flipper->GetRotation(), anchorRVec.x + 48, anchorRVec.y-4);

	b2Vec2 anchorLVec = left_flipper->joint->GetAnchorB();
	App->renderer->Blit(flippers_tex, 166, 760, &rect_lFlipper, 1.0f, left_flipper->GetRotation(), anchorLVec.x, anchorLVec.y - 4);


	// ----- Flippers and plunge audio control -----

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		App->audio->PlayFx(flipper_hit_fx);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		App->audio->PlayFx(flipper_hit_fx);

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
		App->audio->PlayFx(plunge_fx);
		

	// ----- Flippers and plunge input control -----

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		left_flipper->body->ApplyTorque(-60.0f, true);
	else 
		left_flipper->body->ApplyTorque(10.0f, true);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		right_flipper->body->ApplyTorque(60.0f, true);
	else 
		right_flipper->body->ApplyTorque(-10.0f, true);

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		plunge->body->ApplyForceToCenter(b2Vec2(0, 250), true);

	return UPDATE_CONTINUE;
}