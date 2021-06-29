#pragma once
#include "ToolExampleEditor/ExampleTabToolBase.h"


class FSlateStyleSet;


class ExampleEdModeTool : public FExampleTabToolBase
{
public:
	virtual ~ExampleEdModeTool() override {}

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;


private:
	void RegisterEditorMode();
	void RegisterStyleSet();

	void UnregisterEditorMode();
	void UnregisterStyleSet();


private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};
