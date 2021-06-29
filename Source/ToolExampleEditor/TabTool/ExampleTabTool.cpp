#include "ExampleTabTool.h"

#include "ExampleTabToolPanel.h"
#include "ToolExampleEditor/ToolExampleEditor.h"



void FExampleTabTool::OnStartupModule()
{
	FExampleTabToolBase::OnStartupModule();

	FToolExampleEditor::Get().AddMenuExtension( FMenuExtensionDelegate::CreateRaw( this, &FExampleTabTool::MakeMenuEntry ), FName( "Section_2" ) );
}


void FExampleTabTool::OnShutdownModule()
{
	FExampleTabToolBase::OnShutdownModule();
}


void FExampleTabTool::Initialize()
{
	TabName = "TabTool";

	TabDisplayName = FText::FromString( "Tab Tool" );

	ToolTipText = FText::FromString( "Tab Tool Window" );
}


TSharedRef<SDockTab> FExampleTabTool::SpawnTab( FSpawnTabArgs const& InArgs )
{
	TSharedRef<SDockTab> SpawnedTab = SNew( SDockTab ).TabRole( ETabRole::NomadTab )[SNew( SExampleTabToolPanel ).Tool( SharedThis( this ) )];

	return SpawnedTab;
}
