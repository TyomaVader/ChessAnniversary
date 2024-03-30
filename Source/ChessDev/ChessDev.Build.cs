// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ChessDev : ModuleRules
{
	public ChessDev(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;
	
		PublicDependencyModuleNames.AddRange(
			new string[] { 
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				// "OnlineSubsystemEOS",
				// "OnlineSubsystemUtils",
				"CommonLoadingScreen",
				"Json",
				"JsonUtilities"
			}
		);

		PublicIncludePaths.AddRange(
			new string[] { 
				"ChessDev"
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"InputCore",
				"RenderCore",
				"DeveloperSettings",
				"EnhancedInput",
				"NetCore",
				"RHI",
				"Gauntlet",
				"UMG",
				"CommonUI",
				"CommonInput",
				"GameSettings",
				"CommonGame",
				"CommonUser",
				"GameSubtitles",
				"GameplayMessageRuntime",
				"AudioMixer",
				"UIExtension",
				"ClientPilot",
				"AudioModulation",
				"EngineSettings",
				"Slate",
				"SlateCore"
			}
		);
		
		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");
	}
}