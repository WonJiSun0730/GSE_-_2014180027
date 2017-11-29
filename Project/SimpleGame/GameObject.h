#pragma once

class CGameObject
{
public:
	CGameObject();
	~CGameObject();
	CGameObject(Position* pos, float* size, Color* rgba);
	CGameObject(Position* pos, int ObjType, int MyTeam = Team_Red);
public:
	virtual void initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

	void SetPos(Position* Pos);
	void SetSize(float* Size);
	void SetColor(Color* RGBA);
	Position* GetPos(void);
	float* GetSize(void);
	Color* GetColor(void);

	bool CollisionCheck(CGameObject* ObjInfo);
	void SetElapsedTime(float fElapsedTime);

	int getObjType(void);
	int getMyTeam(void);

	float GetLifeTime(void);
	void SetLifeTime(float Lifetime);

	int GetSpriteX(void);
private:
	int			m_ObjType;
	int			m_MyTeam;

	Position	m_Pos;
	float		m_fSize;
	Color		m_Color;

	float		m_fSpeed;
	Position		m_Dir;

	static float		m_fElapsedTime;
	float		m_fLifeTime;

	float		m_fBulletCoolTime;
	float		m_fArrowCoolTime;

	int			m_iSpriteMaxX;
	int			m_iSpriteX;

	float		m_fSpriteCoolTime;
};

