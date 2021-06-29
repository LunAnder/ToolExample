#pragma once
#include "ToolExampleEditor/IExampleModuleInterface.h"



class FExampleMenuTool final : public IExampleModuleListenerInterface, public TSharedFromThis<FExampleMenuTool>
{
public: /// Public Virtual Overriden Functions
	virtual ~FExampleMenuTool() override {}

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;


public: /// Public Functions
	void MakeMenuEntry( FMenuBuilder& RefBuilder );
	void MakeSubMenu( FMenuBuilder& RefBuilder );


protected: /// Protected Functions
	void MapCommands();


protected: /// UI Command functions
	void MenuCommand1();
	void MenuCommand2();
	void MenuCommand3();
	void OnTagToAddTextCommited( FText const& InText, ETextCommit::Type InCommitInfo );

	FName TagToAdd;

	FText GetTagToAddText() const;

	FReply AddTag();


protected: /// Protected Variables
	TSharedPtr<FUICommandList> CommandList;
};
