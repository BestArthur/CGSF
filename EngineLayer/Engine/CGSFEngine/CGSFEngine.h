#pragma once
#include "INetworkEngine.h"
#include "ProactorAcceptor.h"
#include "ACETimeOutHandler.h"

class CGSFServerEngine : public INetworkEngine
{
public:
	CGSFServerEngine(IEngine* pEngine);
	virtual ~CGSFServerEngine(void);

	virtual bool Init() override;
	virtual bool Start(char* szIP, unsigned short Port) override;
    virtual bool Shutdown() override;

	virtual bool SendRequest(BasePacket* pPacket) override;

	virtual bool Disconnect(int Serial) override;

	virtual bool CheckTimerImpl() override; //default timer ���
	virtual bool CreateTimerTask(unsigned int TimerID, unsigned int StartTime, unsigned int Period) override;

protected:

private:
	int m_WorkThreadGroupID;
	ProactorAcceptor m_Acceptor;
	ACETimeOutHandler m_TimeOutHandler;
};

class CGSFClientEngine : public INetworkEngine
{
public:
	CGSFClientEngine(IEngine* pEngine);
	virtual ~CGSFClientEngine(void);

	virtual bool Init() override;
	virtual bool Start(char* szIP, unsigned short Port) override;
    virtual bool Shutdown() override;

	virtual bool SendRequest(BasePacket* pPacket) override;
	virtual bool Disconnect(int Serial) override;

	virtual bool CheckTimerImpl() override; //default timer ���
	virtual bool CreateTimerTask(unsigned int TimerID, unsigned int StartTime, unsigned int Period) override;

protected:

private:
	int m_WorkThreadGroupID;
	ProactorService* m_ProactorService;
	ACETimeOutHandler m_TimeOutHandler;
};

