#include "ExampleEdMode.h"

#include "ExampleEdModeToolkit.h"
#include "ToolExample/EditorMode/ExampleTargetPoint.h"
#include "ToolExampleEditor/ToolExampleEditor.h"
//
#include "ScopedTransaction.h"
#include "Toolkits/ToolkitManager.h"



class ExampleEditorCommands final : public TCommands<ExampleEditorCommands>
{
public:
	ExampleEditorCommands()
	: TCommands<ExampleEditorCommands>( "ExampleEditor" /*RENAME_ME*/, // Context name for fast lookup
																			FText::FromString( TEXT( "Example Editor" /*RENAME_ME*/ ) ), // context name for displaying
																			NAME_None, // Parent
																			FEditorStyle::GetStyleSetName() )
	{}

#define LOCTEXT_NAMESPACE ""
	virtual void RegisterCommands() override
	{
		UI_COMMAND( DeletePoint, "Delete Point", "Delete the currently selected point.", EUserInterfaceActionType::Button, FInputChord( EKeys::Delete ) );
	}
#undef LOCTEXT_NAMESPACE


public:
	TSharedPtr<FUICommandInfo> DeletePoint;
};


IMPLEMENT_HIT_PROXY( HExamplePointProxy, HHitProxy );


FEditorModeID const FExampleEdMode::EM_Example( TEXT( "EM_Example" /*RENAME_ME*/ ) );


FExampleEdMode::FExampleEdMode()
{
	ExampleEditorCommands::Register();

	ExampleEdModeActions = MakeShareable( new FUICommandList );
}


FExampleEdMode::~FExampleEdMode()
{
	ExampleEditorCommands::Unregister();
}


void FExampleEdMode::MapCommands()
{
	ExampleEditorCommands const& Commands = ExampleEditorCommands::Get();

	ExampleEdModeActions->MapAction( Commands.DeletePoint, FExecuteAction::CreateSP( this, &FExampleEdMode::RemovePoint ), FCanExecuteAction::CreateSP( this, &FExampleEdMode::CanRemovePoint ) );
}


void FExampleEdMode::Enter()
{
	FEdMode::Enter();

	if( !Toolkit.IsValid() )
	{
		Toolkit = MakeShareable( new FExampleEdModeToolkit );

		Toolkit->Init( Owner->GetToolkitHost() );
	}


	/// reset
	CurSelTarget = nullptr;
	CurSelIndex	 = -1;

	MapCommands();
}


void FExampleEdMode::Exit()
{
	FToolkitManager::Get().CloseToolkit( Toolkit.ToSharedRef() );

	Toolkit.Reset();

	FEdMode::Exit();
}


void FExampleEdMode::Render( FSceneView const* InView, FViewport* InViewport, FPrimitiveDrawInterface* InInterface )
{
	FColor const NrmColor( 200, 200, 200 );
	FColor const SelColor( 255, 128, 0 );

	UWorld* World = GetWorld();

	for( TActorIterator<AExampleTargetPoint> It( World ); It; ++It )
	{
		AExampleTargetPoint* Actor = ( *It );

		if( Actor != nullptr )
		{
			FVector ActorLoc = Actor->GetActorLocation();

			for( int32 IdxPoint = 0; IdxPoint < Actor->Points.Num(); ++IdxPoint )
			{
				bool const bSelected = Actor == CurSelTarget && IdxPoint == CurSelIndex;

				FColor const& Color = bSelected ? SelColor : NrmColor;

				/// set hit proxy and draw
				InInterface->SetHitProxy( new HExamplePointProxy( Actor, IdxPoint ) );
				InInterface->DrawPoint( Actor->Points[IdxPoint], Color, 15.f, SDPG_Foreground );
				InInterface->DrawLine( Actor->Points[IdxPoint], ActorLoc, Color, SDPG_Foreground );
				InInterface->SetHitProxy( nullptr );
			}
		}
	}


	FEdMode::Render( InView, InViewport, InInterface );
}


bool FExampleEdMode::HandleClick( FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy, FViewportClick const& InClick )
{
	bool bIsHandled = false;

	if( InHitProxy != nullptr )
	{
		if( InHitProxy->IsA( HExamplePointProxy::StaticGetType() ) )
		{
			bIsHandled = true;

			HExamplePointProxy* ExamplePointProxy = static_cast<HExamplePointProxy*>( InHitProxy );

			AExampleTargetPoint* Actor = Cast<AExampleTargetPoint>( ExamplePointProxy->ReferenceObj );

			int32 Index = ExamplePointProxy->Index;

			if( Actor != nullptr && Index >= 0 && Index < Actor->Points.Num() )
			{
				SelectPoint( Actor, Index );
			}
		}
	}


	if( InHitProxy != nullptr && bIsHandled && InClick.GetKey() == EKeys::RightMouseButton )
	{
		TSharedPtr<SWidget> const MenuWidget = GenerateContextMenu( InViewportClient );

		if( MenuWidget.IsValid() )
		{
			FSlateApplication::Get().PushMenu( Owner->GetToolkitHost()->GetParentWidget(),
																				 FWidgetPath(),
																				 MenuWidget.ToSharedRef(),
																				 FSlateApplication::Get().GetCursorPos(),
																				 FPopupTransitionEffect( FPopupTransitionEffect::ContextMenu ) );
		}
	}


	return bIsHandled;
}


