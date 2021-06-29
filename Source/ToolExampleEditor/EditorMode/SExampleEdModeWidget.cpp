#include "SExampleEdModeWidget.h"

#include "ExampleEdMode.h"
#include "ToolExampleEditor/ToolExampleEditor.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SExampleEdModeWidget::Construct( FArguments const& InArgs )
{
	/* clang-format off */
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 5.f, 0.f, 0.f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("This is a editor mode example.")))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.f, 5.f, 0.f, 0.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(2, 0, 0, 0)
				.VAlign(VAlign_Center)
				[
					SNew(SButton)
					.Text(FText::FromString("Add"))
					.OnClicked(this, &SExampleEdModeWidget::OnAddPoint)
					.IsEnabled(this, &SExampleEdModeWidget::CanAddPoint)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0, 0, 2, 0)
				[
					SNew(SButton)
					.Text(FText::FromString("Remove"))
					.OnClicked(this, &SExampleEdModeWidget::OnRemovePoint)
					.IsEnabled(this, &SExampleEdModeWidget::CanRemovePoint)
				]
			]
		]
	];
	/* clang-format on */
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION


FExampleEdMode* SExampleEdModeWidget::GetEdMode() const
{
	return static_cast<FExampleEdMode*>( GLevelEditorModeTools().GetActiveMode( FExampleEdMode::EM_Example ) );
}


FReply SExampleEdModeWidget::OnAddPoint()
{
	GetEdMode()->AddPoint();

	return FReply::Handled();
}


bool SExampleEdModeWidget::CanAddPoint() const
{
	return GetEdMode()->CanAddPoint();
}


FReply SExampleEdModeWidget::OnRemovePoint()
{
	GetEdMode()->RemovePoint();

	return FReply::Handled();
}


bool SExampleEdModeWidget::CanRemovePoint() const
{
	return GetEdMode()->CanRemovePoint();
}
