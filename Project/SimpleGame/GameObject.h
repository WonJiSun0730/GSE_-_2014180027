#pragma once

class CGameObject
{
public:
	CGameObject();
	~CGameObject();
	CGameObject(Position* pos, float* size, Color* rgba);
	CGameObject(Position* pos, int ObjType, CGameObject* pMyOwner = NULL);
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

	float GetLifeTime(void);
	void SetLifeTime(float Lifetime);

	CGameObject* getMyOwner(void);
private:
	Position	m_Pos;
	float		m_fSize;
	Color		m_Color;

	float		m_fSpeed;
	Position		m_Dir;

	static float		m_fElapsedTime;
	float		m_fLifeTime;

	int			m_ObjType;
	float		m_fBulletCoolTime;
	float		m_fArrowCoolTime;

	CGameObject* m_pMyOwner;
};

