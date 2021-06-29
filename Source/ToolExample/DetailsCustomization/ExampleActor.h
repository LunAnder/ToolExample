#pragma once
#include "ExampleActor.generated.h"


UCLASS()
class TOOLEXAMPLE_API AExampleActor : public AActor
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere, Category = "Options")
	bool bOption1 = false;

	UPROPERTY(EditAnywhere, Category = "Options")
	bool bOption2 = false;
	
	UPROPERTY(EditAnywhere, Category = "Test")
	int32 testInt = 0;
};