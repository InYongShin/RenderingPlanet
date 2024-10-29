
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

void SphereModel::createSphere(float radius, int slices, int stacks, const int noiseWidth, const int noiseHeight, const float noiseWeight /*= 1.f*/)
{
	if (this->isCreated && this->mesh.nTris > 0 && this->mesh.nVerts > 0)
	{
		this->mesh.clear();
	}
	this->mesh.createSphere(radius, slices, stacks, noiseWidth, noiseHeight, noiseWeight);
	this->mesh.createMeshGL();
	this->isCreated = true;
}

