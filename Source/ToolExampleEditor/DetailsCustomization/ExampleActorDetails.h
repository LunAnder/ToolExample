#pragma once
#include "IDetailCustomization.h"



class AExampleActor;


class FExampleActorDetails final : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance(); // Makes a new instance of this detail layout class for a specific detail view requesting it


public: /** IDetailCustomization interface */
	virtual void CustomizeDetails( IDetailLayoutBuilder& RefBuilder ) override;


protected: // widget functions
	void OnModeRadioChanged( ECheckBoxState InCheckType, AExampleActor* InActor, int32 InOptionIndex );

	ECheckBoxState IsModeRadioChecked( AExampleActor* InActor, int32 InOptionIndex ) const;
};
