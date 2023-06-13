#include <sys/time.h>
#include "atshared.h"

/**
 * Get the current server epoch time in milliseconds.
 */
uint64_t get_time_since_epoch()
{
	struct timeval tv;

	gettimeofday(&tv, 0);

	uint64_t milliseconds =
	    (uint64_t)(tv.tv_sec) * 1000 +
	    (uint64_t)(tv.tv_usec) / 1000;

	return milliseconds;
}

