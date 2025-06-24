#include "RenderPass.hpp"

#include "TextureManager.hpp"
#include "SceneManager.hpp"

void RenderPass::loadProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessControlPath, const char* tessEvaluatePath)
{
	std::shared_ptr<Program> prog = std::make_shared<Program>(vertexPath, fragmentPath, geometryPath, tessControlPath, tessEvaluatePath);
	if (prog->isUsable() == false)
	{
		assert(false);
		std::cerr << "Error loading program" << std::endl;
		return;
	}
	
	setProgram(prog);
}

void RenderPass::setState()
{
	if (this->program == nullptr)
	{
		std::cerr << "Program is nullptr" << std::endl;
		return;
	}

	// TODO: State 包府
	if (this->depthTest) glEnable(GL_DEPTH_TEST);
	else				 glDisable(GL_DEPTH_TEST);
	if (this->cullFace)  glEnable(GL_CULL_FACE);
	else				 glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderPass::addModel(const std::shared_ptr<Model>& model)
{
	if (model == nullptr)
	{
		std::cerr << "Model is nullptr" << std::endl;
		return;
	}

	this->models.push_back(model);
}

void RenderPass::draw()
{
	if(this->program == nullptr || !this->program->isUsable())
	{
		// TODO: Load default program
		// e.g., program.loadShaders("shaders/default.vert", "shaders/default.frag");
		std::cerr << "program is nullptr" << std::endl;
		return;
	}

	this->program->use();

	this->program->setUniform("viewMat", SceneManager::getInstance()->getCamera().viewMat());
	this->program->setUniform("projMat", SceneManager::getInstance()->getCamera().projMat());

	setState();

	for(const auto& model : this->models)
	{
		if (model == nullptr)
		{
			std::cerr << "Model is nullptr" << std::endl;
			continue;
		}

		this->program->setUniform("modelMat", model->getModelMat());

		std::vector<int> texIDs = model->getTexIDs();
		std::vector<std::string> shaderNames = model->getShaderNames();
		for (int i = 0; i < texIDs.size(); ++i)
		{
			int texID = texIDs[i];
			Texture& tex = TextureManager::getInstance()->getTexture(texID);
			tex.bind(tex.getTexID(), program, shaderNames[i].c_str());
		}

		// TODO: Primitive 包府
		const Mesh& mesh = model->getMesh();
		glBindVertexArray(mesh.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.eBuf);
		glDrawElements(mesh.primitive, mesh.nTris * 3, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderPass::onDepthTest()
{
	this->depthTest = GL_TRUE;
}

void RenderPass::offDepthTest()
{
	this->depthTest = GL_FALSE;
}

void RenderPass::onCullFace()
{
	this->cullFace = GL_TRUE;
}

void RenderPass::offCullFace()
{
	this->cullFace = GL_FALSE;
}
