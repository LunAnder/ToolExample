#include "ExampleTabToolPanel.h"

#include "ToolExampleEditor/ToolExampleEditor.h"



void SExampleTabToolPanel::Construct( FArguments const& InArgs )
{
	tool = InArgs._Tool;

	if( tool.IsValid() )
	{
		// do anything you need from tool object
	}

	/* clang-format off */
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FColor(192, 192, 192, 255))
			.Padding(15.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("This is a tab example.")))
			]
		]
	];
	/* clang-format on */
}
