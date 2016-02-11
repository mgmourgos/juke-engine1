#include "Physics.h"
#include <algorithm>

Box Physics::actPhysicsOn(double elapsed_time_ms, double max_velocity, Box box) {

	//Position and Velocity setting
	//box.x += (0.5f) * box.ax * elapsed_time_ms * elapsed_time_ms + box.vx * elapsed_time_ms;
	//box.y += (0.5f) * box.ay * elapsed_time_ms * elapsed_time_ms + box.vy * elapsed_time_ms;

	box.x += box.vx * elapsed_time_ms;
	box.y += box.vy * elapsed_time_ms;

	box.vx += box.ax * elapsed_time_ms;
	box.vy += box.ay * elapsed_time_ms;

	//Terminal Velocity Check
	if (box.ax < 0.0f) {
		box.vx = std::max(box.vx, -max_velocity);
	}
	else if (box.ax > 0.0f) {
		box.vx = std::min(box.vx, max_velocity);
	}

	return box;
}

Box handleCollisions(std::vector<std::shared_ptr<CollisionData>> collision_data, int elapsed_time_ms)
{
	Box collision_box;

	return collision_box;
}
