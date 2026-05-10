#include "DeveloperProfileEditorToolkit.h"

#include "DeveloperProfileCardWidget.h"

const FName FDeveloperProfileEditorToolkit::ProfileCardTabID = "Profile Card";
const FName FDeveloperProfileEditorToolkit::DetailsTabID = "Details Panel";

void FDeveloperProfileEditorToolkit::InitEditor(UDeveloperProfileAsset* InAsset)
{
	Asset = InAsset;
	const TSharedRef<FTabManager::FLayout> TabLayout = FTabManager::NewLayout("DeveloperProfileEditorLayout")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
		->SetOrientation
		(
			Orient_Horizontal
		)
		->Split
		(
			FTabManager::NewStack()->AddTab(ProfileCardTabID, ETabState::OpenedTab)
		)
		->Split
		(
			FTabManager::NewStack()->AddTab(DetailsTabID, ETabState::OpenedTab)
		)
	);
	
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	
	InitAssetEditor(EToolkitMode::Standalone,
	nullptr,	
	GetToolkitFName(),
	TabLayout,
	true,
	true,
	Asset);
	
	DetailsView->SetObject(Asset);
	
}

void FDeveloperProfileEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManagerRef)
{
	FAssetEditorToolkit::RegisterTabSpawners(TabManagerRef);
	
	TabManagerRef->RegisterTabSpawner(ProfileCardTabID,
		FOnSpawnTab::CreateSP(this, &FDeveloperProfileEditorToolkit::OnSpawnProfileCardPanel));
		
	TabManagerRef->RegisterTabSpawner(DetailsTabID,
		FOnSpawnTab::CreateSP(this, &FDeveloperProfileEditorToolkit::OnSpawnDetailsPanel));
}

void FDeveloperProfileEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManagerRef)
{
	FAssetEditorToolkit::UnregisterTabSpawners(TabManagerRef);
	
	TabManagerRef->UnregisterTabSpawner(ProfileCardTabID);
	TabManagerRef->UnregisterTabSpawner(DetailsTabID);
}

FText FDeveloperProfileEditorToolkit::GetBaseToolkitName() const
{
	return FText::FromString("Developer Profile Editor");
}

FName FDeveloperProfileEditorToolkit::GetToolkitFName() const
{
	return FName("Developer Profile Editor");
}

FString FDeveloperProfileEditorToolkit::GetWorldCentricTabPrefix() const
{
	return FString("Developer Profile Editor");
}

FLinearColor FDeveloperProfileEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(138.f/255.f, 154.f/255.f, 91.f/255.f);;// Green like a Turtle :) 
}

FText FDeveloperProfileEditorToolkit::GetToolkitName() const
{
	if (!Asset)
		return FText::FromString("Developer Profile Editor");
	
	FString TabTitle =  FString::Printf(TEXT("%s - DevEditor"), *(Asset->DisplayName));
	return FText::FromString(TabTitle);
}

TSharedRef<SDockTab> FDeveloperProfileEditorToolkit::OnSpawnProfileCardPanel(const FSpawnTabArgs& TabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::MajorTab)
		[
			SNew(SDeveloperProfileCardWidget)
			.DeveloperProfileAsset(Asset)
		];
}

TSharedRef<SDockTab> FDeveloperProfileEditorToolkit::OnSpawnDetailsPanel(const FSpawnTabArgs& TabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			DetailsView.ToSharedRef()
		];
}
