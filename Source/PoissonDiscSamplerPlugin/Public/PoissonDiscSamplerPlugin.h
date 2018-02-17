/*
 
 -----
 
*/

#pragma once

#include "ModuleManager.h"

class FPoissonDiscSamplerPlugin : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

