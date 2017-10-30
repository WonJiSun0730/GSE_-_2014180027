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
	for (int i = 0; i < MAXCOUNT; ++i)
	{	//0,0 500,500....
		Position Pos = Position(rand()  % 500 - 250, rand() % 500 - 250);
		//Position(x - 250, -(y - 250)); -250~250
		float fsize = float((rand() % 5 + 2) * 5) * 3; //10~35
		Color RGBA = Color(1.f, 1.f, 1.f);
		CGameObject *Obj = new CGameObject(&Pos, &fsize, &RGBA);

		//m_Objlist.push_back(Obj);
		m_ObjArr[i] = Obj;
	}
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
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i] != NULL)
		{
			if (m_ObjArr[i]->Update() == 1)
			{
				delete m_ObjArr[i];
				m_ObjArr[i] = NULL;
			}
		}
	}

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
		if (m_ObjArr[i] == NULL)
		{
			m_ObjArr[i] = NewObj;
			break;
		}
		else
			iObjNum++;
	}
	if (iObjNum == MAXCOUNT)//꽉 차있다.
	{//가장 늦게 만들어진
		static int iSecquen = 0;
		if (m_ObjArr[iSecquen] != NULL)
		{
			delete m_ObjArr[iSecquen];
			m_ObjArr[iSecquen] = NULL;

			m_ObjArr[iSecquen] = NewObj;
			iSecquen++;
			iSecquen %= 10;
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

CSceneMgr::CSceneMgr()
	: m_Renderer(NULL)
{
	Initialize();
}


CSceneMgr::~CSceneMgr()
{
	Release();
}
