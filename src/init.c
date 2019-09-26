#include "scop.h"

void init_glew(SDL_Window *window)
{
	SDL_GLContext context;
	GLenum err;

	context = SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	err = glewInit();
	if (err != GLEW_OK)
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

SDL_Window *init_window()
{
	SDL_Window *window;
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		printf("Unable to initialize SDL.\n");
		return (0);
	}
	window = SDL_CreateWindow("SCOP",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		960, 540, SDL_WINDOW_OPENGL);
	if (!window)
	{
		printf("Unable to create SDL window.\n");
		return (0);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
						SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetSwapInterval(1);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (window);
}

void		init_timer(t_timer *timer)
{
	mach_timebase_info_data_t coeff;

	mach_timebase_info(&coeff);
	timer->numer = coeff.numer;
	timer->denom = coeff.denom;
	timer->current_time = 0;
	timer->start = mach_absolute_time();
	timer->current = timer->start;
	timer->ttime = 0.0f;
	timer->old_time = 0.0f;
}

void		tick(t_timer *timer)
{
	float delta_ttime;

	timer->current = mach_absolute_time() - timer->start;
	timer->current_time = timer->current * timer->numer / timer->denom;
	timer->ttime = (float)(timer->current_time / 1000) / 1000000.0f;
	timer->delta_time = timer->ttime - timer->old_time;
	timer->old_time = timer->ttime;
}

void		init_keys(short *key_states)
{
	for (int i = 0; i < 255; i++)
		key_states[i] = 0;
}