#include "DeveloperProfileEditorModule.h"
#include "DeveloperProfileAssetTypeActions.h"
#include "AssetToolsModule.h"
#include "DeveloperProfileStyle.h"

IMPLEMENT_MODULE(FDeveloperProfileEditorModule, DeveloperProfileEditor)

void FDeveloperProfileEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTypeActions = MakeShared<FDeveloperProfileAssetTypeActions>();
	AssetTools.RegisterAssetTypeActions(AssetTypeActions.ToSharedRef());

	FDeveloperProfileStyle::Initialize();
}

void FDeveloperProfileEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(AssetTypeActions.ToSharedRef());
	}

	FDeveloperProfileStyle::Shutdown();
}