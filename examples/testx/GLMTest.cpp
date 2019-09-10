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
	//1，行优先存储
	//============================================================================

	/***
	* glm中矩阵是行优先存储的，这不同于opengl默认的以列优先存储的方式？？，以下面矩阵mat为例
	* 它是用四个行向量来模拟存储四个行：vec4 value[4]，其中
	* value[0] = (1,0,0,0) = (m[0][0],m[0][1],m[0][2],m[0][3]) = (m[0].x, m[0].y, m[0].z, m[0].w)
	* value[1] = (0,1,0,0) = (m[1][0],m[1][1],m[1][2],m[1][3]) = (m[1].x, m[1].y, m[1].z, m[1].w)
	* value[2] = (0,0,1,0) = (m[2][0],m[2][1],m[2][2],m[2][3]) = (m[2].x, m[2].y, m[2].z, m[2].w)
	* value[3] = (1,2,3,4) = (m[3][0],m[3][1],m[3][2],m[3][3]) = (m[3].x, m[3].y, m[3].z, m[3].w)
	* 这个存储与opengl从直观看是不一样的，它的平移部分存储到了第四行，而不是第四列，这与一般线性代数中的写法一致，与D3D中的写法一致
	*/
	glm::mat4 mat = glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		1, 2, 3, 4
	);

	XPrint(mat);

	//============================================================================
	//2，矩阵与向量乘法
	//============================================================================

	/***
	* 矩阵与向量向乘规则，遵守opengl的谁在前谁是列向量的规则
	* 矩阵在前则矩阵看成是四个列向量，向量在后则为一个行向量
	* 向量在前则向量看成一个列向量，矩阵在后则视为四个行向量
	*/
	/***
	* 【矩阵与向量相乘，一般的用法是矩阵在左向量在右】
	* 如下运算是把mat看作四个列向量，V看作行向量：(1*1+2*2+3*3+0*1, 4*1+1*2+5*3+0*1, 6*1+7*2,1*3+0*1, 8*1+9*2+0*3+0*1) = (14,21,23,26)
	*/
	glm::vec4 v(1, 2, 3, 1);
	glm::mat4 m2(
		1, 4, 6, 8,
		2, 1, 7, 9,
		3, 5, 1, 0,
		0, 0, 0, 0
	);
	auto vt = mat * v; //结果是(14,21,23,26)
	XPrint(vt);

	XPrint(m2,"m2");
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
}

//====================================================================
//平移
//====================================================================
void GLMTest::TestTranslate()
{
	glm::mat4 mat(1.0f); //单位矩阵mat[0][0]=mat[1][1]=mat[2][2]=1，其余全0
	glm::vec3 v1(1.0f);  //(1,1,1)
	glm::vec3 v2(1, 2, 3);

	XPrint(mat, "mat");
	XPrint(v1, "v1");
	XPrint(v2, "v2");

	/*********************************************************************************
	*	【注意】1，平移，2，乘以mat
	*	对于连续平移，这个操作比较低效，高效的作法是每次平移只改变矩阵第四行的x,y,z
	**********************************************************************************/

	mat = glm::translate(mat, v1);
	XPrint(mat, "mat");//mat[3] = (1,1,1,1)

	mat = glm::translate(mat, v2);
	XPrint(mat, "mat");//mat[3] = (1,1,1,1) + (1,2,3,0) = (2,3,4,1)
}

//====================================================================
//旋转
//====================================================================
void GLMTest::TestRotate()
{
	glm::mat4 mat(1.0f);
	glm::vec4 v1(1,0,0,1);

	//【注意】1，旋转，2，乘以mat
	mat = glm::rotate(mat, glm::radians(60.0f), glm::vec3(0, 0, 1));
	XPrint(mat, "旋转60度");

	//glm中使用GL的右手坐标系，X向右，Y向上，Z向屏幕外
	//右手坐标系下旋转规则：右手握住旋转轴-大拇指指向旋转轴正方向，其余四指的指向便是旋转正向

	//0.5	0.87		0	0
	//-0,87	0.5		0	0
	//0		0		1	0
	//0		0		0	1

	//对应矩阵公式如下
	//cosa	sina		0	0
	//-sina	cosa		0	0
	//0		0		1	0
	//0		0		0	1

	v1 = mat * v1; //0.5, 0.87, 0, 1

	XPrint(v1);

	//矩阵形式也有：先后旋转a,b角度等于一次旋转(a+b)角度
	/*	|cosa	sina|  *  |cosb		sinb| =	|cos(a+b)	sin(a+b)|
		|-sina	cosa|	 |-sinb		cosb|    |-sin(a+b)	cos(a+b)|
	*/
	
	//先旋转30度，再旋转60度(即乘以mat)，一共旋转了90度
	mat = glm::rotate(mat, glm::radians(30.0f), glm::vec3(0, 0, 1));
	XPrint(mat, "旋转90度");
}

void GLMTest::TestScale()
{
	glm::mat4 mat(1.0f);
	glm::vec3 v(1, 2, 3);
	glm::vec3 v2(2, 2, 2);

	//【注意】1，缩放，2，乘以mat
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
	XPrint(mat, "旋转60度");

	//=================================================================
	//【注意】先平移(1,2,3)，再旋转60度
	//=================================================================
	mat = glm::translate(mat, glm::vec3(1, 2, 3));

	pt = mat * pt;
	XPrint(pt, "pt");

	//=================================================================
	//【可以证明】平移只改变矩阵的最后一行 ，不管这个矩阵有无旋转，缩放 
	//=================================================================
}
