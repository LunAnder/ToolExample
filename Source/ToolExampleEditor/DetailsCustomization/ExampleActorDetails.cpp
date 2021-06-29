#include "ExampleActorDetails.h"

#include "ToolExample/DetailsCustomization/ExampleActor.h"
#include "ToolExampleEditor/ToolExampleEditor.h"
//
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"



TSharedRef<IDetailCustomization> FExampleActorDetails::MakeInstance()
{
	return MakeShareable( new FExampleActorDetails );
}


void FExampleActorDetails::CustomizeDetails( IDetailLayoutBuilder& RefBuilder )
{
	TArray<TWeakObjectPtr<UObject>> Objects;

	RefBuilder.GetObjectsBeingCustomized( Objects );

	if( Objects.Num() != 1 )
	{ // Skip customization if select more than one objects
		return;
	}


	AExampleActor* Actor = static_cast<AExampleActor*>( Objects[0].Get() );

	/// Hide original property
	RefBuilder.HideProperty( RefBuilder.GetProperty( GET_MEMBER_NAME_CHECKED( AExampleActor, bOption1 ) ) );
	RefBuilder.HideProperty( RefBuilder.GetProperty( GET_MEMBER_NAME_CHECKED( AExampleActor, bOption2 ) ) );

	/// Add custom widget to "Options" category
	IDetailCategoryBuilder& OptionsCategory = RefBuilder.EditCategory( "Options", FText::FromString( "" ), ECategoryPriority::Important );

	/* clang-format off */
	OptionsCategory.AddCustomRow(FText::FromString("Options"))
				.WholeRowContent()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(SCheckBox)
						.Style(FEditorStyle::Get(), "RadioButton")
						.IsChecked(this, &FExampleActorDetails::IsModeRadioChecked, Actor, 1)
						.OnCheckStateChanged(this, &FExampleActorDetails::OnModeRadioChanged, Actor, 1)
						[
							SNew(STextBlock).Text(FText::FromString("Option 1"))
						]
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(10.f, 0.f, 0.f, 0.f)
					.VAlign(VAlign_Center)
					[
						SNew(SCheckBox)
						.Style(FEditorStyle::Get(), "RadioButton")
						.IsChecked(this, &FExampleActorDetails::IsModeRadioChecked, Actor, 2)
						.OnCheckStateChanged(this, &FExampleActorDetails::OnModeRadioChanged, Actor, 2)
						[
							SNew(STextBlock).Text(FText::FromString("Option 2"))
						]
					]
				];
	/* clang-format on */
}


ECheckBoxState FExampleActorDetails::IsModeRadioChecked( AExampleActor* InActor, int32 const InOptionIndex ) const
{
	bool bFlag = false;

	if( InActor != nullptr )
	{
		if( InOptionIndex == 1 )
		{
			bFlag = InActor->bOption1;
		}

		else if( InOptionIndex == 2 )
		{
			bFlag = InActor->bOption2;
		}
	}


	return bFlag ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}


void FExampleActorDetails::OnModeRadioChanged( ECheckBoxState const InCheckType, AExampleActor* InActor, int32 const InOptionIndex )
{
	bool const bFlag = ( InCheckType == ECheckBoxState::Checked );

	if( InActor != nullptr )
	{
		InActor->Modify();

		if( bFlag )
		{ // Clear all options first
			InActor->bOption1 = false;
			InActor->bOption2 = false;
		}


		if( InOptionIndex == 1 )
		{
			InActor->bOption1 = bFlag;
		}

		else if( InOptionIndex == 2 )
		{
			InActor->bOption2 = bFlag;
		}
	}
}
