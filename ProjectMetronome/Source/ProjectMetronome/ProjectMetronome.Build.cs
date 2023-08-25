// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectMetronome : ModuleRules
{
	public ProjectMetronome(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore",
			"GameplayAbilities", "GameplayTags", "GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput", "EnhancedInput" });
	}
}
