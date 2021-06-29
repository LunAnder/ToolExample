#pragma once
#include "ExampleDataFactory.h"

#include "ReimportExampleDataFactory.generated.h"

UCLASS()
class UReimportExampleDataFactory final : public UExampleDataFactory, public FReimportHandler
{
	GENERATED_BODY()


private: /// FReimportHandler interface
	virtual void SetReimportPaths( UObject* PtrObject, TArray<FString> const& RefNewReimportPaths ) override;

	virtual bool CanReimport( UObject* PtrObject, TArray<FString>& RefFileNames ) override;

	virtual EReimportResult::Type Reimport( UObject* PtrObject ) override;
};
