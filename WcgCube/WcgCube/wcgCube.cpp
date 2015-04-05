#include "wcgCube.h"

char wcgCube::mCubes[27][6] =
{
	0, -1, -1, 27, 38, -1,
	1, -1, -1, 28, -1, -1,
	2, -1, 20, 29, -1, -1,
	3, -1, -1, -1, 37, -1,
	4, -1, -1, -1, -1, -1,
	5, -1, 19, -1, -1, -1,
	6,  9, -1, -1, 36, -1,
	7, 10, -1, -1, -1, -1,
	8, 11, 18, -1, -1, -1,

	-1, -1, -1, 30, 41, -1,
	-1, -1, -1, 31, -1, -1,
	-1, -1, 23, 32, -1, -1,
	-1, -1, -1, -1, 40, -1,
	-1, -1, -1, -1, -1, -1,
	-1, -1, 22, -1, -1, -1,
	-1, 12, -1, -1, 39, -1,
	-1, 13, -1, -1, -1, -1,
	-1, 14, 21, -1, -1, -1,

	-1, -1, -1, 33, 44, 45,
	-1, -1, -1, 34, -1, 46,
	-1, -1, 26, 35, -1, 47,
	-1, -1, -1, -1, 43, 48,
	-1, -1, -1, -1, -1, 49,
	-1, -1, 25, -1, -1, 50,
	-1, 15, -1, -1, 42, 51,
	-1, 16, -1, -1, -1, 52,
	-1, 17, 24, -1, -1, 53,
};



float wcgCube::mColors[7][4] = 
{
	1, 1, 1, 1,
	1, 0, 0, 1,
	0, 1, 0, 1,
	0, 0, 1, 1,
	1, 1, 0, 1,
	0, 1, 1, 1,
	0.5f, 0.5f, 0.5f, 1
};

char wcgCube::mBlocks[9][22] = 
{
	0,  3,  6,  9, 12, 15, 51, 48, 45, 33, 30, 27, 36, 39, 42, 43, 44, 41, 38, 37, 40, 21,
	1,  4,  7, 10, 13, 16, 52, 49, 46, 34, 31, 28,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,
	2,  5,  8, 11, 14, 17, 53, 50, 47, 35, 32, 29, 18, 21, 24, 25, 26, 23, 20, 19, 22, 21,
	9, 10, 11, 18, 19, 20, 29, 28, 27, 38, 37, 36,  0,  3,  6,  7,  8,  5,  2,  1,  4, 21,
	12, 13, 14, 21, 22, 23, 32, 31, 30, 41, 40, 39,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,
	15, 16, 17, 24, 25, 26, 35, 34, 33, 44, 43, 42, 45, 48, 51, 52, 53, 50, 47, 46, 49, 21,
	2,  1,  0, 38, 41, 44, 45, 46, 47, 26, 23, 20, 27, 30, 33, 34, 35, 32, 29, 28, 21, 21,
	5,  4,  3, 37, 40, 43, 48, 49, 50, 25, 22, 19,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,
	8,  7,  6, 36, 39, 42, 51, 52, 53, 24, 21, 18,  9, 12, 15, 16, 17, 14, 11, 10, 13, 21
};

char wcgCube::mBlockCubes[9][9] =
{
	0, 3, 6, 9, 12, 15, 18, 21, 24, 
	1, 4, 7, 10, 13, 16, 19, 22, 25,
	2, 5, 8, 11, 14, 17, 20, 23, 26,
	0, 1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25, 26,
	0, 1, 2, 9, 10, 11, 18, 19, 20,
	3, 4, 5, 12, 13, 14, 21, 22, 23,
	6, 7, 8, 15, 16, 17, 24, 25, 26
};

wcgCube::wcgCube(void)
{
	init();

	//Rotate(1, 1);
	//Rotate(3, 1);
}


wcgCube::~wcgCube(void)
{
}



void wcgCube::init()
{
	int i, j, idx;

	idx = 0;
	for (i=0; i<6; i++)
	{
		for (j=0; j<9; j++)
		{
			mPieces[idx++] = i;
		}
	}
}

void wcgCube::SetupCube( /*int icube, float x0, float y0, float z0, float dx, float dy, float dz, bool isSelect *//*= false*/ )
{
	static float vertexs[8][3] = 
	{
		0, 1, 0,
		0, 1, 1,  
		1, 1, 1,
		1, 1, 0,

		0, 0, 0,
		0, 0, 1,
		1, 0, 1,
		1, 0, 0,
	};

	static int faces[6][4] =
	{
		0, 1, 2, 3,
		1, 5, 6, 2,
		2, 6, 7, 3,
		0, 3, 7, 4,
		0, 4, 5, 1,
		4, 7, 6, 5
	};

	static int edges[12][2] =
	{
		0, 1, 1, 2, 2, 3, 3, 0,
		4, 5, 5, 6, 6, 7, 7, 4,
		0, 4, 1, 5, 2, 6, 3, 7
	};

	//initial 27 small cube 
	for (int icube = 0; icube < 27; icube++)
	{
		//initial six face of one small cube
		for (int i = 0; i< 6; i++)
		{
			GLfloat tempColor[16];
			GLfloat tempVertex[12];
			int index;
			if (mCubes[icube][i] != -1)
			{
				index = 0;
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						tempColor[index++] = mColors[mPieces[mCubes[icube][i]]][k];
						
					}
				}
			}
			else
			{
				index = 0;
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						tempColor[index++] = mColors[6][k];
					}
				}
			}

			index = 0;
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					tempVertex[index++] = vertexs[faces[i][j]][k];
				}
			}
			faceBatch[icube][i].Begin(GL_QUADS, 4);	
			faceBatch[icube][i].CopyVertexData3f(tempVertex);
			faceBatch[icube][i].CopyColorData4f(tempColor);
			faceBatch[icube][i].End();
		}

		glLineWidth(2);
		//initial 12 line of very small cube
		for (int i = 0; i< 12; i++)
		{
			lineBatch[icube][i].Begin(GL_LINES, 2);
			lineBatch[icube][i].Vertex3fv(vertexs[edges[i][0]]);
			lineBatch[icube][i].Color4fv(mColors[6]);
			lineBatch[icube][i].Vertex3fv(vertexs[edges[i][1]]);
			lineBatch[icube][i].Color4fv(mColors[6]);
			lineBatch[icube][i].End();
		}
	}
	
}


