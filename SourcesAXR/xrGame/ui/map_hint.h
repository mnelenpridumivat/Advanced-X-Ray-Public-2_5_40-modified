#pragma once
#include "UIFrameWindow.h"
#include "..\../xrServerEntities/associative_vector.h"

class CUIStatic;
class CUITextWnd;
class CUIXml;
class CGameTask;
class CMapSpot;

class CUIMapLocationHint :public CUIFrameWindow
{
	typedef CUIFrameWindow inherited;

	CUIWindow*			m_owner;
	associative_vector<shared_str, CUIStatic*>		m_info;
	void				SetInfoMode					(u8 mode);
public:
					CUIMapLocationHint	():m_owner(nullptr){};
	~CUIMapLocationHint	() override {};

	void			Init		(CUIXml& uiXml, LPCSTR path);

	void			SetInfoStr	(LPCSTR text);
	void			SetInfoMSpot(CMapSpot* spot);
	void			SetInfoTask	(CGameTask* task);

	void	Draw		() override {return;};
			void	Draw_		();
	void			SetOwner	(CUIWindow* w)	{m_owner = w;}
	CUIWindow*		GetOwner	()				{return m_owner;}

private:
	float			m_posx_icon;
	float			m_posx_caption;
};