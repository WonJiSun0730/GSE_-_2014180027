#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

CGameObject::CGameObject(Position* pos, float* size, Color* rgba)
	: m_Pos(*pos), m_fSize(*size), m_Color(*rgba), m_fSpeed(0.f)
{
	initialize();
}

void CGameObject::initialize(void)
{
	float rad = float(rand() % 360);

	//0~1사이의 단위 벡터
	m_Dir.fX = cos(rad * 3.141592f / 180.f);
	m_Dir.fY = sin(rad * 3.141592f / 180.f);

	m_bCollision = false;
}

int CGameObject::Update(void)
{
	m_Pos.fX += m_fSpeed * m_Dir.fX;
	m_Pos.fY += m_fSpeed * m_Dir.fY;

	if (m_bCollision && m_Color.fG == 1 && m_Color.fB == 1)
	{
		m_Color.fG = 0, m_Color.fB = 0;
	}
	if (!m_bCollision && m_Color.fG == 0 && m_Color.fB == 0)
	{
		m_Color.fG = 1, m_Color.fB = 1;
	}

	//만약 >> 이건 임시...입사각과 반사각을 구하자
	if (-250.f > m_Pos.fX || m_Pos.fX > 250.f)
	{
		m_Dir.fX *= -1;
	}
	if (-250.f > m_Pos.fY || m_Pos.fY > 250.f)
	{
		m_Dir.fY *= -1;
	}

	return 0;
}

void CGameObject::Render(void)
{
	//g_Renderer->DrawSolidRect(m_Pos.fX, m_Pos.fY, 0, m_fSize, m_Color.fR, m_Color.fG, m_Color.fB, m_Color.fAlpha);
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

bool CGameObject::CollisionCheck(CGameObject* ObjInfo)
{
	//left보다 더 왼쪽에 있는 오른쪽
	float fMyLeft = this->m_Pos.fX - this->m_fSize * 0.5f;
	float fYourRight = ObjInfo->GetPos()->fX + *ObjInfo->GetSize() * 0.5f;
	if (fYourRight < fMyLeft)
		return false;
	
	float fMyRight = this->m_Pos.fX + this->m_fSize * 0.5f;
	float fYourLeft = ObjInfo->GetPos()->fX - *ObjInfo->GetSize() * 0.5f;
	if (fMyRight < fYourLeft)
		return false;

	float fMyTop = this->m_Pos.fY + this->m_fSize * 0.5f;
	float fYourBottom = ObjInfo->GetPos()->fY - *ObjInfo->GetSize() * 0.5f;
	if (fMyTop < fYourBottom)
		return false;

	float fMyBottom = this->m_Pos.fY - this->m_fSize * 0.5f;
	float fYourTop = ObjInfo->GetPos()->fY + *ObjInfo->GetSize() * 0.5f;
	if (fYourTop < fMyBottom)
		return false;

	return true;
}

