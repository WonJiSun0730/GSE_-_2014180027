#pragma once
#include "Dependencies\glew.h"

class CGameObject;
class Renderer;

enum {
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW,
	OBJECT_end
}ObjType;

enum {
	Team_Red,
	Team_Blue,
	Team_end
}Teams;

class CSceneMgr
{
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
	void PushArrow(CGameObject* NewObj);
public:
	CSceneMgr();
	~CSceneMgr();
private:
	Renderer* m_Renderer;
	CGameObject* m_ObjArr[MAXCOUNT][OBJECT_end];
	GLuint m_ObjTex[Team_end][OBJECT_end];

	float m_fElapsedTime;
};

