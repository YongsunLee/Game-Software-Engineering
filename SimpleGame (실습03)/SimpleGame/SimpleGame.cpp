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

#include "Renderer.h"
#include "GameObject.h"
#include "CRectangle.h"

Renderer *g_Renderer = NULL;
CRectangle rectangle(Vec3{ 10, 10, 0 }, 10.0f, Vec4{ 1,0,0,0 });
CRectangle clickObject;

enum MouseInputSide {
	LEFT = 0,
	RIGHT = 2
};

enum MouseInputType{
	BUTTONDOWN = 0,
	BUTTONUP = 1
};

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	g_Renderer->DrawSolidRect(0, 0, 0, 10, 1, 0, 1, 1);

	// GameObject Test
	rectangle.BuildObject(g_Renderer);
	clickObject.BuildObject(g_Renderer);

	glutSwapBuffers();
}

// 계속 실행
void Idle(void)
{
	rectangle.Update();
	clickObject.Update();
	RenderScene();
}

// MouseInputSide (0이면 왼쪽 2면 오른쪽)
// MouseInputType (0이면 다운 1이면 업)
// x, y는 마우스 좌표
void MouseInput(int button, int state, int x, int y)
{
	if (button == BUTTONDOWN && state == LEFT) {
		float windowX = (float)(x - (float)WINDOWWIDTH / 2.0);
		float windowY = -(y - (float)WINDOWHEIGHT / 2.0);

		clickObject.IsInitialized(Vec3{ windowX, windowY, 0 }, 10, Vec4{0,1,0,0});
	}
	RenderScene();
}

// x, y는 키가 눌렸을 때의 마우스의 좌표
// 키보드 전반
void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

// x, y는 키가 눌렸을 때의 마우스의 좌표
// 방향키, 쉬프트, 컨트롤
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
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
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
	g_Renderer = new Renderer(WINDOWWIDTH, WINDOWHEIGHT);
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

    return 0;
}

