#include "GLMTest.h"
#include "XUtils.h"

using namespace XUtils;

void GLMTest::Test()
{
	//TestBase();
	//TestTranslate();
	//TestRotate();
	//TestScale();
	TestCombined();
}

void GLMTest::TestBase()
{
	//============================================================================
	//1�������ȴ洢
	//============================================================================

	/***
	* glm�о����������ȴ洢�ģ��ⲻͬ��openglĬ�ϵ��������ȴ洢�ķ�ʽ���������������matΪ��
	* �������ĸ���������ģ��洢�ĸ��У�vec4 value[4]������
	* value[0] = (1,0,0,0) = (m[0][0],m[0][1],m[0][2],m[0][3]) = (m[0].x, m[0].y, m[0].z, m[0].w)
	* value[1] = (0,1,0,0) = (m[1][0],m[1][1],m[1][2],m[1][3]) = (m[1].x, m[1].y, m[1].z, m[1].w)
	* value[2] = (0,0,1,0) = (m[2][0],m[2][1],m[2][2],m[2][3]) = (m[2].x, m[2].y, m[2].z, m[2].w)
	* value[3] = (1,2,3,4) = (m[3][0],m[3][1],m[3][2],m[3][3]) = (m[3].x, m[3].y, m[3].z, m[3].w)
	* ����洢��opengl��ֱ�ۿ��ǲ�һ���ģ�����ƽ�Ʋ��ִ洢���˵����У������ǵ����У�����һ�����Դ����е�д��һ�£���D3D�е�д��һ��
	*/
	glm::mat4 mat = glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		1, 2, 3, 4
	);

	XPrint(mat);

	//============================================================================
	//2�������������˷�
	//============================================================================

	/***
	* ������������˹�������opengl��˭��ǰ˭���������Ĺ���
	* ������ǰ����󿴳����ĸ��������������ں���Ϊһ��������
	* ������ǰ����������һ���������������ں�����Ϊ�ĸ�������
	*/
	/***
	* ��������������ˣ�һ����÷��Ǿ��������������ҡ�
	* ���������ǰ�mat�����ĸ���������V������������(1*1+2*2+3*3+0*1, 4*1+1*2+5*3+0*1, 6*1+7*2,1*3+0*1, 8*1+9*2+0*3+0*1) = (14,21,23,26)
	*/
	glm::vec4 v(1, 2, 3, 1);
	glm::mat4 m2(
		1, 4, 6, 8,
		2, 1, 7, 9,
		3, 5, 1, 0,
		0, 0, 0, 0
	);
	auto vt = mat * v; //�����(14,21,23,26)
	XPrint(vt);

	XPrint(m2,"m2");
	/***
	*���ܽ᡿
	* 1�� glm�о���Ĵ洢�ǰ��д洢�ģ���DXһ��
	* 2�� glm��������������ĳ˷�=DX���������Ҿ���˷�
	* ������������ԣ���ʹ��glm��ʱֻ��Ҫע�������������д�����ڲ�ԭ��������ɰ�DX����
	* ������������㰴DX����
	* (1,2,3,1) * (1,0,0,0) = (1*1+2*0+3*0+1*1,1*0+2*1+3*0+1*1, 1*0+2*0+3*1+1*1, 1*0+2*0+3*0+1*1) = (2,3,4,1)��������������ȫһ��
				  (0,1,0,0)
				 (0,0,1,0)
				 (1,1,1,1)
	*/
}

//====================================================================
//ƽ��
//====================================================================
void GLMTest::TestTranslate()
{
	glm::mat4 mat(1.0f); //��λ����mat[0][0]=mat[1][1]=mat[2][2]=1������ȫ0
	glm::vec3 v1(1.0f);  //(1,1,1)
	glm::vec3 v2(1, 2, 3);

	XPrint(mat, "mat");
	XPrint(v1, "v1");
	XPrint(v2, "v2");

	/*********************************************************************************
	*	��ע�⡿
	*	����һ����λ����M����v1�ŵ������У�Ȼ��mat = mat*M��������ֱ�ӽ�v1�ŵ�mat�ĵ�����
	*	Դ���е�ʵ�ֱ����Ҫ��Ч����ԭ���������
	*	�������ʵ���������������ĺϳɣ�1��ƽ�ƣ�2������һ������mat
	*	��������ƽ�ƣ���������Ƚϵ�Ч����Ч��������ÿ��ƽ��ֻ�ı��������е�x,y,z
	*	�����TestCombined
	**********************************************************************************/

	mat = glm::translate(mat, v1);
	XPrint(mat, "mat");//mat[3] = (1,1,1,1)

	mat = glm::translate(mat, v2);
	XPrint(mat, "mat");//mat[3] = (1,1,1,1) + (1,2,3,0) = (2,3,4,1)
}

//====================================================================
//��ת
//====================================================================
void GLMTest::TestRotate()
{
	glm::mat4 mat(1.0f);
	glm::vec4 v1(1,0,0,1);

	mat = glm::rotate(mat, glm::radians(60.0f), glm::vec3(0, 0, 1));
	XPrint(mat, "��ת60��");

	//glm��ʹ��GL����������ϵ��X���ң�Y���ϣ�Z����Ļ��
	//��������ϵ����ת����������ס��ת��-��Ĵָָ����ת��������������ָ��ָ�������ת����

	//0.5	0.87		0	0
	//-0,87	0.5		0	0
	//0		0		1	0
	//0		0		0	1

	//��Ӧ����ʽ����
	//cosa	sina		0	0
	//-sina	cosa		0	0
	//0		0		1	0
	//0		0		0	1

	v1 = mat * v1; //0.5, 0.87, 0, 1

	XPrint(v1);

	//������ʽҲ�У��Ⱥ���תa,b�Ƕȵ���һ����ת(a+b)�Ƕ�
	/*	|cosa	sina|  *  |cosb		sinb| =	|cos(a+b)	sin(a+b)|
		|-sina	cosa|	 |-sinb		cosb|    |-sin(a+b)	cos(a+b)|
	*/
	
	//����ת30�ȣ�һ����ת��90��
	mat = glm::rotate(mat, glm::radians(30.0f), glm::vec3(0, 0, 1));
	XPrint(mat, "��ת90��");
}

void GLMTest::TestScale()
{
	glm::mat4 mat(1.0f);
	glm::vec3 v(1, 2, 3);
	glm::vec3 v2(2, 2, 2);

	mat = glm::scale(mat, v);
	XPrint(mat, "scale");

	mat = glm::scale(mat, v2);
	XPrint(mat, "scale2");
}

void GLMTest::TestCombined()
{
	glm::mat4 mat(1.0f);
	glm::vec4 v1(1, 0, 0, 1);

	glm::vec4 pt(1, 0, 0, 1);
	mat = glm::rotate(mat, glm::radians(60.0f), glm::vec3(0, 0, 1));
	XPrint(mat, "��ת60��");

	//=================================================================
	//��ע�⡿��ƽ��(1,2,3)������ת60��
	//=================================================================
	mat = glm::translate(mat, glm::vec3(1, 2, 3));

	pt = mat * pt;
	XPrint(pt, "pt");

	//=================================================================
	//������֤����ƽ��ֻ�ı��������һ�� �������������������ת������ 
	//=================================================================
}