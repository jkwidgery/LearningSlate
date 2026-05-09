#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "DeveloperProfileFactory.generated.h"

UCLASS()
class UDeveloperProfileFactory : public UFactory
{
	GENERATED_BODY()

public:

	UDeveloperProfileFactory();

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
};