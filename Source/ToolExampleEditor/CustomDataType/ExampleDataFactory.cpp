#include "ExampleDataFactory.h"

#include "ToolExample/CustomDataType/ExampleData.h"
#include "ToolExampleEditor/ToolExampleEditor.h"

UExampleDataFactory::UExampleDataFactory( const FObjectInitializer& ObjectInitializer )
: Super( ObjectInitializer )
{
	Formats.Add( TEXT( "xmp;Example Data" ) );
	SupportedClass = UExampleData::StaticClass();
	bCreateNew		 = false; // turned off for import
	bEditAfterNew	 = false; // turned off for import
	bEditorImport	 = true;
	bText					 = true;
}

UObject* UExampleDataFactory::FactoryCreateNew( UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn )
{
	UExampleData* NewObjectAsset = NewObject<UExampleData>( InParent, Class, Name, Flags | RF_Transactional );
	return NewObjectAsset;
}

UObject* UExampleDataFactory::FactoryCreateText( UClass*					 InClass,
																								 UObject*					 InParent,
																								 FName						 InName,
																								 EObjectFlags			 Flags,
																								 UObject*					 Context,
																								 const TCHAR*			 Type,
																								 const TCHAR*&		 Buffer,
																								 const TCHAR*			 BufferEnd,
																								 FFeedbackContext* Warn )
{
	GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetPreImport.Broadcast( this, InClass, InParent, InName, Type );	//FEditorDelegates::OnAssetPreImport.Broadcast( this, InClass, InParent, InName, Type );

	// if class type or extension doesn't match, return
	if( InClass != UExampleData::StaticClass() || FCString::Stricmp( Type, TEXT( "xmp" ) ) != 0 )
		return nullptr;

	UExampleData* Data = CastChecked<UExampleData>( NewObject<UExampleData>( InParent, InName, Flags ) );
	MakeExampleDataFromText( Data, Buffer, BufferEnd );

	// save the source file path
	Data->SourceFilePath = UAssetImportData::SanitizeImportFilename( CurrentFilename, Data->GetOutermost() );

	GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetPostImport.Broadcast( this, Data );	//FEditorDelegates::OnAssetPostImport.Broadcast( this, Data );

	return Data;
}

bool UExampleDataFactory::FactoryCanImport( const FString& Filename )
{
	return FPaths::GetExtension( Filename ).Equals( TEXT( "xmp" ) );
}

void UExampleDataFactory::MakeExampleDataFromText( class UExampleData* Data, const TCHAR*& Buffer, const TCHAR* BufferEnd )
{
	Data->ExampleString = Buffer;
}
