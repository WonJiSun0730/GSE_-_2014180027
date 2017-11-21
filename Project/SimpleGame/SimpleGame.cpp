/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
//#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "GameObject.h"

CSceneMgr*	SceneManager = NULL;

DWORD fPrevTime = 0;
float fElapsedTime = 0.f;
float fClickCoolTime = 0.f;

void RenderScene(void)
{
	SceneManager->SetElapsedTime(fElapsedTime);
	fPrevTime = timeGetTime();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.0f);

	SceneManager->Update();
	SceneManager->Render();	

	glutSwapBuffers();

	DWORD fCurTime = timeGetTime();

	fElapsedTime = float(fCurTime - fPrevTime) * 0.001f;

	if (fClickCoolTime > 0.f)
		fClickCoolTime -= fElapsedTime;
	else
		fClickCoolTime = 0.f;
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{//다운만 체크하면 ui에 중복성이 생긴다...나중에 분기를 나눠라

		if (fClickCoolTime != 0.f)
		{
			std::cout << "Cooltime Remain: " << fClickCoolTime << endl;
			return;
		}
		else
		{
			fClickCoolTime = 2.0f;
			if (WINSY / 2 <= y && y <= WINSY)
			{
				std::cout << "마우스 입력 : 객체 추가합니다." << endl;
				std::cout << x << "," << y << endl;
				Position Pos = Position(x - float(WINSX / 2), -(y - float(WINSY / 2)));
				CGameObject *Obj = new CGameObject(&Pos, OBJECT_CHARACTER, Team_Blue);

				SceneManager->PushObj(Obj);
			}
			else
			{
				std::cout << "마우스 입력 : 범위 밖입니다. 객체 추가 못합니다." << endl;
				std::cout << x << "," << y << endl;
			}
		}
	}
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINSX, WINSY);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}
	//OPENGL 초기화 한 다음에 생성.
	SceneManager = new CSceneMgr;

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete SceneManager;
	if (SceneManager != NULL)
	{
		SceneManager = NULL;
	}
    return 0;
}

