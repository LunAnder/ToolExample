#pragma once
#include "ToolExampleEditor/ExampleTabToolBase.h"


class FSlateStyleSet;


class FExampleEdModeTool : public FExampleTabToolBase
{
public:
	virtual ~FExampleEdModeTool() override {}

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
