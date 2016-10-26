#pragma once

#ifndef APPMANAGER_H
#define APPMANAGER_H

#include "RenderManager.h"

class AppManager
{
public:
	AppManager();
	~AppManager();

	void Startup();
	void Shutdown();

private:
};

#endif // APPMANAGER_H

