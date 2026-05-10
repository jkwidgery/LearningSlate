#pragma once
#include "DeveloperProfileAsset.h"

class SDeveloperProfileCardWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDeveloperProfileCardWidget)
		{}
		SLATE_ARGUMENT(UDeveloperProfileAsset*, DeveloperProfileAsset)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

private:
	TObjectPtr<UDeveloperProfileAsset> Asset;
	
};
