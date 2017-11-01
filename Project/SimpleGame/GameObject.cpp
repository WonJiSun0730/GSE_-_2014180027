#include "stdafx.h"
#include "GameObject.h"


float CGameObject::m_fElapsedTime = 0.f;

CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

CGameObject::CGameObject(Position* pos, float* size, Color* rgba)
	: m_Pos(*pos), m_fSize(*size), m_Color(*rgba), m_fSpeed(200.f), m_fLifeTime(100.f)
{
	m_ObjType = OBJECT_end;
	initialize();
}

CGameObject::CGameObject(Position * pos, int ObjType)
	: m_Pos(*pos), m_ObjType(ObjType)
{
	initialize();
}

void CGameObject::initialize(void)
{
	float rad = float(rand() % 360);

	//0~1������ ���� ����
	m_Dir.fX = cos(rad * 3.141592f / 180.f);
	m_Dir.fY = sin(rad * 3.141592f / 180.f);

	m_fBulletCoolTime = 0.5;
	switch (m_ObjType)
	{
	case OBJECT_BUILDING:
		m_Color.fR = 1, m_Color.fG = 1, m_Color.fB = 0;
		m_fSize = 50;
		m_fSpeed = 0.f;
		m_fLifeTime = 500.f;
		break;
	case OBJECT_CHARACTER:
		m_Color.fR = 1, m_Color.fG = 1, m_Color.fB = 1;
		m_fSize = 10;
		m_fSpeed = 100.f;
		m_fLifeTime = 10.f;
		break;
	case OBJECT_BULLET:
		m_Color.fR = 1, m_Color.fG = 0, m_Color.fB = 0;
		m_fSize = 2;
		m_fSpeed = 300.f;
		m_fLifeTime = 20.f;
		break;
	case OBJECT_ARROW:
		m_Color.fR = 0, m_Color.fG = 1, m_Color.fB = 0;
		m_fSize = 2;
		m_fSpeed = 100.f;
		m_fLifeTime = 10.f;
		break;
	case OBJECT_end:
		m_Color.fR = 0.5, m_Color.fG = 0.5, m_Color.fB = 0.5;
		m_fSize = 1;
		m_fSpeed = 1000000;
		m_fLifeTime = 10.f;
		break;
	default:
		break;
	}

	m_bCollision = false;
}

int CGameObject::Update(void)
{
	m_Pos.fX += m_fSpeed * m_fElapsedTime * m_Dir.fX;
	m_Pos.fY += m_fSpeed * m_fElapsedTime * m_Dir.fY;

	if ((m_ObjType == OBJECT_CHARACTER || m_ObjType == OBJECT_BULLET) && m_bCollision)
		return 1;

	if (m_ObjType == OBJECT_BUILDING)
	{
		m_fBulletCoolTime -= m_fElapsedTime;
		if (m_fBulletCoolTime <= 0)
		{
			m_fBulletCoolTime = 0.5f;
			return 2;
		}
	}

	//���� >> �̰� �ӽ�...�Ի簢�� �ݻ簢�� ������
	if (-250.f > m_Pos.fX || m_Pos.fX > 250.f)
	{
		m_Dir.fX *= -1;
	}
	if (-250.f > m_Pos.fY || m_Pos.fY > 250.f)
	{
		m_Dir.fY *= -1;
	}

	m_fLifeTime -= m_fElapsedTime;
	if (m_fLifeTime <= 0)
			return 1;

	return 0;
}

void CGameObject::Render(void)
{

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

void CGameObject::setCollision(bool Collstate)
{
	m_bCollision = Collstate;
}

bool CGameObject::getCollision(void)
{
	return m_bCollision;
}

bool CGameObject::CollisionCheck(CGameObject* ObjInfo)
{
	//left���� �� ���ʿ� �ִ� ������
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

	//1. �浹üũ �ϴ� ��ü���� ���� ��� false
	if (this->getObjType() == ObjInfo->getObjType())
		return false;
	else
	{
		if (this->getObjType() == OBJECT_BUILDING)
		{
			if (ObjInfo->getObjType() == OBJECT_CHARACTER)
			{
				this->m_fLifeTime -= ObjInfo->m_fLifeTime;
				return true;
			}
			else if (ObjInfo->getObjType() == OBJECT_BULLET)
			{
				return false;
			}
		}
		else if (this->getObjType() == OBJECT_CHARACTER)
		{
			if (ObjInfo->getObjType() == OBJECT_BUILDING)
			{
				ObjInfo->m_fLifeTime -= this->m_fLifeTime;
				return true;
			}
			else if (ObjInfo->getObjType() == OBJECT_BULLET)
			{
				this->m_fLifeTime -= ObjInfo->m_fLifeTime;
				return true;
			}
		}
		else if (this->getObjType() == OBJECT_BULLET)
		{
			if (ObjInfo->getObjType() == OBJECT_BUILDING)
			{
				return false;
			}
			else if (ObjInfo->getObjType() == OBJECT_CHARACTER)
			{
				ObjInfo->m_fLifeTime -= this->m_fLifeTime;
				return true;
			}
		}
	}

	return true;
}

void CGameObject::SetElapsedTime(float fElapsedTime)
{
	m_fElapsedTime = fElapsedTime;
}

int CGameObject::getObjType(void)
{
	return m_ObjType;
}
