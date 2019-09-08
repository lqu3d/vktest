#include "XGame.h"
#include "XObjectMgr.h"
#include "XUtils.h"

#include "DrawCube.h"
#include "XCamera.h"
#include <glm/ext.hpp>
#include "XTransform.h"

void XGame::Start()
{
	XGameObject* go = objMgr.AddObject<XGameObject>();
	XCamera* cam = go->AddComponent<XCamera>();
	//cam->gameObject.
	auto trans = cam->gameObject->transform;
	auto pos = trans->GetPosition();
	trans->SetPos(glm::vec3(0, 1, 0));

	/***
	* glm�о����������ȴ洢�ģ��ⲻͬ��openglĬ�ϵ��������ȴ洢�ķ�ʽ���������������matΪ��
	* �������ĸ���������ģ��洢�ĸ��У�vec4 value[4]������
	* value[0] = (1,0,0,0) = (m[0][0],m[0][1],m[0][2],m[0][3])
	* value[1] = (0,1,0,0) = (m[1][0],m[1][1],m[1][2],m[1][3])
	* value[2] = (0,0,1,0) = (m[2][0],m[2][1],m[2][2],m[2][3])
	* value[3] = (1,1,1,1) = (m[3][0],m[3][1],m[3][2],m[3][3])
	* ����洢��opengl��ֱ�ۿ��ǲ�һ���ģ�����ƽ�Ʋ��ִ洢���˵����У������ǵ����У�����һ�����Դ����е�д��һ�£���D3D�е�д��һ��
	*/
	glm::mat4 mat = mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		1, 1, 1, 1
	);


	glm::vec4 v(1, 2, 3, 1);
	
	/*** 
	* ������������˹�������opengl��˭��ǰ˭���������Ĺ���
	* ������ǰ����󿴳����ĸ��������������ں���Ϊһ��������
	* ������ǰ����������һ���������������ں�����Ϊ�ĸ�������
	*/
	/***
	* ��������������ˣ�һ����÷��Ǿ��������������ҡ�
	* ���������ǰ�mat�����ĸ���������V������������(1*1+0*2+0*3+1*1, 0*1+1*2+0*3+1*1, 0*1+0*2+1*3+1*1, 0*1+0*2+0*3+1*1) = (2,3,4,1)
	*/
	auto vt = mat * v; //�����(2,3,4,1)

	mat4 m2(
		1, 4, 6, 8,
		2, 1, 7, 9,
		3, 5, 1, 0,
		0, 0, 0, 0
	);

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

	//translate�����ǽ�1��2��3 ��ӵ�����ĵ����У����Ϊvalue[3] = 1,2,3,1
	//auto m3 = glm::translate(vec3(1, 2, 3));
}

void XGame::Update()
{
}

void XGame::OnDestroy()
{
}

void XGame::SetupCamera()
{
	//float fov = glm::radians(45.0f);
	//float wdh = xvk.xWnd.width * 1.0f / xvk.xWnd.height;
	//float hdw = xvk.xWnd.height * 1.0f / xvk.xWnd.width;
	//fov *= wdh;

}