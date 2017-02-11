#include "Rubiks3x3.h"
#include "faces.h"
#include <iostream>

using namespace std;

Rubiks3x3::Rubiks3x3()
{
	init();
}

void Rubiks3x3::init()
{
	char color;
	
	for (int n = 0; n < nbFaces; n++)
	{
		switch (n)
		{
		case FACE_UP:
			color = 'G';
			break;
		case FACE_LEFT:
			color = 'R';
			break;
		case FACE_FRONT:
			color = 'W';
			break;
		case FACE_RIGHT:
			color = 'O';
			break;
		case FACE_BACK:
			color = 'Y';
			break;
		case FACE_DOWN:
			color = 'B';
			break;
		}

		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				rubiks[n][i][j] = color;
			}
		}
	}
}

void Rubiks3x3::moveLeft() // TODO
{
	for (int n = 0; n < nbFaces; n++)
	{

	}
}

void Rubiks3x3::moveRight() // TODO
{

}

void Rubiks3x3::consoleShow()
{
	for (int n = 0; n < nbFaces; n++)
	{
		cout << " ";
		for (int j = 0; j < dim; j++)
		{
			cout << "_";
		}
		cout << endl;

		for (int i = 0; i < dim; i++)
		{
			cout << "|";
			for (int j = 0; j < dim; j++)
			{
				cout << rubiks[n][i][j];
			}
			cout << "|" << endl;
		}
	}
}

void Rubiks3x3::rotateFace(int face) // TODO
{
	char buff1[dim], buff2[dim];


}

void Rubiks3x3::changeFace(int rFace, int sFace, int dFace) // TODO
{
	
}