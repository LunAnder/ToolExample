// Fill out your copyright notice in the Description page of Project Settings.
#include "ToolExampleEditor.h"

#include "CustomDataType/ExampleDataTypeActions.h"
#include "CustomProjectSettings/ExampleSettings.h"
#include "DetailsCustomization/ExampleActorDetails.h"
#include "EditorMode/ExampleEdModeTool.h"
#include "MenuTool/ExampleMenuTool.h"
#include "TabTool/ExampleTabTool.h"
#include "ToolExample/DetailsCustomization/ExampleActor.h"
//
#include "Developer/Settings/Public/ISettingsContainer.h"
#include "ISettingsModule.h"


IMPLEMENT_GAME_MODULE( FToolExampleEditor, ToolExampleEditor )

TSharedRef<FWorkspaceItem> FToolExampleEditor::MenuRoot = FWorkspaceItem::NewGroup( FText::FromString( "Menu Root" ) );


void FToolExampleEditor::AddModuleListeners()
{
	/// Add tools
	ModuleListeners.Add( MakeShareable( new FExampleMenuTool ) );
	ModuleListeners.Add( MakeShareable( new FExampleTabTool ) );
	ModuleListeners.Add( MakeShareable( new FExampleEdModeTool ) );
}


FToolExampleEditor& FToolExampleEditor::Get()
{
	return FModuleManager::LoadModuleChecked<FToolExampleEditor>( "ToolExampleEditor" );
}


bool FToolExampleEditor::IsAvailable()
{
	return FModuleManager::Get().IsModuleLoaded( "ToolExampleEditor" );
}


void FToolExampleEditor::StartupModule()
{
	if( !IsRunningCommandlet() )
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>( "LevelEditor" );

		LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();

		MenuExtender = MakeShareable( new FExtender );

		MenuExtender->AddMenuBarExtension( "Window", EExtensionHook::After, nullptr, FMenuBarExtensionDelegate::CreateRaw( this, &FToolExampleEditor::MakePulldownMenu ) );

		LevelEditorMenuExtensibilityManager->AddExtender( MenuExtender );
	}


	{ /// Register custom layouts
		static FName PropertyEditor( "PropertyEditor" );

		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>( PropertyEditor );

		PropertyModule.RegisterCustomClassLayout( AExampleActor::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic( &FExampleActorDetails::MakeInstance ) );
	}


	{ /// Register custom types:
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>( "AssetTools" ).Get();

		/// Add custom category
		EAssetTypeCategories::Type const ExampleCategory = AssetTools.RegisterAdvancedAssetCategory( FName( TEXT( "Example" ) ), FText::FromString( "Example" ) );

		/// Register our custom asset with example category
		TSharedPtr<IAssetTypeActions> const Action = MakeShareable( new FExampleDataTypeActions( ExampleCategory ) );

		AssetTools.RegisterAssetTypeActions( Action.ToSharedRef() );

		/// Save it here for unregister later
		CreatedAssetTypeActions.Add( Action );
	}


	{ /// Register settings:
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>( "Settings" );

		if( SettingsModule != nullptr )
		{
			TSharedPtr<ISettingsContainer> ProjectSettingsContainer = SettingsModule->GetContainer( "Project" );

			ProjectSettingsContainer->DescribeCategory( "ExampleCategory", FText::FromString( "Example Category" ), FText::FromString( "Example settings description text here" ) );

			SettingsModule->RegisterSettings( "Project", "ExampleCategory", "ExampleSettings", FText::FromString( "Example Settings" ), FText::FromString( "Configure Example Settings" ), GetMutableDefault<UExampleSettings>() );
		}
	}


	IExampleModuleInterface::StartupModule();
}


void FToolExampleEditor::ShutdownModule()
{
	if( FModuleManager::Get().IsModuleLoaded( "PropertyEditor" ) )
	{ /// Unregister custom layouts
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>( "PropertyEditor" );

		PropertyModule.UnregisterCustomClassLayout( AExampleActor::StaticClass()->GetFName() );
	}


	if( FModuleManager::Get().IsModuleLoaded( "AssetTools" ) )
	{ /// Unregister all the asset types that we registered
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>( "AssetTools" ).Get();

		for( int32 IdxAction = 0; IdxAction < CreatedAssetTypeActions.Num(); ++IdxAction )
		{
			AssetTools.UnregisterAssetTypeActions( CreatedAssetTypeActions[IdxAction].ToSharedRef() );
		}
	}


	CreatedAssetTypeActions.Empty();


	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>( "Settings" );

	if( SettingsModule != nullptr )
	{ /// Unregister settings
		SettingsModule->UnregisterSettings( "Project", "ExampleCategory", "ExampleSettings" );
	}


	IExampleModuleInterface::ShutdownModule();
}


void FToolExampleEditor::AddMenuExtension( FMenuExtensionDelegate const& InDelegate, FName const InHookName, TSharedPtr<FUICommandList> const& InCmds, EExtensionHook::Position const InPos )
{
	MenuExtender->AddMenuExtension( InHookName, InPos, InCmds, InDelegate );
}


void FToolExampleEditor::MakePulldownMenu( FMenuBarBuilder& RefBuilder )
{
	RefBuilder.AddPullDownMenu( FText::FromString( "Example" ),
															FText::FromString( "Open the Example menu" ),
															FNewMenuDelegate::CreateRaw( this, &FToolExampleEditor::FillPulldownMenu ),
															"Example",
															FName( TEXT( "ExampleMenu" ) ) );
}


void FToolExampleEditor::FillPulldownMenu( FMenuBuilder& RefBuilder )
{
	RefBuilder.BeginSection( "ExampleSection", FText::FromString( "Section 1" ) );
	RefBuilder.AddMenuSeparator( FName( "Section_1" ) );
	RefBuilder.EndSection();

	RefBuilder.BeginSection( "ExampleSection", FText::FromString( "Section 2" ) );
	RefBuilder.AddMenuSeparator( FName( "Section_2" ) );
	RefBuilder.EndSection();
}
