#include "ExampleEdModeTool.h"

#include "ExampleEdMode.h"
#include "ToolExampleEditor/ToolExampleEditor.h"
//
#include "AssetRegistryModule.h"
#include "EditorModeRegistry.h"
#include "Textures/SlateIcon.h"


#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( StyleSet->RootToContentDir( RelativePath, TEXT( ".png" ) ), __VA_ARGS__ )


TSharedPtr<FSlateStyleSet> FExampleEdModeTool::StyleSet = nullptr;


void FExampleEdModeTool::OnStartupModule()
{
	RegisterStyleSet();

	RegisterEditorMode();
}


void FExampleEdModeTool::OnShutdownModule()
{
	UnregisterStyleSet();

	UnregisterEditorMode();
}


void FExampleEdModeTool::RegisterStyleSet()
{
	FVector2D const Icon20x20( 20.F, 20.F );
	FVector2D const Icon40x40( 40.F, 40.F );

	if( StyleSet.IsValid() )
	{ // Only register once
		return;
	}


	StyleSet = MakeShareable( new FSlateStyleSet( "ExampleEdModeToolStyle" /*RENAME_ME*/ ) );

	StyleSet->SetContentRoot( FPaths::ProjectPluginsDir() / TEXT( "ToolExample/Resources" ) );
	StyleSet->SetCoreContentRoot( FPaths::ProjectPluginsDir() / TEXT( "ToolExample/Resources" ) );

	{ // Spline editor
		StyleSet->Set( "ExampleEdMode", new IMAGE_BRUSH( TEXT( "IconExampleEditorMode" ), Icon40x40 ) );
		StyleSet->Set( "ExampleEdMode.Small", new IMAGE_BRUSH( TEXT( "IconExampleEditorMode" ), Icon20x20 ) );
	}


	FSlateStyleRegistry::RegisterSlateStyle( *StyleSet.Get() );
}


void FExampleEdModeTool::UnregisterStyleSet()
{
	if( StyleSet.IsValid() )
	{
		FSlateStyleRegistry::UnRegisterSlateStyle( *StyleSet.Get() );
		ensure( StyleSet.IsUnique() );

		StyleSet.Reset();
	}
}


void FExampleEdModeTool::RegisterEditorMode()
{
	FEditorModeRegistry::Get().RegisterMode<FExampleEdMode>( FExampleEdMode::EM_Example,
																													 FText::FromString( "Example Editor Mode" /*RENAME_ME*/ ),
																													 FSlateIcon( StyleSet->GetStyleSetName(), "ExampleEdMode", "ExampleEdMode.Small" ),
																													 true,
																													 500 );
}


void FExampleEdModeTool::UnregisterEditorMode()
{
	FEditorModeRegistry::Get().UnregisterMode( FExampleEdMode::EM_Example );
}


#undef IMAGE_BRUSH
