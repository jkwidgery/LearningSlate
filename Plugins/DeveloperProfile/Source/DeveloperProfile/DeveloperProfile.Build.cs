// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class DeveloperProfile : ModuleRules
{
	public DeveloperProfile(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine"
		});
	}
}