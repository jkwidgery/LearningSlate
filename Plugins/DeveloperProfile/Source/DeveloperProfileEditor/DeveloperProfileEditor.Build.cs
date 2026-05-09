using UnrealBuildTool;

public class DeveloperProfileEditor : ModuleRules
{
	public DeveloperProfileEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UnrealEd",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"AssetTools",
			"PropertyEditor",
			"ToolMenus",
			"DeveloperProfile"
		});
		
	}
}