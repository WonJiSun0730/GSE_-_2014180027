#pragma once

class CGameObject
{
public:
	CGameObject();
	~CGameObject();
	CGameObject(Position* pos, float* size, Color* rgba);
	CGameObject(Position* pos, int ObjType);
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

	void setCollision(bool Collstate);
	bool getCollision(void);

	bool CollisionCheck(CGameObject* ObjInfo);
	void SetElapsedTime(float fElapsedTime);

	int getObjType(void);
private:
	Position	m_Pos;
	float		m_fSize;
	Color		m_Color;

	float		m_fSpeed;
	Position		m_Dir;

	bool		m_bCollision;
	static float		m_fElapsedTime;
	float		m_fLifeTime;

	int			m_ObjType;
	float		m_fBulletCoolTime;


};