bool FExampleEdMode::InputDelta( FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale )
{
	if( InViewportClient->GetCurrentWidgetAxis() == EAxisList::None )
	{
		return false;
	}


	if( HasValidSelection() )
	{
		if( !InDrag.IsZero() )
		{
			CurSelTarget->Modify();

			CurSelTarget->Points[CurSelIndex] += InDrag;
		}


		return true;
	}


	return false;
}


bool FExampleEdMode::InputKey( FEditorViewportClient* InClient, FViewport* InViewport, FKey const InKey, EInputEvent const InEvent )
{
	bool bIsHandled = false;

	if( !bIsHandled && InEvent == IE_Pressed )
	{
		bIsHandled = ExampleEdModeActions->ProcessCommandBindings( InKey, FSlateApplication::Get().GetModifierKeys(), false );
	}


	return bIsHandled;
}


TSharedPtr<SWidget> FExampleEdMode::GenerateContextMenu( FEditorViewportClient* InClient ) const
{
	FMenuBuilder MenuBuilder( true, nullptr );

	MenuBuilder.PushCommandList( ExampleEdModeActions.ToSharedRef() );


	MenuBuilder.BeginSection( "Example Section" );
	{
		if( HasValidSelection() )
		{
			/// add label for point index
			TSharedRef<SWidget> const LabelWidget = SNew( STextBlock ).Text( FText::FromString( FString::FromInt( CurSelIndex ) ) ).ColorAndOpacity( FLinearColor::Green );

			MenuBuilder.AddWidget( LabelWidget, FText::FromString( TEXT( "Point Index: " ) ) );
			MenuBuilder.AddMenuSeparator();

			/// add delete point entry
			MenuBuilder.AddMenuEntry( ExampleEditorCommands::Get().DeletePoint );
		}
	}
	MenuBuilder.EndSection();


	MenuBuilder.PopCommandList();

	TSharedPtr<SWidget> MenuWidget = MenuBuilder.MakeWidget();

	return MenuWidget;
}


bool FExampleEdMode::ShowModeWidgets() const
{
	return true;
}


bool FExampleEdMode::ShouldDrawWidget() const
{
	return true;
}


bool FExampleEdMode::UsesTransformWidget() const
{
	return true;
}


FVector FExampleEdMode::GetWidgetLocation() const
{
	if( HasValidSelection() )
	{
		return CurSelTarget->Points[CurSelIndex];
	}


	return FEdMode::GetWidgetLocation();
}


AExampleTargetPoint* GetSelectedTargetPointActor()
{
	TArray<UObject*> SelObjs;

	GEditor->GetSelectedActors()->GetSelectedObjects( SelObjs );

	if( SelObjs.Num() == 1 )
	{
		return Cast<AExampleTargetPoint>( SelObjs[0] );
	}


	return nullptr;
}


void FExampleEdMode::AddPoint()
{
	AExampleTargetPoint* Actor = GetSelectedTargetPointActor();

	if( Actor != nullptr )
	{
		FScopedTransaction const Transaction( FText::FromString( "Add Point" ) );

		/// add new point, slightly in front of camera
		FEditorViewportClient* Client = static_cast<FEditorViewportClient*>( GEditor->GetActiveViewport()->GetClient() );

		FVector const NewPoint = Client->GetViewLocation() + Client->GetViewRotation().Vector() * 50.F;

		Actor->Modify();
		Actor->Points.Add( NewPoint );

		/// auto select this new point
		SelectPoint( Actor, Actor->Points.Num() - 1 );
	}
}


bool FExampleEdMode::CanAddPoint() const
{
	return GetSelectedTargetPointActor() != nullptr;
}


void FExampleEdMode::RemovePoint()
{
	if( HasValidSelection() )
	{
		FScopedTransaction const Transaction( FText::FromString( "Remove Point" ) );

		CurSelTarget->Modify();
		CurSelTarget->Points.RemoveAt( CurSelIndex );

		/// deselect the point
		SelectPoint( nullptr, -1 );
	}
}


bool FExampleEdMode::CanRemovePoint() const
{
	return HasValidSelection();
}


bool FExampleEdMode::HasValidSelection() const
{
	return CurSelTarget.IsValid() && CurSelIndex >= 0 && CurSelIndex < CurSelTarget->Points.Num();
}


void FExampleEdMode::SelectPoint( AExampleTargetPoint* InActor, int32 const InIndex )
{
	CurSelTarget = InActor;
	CurSelIndex	 = InIndex;

	/// select this actor only
	if( CurSelTarget.IsValid() )
	{
		GEditor->SelectNone( true, true );
		GEditor->SelectActor( CurSelTarget.Get(), true, true );
	}
}
