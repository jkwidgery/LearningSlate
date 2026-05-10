#include "DeveloperProfileAssetTypeActions.h"
#include "DeveloperProfileAsset.h"
#include "DeveloperProfileEditorToolkit.h"

void FDeveloperProfileAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
                                                        TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	if (InObjects.IsEmpty())
		return;
	
	TSharedRef<FDeveloperProfileEditorToolkit> EditorToolkit = MakeShareable(new FDeveloperProfileEditorToolkit());
	//TODO: Add support for opening multiple assets
	if (UDeveloperProfileAsset* DeveloperProfile = Cast<UDeveloperProfileAsset>(InObjects[0]))
		EditorToolkit->InitEditor(DeveloperProfile);
}

FText FDeveloperProfileAssetTypeActions::GetName() const
{
	return NSLOCTEXT("DeveloperProfile", "DeveloperProfileAssetTypeActions", "Developer Profile");
}

FColor FDeveloperProfileAssetTypeActions::GetTypeColor() const
{
	return FColor(138, 154, 91);// Green like a Turtle :) 
}

UClass* FDeveloperProfileAssetTypeActions::GetSupportedClass() const
{
	return UDeveloperProfileAsset::StaticClass();
}

uint32 FDeveloperProfileAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}