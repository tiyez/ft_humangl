#include "ftm.hpp"
// General form of the Projection Matrix
//
// uh = Cot( fov/2 ) == 1/Tan(fov/2)
// uw / uh = 1/aspect
//
//   uw         0       0       0
//    0        uh       0       0
//    0         0      f/(f-n)  1
//    0         0    -fn/(f-n)  0

ftm::mat4 ftm::infinitePerspective(float fov, float aspect, float znear) {
	ftm::mat4 res(0);

	float zfar = (float)std::numeric_limits<int>::max();

	float frustumDepth = zfar - znear;
	float oneOverDepth = 1 / -frustumDepth;

	res.r1.y = 1 / tanf(0.5f * fov);
	res.r0.x = res.r1.y / aspect;
	res.r2.z = zfar * oneOverDepth;
	res.r2.w = -1;
	res.r3.z = (zfar * znear) * oneOverDepth;

	return res;
}

ftm::mat4 ftm::lookAt(const ftm::vec3 &cam_pos, const ftm::vec3 &cam_dir, const ftm::vec3 &up_dir) {
	ftm::mat4 cam_translation(1);
	ftm::mat4 cam_rotation(1);

	ftm::vec3 forward = ftm::normalize(cam_dir);
	ftm::vec3 up = ftm::normalize(up_dir);
	ftm::vec3 right = ftm::cross(forward, up); // TODO: check

	cam_translation.r3 = ftm::vec4 (-cam_pos.x, -cam_pos.y, -cam_pos.z, 1);
	cam_rotation.r0 = ftm::vec4 (right.x, up.x, forward.x, 0);
	cam_rotation.r1 = ftm::vec4 (right.y, up.y, forward.y, 0);
	cam_rotation.r2 = ftm::vec4 (right.z, up.z, forward.z, 0);

	return cam_rotation * cam_translation;
}