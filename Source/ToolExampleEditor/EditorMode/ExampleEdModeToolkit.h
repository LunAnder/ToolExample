#pragma once

#include "EditorModeManager.h"
#include "ExampleEdMode.h"
#include "SExampleEdModeWidget.h"


class FEdMode;
class SWidget;


class FExampleEdModeToolkit : public FModeToolkit
{
public:
	FExampleEdModeToolkit();


public: /** IToolkit interface */
	virtual FName GetToolkitFName() const override;

	virtual FText GetBaseToolkitName() const override;

	virtual FEdMode* GetEditorMode() const override;

	virtual TSharedPtr<SWidget> GetInlineContent() const override;


private:
	TSharedPtr<SExampleEdModeWidget> ExampleEdModeWidget;
};



inline FExampleEdModeToolkit::FExampleEdModeToolkit()
{
	SAssignNew( ExampleEdModeWidget, SExampleEdModeWidget );
}


inline FName FExampleEdModeToolkit::GetToolkitFName() const
{
	return FName( "ExampleEdMode" );
}


inline FText FExampleEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT( "BuilderModeToolkit", "DisplayName", "Builder" );
}


inline FEdMode* FExampleEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode( FExampleEdMode::EM_Example );
}


inline TSharedPtr<SWidget> FExampleEdModeToolkit::GetInlineContent() const
{
	return ExampleEdModeWidget;
}
