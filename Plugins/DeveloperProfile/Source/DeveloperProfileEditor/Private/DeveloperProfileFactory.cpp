#include "DeveloperProfileFactory.h"
#include "DeveloperProfileAsset.h"

UDeveloperProfileFactory::UDeveloperProfileFactory()
{
	SupportedClass = UDeveloperProfileAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UDeveloperProfileFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDeveloperProfileAsset>(InParent, InClass, InName, Flags);
}

bool UDeveloperProfileFactory::ShouldShowInNewMenu() const
{
	return true;
}