void wcgCube::SetupDraw()
{

}

void wcgCube::Draw(GLint& locMVP, GLMatrixStack& modelViewMatrix, GLGeometryTransform& transformPipeline)
{
	GLfloat x, y, z;
	GLfloat dx, dy, dz;
	int iCube;

	
	dx = dy = dz = 1.0f / 3;

	modelViewMatrix.PushMatrix();
  
	modelViewMatrix.Translate(-0.5, -0.5, -0.5);

	//modelViewMatrix.Scale(0.5, 0.5, 0.5);
	//modelViewMatrix.Translate(0.5, 0.5, 0.5);

	
	iCube = 0;
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k< 3; k++)
			{
				modelViewMatrix.PushMatrix();


				modelViewMatrix.Scale(dx, dy, dz);
				modelViewMatrix.Translate(k, i, j);

				glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());

				for (int m = 0; m < 6; m++)
				{
					faceBatch[iCube][m].Draw();
				}
				for (int m = 0; m< 12; m++)
				{
					lineBatch[iCube][m].Draw();
				}

				modelViewMatrix.PopMatrix();

				iCube++;
			}
		}
	}
	modelViewMatrix.PopMatrix();
}

void wcgCube::Rotate(int iBlock, int direction)
{
	int i;
	char tmp[12];

	//旋转环装部分的12个小片
	for (i=0; i< 12; i++)
	{
		tmp[i] = mPieces[mBlocks[iBlock][i]];
	}

	if (direction > 0)
	{
		for (i=0; i<12; i++)
		{
			mPieces[mBlocks[iBlock][(i+3)%12]] = tmp[i];
		}
	}
	else
	{
		for (i=0; i<12; i++)
		{
			mPieces[mBlocks[iBlock][i]] = tmp[(i+3)%12];
		}
	}

	if(mBlocks[iBlock][21] <= 12 ) return;
	//底面8个小片的旋转
	for (i=0; i<8; i++)
	{
		tmp[i] = mPieces[mBlocks[iBlock][i+12]];
	}
	if (direction > 0)
	{
		for (i=0; i<8; i++)
		{
			mPieces[mBlocks[iBlock][12+(i+2)%8]] = tmp[i];
		}
	}
	else
	{
		for (i=0; i<8; i++)
		{
			mPieces[mBlocks[iBlock][12+i]] = tmp[(i+2)%8];
		}
	}
}

void wcgCube::DrawRotate( int iBlock, GLfloat af, GLint& locMVP, GLMatrixStack& modelViewMatrix, GLGeometryTransform& transformPipeline)
{
	bool flags[27] = { 0 };
	GLfloat x, y, z;
	GLfloat j;
	static GLfloat dx, dy, dz;
	dx = dy = dz = 1.0f / 3;
	
	//draw rotated block(six small cube)
	modelViewMatrix.PushMatrix();
	
	if (iBlock < 3)
	{
		modelViewMatrix.Rotate(af, 1.0f, 0.0f, 0.0f);
	}
	else if (iBlock >= 3 && iBlock < 6)
	{
		modelViewMatrix.Rotate(af, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		modelViewMatrix.Rotate(af, 0.0f, 0.0f, 1.0f);
	}
	modelViewMatrix.Translate(-0.5, -0.5, -0.5);

	for (int i = 0; i < 9; i++)
	{
		int iCube = mBlockCubes[iBlock][i];
		flags[iCube] = true;

		x = 0.0f;
		y = 2 - iCube/9;
		z = (iCube % 9) / 3;

		modelViewMatrix.PushMatrix();

		modelViewMatrix.Scale(dx, dy, dz);
		modelViewMatrix.Translate(x, y, z);

		glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());

		for (int m = 0; m < 6; m++)
		{
			faceBatch[iCube][m].Draw();
		}
		for (int m = 0; m< 12; m++)
		{
			lineBatch[iCube][m].Draw();
		}
		modelViewMatrix.PopMatrix();
	}

	modelViewMatrix.PopMatrix();

	//draw others small cube
	modelViewMatrix.PushMatrix();

	modelViewMatrix.Translate(-0.5, -0.5, -0.5);

	//modelViewMatrix.Scale(0.5, 0.5, 0.5);
	//modelViewMatrix.Translate(0.5, 0.5, 0.5);


	GLint iCube = 0;
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k< 3; k++)
			{

				if (!flags[iCube])
				{
					modelViewMatrix.PushMatrix();


					modelViewMatrix.Scale(dx, dy, dz);
					modelViewMatrix.Translate(k, i, j);

					glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());

					for (int m = 0; m < 6; m++)
					{
						faceBatch[iCube][m].Draw();
					}
					for (int m = 0; m< 12; m++)
					{
						lineBatch[iCube][m].Draw();
					}

					modelViewMatrix.PopMatrix();
				}

				iCube++;
			}
		}
	}
	modelViewMatrix.PopMatrix();

}
