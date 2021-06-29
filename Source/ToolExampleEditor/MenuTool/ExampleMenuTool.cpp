#include "ExampleMenuTool.h"

#include "ScopedTransaction.h"
#include "ToolExampleEditor/ToolExampleEditor.h"


#define LOCTEXT_NAMESPACE "MenuTool"


class ExampleMenuToolCommands final : public TCommands<ExampleMenuToolCommands>
{
public: /// Public Virtual Overriden Functions
	virtual void RegisterCommands() override;


public: /// Public Functions
	ExampleMenuToolCommands();


public: /// Public Variables
	TSharedPtr<FUICommandInfo> MenuCommand1;
	TSharedPtr<FUICommandInfo> MenuCommand2;
	TSharedPtr<FUICommandInfo> MenuCommand3;
};



void ExampleMenuToolCommands::RegisterCommands()
{
	UI_COMMAND( MenuCommand1, "Menu Command 1", "Test Menu Command 1.", EUserInterfaceActionType::Button, FInputChord() );
	UI_COMMAND( MenuCommand2, "Menu Command 2", "Test Menu Command 2.", EUserInterfaceActionType::Button, FInputChord() );
	UI_COMMAND( MenuCommand3, "Menu Command 3", "Test Menu Command 3.", EUserInterfaceActionType::Button, FInputChord() );
}


ExampleMenuToolCommands::ExampleMenuToolCommands()
: TCommands<ExampleMenuToolCommands>( TEXT( "MenuTool" ) /*Context name for fast lookup*/,
																			FText::FromString( "Example Menu tool" ) /*Context name for displaying*/,
																			NAME_None /*No parent context*/,
																			FEditorStyle::GetStyleSetName() /*Icon Style Set*/ )
{}


void FExampleMenuTool::MapCommands()
{
	ExampleMenuToolCommands const& Commands = ExampleMenuToolCommands::Get();

	CommandList->MapAction( Commands.MenuCommand1, FExecuteAction::CreateSP( this, &FExampleMenuTool::MenuCommand1 ), FCanExecuteAction() );
	CommandList->MapAction( Commands.MenuCommand2, FExecuteAction::CreateSP( this, &FExampleMenuTool::MenuCommand2 ), FCanExecuteAction() );
	CommandList->MapAction( Commands.MenuCommand3, FExecuteAction::CreateSP( this, &FExampleMenuTool::MenuCommand3 ), FCanExecuteAction() );
}


void FExampleMenuTool::OnStartupModule()
{
	CommandList = MakeShareable( new FUICommandList );

	ExampleMenuToolCommands::Register();

	MapCommands();

	FToolExampleEditor::Get().AddMenuExtension( FMenuExtensionDelegate::CreateRaw( this, &FExampleMenuTool::MakeMenuEntry ), FName( "Section_1" ), CommandList );
}


void FExampleMenuTool::OnShutdownModule()
{
	ExampleMenuToolCommands::Unregister();
}


void FExampleMenuTool::MakeMenuEntry( FMenuBuilder& RefBuilder )
{
	RefBuilder.AddMenuEntry( ExampleMenuToolCommands::Get().MenuCommand1 );
	RefBuilder.AddSubMenu( FText::FromString( "Sub Menu" ), FText::FromString( "This is example sub menu" ), FNewMenuDelegate::CreateSP( this, &FExampleMenuTool::MakeSubMenu ) );

	/// Add tag
	/* clang-format off */
	TSharedRef<SWidget> const AddTagWidget =
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SEditableTextBox)
			.MinDesiredWidth(50)
			.Text(this, &FExampleMenuTool::GetTagToAddText)
			.OnTextCommitted(this, &FExampleMenuTool::OnTagToAddTextCommited)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(5, 0, 0, 0)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Text(FText::FromString("Add Tag"))
			.OnClicked(this, &FExampleMenuTool::AddTag)
		];
	/* clang-format on */


	RefBuilder.AddWidget( AddTagWidget, FText::FromString( "" ) );
}

void FExampleMenuTool::MakeSubMenu( FMenuBuilder& RefBuilder )
{
	RefBuilder.AddMenuEntry( ExampleMenuToolCommands::Get().MenuCommand2 );
	RefBuilder.AddMenuEntry( ExampleMenuToolCommands::Get().MenuCommand3 );
}


void FExampleMenuTool::MenuCommand1()
{
	UE_LOG( LogClass, Log, TEXT( "clicked MenuCommand1" ) );
}


void FExampleMenuTool::MenuCommand2()
{
	UE_LOG( LogClass, Log, TEXT( "clicked MenuCommand2" ) );
}


void FExampleMenuTool::MenuCommand3()
{
	UE_LOG( LogClass, Log, TEXT( "clicked MenuCommand3" ) );
}


FReply FExampleMenuTool::AddTag()
{
	if( !TagToAdd.IsNone() )
	{
		FScopedTransaction const Transaction( FText::FromString( "Add Tag" ) );

		for( FSelectionIterator It( GEditor->GetSelectedActorIterator() ); It; ++It )
		{
			AActor* Actor = static_cast<AActor*>( *It );

			if( !Actor->Tags.Contains( TagToAdd ) )
			{
				Actor->Modify();
				Actor->Tags.Add( TagToAdd );
			}
		}
	}


	return FReply::Handled();
}


FText FExampleMenuTool::GetTagToAddText() const
{
	return FText::FromName( TagToAdd );
}


void FExampleMenuTool::OnTagToAddTextCommited( FText const& InText, ETextCommit::Type InCommitInfo )
{
	FString const Str = InText.ToString();

	TagToAdd = FName( *Str.TrimStartAndEnd() );
}


#undef LOCTEXT_NAMESPACE
