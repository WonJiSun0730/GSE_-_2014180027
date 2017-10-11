/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "GameObject.h"

#include <list>

using namespace std;

Renderer *g_Renderer = NULL;

////임시 선언 변수
//Position pos = Position(50.f, 50.f);
//float size1= 10.f;
//Color rgba= Color(0.f,1.f,1.f,1.f);
//CGameObject *gObj = new CGameObject(&pos, &size1, &rgba);
//
//
//Position pos2 = Position(-50.f, -50.f);
//float size2 = 20.f;
//Color rgba2 = Color(0.f, 0.f, 1.f, 1.f);
//
//CGameObject *gObj2 = new CGameObject(&pos2, &size2, &rgba2);

list<CGameObject*> Objlist;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);

	////static 
	//gObj->Update();
	//gObj2->Update();

	//gObj->Render();
	//gObj2->Render();


	list<CGameObject*>::iterator iter = Objlist.begin();
	list<CGameObject*>::iterator iter_end = Objlist.end();

	for (; iter != iter_end;)
	{
		(*iter)->Update();
		(*iter)->Render();
			++iter;
	}


	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		std::cout << "마우스 입력 : 객체 추가합니다." << endl;
		std::cout << x << "," << y << endl;
		Position Pos = Position(x - 250, -(y - 250));
		float fsize = float((rand() % 5 + 2) * 5);
		Color RGBA = Color( float(rand() % 255) / 255.f , float(rand() % 255) / 255.f, float(rand() % 255) / 255.f);
		CGameObject *Obj = new CGameObject(&Pos,&fsize,&RGBA);

		Objlist.push_back(Obj);
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
	glutInitWindowSize(500, 500);
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

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

	list<CGameObject*>::iterator iter = Objlist.begin();
	list<CGameObject*>::iterator iter_end = Objlist.end();

	for (iter; iter != iter_end; ++iter)
	{
		delete *iter;
	}
	Objlist.clear();

    return 0;
}

