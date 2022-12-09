#include <gb/gb.h>
#include <stdbool.h>

bool is_grace_period_over(UINT8 n_grace_frames, UINT16 time, UINT16 prev_time) {
	UINT8 n_frames = 0;

	if (time < prev_time) {
		n_frames = (UINT16_MAX - prev_time) + time;
	}
	else {
		n_frames = time - prev_time - 1; //-1 doesnt count current frame
	}

	if (n_frames >= n_grace_frames) {
		return true;
	}

    return false;
}