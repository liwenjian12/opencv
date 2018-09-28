/*
 *
 * 功能：通过灰度图做简单的图像分割
 *
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc,char* argv[]){

	//--1.读入图片
	cv::Mat image = cv::imread("horses.jpg");

	//--2.转换灰度图
	cv::Mat gray;
	cv::cvtColor(image,gray,CV_RGB2GRAY);
	
	//--3.二值化灰度图
	cv::Mat dst;
	cv::threshold(gray,dst,60,255,cv::THRESH_BINARY_INV);
	//平滑处理(平滑/高斯平滑两种)
	//cv::blur(dst,dst,cv::Size(3,3));
	//cv::GaussianBlur(dst,dst,cv::Size(3,3),0,0); //高斯平滑
	
	//形态学操作（此处效果不好，只用来展示加强理解）
	//cv::erode(dst,dst,cv::Mat(),cv::Point(-1,-1),1);
	//cv::dilate(dst,dst,cv::Mat(),cv::Point(-1,-1),1);
	
	//--4.显示结果(原图和结果图显示在一起)
	const int width  = image.cols;
	const int height = image.rows;
	cv::Mat show_image(cv::Size(2*width,height),CV_8UC3);
	//将image拷贝到显示图片指定位置
	image.copyTo(show_image(cv::Rect(0,0,width,height)));
	//将dst转换为3通道，使得show_image和dst通道数一致，或者使用convertTo()函数做操作
	cv::cvtColor(dst,dst,CV_GRAY2RGB);
	//将dst拷贝image指定位置
	dst.copyTo(show_image(cv::Rect(width,0,width,height)));
	//显示
	cv::imshow("show",show_image);
	cv::waitKey(0);
}
