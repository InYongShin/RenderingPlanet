
#include "Model.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"

void Model::setPosition(const glm::vec3& position)
{
	this->position = position;
	this->_modelMat = glm::translate(glm::mat4(1.f), this->position);
}

void Model::addTexture(int id, const std::string& shaderName)
{
	if(id < 0)
	{
		return;
	}
	this->texIDs.push_back(id);
	this->shaderNames.push_back(shaderName);
}

void Model::draw()
{
}

void Model::clear()
{
	this->mesh.clear();
}
