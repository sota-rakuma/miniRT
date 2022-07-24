#include "../minirt.h"

double vec3d_dot(t_vec3d a, t_vec3d b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3d vec3d_cross(t_vec3d a, t_vec3d b)
{
	return ((t_vec3d){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
		});
}

t_vec3d vec3d_sub(t_vec3d a, t_vec3d b) {
	t_vec3d ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}

t_vec3d vec3d_add(t_vec3d a, t_vec3d b) {
	t_vec3d ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}

t_vec3d vec3d_mult(t_vec3d a, double n) {
	return (t_vec3d){a.x * n, a.y * n, a.z * n};
}

double vec3d_length(t_vec3d a) {
	return sqrt(vec3d_dot(a, a));
}
