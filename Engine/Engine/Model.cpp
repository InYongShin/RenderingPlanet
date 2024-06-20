
#include "Model.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"

void Model::loadProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath /*= nullptr*/, const char* tessControlPath /*= nullptr*/, const char* tessEvaluatePath /*= nullptr*/)
{
	program.loadShaders(vertexPath, vertexPath, geometryPath, tessControlPath, tessEvaluatePath);
	if (program.isUsable() == false)
	{
		assert(false);
		std::cerr << "Error loading program" << std::endl;
	}
}

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
	if(this->program.isUsable() == false)
	{
		// TODO: Load default program
		// ex) program.loadShaders("shaders/default.vert", "shaders/default.frag");
	}
	this->program.use();

	this->program.setUniform("modelMat", this->_modelMat);
	this->program.setUniform("viewMat", SceneManager::getInstance()->getCamera().viewMat());
	this->program.setUniform("projMat", SceneManager::getInstance()->getCamera().projMat());

	for(int i = 0; i<this->texIDs.size(); ++i)
	{
		int texID = this->texIDs[i];
		Texture& tex = TextureManager::getInstance()->getTexture(texID);
		tex.bind(i, this->program, shaderNames[i].c_str());
	}

	glBindVertexArray(this->mesh.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh.eBuf);
	glDrawElements(GL_TRIANGLES, this->mesh.nTris*3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::clear()
{
	program.clear();
	mesh.clear();
}
