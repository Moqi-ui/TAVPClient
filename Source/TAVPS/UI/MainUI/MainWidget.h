// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class TAVPS_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

		UPROPERTY(meta = (BindWidget))
		class UButton* ConnectButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* SendButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* RecvButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* KillButton;

public:

	virtual void NativeConstruct();

	virtual void NativeDeStruct();

	UFUNCTION()
		void Connect();

	UFUNCTION()
		void Start();

	UFUNCTION()
		void Reve();

	UFUNCTION()
		void Kill();

private:

};
