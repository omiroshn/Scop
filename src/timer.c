#include "scop.h"

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
	update_time(timer);
}

void		update_time(t_timer *timer)
{
	timer->current = mach_absolute_time() - timer->start;
	timer->current_time = timer->current * timer->numer / timer->denom;
	timer->ttime = (float)(timer->current_time / 1000) / 1000000.0f;
	timer->delta_time = timer->ttime - timer->old_time;
	timer->old_time = timer->ttime;
}

float		time_elapsed(t_timer *timer)
{
	return (mach_absolute_time() - timer->start);
}