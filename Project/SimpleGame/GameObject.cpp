#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

CGameObject::CGameObject(Position* pos, float* size, Color* rgba)
	: m_Pos(*pos), m_fSize(*size), m_Color(*rgba), m_fSpeed(0.1)
{
	m_tempPos = m_Pos;
}

void CGameObject::initialize(void)
{
}

int CGameObject::Update(void)
{
	//È¸Àü³îÀÌ
	/*static float angle = 0.f;
	angle+= m_fSpeed;

	if (angle >= 360.f)
		angle = 0.f;*/

	//m_Pos.fX = m_tempPos.fX + 100 * cos(3.141592 / 180 * angle);
	//m_Pos.fY = m_tempPos.fY + 100 * sin(3.141592 / 180 * angle);
	
	m_Pos.fX += m_fSpeed * (rand() % 3 - 1) * 5;
	m_Pos.fY += m_fSpeed * (rand() % 3 - 1) * 5;
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

