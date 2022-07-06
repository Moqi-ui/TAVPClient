// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "../../Net/TAVPClient.h"

void UMainWidget::NativeConstruct()
{
	ConnectButton->OnReleased.AddDynamic(this, &UMainWidget::Connect);
	SendButton->OnReleased.AddDynamic(this, &UMainWidget::Start);
	RecvButton->OnReleased.AddDynamic(this, &UMainWidget::Reve);
	KillButton->OnReleased.AddDynamic(this, &UMainWidget::Kill);

}

void UMainWidget::NativeDeStruct()
{

}

void UMainWidget::Connect()
{
	FTAVPClient::Get()->Connection();

}
void UMainWidget::Start()
{
	//FString meg = " -game -messaging -dc_cluster -nosplash -fixedseed -NoVerifyGC -noxrstereo -xrtrackingonly -RemoteControlIsHeadless   -StageFriendlyName=Node_0    -dc_cfg=\"D:/N2.ndisplay\" -dx12 -dc_dev_mono -windowed -forceres WinX=0 WinY=0 ResX=1920 ResY=1080 -dc_node=Node_0 Log=Node_0.log";
	FTAVPClient::Get()->StartProcess();

}
void UMainWidget::Reve()
{
	FTAVPClient::Get()->RecvMessages();
}
void UMainWidget::Kill()
{
	FTAVPClient::Get()->KillProcess();
}

