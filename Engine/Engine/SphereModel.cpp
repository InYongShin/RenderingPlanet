
#include "SphereModel.hpp"

void SphereModel::createSphere(float radius, int slices /*= 63*/, int stacks /*= 65*/)
{
	this->mesh.clear();
	this->mesh.createSphere(radius, slices, stacks);
	this->mesh.createMeshGL();
}

