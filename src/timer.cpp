/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:25:40 by omiroshn          #+#    #+#             */
/*   Updated: 2019/09/05 15:25:41 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdint.h>
// #include <mach/mach_time.h>

// uint64_t	start;
// uint64_t	current;
// uint64_t	current_time;
// uint64_t	numer;
// uint64_t	denom;
// float		ttime;
// float		old_time;

// void		init_timer()
// {
// 	mach_timebase_info_data_t coeff;

// 	mach_timebase_info(&coeff);
// 	numer = coeff.numer;
// 	denom = coeff.denom;
// 	current_time = 0;
// 	start = mach_absolute_time();
// 	current = start;
// 	ttime = 0.0f;
// 	old_time = 0.0f;
// }

// float delta_time = 0.0f;

// void		tick()
// {
// 	float delta_ttime;

// 	current = mach_absolute_time() - start;
// 	current_time = current * numer / denom;
// 	ttime = (float)(current_time / 1000) / 1000000.0f;
// 	delta_time = ttime - old_time;
// 	old_time = ttime;
// }
