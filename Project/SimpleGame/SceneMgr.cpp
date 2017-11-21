#include "stdafx.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Renderer.h"


void CSceneMgr::Initialize(void)
{
	if(m_Renderer == NULL)
		m_Renderer = new Renderer(WINSX, WINSY);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	//빌딩 각 팀에 3개씩 설치
	int BuildingNum = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			Position Pos = Position(-float(WINSX / 2 * 0.8) + float(WINSX / 2 * 0.8) * i, -float(WINSY/2 * 0.9) + float(WINSY * 0.9)  * j);
			CGameObject *Obj = new CGameObject(&Pos, OBJECT_BUILDING, 1-j);
			m_ObjArr[BuildingNum][OBJECT_BUILDING] = Obj;

			BuildingNum++;
		}
	}

	//현재 다른 리소스는 추가되지 않았음
	m_ObjTex[Team_Red][OBJECT_BUILDING] = m_Renderer->CreatePngTexture("../Resource/Building_Red.png");
	m_ObjTex[Team_Blue][OBJECT_BUILDING] = m_Renderer->CreatePngTexture("../Resource/Building_Blue.png");
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
				{//총알 생성
					if (j == OBJECT_BUILDING)
					{
						CGameObject* temp = new CGameObject(m_ObjArr[i][j]->GetPos(), OBJECT_BULLET, m_ObjArr[i][j]->getMyTeam());
						PushBullet(temp);
					}
					if (j == OBJECT_CHARACTER)
					{
						CGameObject* temp = new CGameObject(m_ObjArr[i][j]->GetPos(), OBJECT_ARROW, m_ObjArr[i][j]->getMyTeam());
						PushArrow(temp);
					}
				}
			}
		}
	}

	//북 진영 내부에 Blue팀 추가 - 1초마다...
	static float Cooltime = 1.f;
	Cooltime -= m_fElapsedTime;
	if (Cooltime <= 0.f)
	{
		Cooltime = 1.f;

		int temp = 0;
		for (int k = 0; k < MAXCOUNT; ++k)
		{
			if (m_ObjArr[k][OBJECT_CHARACTER] == NULL)
			{
				Position Pos = Position(float(rand() % WINSX - WINSX / 2), float(rand() % (WINSY - WINSY / 2) / 2));
				CGameObject *Obj = new CGameObject(&Pos, OBJECT_CHARACTER, Team_Red);

				m_ObjArr[k][OBJECT_CHARACTER] = Obj;
				std::cout << k << endl;
				break;
			}
			//현재 객체 5개이상 못만드는 에러가...
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
				if (m_ObjArr[i][j]->getObjType() != OBJECT_BUILDING)
				{
					m_Renderer->DrawSolidRect(m_ObjArr[i][j]->GetPos()->fX, m_ObjArr[i][j]->GetPos()->fY, 0.f,
						*m_ObjArr[i][j]->GetSize(),
						m_ObjArr[i][j]->GetColor()->fR, m_ObjArr[i][j]->GetColor()->fG, m_ObjArr[i][j]->GetColor()->fB,
						m_ObjArr[i][j]->GetColor()->fAlpha);
				}
				else
				{
					if (m_ObjArr[i][j]->getMyTeam() == Team_Red)
					{
						m_Renderer->DrawTexturedRect(m_ObjArr[i][j]->GetPos()->fX, m_ObjArr[i][j]->GetPos()->fY, 0.f,
							*m_ObjArr[i][j]->GetSize(),
							m_ObjArr[i][j]->GetColor()->fR, m_ObjArr[i][j]->GetColor()->fG, m_ObjArr[i][j]->GetColor()->fB,
							m_ObjArr[i][j]->GetColor()->fAlpha,
							m_ObjTex[Team_Red][OBJECT_BUILDING]);
					}
					else if (m_ObjArr[i][j]->getMyTeam() == Team_Blue)
					{
						m_Renderer->DrawTexturedRect(m_ObjArr[i][j]->GetPos()->fX, m_ObjArr[i][j]->GetPos()->fY, 0.f,
							*m_ObjArr[i][j]->GetSize(),
							m_ObjArr[i][j]->GetColor()->fR, m_ObjArr[i][j]->GetColor()->fG, m_ObjArr[i][j]->GetColor()->fB,
							m_ObjArr[i][j]->GetColor()->fAlpha,
							m_ObjTex[Team_Blue][OBJECT_BUILDING]);
					}
				}
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

	if (iObjNum < MAXCHARNUM)
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
	//빌딩과 캐릭터
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_BUILDING] == NULL)
			break;
		for (int j = 0; j < MAXCOUNT; ++j)
		{
			if (m_ObjArr[j][OBJECT_CHARACTER] == NULL)
				break;

			if (m_ObjArr[i][OBJECT_BUILDING]->CollisionCheck(m_ObjArr[j][OBJECT_CHARACTER]) &&
				m_ObjArr[j][OBJECT_CHARACTER]->CollisionCheck(m_ObjArr[i][OBJECT_BUILDING]) &&
				m_ObjArr[j][OBJECT_CHARACTER]->getMyTeam() != m_ObjArr[i][OBJECT_BUILDING]->getMyTeam())
			{
				float BulidingLife = m_ObjArr[i][OBJECT_BUILDING]->GetLifeTime() - m_ObjArr[j][OBJECT_CHARACTER]->GetLifeTime();
				m_ObjArr[i][OBJECT_BUILDING]->SetLifeTime(BulidingLife);
				m_ObjArr[j][OBJECT_CHARACTER]->SetLifeTime(0.f);
				break;
			}
		}
	}
	//총알과 캐릭터
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_BULLET] == NULL)
			break;
		for (int j = 0; j < MAXCOUNT; ++j)
		{
			if (m_ObjArr[j][OBJECT_CHARACTER] == NULL)
				break;

			if (m_ObjArr[i][OBJECT_BULLET]->CollisionCheck(m_ObjArr[j][OBJECT_CHARACTER]) &&
				m_ObjArr[j][OBJECT_CHARACTER]->CollisionCheck(m_ObjArr[i][OBJECT_BULLET]) &&
				m_ObjArr[j][OBJECT_CHARACTER]->getMyTeam() != m_ObjArr[i][OBJECT_BULLET]->getMyTeam())
			{
				//캐릭터 생명력 - 불릿 생명력
				float CharaLife = m_ObjArr[j][OBJECT_CHARACTER]->GetLifeTime() - m_ObjArr[i][OBJECT_BULLET]->GetLifeTime();
				m_ObjArr[j][OBJECT_CHARACTER]->SetLifeTime(CharaLife);
				m_ObjArr[i][OBJECT_BULLET]->SetLifeTime(0.f);
				break;
			}
		}
	}
	//빌딩과 화살
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_BUILDING] == NULL)
			break;
		for (int j = 0; j < MAXCOUNT; ++j)
		{
			if (m_ObjArr[j][OBJECT_ARROW] == NULL)
				break;

			if (m_ObjArr[i][OBJECT_BUILDING]->CollisionCheck(m_ObjArr[j][OBJECT_ARROW]) &&
				m_ObjArr[j][OBJECT_ARROW]->CollisionCheck(m_ObjArr[i][OBJECT_BUILDING]) &&
				m_ObjArr[j][OBJECT_ARROW]->getMyTeam() != m_ObjArr[i][OBJECT_BUILDING]->getMyTeam())
			{
				float BulidingLife = m_ObjArr[i][OBJECT_BUILDING]->GetLifeTime() - m_ObjArr[j][OBJECT_ARROW]->GetLifeTime();
				m_ObjArr[i][OBJECT_BUILDING]->SetLifeTime(BulidingLife);
				m_ObjArr[j][OBJECT_ARROW]->SetLifeTime(0.f);
				break;
			}
		}
	}
	//플레이어와 화살
	for (int i = 0; i < MAXCOUNT; ++i)
	{
		if (m_ObjArr[i][OBJECT_CHARACTER] == NULL)
			break;
		for (int j = 0; j < MAXCOUNT; ++j)
		{
			if (m_ObjArr[j][OBJECT_ARROW] == NULL)
				break;

			if (m_ObjArr[i][OBJECT_CHARACTER]->CollisionCheck(m_ObjArr[j][OBJECT_ARROW]) &&	//캐릭터에 화살이 충돌했니?
				m_ObjArr[j][OBJECT_ARROW]->CollisionCheck(m_ObjArr[i][OBJECT_CHARACTER]) &&	//화살에 캐릭터가 충돌했니?
				m_ObjArr[j][OBJECT_ARROW]->getMyTeam() != m_ObjArr[i][OBJECT_CHARACTER]->getMyTeam())	//화살의 주인이 서로 다르니?
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

	m_fElapsedTime = fElapsedTime;
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
	: m_Renderer(NULL), m_fElapsedTime(0.f)
{
	Initialize();
}


CSceneMgr::~CSceneMgr()
{
	Release();
}
