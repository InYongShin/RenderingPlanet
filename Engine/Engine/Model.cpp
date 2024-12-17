
#include "Model.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"

void Model::loadProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath /*= nullptr*/, const char* tessControlPath /*= nullptr*/, const char* tessEvaluatePath /*= nullptr*/)
{
	if(this->renderPass == nullptr)
	{
		assert(false);
		std::cerr << "RenderPass is nullptr" << std::endl;
		return;
	}

	std::unique_ptr<Program> program = std::make_unique<Program>(vertexPath, fragmentPath, geometryPath, tessControlPath, tessEvaluatePath);
	if (program->isUsable() == false)
	{
		assert(false);
		std::cerr << "Error loading program" << std::endl;
		return;
	}

	this->renderPass->setProgram(std::move(program));
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
	if (this->renderPass == nullptr)
	{
		assert(false);
		std::cerr << "RenderPass is nullptr" << std::endl;
		return;
	}

	const std::shared_ptr<Program>& program = this->renderPass->getProgram();
	if (program->isUsable() == false)
	{
		// TODO: Load default program
		// ex) program.loadShaders("shaders/default.vert", "shaders/default.frag");

		assert(false);
		std::cerr << "Program is not usable" << std::endl;
		return;
	}

	program->use();

	program->setUniform("modelMat", this->_modelMat);
	program->setUniform("viewMat", SceneManager::getInstance()->getCamera().viewMat());
	program->setUniform("projMat", SceneManager::getInstance()->getCamera().projMat());

	for (int i = 0; i < this->texIDs.size(); ++i)
	{
		int texID = this->texIDs[i];
		Texture& tex = TextureManager::getInstance()->getTexture(texID);
		tex.bind(tex.getTexID(), program, shaderNames[i].c_str());
	}

	this->renderPass->setVertexData(this->mesh.vao, this->mesh.eBuf, this->mesh.nTris, GL_TRIANGLES);
	this->renderPass->draw();
}

void Model::clear()
{
	this->mesh.clear();
}
