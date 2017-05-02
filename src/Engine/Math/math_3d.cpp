#include "math_3d.h"

std::map<Direction, Direction> oppositeDirections = 
{
	{ x_up  , x_down },
	{ y_up  , y_down },
	{ z_up  , z_down },
	{ x_down, x_up   },
	{ y_down, y_up   },
	{ z_down, z_up   }
};

Direction oppositeTo(Direction direction)
{
	return oppositeDirections[direction];
}

bool isEqual(glm::vec3 vec1, glm::vec3 vec2)
{
	if (round(vec1.x) == round(vec2.x) &&
		round(vec1.y) == round(vec2.y) &&
		round(vec1.z) == round(vec2.z))
		return true;

	return false;
}

btVector3 toBT(glm::vec3 vec)
{
	return btVector3(vec.x, vec.y, vec.z);
}

glm::vec3 toGLM(btVector3& vector)
{
	float x = vector.getX();
	float y = vector.getY();
	float z = vector.getZ();;

	return glm::vec3(x, y, z);
}

glm::vec4 toVec4(glm::vec3& vector)
{
	return glm::vec4(vector, 1.0f);
}

glm::mat4 toGLM(btMatrix3x3& matrix)
{
	glm::mat4 GLM_matrix(1.0f);

	GLM_matrix[0][0] = matrix[0][0]; GLM_matrix[0][1] = matrix[0][1]; GLM_matrix[0][2] = matrix[0][2];
	GLM_matrix[1][0] = matrix[1][0]; GLM_matrix[1][1] = matrix[1][1]; GLM_matrix[1][2] = matrix[1][2];
	GLM_matrix[2][0] = matrix[2][0]; GLM_matrix[2][1] = matrix[2][1]; GLM_matrix[2][2] = matrix[2][2];

	return GLM_matrix;
}

glm::mat3 toGLM_M3x3(btMatrix3x3& matrix)
{
	glm::mat3 GLM_matrix(1.0f);

	GLM_matrix[0][0] = matrix[0][0]; GLM_matrix[0][1] = matrix[0][1]; GLM_matrix[0][2] = matrix[0][2];
	GLM_matrix[1][0] = matrix[1][0]; GLM_matrix[1][1] = matrix[1][1]; GLM_matrix[1][2] = matrix[1][2];
	GLM_matrix[2][0] = matrix[2][0]; GLM_matrix[2][1] = matrix[2][1]; GLM_matrix[2][2] = matrix[2][2];

	return GLM_matrix;
}