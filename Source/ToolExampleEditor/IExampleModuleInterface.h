#pragma once


class IExampleModuleListenerInterface
{
public:
	virtual ~IExampleModuleListenerInterface() = default;

	virtual void OnStartupModule(){};
	virtual void OnShutdownModule(){};
};


class IExampleModuleInterface : public IModuleInterface
{
public:
	void StartupModule() override
	{
		if( !IsRunningCommandlet() )
		{
			AddModuleListeners();
			for( int32 i = 0; i < ModuleListeners.Num(); ++i )
			{
				ModuleListeners[i]->OnStartupModule();
			}
		}
	}

	void ShutdownModule() override
	{
		for( int32 i = 0; i < ModuleListeners.Num(); ++i )
		{
			ModuleListeners[i]->OnShutdownModule();
		}
	}

	virtual void AddModuleListeners(){};

protected:
	TArray<TSharedRef<IExampleModuleListenerInterface>> ModuleListeners;
};
