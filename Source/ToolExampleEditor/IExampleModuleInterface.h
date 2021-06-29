#pragma once


class IExampleModuleListenerInterface
{
public: /// Public Virtual Functions
	virtual ~IExampleModuleListenerInterface() = default;

	virtual void OnStartupModule(){};
	virtual void OnShutdownModule(){};
};



class IExampleModuleInterface : public IModuleInterface
{
public: /// Public Virtual Overriden Functions
	virtual void AddModuleListeners(){};
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


protected: /// Protected Variables
	TArray<TSharedRef<IExampleModuleListenerInterface>> ModuleListeners;
};



inline void IExampleModuleInterface::StartupModule()
{
	if( !IsRunningCommandlet() )
	{
		AddModuleListeners();

		for( int32 IdxListener = 0; IdxListener < ModuleListeners.Num(); ++IdxListener )
		{
			ModuleListeners[IdxListener]->OnStartupModule();
		}
	}
}


inline void IExampleModuleInterface::ShutdownModule()
{
	for( int32 IdxListener = 0; IdxListener < ModuleListeners.Num(); ++IdxListener )
	{
		ModuleListeners[IdxListener]->OnShutdownModule();
	}
}
