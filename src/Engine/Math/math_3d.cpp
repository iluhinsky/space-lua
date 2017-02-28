#include "math_3d.h"

EulerAngles ToEulerAngles(glm::vec3 target, glm::vec3 up)
{
	EulerAngles angles;


	target = glm::normalize(target);
	up     = glm::normalize(up);

	printf("target = %f %f %f\n", target.x, target.y, target.z);
	printf("up = %f %f %f\n", up.x, up.y, up.z);
	
	angles._theta = abs(acos (up.z));
	
	if (up.y > 0) angles._theta *= -1;
	

	if (up.z == 1 || up.z == -1)
	{
		angles._phi = 0;
		angles._csi = 0;// acos(target.x);
	}
	else
	{
		angles._phi = asin(glm::clamp(abs(up.x / sin(angles._theta)), 0.0f + 0.00001f, 1.0f - 0.00001f));
		angles._csi = -1*asin(glm::clamp(abs(target.z / sin(angles._theta)), 0.0f + 0.00001f, 1.0f - 0.00001f));
	}
	if (target.z < 0) angles._csi *= -1;
	if (target.z < 0) angles._phi *= -1;

	printf("theta = %f\n", angles._theta);
	printf("phi = %f\n", angles._phi);
	printf("csi = %f\n", angles._csi);
	return angles;
}