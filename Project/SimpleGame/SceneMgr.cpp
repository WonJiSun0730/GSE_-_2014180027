#include "stdafx.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Renderer.h"


void CSceneMgr::Initialize(void)
{
	if(m_Renderer == NULL)
		m_Renderer = new Renderer(500, 500);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	//임의의 위치에 10개의 사각형 생성
	for (int i = 0; i < 10; ++i)
	{	//0,0 500,500....
		Position Pos = Position(rand()  % 500 - 250, rand() % 500 - 250);
		CGameObject *Obj = new CGameObject(&Pos, OBJECT_CHARACTER);

		//m_Objlist.push_back(Obj);
		m_ObjArr[i] = Obj;
	}

	Position Pos = Position(0.f, 0.f);
	CGameObject *Obj = new CGameObject(&Pos, OBJECT_BUILDING);
	m_ObjArr[10] = Obj;
}

void CSceneMgr::Release(void)
{
	delete m_Renderer;

	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i] != NULL)
		{
			delete m_ObjArr[i];
			m_ObjArr[i] = NULL;
		}
	}
}

void CSceneMgr::Update(void)
{
	CGameObject* temp = NULL;
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i] != NULL)
		{
			if (m_ObjArr[i]->Update() == 1)
			{
				delete m_ObjArr[i];
				m_ObjArr[i] = NULL;
			}
			else if (m_ObjArr[i]->Update() == 2)
			{
				temp = new CGameObject(m_ObjArr[i]->GetPos(), OBJECT_BULLET);
				PushBullet(temp);
			}
		}
	}

	/*if (makeObj)
	{
		PushBullet()
	}*/

	CollisionCheck_Optimi();
}

void CSceneMgr::Render(void)
{
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i] != NULL)
		{
			m_Renderer->DrawSolidRect(m_ObjArr[i]->GetPos()->fX, m_ObjArr[i]->GetPos()->fY, 0.f,
				*m_ObjArr[i]->GetSize(),
				m_ObjArr[i]->GetColor()->fR, m_ObjArr[i]->GetColor()->fG, m_ObjArr[i]->GetColor()->fB, m_ObjArr[i]->GetColor()->fAlpha);
		}
	}
}

void CSceneMgr::PushObj(CGameObject * NewObj)
{
	int iObjNum = 0;
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i] != NULL && m_ObjArr[i]->getObjType() == OBJECT_CHARACTER)
		{
			iObjNum++;
		}
	}

	if (iObjNum < MAXCHAR)
	{
		for (int i = 0; i < MAXCOUNT; ++i)
		{
			if (m_ObjArr[i] == NULL)
			{
				m_ObjArr[i] = NewObj;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < MAXCOUNT; ++i)
		{
			if (m_ObjArr[i] != NULL && m_ObjArr[i]->getObjType() == OBJECT_CHARACTER)
			{
				delete m_ObjArr[i];
				m_ObjArr[i] = NULL;
				m_ObjArr[i] = NewObj;
				break;
			}
		}
	}
}

void CSceneMgr::CollisionCheck_Optimi(void)
{
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i] != NULL)
		{
			bool coll = false;
			for (int j = 0; j < MAXCOUNT; ++j)
			{
				if (m_ObjArr[j] != NULL)
				{
					if (i != j)
					{
						if (m_ObjArr[i]->CollisionCheck(m_ObjArr[j]))
						{
							coll = true;
							break;
						}
					}
				}
			}
			if(coll)
				m_ObjArr[i]->setCollision(true);
			else
				m_ObjArr[i]->setCollision(false);
		}
	}
}

void CSceneMgr::SetElapsedTime(float fElapsedTime)
{
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i] != NULL)
		{
			m_ObjArr[i]->SetElapsedTime(fElapsedTime);
			break;
		}
	}
}

void CSceneMgr::PushBullet(CGameObject * NewObj)
{
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i] == NULL)
		{
			m_ObjArr[i] = NewObj;
			break;
		}
	}
}

CSceneMgr::CSceneMgr()
	: m_Renderer(NULL)
{
	Initialize();
}


CSceneMgr::~CSceneMgr()
{
	Release();
}
