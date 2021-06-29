#include "ExampleDataFactory.h"

#include "ToolExample/CustomDataType/ExampleData.h"
#include "ToolExampleEditor/ToolExampleEditor.h"


class UExampleData;


UExampleDataFactory::UExampleDataFactory( FObjectInitializer const& ObjectInitializer )
: Super( ObjectInitializer )
{
	Formats.Add( TEXT( "xmp;Example Data" ) );

	SupportedClass = UExampleData::StaticClass();

	bCreateNew		= false; // turned off for import
	bEditAfterNew = false; // turned off for import
	bEditorImport = true;
	bText					= true;
}


UObject* UExampleDataFactory::FactoryCreateNew( UClass* PtrClass, UObject* PtrParent, FName const InName, EObjectFlags const InFlags, UObject* PtrContext, FFeedbackContext* PtrWarn )
{
	auto* NewObjectAsset = NewObject<UExampleData>( PtrParent, PtrClass, InName, InFlags | RF_Transactional );

	return NewObjectAsset;
}


UObject* UExampleDataFactory::FactoryCreateText( UClass*						PtrClass,
																								 UObject*						PtrParent,
																								 FName const				InName,
																								 EObjectFlags const InFlags,
																								 UObject*						PtrContext,
																								 TCHAR const*				PtrType,
																								 TCHAR const*&			RefPtrBuffer,
																								 TCHAR const*				PtrBufferEnd,
																								 FFeedbackContext*	PtrWarn )
{
	GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetPreImport.Broadcast( this, PtrClass, PtrParent, InName, PtrType ); //FEditorDelegates::OnAssetPreImport.Broadcast( this, InClass, InParent, InName, Type );

	if( PtrClass != UExampleData::StaticClass() || FCString::Stricmp( PtrType, TEXT( "xmp" ) ) != 0 )
	{ // If class type or extension doesn't match, return
		return nullptr;
	}


	UExampleData* Data = CastChecked<UExampleData>( NewObject<UExampleData>( PtrParent, InName, InFlags ) );

	MakeExampleDataFromText( Data, RefPtrBuffer, PtrBufferEnd );

	Data->SourceFilePath = UAssetImportData::SanitizeImportFilename( CurrentFilename, Data->GetOutermost() );

	GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetPostImport.Broadcast( this, Data );

	return Data;
}


bool UExampleDataFactory::FactoryCanImport( FString const& InFilename )
{
	return FPaths::GetExtension( InFilename ).Equals( TEXT( "xmp" ) );
}


void UExampleDataFactory::MakeExampleDataFromText( UExampleData* PtrData, TCHAR const*& RefPtrBuffer, TCHAR const* PtrBufferEnd )
{
	PtrData->ExampleString = RefPtrBuffer;
}
