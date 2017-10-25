#pragma once

class CGameObject;
class Renderer;

class CSceneMgr
{
private:
	Renderer* m_Renderer;

	CGameObject* m_ObjArr[MAXCOUNT];
private:
	void Initialize(void);
	void Release(void);
public:
	void Update(void);
	void Render(void);
	void PushObj(CGameObject* NewObj);
	void CollisionCheck_Optimi(void);

public:
	CSceneMgr();
	~CSceneMgr();
};

