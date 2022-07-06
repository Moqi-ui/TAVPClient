/*********************************************************
*
* @copyright 2021-2022,时光坐标（C），All right reserved
*
* @author 曹落
*
* @date 2022年06月28日15:25:00
*
* @brief 客户端，单例
*
* @See
*
**********************************************************/


#pragma once
#include "Runtime/Networking/Public/Networking.h"
#include "../TAVPDataType.h"
#include "CoreMinimal.h"

/**
 * 
 */
//struct FRenderNodeData;

class TAVPS_API FTAVPClient
{
public:
	FTAVPClient();
	~FTAVPClient();


public:
	static FTAVPClient* Get();
	bool Init();
	bool ParseConfigData();
	bool Connection();
	bool Disconnetion();
	bool StartProcess();
	bool KillProcess();
	void SendMessages(FString Command);
	void RecvMessages();

private:

	uint32 ServerPort;

	static FTAVPClient* TAVPClient;
	
	FSocket* ClientSocket;

	//TMap<FRenderNodeData, FString> PendingConnections;
	TMap<FRenderNodeData, TSharedPtr<FSocket>> PendingConnections;

	TMap<FIPv4Address, TSharedPtr<FSocket>> Connections;

	TMap<FIPv4Address, FString> Commannds;

};
