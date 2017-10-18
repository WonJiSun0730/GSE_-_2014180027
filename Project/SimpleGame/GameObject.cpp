#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

CGameObject::CGameObject(Position* pos, float* size, Color* rgba)
	: m_Pos(*pos), m_fSize(*size), m_Color(*rgba), m_fSpeed(0.03)
{
	initialize();
}

void CGameObject::initialize(void)
{
	do {
		m_Dir.fX = float(rand() % 3 - 1);
		m_Dir.fY = float(rand() % 3 - 1);
	} while (m_Dir.fX == 0 && m_Dir.fY == 0);
	//아니면 음...중앙각도를 중심으로다가 랜덤으로 이동하게?
}

int CGameObject::Update(void)
{
	m_Pos.fX += m_fSpeed * m_Dir.fX;
	m_Pos.fY += m_fSpeed * m_Dir.fY;
	return 0;
}

void CGameObject::Render(void)
{
	g_Renderer->DrawSolidRect(m_Pos.fX, m_Pos.fY, 0, m_fSize, m_Color.fR, m_Color.fG, m_Color.fB, m_Color.fAlpha);
}

void CGameObject::Release(void)
{
}

void CGameObject::SetPos(Position* Pos)
{
	m_Pos = *Pos;
}

void CGameObject::SetSize(float * Size)
{
	m_fSize = *Size;
}

void CGameObject::SetColor(Color * RGBA)
{
	m_Color = *RGBA;
}

Position* CGameObject::GetPos(void)
{
	return &m_Pos;
}

float* CGameObject::GetSize(void)
{
	return &m_fSize;
}

Color* CGameObject::GetColor(void)
{
	return &m_Color;
}

