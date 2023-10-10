// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QLProj : ModuleRules
{
    public QLProj(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});

        PrivateDependencyModuleNames.AddRange(new string[] {"GameplayTasks", "Slate", "SlateCore"});

        PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem", "GameplayAbilities", "GameplayTags" });
    }
}
