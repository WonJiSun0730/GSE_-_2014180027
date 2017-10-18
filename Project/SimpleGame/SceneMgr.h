#pragma once

class CGameObject;

class CSceneMgr
{
private:
	list<CGameObject*> m_Objlist;
private:
	void Initialize(void);
	void Release(void);
public:
	void Update(void);
	void Render(void);
	void PushObj(CGameObject* NewObj);
	void CollisionCheck(void);
public:
	CSceneMgr();
	~CSceneMgr();
};

