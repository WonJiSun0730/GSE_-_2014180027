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

	//������ ��ġ�� 10���� �簢�� ����
	for (int i = 0; i < 10; ++i)
	{	//0,0 500,500....
		Position Pos = Position(float(rand()  % 500 - 250), float(rand() % 500 - 250));
		CGameObject *Obj = new CGameObject(&Pos, OBJECT_CHARACTER);

		m_ObjArr[i][OBJECT_CHARACTER] = Obj;
	}

	Position Pos = Position(0.f, 0.f);
	CGameObject *Obj = new CGameObject(&Pos, OBJECT_BUILDING);
	m_ObjArr[0][OBJECT_BUILDING] = Obj;
}

void CSceneMgr::Release(void)
{
	delete m_Renderer;

	for (int i = 0; i < MAXCOUNT; ++i)
	{
		for (int j = 0; j < OBJECT_end; ++j)
		{
			if (m_ObjArr[i][j] != NULL)
			{
				delete m_ObjArr[i][j];
				m_ObjArr[i][j] = NULL;
			}
		}
	}
}

void CSceneMgr::Update(void)
{
	CGameObject* temp = NULL;
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		for (int j = 0; j < OBJECT_end; j++)
		{
			if (m_ObjArr[i][j] != NULL)
			{
				if (m_ObjArr[i][j]->Update() == 1)
				{
					delete m_ObjArr[i][j];
					m_ObjArr[i][j] = NULL;
				}
				else if (m_ObjArr[i][j]->Update() == 2)
				{//�Ѿ� ����
					if (j == OBJECT_BUILDING)
					{
						CGameObject* temp = new CGameObject(m_ObjArr[i][j]->GetPos(), OBJECT_BULLET, m_ObjArr[i][j]);
						PushBullet(temp);
					}
					if (j == OBJECT_CHARACTER)
					{
						CGameObject* temp = new CGameObject(m_ObjArr[i][j]->GetPos(), OBJECT_ARROW, m_ObjArr[i][j]);
						PushArrow(temp);
					}
				}
			}
		}
	}

	CollisionCheck_Optimi();
}

void CSceneMgr::Render(void)
{
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		for (int j = 0; j < OBJECT_end; j++)
		{
			if (m_ObjArr[i][j] != NULL)
			{
				m_Renderer->DrawSolidRect(m_ObjArr[i][j]->GetPos()->fX, m_ObjArr[i][j]->GetPos()->fY, 0.f,
					*m_ObjArr[i][j]->GetSize(),
					m_ObjArr[i][j]->GetColor()->fR, m_ObjArr[i][j]->GetColor()->fG, m_ObjArr[i][j]->GetColor()->fB,
					m_ObjArr[i][j]->GetColor()->fAlpha);
			}
		}
	}
}

void CSceneMgr::PushObj(CGameObject * NewObj)
{
	int iObjNum = 0;
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_CHARACTER] != NULL)
		{
			iObjNum++;
		}
	}

	if (iObjNum < MAXCHAR)
	{
		for (int i = 0; i < MAXCOUNT; ++i)
		{
			if (m_ObjArr[i][OBJECT_CHARACTER] == NULL)
			{
				m_ObjArr[i][OBJECT_CHARACTER] = NewObj;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < MAXCOUNT; ++i)
		{
			if (m_ObjArr[i][OBJECT_CHARACTER] != NULL)
			{
				delete m_ObjArr[i][OBJECT_CHARACTER];
				m_ObjArr[i][OBJECT_CHARACTER] = NULL;
				m_ObjArr[i][OBJECT_CHARACTER] = NewObj;
				break;
			}
		}
	}
}

