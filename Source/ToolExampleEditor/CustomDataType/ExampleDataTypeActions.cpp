#include "ExampleDataTypeActions.h"

#include "ToolExample/CustomDataType/ExampleData.h"
#include "ToolExampleEditor/ToolExampleEditor.h"


FExampleDataTypeActions::FExampleDataTypeActions( EAssetTypeCategories::Type const InAssetCategory )
: MyAssetCategory( InAssetCategory )
{}


FText FExampleDataTypeActions::GetName() const
{
	return FText::FromString( "Example Data" );
}


FColor FExampleDataTypeActions::GetTypeColor() const
{
	return FColor( 230, 205, 165 );
}


UClass* FExampleDataTypeActions::GetSupportedClass() const
{
	return UExampleData::StaticClass();
}


uint32 FExampleDataTypeActions::GetCategories()
{
	return MyAssetCategory;
}


bool FExampleDataTypeActions::HasActions( TArray<UObject*> const& InObjects ) const
{
	return true;
}


void FExampleDataTypeActions::GetActions( TArray<UObject*> const& InObjects, FMenuBuilder& RefBuilder )
{
	TArray<TWeakObjectPtr<UExampleData>> const ExampleDataImports = GetTypedWeakObjectPtrs<UExampleData>( InObjects );

	RefBuilder.AddMenuEntry( FText::FromString( "Reimport" ),
													 FText::FromString( "Reimports example data." ),
													 FSlateIcon(),
													 FUIAction( FExecuteAction::CreateSP( this, &FExampleDataTypeActions::ExecuteReimport, ExampleDataImports ), FCanExecuteAction() ) );
}


void FExampleDataTypeActions::ExecuteReimport( TArray<TWeakObjectPtr<UExampleData>> const InObjects )
{
	for( TArray<TWeakObjectPtr<UExampleData>>::TConstIterator ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt )
	{
		UExampleData* Object = ( *ObjIt ).Get();

		if( Object != nullptr )
		{
			FReimportManager::Instance()->Reimport( Object, /*bAskForNewFileIfMissing=*/true );
		}
	}
}
