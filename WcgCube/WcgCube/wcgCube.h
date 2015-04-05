#ifndef _H_WCGCUBE_H_
#define _H_WCGCUBE_H_

#include <GLBatch.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include<GL/glut.h>


class wcgCube
{
public:
	static char mCubes[27][6];   // 27个小立方块与魔方Pieces的对应关系
	static char mBlocks[9][22];  //条带与魔方Pieces的对应关系
	static float mColors[7][4];  //颜色表
	static char mBlockCubes[9][9]; //块体对应的小立方体下标
	char mPieces[54];           //记录魔方6个面上每个小片的颜色

	GLBatch   faceBatch[27][6];
	GLBatch   lineBatch[27][12];



	//建立小立方体
	void SetupCube(/*int icube, float x0, float y0, float z0, 
		float dx, float dy, float dz, bool isSelect = false*/);
public:
	wcgCube(void);
	~wcgCube(void);

	void init();

	//建立魔方函数
	void SetupDraw();

	//建立魔方函数
	void Draw(GLint& locMVP, GLMatrixStack& modelViewMatrix, GLGeometryTransform& transformPipeline);

	void Rotate(int iBlock, int direction);

	void DrawRotate(int iBlock, GLfloat af, GLint& locMVP, GLMatrixStack& modelViewMatrix, GLGeometryTransform& transformPipeline);
};

#endif


