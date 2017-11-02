#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack(Application* app, bool start_enabled = true);
	~ModuleFadeToBlack();

	bool Start();
	update_status Update();
	bool FadeToBlack(Module* module_off, Module* module_on, float time = 2.0f);
	bool FadeIsOver();

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} 
	
	current_step = fade_step::none;

private:

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
	Module* moduleOff;
	Module* moduleOn;
};

#endif //__MODULEFADETOBLACK_H__