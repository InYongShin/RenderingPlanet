#ifndef PLANET_HPP
#define PLANET_HPP

#include "SphereModel.hpp"
#include "Program.hpp"
#include "Texture.hpp"

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

	glm::vec3 centerPosition;
	float orbitSpeed;

public:

	// TODO: Texture를 어떻게 넘겨줄지. shader name 고민 필요
	void createPlanet(const float radius, const glm::vec3& position, const int texID, const std::string& shaderTexName);
	void createPlanet(const float radius, const glm::vec3& position);
	void createPlanet(const float radius, const glm::vec3& position, const int noiseWidth, const int noiseHeight, const float noiseWeight);
	void createPlanet(const float radius, const glm::vec3& position, const int resolution);

	void setSphereProgram(const std::shared_ptr<Program>& program);

	inline std::string getName() const { return this->_name; }

	inline void setPosition(const glm::vec3& position) { this->sphere->setPosition(position); }
	inline glm::vec3 getPosition() const { return this->sphere->getPosition(); }

	inline float getRadius() const { return this->_radius; }

	void draw() const;
	
	virtual void update();

	void addModel(const std::shared_ptr<Model>& model);
	void addTexture(int id, const std::string& shaderName);

	Planet()
		: centerPosition(glm::vec3(0.0f)), orbitSpeed(0.0f) {}

	Planet(const std::string& name,
		   const glm::vec3& position,
		   const float radius,
		   const int resolution,
		   const std::shared_ptr<Program>& sphereProgram)
		: _name(name), _radius(radius), centerPosition(glm::vec3(0.f)), orbitSpeed(0.f)
	{
		createPlanet(radius, position, resolution);
		setSphereProgram(sphereProgram);
	}

	Planet(const std::string& name, 
		const glm::vec3& position, 
		const float radius, 
		const std::shared_ptr<Program>& sphereProgram)
		: _name(name), _radius(radius), centerPosition(glm::vec3(0.f)), orbitSpeed(0.f)
	{
		createPlanet(radius, position);
		setSphereProgram(sphereProgram);
	}

	Planet(const std::string& name, 
		   const glm::vec3& position, 
		   const float radius, 
		   const std::shared_ptr<Program>& sphereProgram,
		   const int noiseWidth, 
		   const int noiseHeight,
		   const float noiseWeight)
		: _name(name), _radius(radius), centerPosition(glm::vec3(0.f)), orbitSpeed(0.f)
	{
		createPlanet(radius, position, noiseWidth, noiseHeight, noiseWeight);
		setSphereProgram(sphereProgram);
	}

	Planet(const std::string& name, 
		   const glm::vec3& position, 
		   const float radius, 
		   const std::shared_ptr<Program>& sphereProgram, 
		   const int texID, 
		   const std::string& shaderTexName,
		   const glm::vec3 centerPosition,
		   const float orbitSpeed)
		: _name(name), _radius(radius), centerPosition(centerPosition), orbitSpeed(orbitSpeed)
	{
		createPlanet(radius, position, texID, shaderTexName);
		setSphereProgram(sphereProgram);
	}

	virtual ~Planet() {}
};


#endif /* PLANET_HPP */
