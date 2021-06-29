#pragma once

#include "ToolExampleEditor/IExampleModuleInterface.h"
#include "ToolExampleEditor/ToolExampleEditor.h"


class FExampleTabToolBase : public IExampleModuleListenerInterface, public TSharedFromThis<FExampleTabToolBase>
{
public: /// Public Virtual Overriden Functions
	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;


public: /// Public Virtual Functions
	virtual void Initialize(); // In this function; Set TabName/TabDisplayName/ToolTipText
	virtual void MakeMenuEntry( FMenuBuilder& RefBuilder );

	virtual TSharedRef<SDockTab> SpawnTab( FSpawnTabArgs const& InArgs );


protected: /// Protected Variables
	FName TabName;

	FText TabDisplayName;
	FText ToolTipText;
};



inline void FExampleTabToolBase::OnStartupModule()
{
	Initialize();
	FGlobalTabmanager::Get()
		->RegisterNomadTabSpawner( TabName, FOnSpawnTab::CreateRaw( this, &FExampleTabToolBase::SpawnTab ) )
		.SetGroup( FToolExampleEditor::Get().GetMenuRoot() )
		.SetDisplayName( TabDisplayName )
		.SetTooltipText( ToolTipText );
}


inline void FExampleTabToolBase::OnShutdownModule()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner( TabName );
}


inline void FExampleTabToolBase::Initialize()
{ // In this function; Set TabName/TabDisplayName/ToolTipText
}


inline TSharedRef<SDockTab> FExampleTabToolBase::SpawnTab( FSpawnTabArgs const& InArgs )
{
	return SNew( SDockTab );
}


inline void FExampleTabToolBase::MakeMenuEntry( FMenuBuilder& RefBuilder )
{
	FGlobalTabmanager::Get()->PopulateTabSpawnerMenu( RefBuilder, TabName );
}
