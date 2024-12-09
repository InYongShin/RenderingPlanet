#ifndef SPHEREMODEL_HPP
#define SPHEREMODEL_HPP

#include "Model.hpp"

class SphereModel : public Model
{
private:


public:

	void createSphere(float radius, int slices, int stacks);
	void createSphere(float radius, int slices, int stacks, const int noiseWidth, const int noiseHeight, const float noiseWeight = 1.f);
	void createSphere(float radius, int resolution);

	SphereModel() {}
	virtual ~SphereModel() { clear(); }
};


#endif /* SPHEREMODEL_HPP */
