#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "Singleton.hpp"

class RenderManager : public Singleton<RenderManager>
{
private:
	friend class Singleton;

public:

	RenderManager() {}
	virtual ~RenderManager() {}
};

#endif /* RENDERMANAGER_HPP */
