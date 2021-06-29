#pragma once
#include "AssetTypeActions_Base.h"


class UExampleData;


class FExampleDataTypeActions final : public FAssetTypeActions_Base
{
public: /// IAssetTypeActions interface
	virtual void GetActions( const TArray<UObject*>& InObjects, FMenuBuilder& RefBuilder ) override;

	virtual bool HasActions( const TArray<UObject*>& InObjects ) const override;

	virtual uint32 GetCategories() override;

	virtual FText GetName() const override;

	virtual FColor GetTypeColor() const override;

	virtual UClass* GetSupportedClass() const override;


public: /// Public Functions
	FExampleDataTypeActions( EAssetTypeCategories::Type InAssetCategory );

	void ExecuteReimport( TArray<TWeakObjectPtr<UExampleData>> InObjects );


private: /// Private Variables
	EAssetTypeCategories::Type MyAssetCategory;
};
