#include "ReimportExampleDataFactory.h"

#include "ExampleDataFactory.h"
#include "ToolExample/CustomDataType/ExampleData.h"
#include "ToolExampleEditor/ToolExampleEditor.h"



bool UReimportExampleDataFactory::CanReimport( UObject* PtrObject, TArray<FString>& RefFileNames )
{
	UExampleData* ExampleData = Cast<UExampleData>( PtrObject );

	if( ExampleData != nullptr )
	{
		RefFileNames.Add( UAssetImportData::ResolveImportFilename( ExampleData->SourceFilePath, ExampleData->GetOutermost() ) );

		return true;
	}


	return false;
}


void UReimportExampleDataFactory::SetReimportPaths( UObject* PtrObject, TArray<FString> const& RefNewReimportPaths )
{
	UExampleData* ExampleData = Cast<UExampleData>( PtrObject );

	if( ExampleData != nullptr && ensure( RefNewReimportPaths.Num() == 1 ) )
	{
		ExampleData->SourceFilePath = UAssetImportData::SanitizeImportFilename( RefNewReimportPaths[0], ExampleData->GetOutermost() );
	}
}


EReimportResult::Type UReimportExampleDataFactory::Reimport( UObject* PtrObject )
{
	UExampleData* ExampleData = Cast<UExampleData>( PtrObject );

	if( ExampleData == nullptr )
	{
		return EReimportResult::Failed;
	}


	FString const Filename = UAssetImportData::ResolveImportFilename( ExampleData->SourceFilePath, ExampleData->GetOutermost() );

	if( !FPaths::GetExtension( Filename ).Equals( TEXT( "xmp" ) ) )
	{
		return EReimportResult::Failed;
	}


	CurrentFilename = Filename;

	FString Data;

	if( FFileHelper::LoadFileToString( Data, *CurrentFilename ) )
	{
		TCHAR const* Ptr = *Data;

		ExampleData->Modify();

		bool bNotUsed = ExampleData->MarkPackageDirty();

		UExampleDataFactory::MakeExampleDataFromText( ExampleData, Ptr, Ptr + Data.Len() );

		ExampleData->SourceFilePath = UAssetImportData::SanitizeImportFilename( CurrentFilename, ExampleData->GetOutermost() );
	}


	return EReimportResult::Succeeded;
}
