#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleFadeToBlack.h"
#include "p2SString.h"

#include <string.h>
#include<stdio.h>


ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	score = 0;
}

ModuleUI::~ModuleUI()
{}

// Load assets
bool ModuleUI::Start()
{
	LOG("Loading ModuleUI assets");
	bool ret = true;
	font_score = this->Load("pinball/score_numberPoints.png", "0123456789", 1);

	return ret;
}

// Update: draw background
update_status ModuleUI::Update()
{

	update_status status = UPDATE_CONTINUE;
	if (App->scene_intro->IsEnabled() && App->fade->current_step == ModuleFadeToBlack::fade_step::fade_to_black) {
		char str[10];
		sprintf_s(str, "%i", score);

		int x_correction = SCREEN_WIDTH / 2;
		if (score > 99)
			x_correction -= fonts[font_score].char_w;
		if (score > 999)
			x_correction -= fonts[font_score].char_w;
		if (score > 9999)
			x_correction -= fonts[font_score].char_w;
		this->BlitText(x_correction, SCREEN_HEIGHT / 2 - fonts[font_score].char_h / 2, font_score, str);

	}

	p2SString title("SONIC PINBALL PARTY	              SCORE: %i    BALLS LEFT: %i", App->ui->score, App->scene_intro->balls_left);

	App->window->SetTitle(title.GetString());

	return status;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading ModuleUI");

	bool ret = true;

	this->UnLoad(font_score);

	return ret;
}

// Load new texture from file path
int ModuleUI::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].graphic == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}

	fonts[id].graphic = tex; // graphic: pointer to the texture
	fonts[id].rows = rows; // rows: rows of characters in the texture

	fonts[id].len = strlen(characters);

	fonts[id].row_chars = fonts[id].len / rows;

	strcpy_s(fonts[id].table, MAX_FONT_CHARS, characters);

	uint wTex = 0, hTex = 0;
	App->textures->GetSize(tex, wTex, hTex);

	fonts[id].char_w = wTex / fonts[id].row_chars;
	fonts[id].char_h = hTex / rows;


	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleUI::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

// Render text using a bitmap font
void ModuleUI::BlitText(int x, int y, int font_id, const char* text) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	if (strcmp(text, "0") == 0)
		text = "00";

	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for (uint i = 0; i < len; ++i)
	{
		for (int j = 0; j < font->len; j++)
		{
			if (text[i] == fonts->table[j]) {
				rect.x = rect.w * (j % font->row_chars);
				rect.y = rect.h * (j / font->row_chars);
				App->renderer->Blit(font->graphic, x, y, &rect, 1.0f);
				x += font->char_w;
				break;
			}
		}

	}
}
