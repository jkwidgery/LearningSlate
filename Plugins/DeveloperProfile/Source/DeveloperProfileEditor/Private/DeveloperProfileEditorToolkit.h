#pragma once
#include "DeveloperProfileAsset.h"
#include "IDetailsView.h"
#include "Toolkits/AssetEditorToolkit.h"

class FDeveloperProfileEditorToolkit : public FAssetEditorToolkit
{
public:
	void InitEditor(UDeveloperProfileAsset* InAsset);
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	
	virtual FText GetBaseToolkitName() const override;
	virtual FName GetToolkitFName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FText GetToolkitName() const override;


private:

	TSharedRef<SDockTab> OnSpawnProfileCardPanel(const FSpawnTabArgs& TabArgs);
	TSharedRef<SDockTab> OnSpawnDetailsPanel(const FSpawnTabArgs& TabArgs);
	
	TObjectPtr<UDeveloperProfileAsset> Asset;
	TSharedPtr<IDetailsView> DetailsView;

	static const FName ProfileCardTabID;
	static const FName DetailsTabID;
	
};
