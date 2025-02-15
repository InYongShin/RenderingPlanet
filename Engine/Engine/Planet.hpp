#ifndef PLANET_HPP
#define PLANET_HPP

#include "SphereModel.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "RenderPass.hpp"

#include <string>

class Planet
{
private:
	std::string _name = "";
	float _radius = 0.f;

	std::vector<std::shared_ptr<Model>> models;

	bool isCreated = false;

protected:
	std::shared_ptr<SphereModel> sphere = nullptr;

public:

	// TODO: Texture를 어떻게 넘겨줄지. shader name 고민 필요
	void createPlanet(const float radius, const glm::vec3& position, const int texID, const std::string& shaderTexName);
	void createPlanet(const float radius, const glm::vec3& position);
	void createPlanet(const float radius, const glm::vec3& position, const int noiseWidth, const int noiseHeight, const float noiseWeight);
	void createPlanet(const float radius, const glm::vec3& position, const int resolution);

	inline std::string getName() const { return this->_name; }

	inline void setPosition(const glm::vec3& position) { this->sphere->setPosition(position); }
	inline glm::vec3 getPosition() const { return this->sphere->getPosition(); }

	inline float getRadius() const { return this->_radius; }

	inline std::shared_ptr<SphereModel> getSphere() const { return this->sphere; }

	void setRenderPass(const std::shared_ptr<RenderPass>& renderPass);

	void draw() const;
	
	virtual void update();

	void addModel(const std::shared_ptr<Model>& model);
	void addTexture(int id, const std::string& shaderName);

	Planet() {};

	Planet(const std::string& name,
		const glm::vec3& position,
		const float radius,
		const int resolution)
		: _name(name), _radius(radius)
	{
		createPlanet(radius, position, resolution);
	}

	Planet(const std::string& name,
		   const glm::vec3& position,
		   const float radius,
		   const int resolution,
		   const std::shared_ptr<Program>& sphereProgram)
		: _name(name), _radius(radius)
	{
		createPlanet(radius, position, resolution);
	}

	Planet(const std::string& name, 
		const glm::vec3& position, 
		const float radius)
		: _name(name), _radius(radius)
	{
		createPlanet(radius, position);
	}

	Planet(const std::string& name, 
		const glm::vec3& position, 
		const float radius, 
		const std::shared_ptr<Program>& sphereProgram)
		: _name(name), _radius(radius)
	{
		createPlanet(radius, position);
	}

	Planet(const std::string& name, 
		   const glm::vec3& position, 
		   const float radius, 
		   const std::shared_ptr<Program>& sphereProgram,
		   const int noiseWidth, 
		   const int noiseHeight,
		   const float noiseWeight)
		: _name(name), _radius(radius)
	{
		createPlanet(radius, position, noiseWidth, noiseHeight, noiseWeight);
	}

	Planet(const std::string& name, 
		   const glm::vec3& position, 
		   const float radius, 
		   const std::shared_ptr<Program>& sphereProgram, 
		   const int texID, 
		   const std::string& shaderTexName)
		: _name(name), _radius(radius)
	{
		createPlanet(radius, position, texID, shaderTexName);
	}

	virtual ~Planet() {}
};


#endif /* PLANET_HPP */
