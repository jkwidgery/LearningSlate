#pragma once

class FDeveloperProfileStyle
{
public:
	static void Initialize();
	static const ISlateStyle& Get();
	static void Shutdown();
	static FName GetStyleSetName();

private:
	static TSharedRef<FSlateStyleSet> Create();

	
	static TSharedPtr<FSlateStyleSet> StyleInstance;
};