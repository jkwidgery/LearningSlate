#include "DeveloperProfileAssetTypeActions.h"
#include "DeveloperProfileAsset.h"

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