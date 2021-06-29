// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "IExampleModuleInterface.h"
//
#include "Editor/LevelEditor/Public/LevelEditor.h"
#include "IAssetTypeActions.h"
#include "SlateExtras.h"
#include "UnrealEd.h"


class FToolExampleEditor : public IExampleModuleInterface
{
public: /// Public Static Functions
	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static FToolExampleEditor& Get();

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	* @return True if the module is loaded and ready to use
	*/
	static bool IsAvailable();


public: /// IModuleInterface implementation
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


public: /// Public Virtual Overriden Functions
	virtual void AddModuleListeners() override;


public: /// Public Functions
	void AddMenuExtension( FMenuExtensionDelegate const& InDelegate, FName InHookName, TSharedPtr<FUICommandList> const& InCmds = nullptr, EExtensionHook::Position InPos = EExtensionHook::Before );

	TSharedRef<FWorkspaceItem> GetMenuRoot();
	;


protected: /// Protected Functions
	void FillPulldownMenu( FMenuBuilder& RefBuilder );
	void MakePulldownMenu( FMenuBarBuilder& RefBuilder );


protected: /// Protected Static Variables
	static TSharedRef<FWorkspaceItem> MenuRoot;


protected: /// Protected Variables
	TSharedPtr<FExtender> MenuExtender;

	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;

	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};



inline TSharedRef<FWorkspaceItem> FToolExampleEditor::GetMenuRoot()
{
	return MenuRoot;
}
