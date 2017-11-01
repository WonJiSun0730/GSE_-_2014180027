#pragma once

class CGameObject;
class Renderer;

enum {
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW,
	OBJECT_end
}ObjType;

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
	void SetElapsedTime(float fElapsedTime);
	void PushBullet(CGameObject* NewObj);
public:
	CSceneMgr();
	~CSceneMgr();
};

