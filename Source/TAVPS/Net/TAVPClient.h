/*********************************************************
*
* @copyright 2021-2022,ʱ�����꣨C����All right reserved
*
* @author ����
*
* @date 2022��06��28��15:25:00
*
* @brief �ͻ��ˣ�����
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
