#pragma once
#include "Dependencies\glew.h"

class CGameObject;
class Renderer;
class Sound;

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

enum {
	LEVEL_BUILD = 1,
	LEVEL_CHAR,
	LEVEL_BANDA,
	LEVEL_BACKG,
	LEVEL_end
}RenderLev;


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
	Sound* m_Sound;

	CGameObject* m_ObjArr[MAXCOUNT][OBJECT_end];
	GLuint m_ObjTex[Team_end][OBJECT_end];
	
	GLuint m_BackGround;
	GLuint m_ParticleTex;

	float m_fElapsedTime;

	float Cooltime;

	int m_BGMusic;
};

