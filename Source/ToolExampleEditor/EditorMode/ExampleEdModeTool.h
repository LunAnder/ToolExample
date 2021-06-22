#pragma once

#include "ToolExampleEditor/ExampleTabToolBase.h"

class ExampleEdModeTool : public FExampleTabToolBase
{
public:
	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	virtual ~ExampleEdModeTool() override	{}

	
private:
	void RegisterStyleSet();
	void UnregisterStyleSet();

	void RegisterEditorMode();
	void UnregisterEditorMode();

	
private:
	static TSharedPtr< class FSlateStyleSet > StyleSet;
};