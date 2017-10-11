#pragma once

class CGameObject
{
public:
	CGameObject();
	~CGameObject();
	CGameObject(Position* pos, float* size, Color* rgba);
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
private:
	Position	m_Pos;
	float		m_fSize;
	Color		m_Color;

	float		m_fSpeed;
};

