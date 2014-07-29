/** 
*  @file  		UIFramework.h
*  @brief 		Server�� ȭ���������̽��� �����ϴ� UIFramework ��ü
*  @remarks 
*  @author  	������(edith2580@gmail.com)
*  @date  		2009-05-09
*/
#pragma once

#include "UICmdEdit.h"
#include "UICmdMsgView.h"
#include <vector>


/// ���ο� Ŀ�ǵ带 �߰��մϴ�.
/// ADD_COMMAND(_T("help"), CCmdHelp, L"ȭ�鿡 Ŀ��帮��Ʈ�� �����ݴϴ�.");
#define ADD_COMMAND(cmd, object, msg) AddCommand(cmd, new object, msg)

/** 
*  @class        UICommand
*  @brief        ���ø����̼ǿ��� Ŀ�ǵ带 �ۼ��Ҷ� ����� Ŀ��� ��ü
*  @remarks      
*                
*  @par          
*  @author  Edith
*  @date    2009-05-09
*/
class UICommand
{
public:
	virtual BOOL DoProcess(WCHAR* lpParam) = 0;    
};

/** 
*  @class        UICommandFactory
*  @brief        Ŀ�ǵ带 �����ϴ� Factory ��ü Server�� Server�� UI��ü�� ��ӹ޴´�.
*  @remarks      
*                
*  @par          
*  @author  Edith
*  @date    2009-05-09
*/
class UICommandFactory
{
public:
	BOOL AddCommand(const WCHAR* szCommand, UICommand* lpCommand, const WCHAR* szMessage);


	VOID ReleaseCommand();
	

	virtual VOID	InitializeCommand() {};

	virtual VOID	StartCommand() {}; 							// UIConsol���� Command �Է�
	virtual VOID	EndCommand() {};

	VOID ShowCommand();


	VOID DoCommand(WCHAR* Command);
	

public:
	UICommandFactory()
	{
	}
	~UICommandFactory()
	{
		ReleaseCommand();
	}

private:
	struct COMMAND
	{
		UINT	m_uiHash;
		WCHAR			m_szCMD[32];
		WCHAR			m_szMSG[128];
		UICommand*		m_lpCMD;

		COMMAND(const WCHAR* szCommand, UICommand* lpCMD, const WCHAR* szMessage);
		
	};

	typedef std::vector<COMMAND>	CMDVector;
	CMDVector						m_CMDVector;
};

/** 
*  @class        UIConsol
*  @brief		  �ܼ� UI
*  @remarks      
*                
*  @par          
*  @author  Edith
*  @date    2009-05-09
*/
class UIConsol : public UICommandFactory
{
	BOOL			m_bCommandExit;
public:
	// ����� ������Ʈ�� �ʱ�ȭ �մϴ�. (�����켳���� ����� �Ŀ� ȣ��)
	virtual VOID	InitObject() {};
	// ����� ������Ʈ�� �����մϴ�. (���η����� ������(EndProcessȣ����) ȣ��)
	virtual VOID	ReleaseObject() {};

	BOOL			Init();

	virtual VOID	InitializeCommand() {};
	virtual VOID	StartCommand();							// UIConsol���� Command �Է�
	virtual VOID	EndCommand();

public:
	UIConsol(VOID);
	~UIConsol(VOID);
};

/** 
*  @class        UIWindow
*  @brief        ������ UI
*  @remarks      
*                
*  @par          
*  @author  Edith
*  @date    2009-05-09
*/
class UIWindow : public UICommandFactory
{
public:
	HWND			GetWnd() { return m_hMainWnd; }
	BOOL			IsExit() { return m_bCommandExit; }
	// ����� ������Ʈ�� �ʱ�ȭ �մϴ�. (�����켳���� ����� �Ŀ� ȣ��)
	virtual VOID	InitObject() {};
	// ����� ������Ʈ�� �����մϴ�. (���η����� ������(EndProcessȣ����) ȣ��)
	virtual VOID	ReleaseObject() {};

	virtual VOID	ShowWindow(int nCmdShow);

	// Windows MsgProc
	virtual LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	BOOL			Init(HINSTANCE hInstance, int nCmdShow, int iWidth, int iHeight, WCHAR* AppName, WCHAR* Icon);
	void SetLogHandle(HWND hWnd){ m_logHwnd = hWnd; }

	virtual VOID	InitializeCommand() {};
	virtual VOID	StartCommand();							// UIConsol���� Command �Է�
	virtual VOID	EndCommand();

public:
	UIWindow(VOID);
	~UIWindow(VOID);

	static HWND			m_logHwnd;

private:
	HWND			m_hMainWnd;
	BOOL			m_bCommandExit;
	HFONT			m_hFont;
	

	VOID			ResizeWindows( VOID );

	// WM_EDIT_RETURN
	virtual VOID	OnEditReturn(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// WM_COMMAND
	virtual VOID	OnCommand(HWND hWnd, INT nID, INT iEvent, LPARAM lParam) { return; }
};