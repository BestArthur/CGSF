#include "stdafx.h"
#include "SFClassicDispatcher.h"


SFClassicDispatcher::SFClassicDispatcher()
: ILogicDispatcher(false)
{
}


SFClassicDispatcher::~SFClassicDispatcher()
{
}

//��������Ʈ���� ť�� ��Ŷ�� ť���Ѵ�.
void SFClassicDispatcher::Dispatch(BasePacket* pPacket)
{
	LogicEntrySingleton::instance()->ProcessPacket(pPacket);
}

void SFClassicDispatcher::Finally()
{

}