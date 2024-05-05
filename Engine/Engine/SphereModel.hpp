#ifndef SPHEREMODEL_HPP
#define SPHEREMODEL_HPP

#include "Model.hpp"

class SphereModel : public Model
{
private:


public:

	void createSphere(float radius, int slices = 63, int stacks = 65);

	SphereModel() {}
	virtual ~SphereModel() { clear(); }
};


#endif /* SPHEREMODEL_HPP */
