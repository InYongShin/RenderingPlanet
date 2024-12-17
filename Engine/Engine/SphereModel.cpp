
#include "SphereModel.hpp"

void SphereModel::createSphere(float radius, int slices, int stacks)
{
	if(this->isCreated && this->mesh.nTris>0 && this->mesh.nVerts>0)
	{
		this->mesh.clear();
	}
	this->mesh.createSphere(radius, slices, stacks);
	this->mesh.createMeshGL();
	this->isCreated = true;
}

void SphereModel::createSphere(float radius, int slices, int stacks, const float noiseWeight)
{
	if (this->isCreated && this->mesh.nTris > 0 && this->mesh.nVerts > 0)
	{
		this->mesh.clear();
	}
	this->mesh.createSphere(radius, slices, stacks, noiseWeight);
	this->mesh.createMeshGL();
	this->isCreated = true;
}

void SphereModel::createSphere(float radius, int resolution)
{
	if (this->isCreated && this->mesh.nTris > 0 && this->mesh.nVerts > 0)
	{
		this->mesh.clear();
	}
	this->mesh.createSphere(radius, resolution);
	this->mesh.createMeshGL();
	this->isCreated = true;
}

