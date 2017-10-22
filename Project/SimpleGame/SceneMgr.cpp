#include "stdafx.h"
#include "SceneMgr.h"
#include "GameObject.h"


void CSceneMgr::Initialize(void)
{
	//임의의 위치에 50개의 사각형 생성
	for (int i = 0; i < 50; ++i)
	{	//0,0 500,500....
		Position Pos = Position(rand()  % 500 - 250, rand() % 500 - 250);
		//(x - 250, -(y - 250)) 해줘야하나 체크
		//0~500
		float fsize = float((rand() % 5 + 2) * 5); //10~35
		Color RGBA = Color(1.f, 1.f, 1.f);
		CGameObject *Obj = new CGameObject(&Pos, &fsize, &RGBA);

		m_Objlist.push_back(Obj);
	}
}

void CSceneMgr::Release(void)
{
	list<CGameObject*>::iterator iter = m_Objlist.begin();
	list<CGameObject*>::iterator iter_end = m_Objlist.end();

	for (iter; iter != iter_end; ++iter)
	{
		delete *iter;
	}
	m_Objlist.clear();
}

void CSceneMgr::Update(void)
{
	list<CGameObject*>::iterator iter = m_Objlist.begin();
	list<CGameObject*>::iterator iter_end = m_Objlist.end();

	for (; iter != iter_end;)
	{
		if ((*iter)->Update() == 1)
		{
			delete *iter;
			iter = m_Objlist.erase(iter);
			iter_end = m_Objlist.end();
			std::cout << "erase" << endl;
		}
		else
		{
			++iter;
		}
	}

	CollisionCheck();
}

void CSceneMgr::Render(void)
{
	list<CGameObject*>::iterator iter = m_Objlist.begin();
	list<CGameObject*>::iterator iter_end = m_Objlist.end();

	for (; iter != iter_end; ++iter)
	{
		(*iter)->Render();
	}
}

void CSceneMgr::PushObj(CGameObject * NewObj)
{
	m_Objlist.push_back(NewObj);
}

void CSceneMgr::CollisionCheck(void)
{
	list<CGameObject*>::iterator iter = m_Objlist.begin();
	list<CGameObject*>::iterator iter_end = m_Objlist.end();

	for (; iter != iter_end; ++iter)
	{
		bool coll = false;
		list<CGameObject*>::iterator iter_other = m_Objlist.begin();
		list<CGameObject*>::iterator iter_other_end = m_Objlist.end();
		for (; iter_other != iter_other_end; ++iter_other)
		{
			if (iter != iter_other)
			{
				float fSize = *(*iter)->GetSize();
				float fSize_other = *(*iter_other)->GetSize();
				//1. 각 객체들과의 거리를 측정 
				if (abs((*iter)->GetPos()->fX - (*iter_other)->GetPos()->fX) <= fSize / 2 + fSize_other / 2
					&& abs((*iter)->GetPos()->fY - (*iter_other)->GetPos()->fY) <= fSize / 2 + fSize_other / 2)
				{
					//안 만나요...연산 하지말자...
					coll = true;
					break;
				}
				else
				{
					/*float fLeft = (*iter)->GetPos()->fX - fSize / 2;
					float fRight = (*iter)->GetPos()->fX + fSize / 2;
					float fUp = (*iter)->GetPos()->fY + fSize / 2;
					float fDown = (*iter)->GetPos()->fY - fSize / 2;

					float fLeft_other = (*iter_other)->GetPos()->fX - fSize_other / 2;
					float fRight_other = (*iter_other)->GetPos()->fX + fSize_other / 2;
					float fUp_other = (*iter_other)->GetPos()->fY + fSize_other / 2;
					float fDown_other = (*iter_other)->GetPos()->fY - fSize_other / 2;

					if (fLeft < fRight_other && fRight > fLeft_other
						&& fUp > fDown_other && fDown < fUp_other)
					{
						coll = true;
						break;
					}*/
				}
			}
		}

		if (coll)
			(*iter)->setCollision(true);
		else
			(*iter)->setCollision(false);
	}
}

CSceneMgr::CSceneMgr()
{
	Initialize();
}


CSceneMgr::~CSceneMgr()
{
	Release();
}