void CSceneMgr::CollisionCheck_Optimi(void)
{
	//������ ĳ����
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_BUILDING] == NULL)
			break;
		for (int j = 0; j < MAXCOUNT; ++j)
		{
			if (m_ObjArr[j][OBJECT_CHARACTER] == NULL)
				break;

			if (m_ObjArr[i][OBJECT_BUILDING]->CollisionCheck(m_ObjArr[j][OBJECT_CHARACTER]) &&
				m_ObjArr[j][OBJECT_CHARACTER]->CollisionCheck(m_ObjArr[i][OBJECT_BUILDING]) )
			{
				float BulidingLife = m_ObjArr[i][OBJECT_BUILDING]->GetLifeTime() - m_ObjArr[j][OBJECT_CHARACTER]->GetLifeTime();
				m_ObjArr[i][OBJECT_BUILDING]->SetLifeTime(BulidingLife);
				m_ObjArr[j][OBJECT_CHARACTER]->SetLifeTime(0.f);
				break;
			}
		}
	}
	//�Ѿ˰� ĳ����
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_BULLET] == NULL)
			break;
		for (int j = 0; j < MAXCOUNT; ++j)
		{
			if (m_ObjArr[j][OBJECT_CHARACTER] == NULL)
				break;

			if (m_ObjArr[i][OBJECT_BULLET]->CollisionCheck(m_ObjArr[j][OBJECT_CHARACTER]) &&
				m_ObjArr[j][OBJECT_CHARACTER]->CollisionCheck(m_ObjArr[i][OBJECT_BULLET]))
			{
				//ĳ���� ����� - �Ҹ� �����
				float CharaLife = m_ObjArr[j][OBJECT_CHARACTER]->GetLifeTime() - m_ObjArr[i][OBJECT_BULLET]->GetLifeTime();
				m_ObjArr[j][OBJECT_CHARACTER]->SetLifeTime(CharaLife);
				m_ObjArr[i][OBJECT_BULLET]->SetLifeTime(0.f);
				break;
			}
		}
	}
	//������ ȭ��
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_BUILDING] == NULL)
			break;
		for (int j = 0; j < MAXCOUNT; ++j)
		{
			if (m_ObjArr[j][OBJECT_ARROW] == NULL)
				break;

			if (m_ObjArr[i][OBJECT_BUILDING]->CollisionCheck(m_ObjArr[j][OBJECT_ARROW]) &&
				m_ObjArr[j][OBJECT_ARROW]->CollisionCheck(m_ObjArr[i][OBJECT_BUILDING]))
			{
				float BulidingLife = m_ObjArr[i][OBJECT_BUILDING]->GetLifeTime() - m_ObjArr[j][OBJECT_ARROW]->GetLifeTime();
				m_ObjArr[i][OBJECT_BUILDING]->SetLifeTime(BulidingLife);
				m_ObjArr[j][OBJECT_ARROW]->SetLifeTime(0.f);
				break;
			}
		}
	}
	//�÷��̾�� ȭ��
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_CHARACTER] == NULL)
			break;
		for (int j = 0; j < MAXCOUNT; ++j)
		{
			if (m_ObjArr[j][OBJECT_ARROW] == NULL)
				break;

			if (m_ObjArr[i][OBJECT_CHARACTER]->CollisionCheck(m_ObjArr[j][OBJECT_ARROW]) &&	//ĳ���Ϳ� ȭ���� �浹�ߴ�?
				m_ObjArr[j][OBJECT_ARROW]->CollisionCheck(m_ObjArr[i][OBJECT_CHARACTER]) &&	//ȭ�쿡 ĳ���Ͱ� �浹�ߴ�?
				m_ObjArr[j][OBJECT_ARROW]->getMyOwner() != m_ObjArr[i][OBJECT_CHARACTER])	//ȭ���� ������ ���� �ٸ���?
			{
				float CharaLife = m_ObjArr[i][OBJECT_CHARACTER]->GetLifeTime() - m_ObjArr[j][OBJECT_ARROW]->GetLifeTime();
				m_ObjArr[i][OBJECT_CHARACTER]->SetLifeTime(CharaLife);
				m_ObjArr[j][OBJECT_ARROW]->SetLifeTime(0.f);
				break;
			}
		}
	}
}

void CSceneMgr::SetElapsedTime(float fElapsedTime)
{
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		for (int j = 0; j < OBJECT_end; ++j)
		{
			if (m_ObjArr[i][j] != NULL)
			{
				m_ObjArr[i][j]->SetElapsedTime(fElapsedTime);
				break;
			}
		}
	}
}

void CSceneMgr::PushBullet(CGameObject * NewObj)
{
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_BULLET] == NULL)
		{
			m_ObjArr[i][OBJECT_BULLET] = NewObj;
			break;
		}
	}
}

void CSceneMgr::PushArrow(CGameObject * NewObj)
{
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_ARROW] == NULL)
		{
			m_ObjArr[i][OBJECT_ARROW] = NewObj;
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
