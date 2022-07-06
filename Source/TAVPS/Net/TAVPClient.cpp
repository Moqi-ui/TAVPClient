// Fill out your copyright notice in the Description page of Project Settings.


#include "TAVPClient.h"

#include "../FileManager/TAVPFileManager.h"

FTAVPClient* FTAVPClient::TAVPClient = nullptr;

FTAVPClient::FTAVPClient()
{

	ClientSocket = nullptr;
	ServerPort = 2980;
}

FTAVPClient::~FTAVPClient()
{
	if (ClientSocket)
	{
		ClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
	}

}

FTAVPClient* FTAVPClient::Get()
{
	if (TAVPClient == nullptr)
	{
		return TAVPClient = new FTAVPClient();
	}

	return TAVPClient;
}

bool FTAVPClient::Init()
{
	//ClientSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, "TAVPClient");
	return false;
}

bool FTAVPClient::ParseConfigData()
{
	//FString Params0 = FTAVPFileManager::Get()->LoadFile("");

	//这里解析从文本读取到的JSon数据，获取到渲染节点Node的数量及对应的IP地址，一个NOde对应一个Connection。
	//Connections.Empty();
	//FString Params0 = "Start---- -game -messaging -dc_cluster -nosplash -fixedseed -NoVerifyGC -noxrstereo -xrtrackingonly -RemoteControlIsHeadless -StageFriendlyName=Node_0 -dc_cfg=\"D:/00_Mrcao/08_Test/W/Render_2node.ndisplay\" -dx12 -dc_dev_mono -windowed -forceres WinX=0 WinY=0 ResX=1920 ResY=1080 -dc_node=Node_0 Log=Node_0.log";
	/*FString Params1 = "-game -messaging -dc_cluster -nosplash -fixedseed -NoVerifyGC -noxrstereo -xrtrackingonly -RemoteControlIsHeadless -StageFriendlyName=Node_0_1 -dc_cfg=\"D:/00_Mrcao/08_Test/W/Render_2node.ndisplay\" -dx12 -dc_dev_mono -windowed -forceres WinX=1920 WinY=0 ResX=1920 ResY=1080 -dc_node=Node_0_1 Log=Node_0_1.log";


	TArray<FRenderNodeData> RenderNode;
	FRenderNodeData OneNode0 = FRenderNodeData("Node_0", "127.0.0.1", "Start", Params0);
	FRenderNodeData OneNode1 = FRenderNodeData("Node_1", "127.0.0.1", "Start", Params1);

	RenderNode.Add(OneNode0);
	RenderNode.Add(OneNode1);*/

	if (!FTAVPFileManager::Get()->DeSerializeNdisConfig())
	{
		UE_LOG(LogTemp, Warning, TEXT("Parse Ndis Config Data Failed!"));

		return false;
	}
	
	TArray<FRenderNodeData> RenderNode = FTAVPFileManager::Get()->GetNodeDatas();

	for (int i = 0; i < RenderNode.Num(); i++)
	{
		FSocket* socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, "TAVPClient");

		PendingConnections.Add(RenderNode[i], MakeShareable(socket));
	}


	return true;
}

bool FTAVPClient::Connection()
{
	ParseConfigData();
	if (PendingConnections.Num() > 0)
	{
		for (auto PendingConnection : PendingConnections)
		{
			TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

			FIPv4Address IP;
			FIPv4Address::Parse(PendingConnection.Key.IPAddress, IP);

			addr->SetIp(IP.Value);
			addr->SetPort(ServerPort);
			if (PendingConnection.Value->Connect(*addr))
			{
				TSharedRef<FInternetAddr> Clientaddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();;
				PendingConnection.Value->GetAddress(*Clientaddr);
				UE_LOG(LogTemp, Display, TEXT("Connect Success, Client: %s"), *Clientaddr->ToString(true));
			}
			else
			{
				TSharedRef<FInternetAddr> Clientaddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();;
				PendingConnection.Value->GetAddress(*Clientaddr);
				UE_LOG(LogTemp, Display, TEXT("Connect Falied, Client: %s"), *Clientaddr->ToString(true));
			}
		}
	}
	return false;
}

bool FTAVPClient::Disconnetion()
{
	//ClientSocket->Close();
	Connections.Empty();
	return false;
}

bool FTAVPClient::StartProcess()
{


	SendMessages("Start");
	return true;
}
bool FTAVPClient::KillProcess()
{

	SendMessages("Kill");
	return true;
}

void FTAVPClient::SendMessages(FString Command)
{
	if (PendingConnections.Num() > 0)
	{
		for (auto connection : PendingConnections)
		{
			FString SendMesg = Command + "----" + connection.Key.Params;

			TCHAR* seriallizedChar = SendMesg.GetCharArray().GetData();
			int32 size = FCString::Strlen(seriallizedChar) + 1;
			int32 sent = 0;
			if (connection.Value->Send((uint8*)TCHAR_TO_UTF8(seriallizedChar), size, sent))
			{
				//seriallizedChar.
				GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("Send Success!"));
				UE_LOG(LogTemp, Warning, TEXT("Send Success!"));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, TEXT("Send Failed!"));
				UE_LOG(LogTemp, Warning, TEXT("Send Failed!"));
			}
		}
	}
}

void FTAVPClient::RecvMessages()
{
	uint32 pendingDataSize;

	if (ClientSocket->HasPendingData(pendingDataSize))
	{
		TArray<uint8> Buffer;
		Buffer.AddUninitialized(pendingDataSize);
		int32 byteSize = 0;

		ClientSocket->Recv(Buffer.GetData(), pendingDataSize, byteSize, ESocketReceiveFlags::None);
		if (Buffer.Num()>0)
		{
			FString RecvData = UTF8_TO_TCHAR(Buffer.GetData());
			UE_LOG(LogTemp, Display, TEXT("Recv data from server: %s"), *RecvData);
		}
	}
}