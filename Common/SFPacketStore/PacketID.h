#pragma once

namespace CGSF
{

typedef enum ePacketID
{
 	Auth = 1000,
 	Login,
	LoginSuccess,
	LoginFail,
	TeamInfo,
	EnterTeamMember,
	LeaveTeamMember,
	InvalidPacket,
	EnterLobby,
	ChatReq,
	ChatRes,
	EnterRoom,
	CreateRoom,
	LeaveRoom,
	RoomList,
	ChangeTeam,
	StartGame,
	LoadingComplete,
	PlayWait,
	PlayStart,
	PeerList,
	
	MSG_CREATE_PLAYER, //���� ���۽� ó�� �ѹ��� �Ǵ� ���� �ѹ���...
	MSG_DESTROY_PLAYER,
	MSG_PLAYER_HEALTH,
	MSG_PLAYER_SCORE,
	MSG_PLAYER_WEAPON_CHANGE,
	MSG_PLAYER_WEAPON_CHANGING,
	MSG_SPAWN_PLAYER,

	MSG_PLAYER_MOVE_UPDATE, //�� �ΰ��� UDP��
	MSG_PLAYER_LOOK_UPDATE, //�� �ΰ��� UDP��

	PlayEnd,
	PlayScoreInfo,
	PlayPlayerScore,
	PlayerIP,
	AddPeer,
	DeletePeer,
};
};
