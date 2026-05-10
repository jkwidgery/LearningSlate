#pragma once

#include "Modules/ModuleManager.h"

class FDeveloperProfileEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<class FDeveloperProfileAssetTypeActions> AssetTypeActions;
};