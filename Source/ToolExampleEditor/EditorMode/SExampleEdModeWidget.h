#pragma once


class FExampleEdMode;


class SExampleEdModeWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SExampleEdModeWidget ) {}
	SLATE_END_ARGS();

	void Construct( FArguments const& InArgs );


public: // Util Functions
	FExampleEdMode* GetEdMode() const;

	bool CanAddPoint() const;
	bool CanRemovePoint() const;

	FReply OnAddPoint();
	FReply OnRemovePoint();
};
