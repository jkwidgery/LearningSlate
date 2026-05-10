using UnrealBuildTool;

public class DeveloperProfileEditor : ModuleRules
{
	public DeveloperProfileEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UnrealEd",
			"Slate",
			"SlateCore",
			"AssetTools",
			"PropertyEditor",
			"DeveloperProfile",
			"AppFramework",
			"InputCore"
		});
		
	}
}