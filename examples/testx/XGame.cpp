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
	* glm中矩阵是行优先存储的，这不同于opengl默认的以列优先存储的方式？？，以下面矩阵mat为例
	* 它是用四个行向量来模拟存储四个行：vec4 value[4]，其中
	* value[0] = (1,0,0,0) = (m[0][0],m[0][1],m[0][2],m[0][3])
	* value[1] = (0,1,0,0) = (m[1][0],m[1][1],m[1][2],m[1][3])
	* value[2] = (0,0,1,0) = (m[2][0],m[2][1],m[2][2],m[2][3])
	* value[3] = (1,1,1,1) = (m[3][0],m[3][1],m[3][2],m[3][3])
	* 这个存储与opengl从直观看是不一样的，它的平移部分存储到了第四行，而不是第四列，这与一般线性代数中的写法一致，与D3D中的写法一致
	*/
	glm::mat4 mat = mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		1, 1, 1, 1
	);


	glm::vec4 v(1, 2, 3, 1);
	
	/*** 
	* 矩阵与向量向乘规则，遵守opengl的谁在前谁是列向量的规则
	* 矩阵在前则矩阵看成是四个列向量，向量在后则为一个行向量
	* 向量在前则向量看成一个列向量，矩阵在后则视为四个行向量
	*/
	/***
	* 【矩阵与向量相乘，一般的用法是矩阵在左向量在右】
	* 如下运算是把mat看作四个列向量，V看作行向量：(1*1+0*2+0*3+1*1, 0*1+1*2+0*3+1*1, 0*1+0*2+1*3+1*1, 0*1+0*2+0*3+1*1) = (2,3,4,1)
	*/
	auto vt = mat * v; //结果是(2,3,4,1)

	mat4 m2(
		1, 4, 6, 8,
		2, 1, 7, 9,
		3, 5, 1, 0,
		0, 0, 0, 0
	);

	/***
	*【总结】
	* 1， glm中矩阵的存储是按行存储的，与DX一致
	* 2， glm中左矩阵右向量的乘法=DX的左向量右矩阵乘法
	* 由以上两点可以，在使用glm库时只需要注意矩阵与向量的写法，内部原理与运算可按DX来看
	* 比如上面的运算按DX来算
	* (1,2,3,1) * (1,0,0,0) = (1*1+2*0+3*0+1*1,1*0+2*1+3*0+1*1, 1*0+2*0+3*1+1*1, 1*0+2*0+3*0+1*1) = (2,3,4,1)，与上面运算完全一样
	              (0,1,0,0)
				 (0,0,1,0)
				 (1,1,1,1)
	*/

	//translate运算是将1，2，3 添加到矩阵的第四行，结果为value[3] = 1,2,3,1
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