/*
 *
 * 功能：使用不同的算子(Sobel,Canny,Laplace)实现边缘检测
 *
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc,char* argv[]){

	//读入图片
	cv::Mat src = cv::imread(argv[1]);

	//Sobel算子
	//Sobel 算子是一个离散微分算子 (discrete differentiation operator)。 它用来计算图像灰度函数的近似梯度。
	cv::Mat dst_sobel;
	//输入图像
	//输出图像
	//输入图像颜色通道数
	//x方向阶数
	//y方向阶数
	cv::Sobel(src,dst_sobel,src.depth(),1,1);

	//Laplace算子
	cv::Mat dst_laplace;
	//输入图像
	//输出图像
	//输入图像颜色通道数
	cv::Laplacian(src,dst_laplace,src.depth());

	//Canny算子
	cv::Mat dst_canny;
	//Canny只处理灰度图
	cv::cvtColor(src,dst_canny,CV_RGB2GRAY);
	//输入图像
	//输出图像
	//低阈值
	//高阈值，opencv建议是低阈值的3倍
	//内部sobel滤波器大小
	cv::Canny(dst_canny,dst_canny,50,150,3);

	//显示图片
	cv::imshow("Sobel",dst_sobel);
	cv::imshow("Laplace",dst_laplace);
	cv::imshow("Canny",dst_canny);

	cv::waitKey(0);

	return 0;
}
