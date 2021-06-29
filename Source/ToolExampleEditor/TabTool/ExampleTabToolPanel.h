#pragma once
#include "ExampleTabTool.h"



class SExampleTabToolPanel final : public SCompoundWidget
{
	SLATE_BEGIN_ARGS( SExampleTabToolPanel ) {}
	SLATE_ARGUMENT( TWeakPtr<class FExampleTabTool>, Tool )
	SLATE_END_ARGS()

	void Construct( FArguments const& InArgs );

	
protected: /// Protected Variables
	TWeakPtr<FExampleTabTool> tool;
};
