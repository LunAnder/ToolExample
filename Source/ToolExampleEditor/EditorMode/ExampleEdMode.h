#pragma once
#include "EdMode.h"
#include "EditorModes.h"


class AExampleTargetPoint;


struct HExamplePointProxy final : HHitProxy
{
	DECLARE_HIT_PROXY();

	HExamplePointProxy( UObject* InReferenceObj, int32 const InIndex )
	: HHitProxy( HPP_UI )
	, Index( InIndex )
	, ReferenceObj( InReferenceObj )
	{}


	int32 Index;

	UObject* ReferenceObj;
};



class FExampleEdMode : public FEdMode
{
public:
	virtual ~FExampleEdMode() override;


public: /** FEdMode interface */
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Render( FSceneView const* PtrView, FViewport* PtrViewport, FPrimitiveDrawInterface* PtrInterface ) override;
	//virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;

	virtual bool HandleClick( FEditorViewportClient* InViewportClient, HHitProxy* InHitProxy, FViewportClick const& InClick ) override;
	virtual bool InputDelta( FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale ) override;
	virtual bool InputKey( FEditorViewportClient* InClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent ) override;
	virtual bool ShowModeWidgets() const override;
	virtual bool ShouldDrawWidget() const override;
	virtual bool UsesTransformWidget() const override;
	//virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;
	//virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;
	//virtual void ActorSelectionChangeNotify() override;
	//virtual void MapChangeNotify() override;
	//virtual void SelectionChanged() override;
	//virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;

	virtual FVector GetWidgetLocation() const override;
	/** End of FEdMode interface */


public:
	FExampleEdMode();

	void AddPoint();
	void MapCommands();
	void RemovePoint();
	void SelectPoint( AExampleTargetPoint* InActor, int32 InIndex );

	bool CanAddPoint() const;
	bool CanRemovePoint() const;
	bool HasValidSelection() const;

	TSharedPtr<SWidget> GenerateContextMenu( FEditorViewportClient* InClient ) const;


public:
	static FEditorModeID const EM_Example;


public:
	int32 CurSelIndex = -1;

	TWeakObjectPtr<AExampleTargetPoint> CurSelTarget;

	TSharedPtr<FUICommandList> ExampleEdModeActions;
};
