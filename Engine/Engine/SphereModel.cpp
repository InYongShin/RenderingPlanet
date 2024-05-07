
#include "SphereModel.hpp"

void SphereModel::createSphere(float radius, int slices /*= 63*/, int stacks /*= 65*/)
{
	if(this->isCreated && this->mesh.nTris>0 && this->mesh.nVerts>0)
	{
		this->mesh.clear();
	}
	this->mesh.createSphere(radius, slices, stacks);
	this->mesh.createMeshGL();
	this->isCreated = true;
}

