// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class RunAway : ModuleRules
{
    public RunAway(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "AIModule"});

        PrivateDependencyModuleNames.AddRange(new string[] { "Paper2D" });
    }
}
