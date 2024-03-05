// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ChessDev : ModuleRules
{
	public ChessDev(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystemEOS", "OnlineSubsystemUtils" });

		PublicIncludePaths.AddRange(new string[] { "ChessDev" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");
	}
}