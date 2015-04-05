#include "wcgCube.h"

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLMatrixStack.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>
#include <GLFrame.h>

#include <GL/glut.h>            // Windows FreeGlut equivalent


GLTriangleBatch sphereBatch;
GLBatch	triangleBatch;
GLBatch cubeBatch;
GLShaderManager shaderManager;
GLMatrixStack  projectionMatrix;
GLMatrixStack  modelViewMatrix;
GLGeometryTransform transformPipeline;
GLFrustum      viewFrustum;
GLFrame        cameraFrame;
wcgCube        mWcgCube;

GLint myShader;

GLint locMVP;
M3DMatrix44f   mRotation;


GLfloat vRed[] = {1, 0, 0, 1};
GLfloat vGreen[] = {0, 1, 0, 1};

GLfloat   mMouseX;
GLfloat   mMouseY;
bool      isStartTrackBall = false;

void SetupRC()
{
	glClearColor(0, 0, 0, 1);

	shaderManager.InitializeStockShaders();
	
	glEnable(GL_DEPTH_TEST);

	gltMakeSphere(sphereBatch, 0.4, 20, 20);
	gltMakeCube(cubeBatch, 0.3);

	// Load up a triangle
	GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f, 
		0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f };

	GLfloat vColors [] = { 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f };

	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.CopyColorData4f(vColors);
	triangleBatch.End();
	
	mWcgCube.SetupCube();

	/*transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);*/
	cameraFrame.MoveForward(-3.0f);

	m3dLoadIdentity44(mRotation);
	
	myShader = gltLoadShaderPairWithAttributes("shader.vp", "shader.fp", 2, GLT_ATTRIBUTE_VERTEX, "vVertex", 
												GLT_ATTRIBUTE_COLOR, "vColor");
	locMVP = glGetUniformLocation(myShader, "mvpMatrix");
}

void MouseEvent(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mMouseX = x;
			mMouseY = y;
			isStartTrackBall = true;
		}
		else if (state == GLUT_UP)
		{
			isStartTrackBall = false;
		}
	}
}

void MousePtToSphereVec(M3DVector3f result, int x, int y, int w, int h)
{
	GLfloat afterX = (2.0 * x - w) / w;
	m3dSetVectorX(result, afterX);
	GLfloat afterY = (h - 2.0 * y) / h;
	m3dSetVectorY(result, afterY);
	GLfloat temp = afterX * afterX + afterY * afterY;
	if (temp > 1)
	{
		temp = 1;
	}
	GLfloat afterZ = sqrt(1 - temp);
	m3dSetVectorZ(result, afterZ);

}

void MouseMoveEvent(int x, int y)
{

	if (isStartTrackBall)
	{
		GLfloat theta;
		M3DVector3f p1, p2, n;
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

		MousePtToSphereVec(p1, mMouseX, mMouseY, width, height);
		MousePtToSphereVec(p2, x, y, width, height);

		mMouseX = x;
		mMouseY = y;

		m3dNormalizeVector3(p1);
		m3dNormalizeVector3(p2);
		theta = acos(m3dDotProduct3(p1, p2)) ;

		//theta = m3dGetAngleBetweenVectors3(p1, p2);

		m3dCrossProduct3(n, p1, p2);
		m3dNormalizeVector3(n);

		M3DMatrix44f tempRotation;
		m3dLoadIdentity44(tempRotation);
		GLfloat dis = m3dGetDistance3(p1, p2);
		if (dis != 0.0f)
		{
			m3dRotationMatrix44(tempRotation, theta, m3dGetVectorX(n), m3dGetVectorY(n), m3dGetVectorZ(n));
		}
		m3dMatrixMultiply44(mRotation, tempRotation, mRotation);

		glutPostRedisplay();

		
	}
	
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);

	viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 500.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	//modelViewMatrix.LoadIdentity();
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	modelViewMatrix.PushMatrix();

	M3DMatrix44f mCamera;
	cameraFrame.GetCameraMatrix(mCamera);
	modelViewMatrix.MultMatrix(mCamera);
	modelViewMatrix.MultMatrix(mRotation);

	glUseProgram(myShader);
	//mWcgCube.Draw(locMVP, modelViewMatrix, transformPipeline);

	mWcgCube.DrawRotate(0, 30, locMVP, modelViewMatrix, transformPipeline);
	//glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());

	
	
	
	//cubeBatch.Draw();
	//sphereBatch.Draw();
	//triangleBatch.Draw();

	modelViewMatrix.PopMatrix();

	glutSwapBuffers();

	glutPostRedisplay();
	
}

void ShutDownRC()
{
	glDeleteShader(myShader);
}


int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("WcgCube");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMoveEvent);


	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRC();

	glutMainLoop();

	ShutDownRC();

	return 0;
}