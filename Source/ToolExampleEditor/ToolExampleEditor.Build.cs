// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class ToolExampleEditor : ModuleRules
{
		public ToolExampleEditor(ReadOnlyTargetRules Target) : base(Target)
		{
				PublicIncludePaths.AddRange(new string[] {
						// ... add public include paths required here ...
				});

				PublicIncludePathModuleNames.AddRange(new string[] {
						"AdvancedPreviewScene",
				});

				PrivateIncludePaths.AddRange(new string[] {
						// ... add other private include paths required here ...
				});

				PrivateIncludePathModuleNames.AddRange(new string[] {
						"AssetRegistry",
						"MainFrame",
						"DesktopPlatform",
						"ContentBrowser",
						"AssetTools",
						"MeshReductionInterface",
						"SequenceRecorder",
						"AnimationBlueprintEditor",
				});

				PublicDependencyModuleNames.AddRange(
						new string[] { "Core", "Engine", "CoreUObject", "InputCore", "LevelEditor", "Slate",
													 "EditorStyle", "AssetTools", "EditorWidgets", "UnrealEd",
													 "BlueprintGraph", "AnimGraph", "ComponentVisualizers",
													 "AdvancedPreviewScene", "ToolExample" });

				PrivateDependencyModuleNames.AddRange(new string[] {
						"AnimGraph",
						"AnimGraphRuntime",
						"AppFramework",
						"ApplicationCore",
						"BlueprintGraph",
						"CommonMenuExtensions",
						"ComponentVisualizers",
						"ContentBrowserData",
						"Core",
						"CoreUObject",
						"CurveEditor",
						"EditorFramework",
						"EditorStyle",
						"EditorWidgets",
						"Engine",
						"GraphEditor",
						"InputCore",
						"Json",
						"JsonUtilities",
						"Kismet",
						"KismetWidgets",
						"MainFrame",
						"PinnedCommandList",
						"PropertyEditor",
						"RenderCore",
						"RHI",
						"Sequencer",
						"SequencerWidgets",
						"Slate",
						"SlateCore",
						"StatusBar",
						"TimeManagement",
						"ToolExample",
						"UnrealEd",
						// ... add private dependencies that you statically link with here ...
						"ToolMenus",
				});

				DynamicallyLoadedModuleNames.AddRange(new string[] {
						"ContentBrowser",
						"Documentation",
						"DesktopPlatform",
						"MeshReductionInterface",
						"SequenceRecorder",
				});
		}
}
