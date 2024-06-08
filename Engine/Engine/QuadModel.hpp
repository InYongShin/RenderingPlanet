#ifndef QUADMODEL_HPP
#define QUADMODEL_HPP

#include "Model.hpp"

#include "GLTools.hpp"

class QuadModel : public Model
{
private:

public:

	void createQuad(const glm::vec3& ltPtn, const glm::vec3& rtPtn, const glm::vec3& lbPtn, const glm::vec3& rbPtn);
	void createQuad(const glm::vec3& ltPtn, const glm::vec3& rbPtn);

	QuadModel() {}
	QuadModel(const glm::vec3& position) : Model(position) {}
	virtual ~QuadModel() { clear(); }
};


#endif /* QUADMODEL_HPP */
