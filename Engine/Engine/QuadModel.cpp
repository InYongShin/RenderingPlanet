
#include "QuadModel.hpp"

void QuadModel::createQuad(const glm::vec3& ltPtn, const glm::vec3& rtPtn, const glm::vec3& lbPtn, const glm::vec3& rbPtn)
{
	if(this->isCreated && this->mesh.nTris>0 && this->mesh.nVerts>0)
	{
		this->mesh.clear();
	}
	this->mesh.createQuad(ltPtn, rtPtn, lbPtn, rbPtn);
	this->mesh.createMeshGL();
	this->isCreated = true;
}

void QuadModel::createQuad(const glm::vec3& ltPtn, const glm::vec3& rbPtn)
{
	if(this->isCreated && this->mesh.nTris>0 && this->mesh.nVerts>0)
	{
		this->mesh.clear();
	}

	glm::vec3 rtPtn = glm::vec3(rbPtn.x, ltPtn.y, ltPtn.z);
	glm::vec3 lbPtn = glm::vec3(ltPtn.x, rbPtn.y, rbPtn.z);

	this->mesh.createQuad(ltPtn, rtPtn, lbPtn, rbPtn);
	this->mesh.createMeshGL();
	this->isCreated = true;
}
