#ifndef _H_WCGCUBE_H_
#define _H_WCGCUBE_H_

#include <GLBatch.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include<GL/glut.h>


class wcgCube
{
public:
	static char mCubes[27][6];   // 27��С��������ħ��Pieces�Ķ�Ӧ��ϵ
	static char mBlocks[9][22];  //������ħ��Pieces�Ķ�Ӧ��ϵ
	static float mColors[7][4];  //��ɫ��
	static char mBlockCubes[9][9]; //�����Ӧ��С�������±�
	char mPieces[54];           //��¼ħ��6������ÿ��СƬ����ɫ

	GLBatch   faceBatch[27][6];
	GLBatch   lineBatch[27][12];



	//����С������
	void SetupCube(/*int icube, float x0, float y0, float z0, 
		float dx, float dy, float dz, bool isSelect = false*/);
public:
	wcgCube(void);
	~wcgCube(void);

	void init();

	//����ħ������
	void SetupDraw();

	//����ħ������
	void Draw(GLint& locMVP, GLMatrixStack& modelViewMatrix, GLGeometryTransform& transformPipeline);

	void Rotate(int iBlock, int direction);

	void DrawRotate(int iBlock, GLfloat af, GLint& locMVP, GLMatrixStack& modelViewMatrix, GLGeometryTransform& transformPipeline);
};

#endif


