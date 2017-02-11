#pragma once

class Rubiks3x3
{
	public:
		Rubiks3x3();
		void init();
		void moveLeft();
		void moveRight();
		void consoleShow();
		
	private:
		static const int nbFaces = 6;
		static const int dim = 3;
		static const int nbSquares = dim * dim;
		char rubiks[nbFaces][dim][dim];

		void rotateFace(int face);
		void changeFace(int rFace, int sFace, int dFace);
};
