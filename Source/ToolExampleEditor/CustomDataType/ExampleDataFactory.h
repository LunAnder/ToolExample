#pragma once
#include "UnrealEd.h"

#include "ExampleDataFactory.generated.h"



UCLASS()
class UExampleDataFactory : public UFactory
{
	GENERATED_UCLASS_BODY()


public: /// Helper function
	static void MakeExampleDataFromText( class UExampleData* PtrData, const TCHAR*& RefPtrBuffer, const TCHAR* PtrBufferEnd );


public: /// UFactory Interface
	virtual bool FactoryCanImport( const FString& InFilename ) override;

	virtual UObject* FactoryCreateNew( UClass* PtrClass, UObject* PtrParent, FName InName, EObjectFlags InFlags, UObject* PtrContext, FFeedbackContext* PtrWarn ) override;
	virtual UObject* FactoryCreateText( UClass* PtrClass, UObject* PtrParent, FName InName, EObjectFlags InFlags, UObject* PtrContext, const TCHAR* PtrType, const TCHAR*& RefPtrBuffer, const TCHAR* PtrBufferEnd, FFeedbackContext* PtrWarn ) override;
};
