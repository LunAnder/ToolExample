#pragma once
#include "ToolExampleEditor/ExampleTabToolBase.h"



class FExampleTabTool final : public FExampleTabToolBase
{
public: /// Public Virtual Overriden Functions
	virtual ~FExampleTabTool() override {}

	virtual void Initialize() override;
	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	virtual TSharedRef<SDockTab> SpawnTab( FSpawnTabArgs const& InArgs ) override;
};
