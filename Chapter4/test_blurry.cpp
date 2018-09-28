/*
 *
 * 功能：使用常用的几种低通滤波器（包括均值(方框)滤波、高斯滤波、中值滤波、和双边滤波），实现边缘平滑
 *
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc,char* argv[]){

	//读入图片
	cv::Mat image = cv::imread(argv[1]);

	/******************** 均值滤波 *********************/
	//这种滤波方法就是取一个像素的邻域内各像素的平均值作为滤波结果
	cv::Mat filter_box;
	//函数形式：blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT )
	//邻域大小为 5 * 5
	//cv::Point(-1, -1) 表明邻域的零位就是邻域的中心，这个是默认值，如果不改变的话可以不填。 
	//cv::BORDER_DEFAULT 是对边界的处理办法，这个一般也不需要改变的。
	cv::blur(image,filter_box,cv::Size(5,5),cv::Point(-1,-1),cv::BORDER_DEFAULT);

	/******************** 高斯滤波 *********************/
	//高斯滤波采取邻域内越靠近的值提供越大的权重的方式计算平均值。权重的选取采用高斯函数的形式。高斯函数有个非常好的特点，就是无论在时域还是频域都是钟形的。通过控制 σ 可以控制低通滤波的截止频率。
	cv::Mat filter_gaussian;
	//函数形式:GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT )
	//Size(3,3)定义了核的大小
	//最后一个参数是高斯滤波的 σ 。从函数原型上可以看到有 sigmaX 和 sigmaY 两个参数。通常情况下 sigmaY 取与 sigmaX 相同的值，这时可以不写出来。也就是用它的默认值 0.
	cv::GaussianBlur(image,filter_gaussian,cv::Size(3,3),1.5);

	/******************** 中值滤波 *********************/
	//中值滤波是一种非线性滤波器。它是取邻域内各点的统计中值作为输出。这种滤波器可以有效的去除椒盐噪声。还能保持图像中各物体的边界不被模糊掉。是一种最常用的非线性滤波器。这种滤波器只能使用正方形的邻域。
	cv::Mat filter_median;
	//函数形式:medianBlur(InputArray src, OutputArray dst, int ksize)
	//ksize一般取奇数，例如3，5，7，滤波尺寸
	cv::medianBlur(image,filter_median,7);

	/******************** 双边滤波 *********************/
	//双边滤波的思想是抑制与中心像素值差别太大的像素，输出像素值依赖于邻域像素值的加权合
	cv::Mat filter_bila;
	//函数形式：bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace,int borderType=BORDER_DEFAULT )；
	//d 表示滤波时像素邻域直径，d为负时由 sigaColor计算得到；d>5时不能实时处理。
	//sigmaColor、sigmaSpace非别表示颜色空间和坐标空间的滤波系数sigma。可以简单的赋值为相同的值。<10时几乎没有效果；>150时为油画的效果。
	//borderType可以不指定。
	cv::bilateralFilter(image,filter_bila,1,10,10);

	//显示结果
	cv::putText(filter_box,"blur",cv::Point(10,10),cv::FONT_HERSHEY_SIMPLEX,1.0,cv::Scalar(255));
	cv::putText(filter_gaussian,"GaussianBlur",cv::Point(10,10),cv::FONT_HERSHEY_SIMPLEX,1.0,cv::Scalar(255));
	cv::putText(filter_median,"medianBlur",cv::Point(10,10),cv::FONT_HERSHEY_SIMPLEX,1.0,cv::Scalar(255));
	cv::putText(filter_bila,"bilateralFilter",cv::Point(10,10),cv::FONT_HERSHEY_SIMPLEX,1.0,cv::Scalar(255));

	const int width = image.cols;
	const int height= image.rows;
	cv::Mat show_image(cv::Size(5*width,height),CV_8UC3);
	image.copyTo(show_image(cv::Rect(0,0,width,height)));
	filter_box.copyTo(show_image(cv::Rect(width,0,width,height)));
	filter_gaussian.copyTo(show_image(cv::Rect(2*width,0,width,height)));
	filter_median.copyTo(show_image(cv::Rect(3*width,0,width,height)));
	filter_bila.copyTo(show_image(cv::Rect(4*width,0,width,height)));

	cv::imshow("show",show_image);
	cv::waitKey(0);


}
