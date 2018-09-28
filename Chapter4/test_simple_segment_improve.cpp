/*
 *
 * 功能：通过灰度图做简单的图像分割,再使用findContours去掉多余的轮廓
 *
 */

#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc,char* argv[]){

	//--1.读入图片
	cv::Mat image = cv::imread("horse_hw.jpg");

	//--2.转换灰度图
	cv::Mat gray;
	cv::cvtColor(image,gray,CV_RGB2GRAY);
	
	//--3.二值化灰度图
	cv::Mat binary;
	cv::threshold(gray,binary,60,255,cv::THRESH_BINARY_INV);
	//平滑处理(平滑/高斯平滑两种)
	//cv::blur(dst,dst,cv::Size(3,3));
	//cv::GaussianBlur(dst,dst,cv::Size(3,3),0,0); //高斯平滑
	
	//形态学操作（此处效果不好，只用来展示加强理解）
	//cv::erode(dst,dst,cv::Mat(),cv::Point(-1,-1),1);
	//cv::dilate(dst,dst,cv::Mat(),cv::Point(-1,-1),1);
	

	//--4.寻找轮廓
	std::vector<std::vector<cv::Point> > contours;
	cv::Mat binary_copy; //因为findcontours函数会改变输入的图像，所以复制一个图像作为函数的输入
	binary.copyTo(binary_copy);
	cv::findContours(binary_copy,contours,CV_RETR_EXTERNAL/*获取外轮廓*/,CV_CHAIN_APPROX_NONE/*获取每个轮廓的每个像素*/);

	//遍历每一个轮廓，把多余的轮廓去掉
	std::vector<std::vector<cv::Point> >::const_iterator it=contours.begin();
	while(it!=contours.end()){
		if(it->size()<500)
			it = contours.erase(it);
		else
			++it;
	}

	//重新绘制轮廓
	cv::Mat dst(image.size(),CV_8U,cv::Scalar(0));
	cv::drawContours(dst,contours,-1/*绘制所有轮廓*/,cv::Scalar(255)/*绘制为白色*/,CV_FILLED/*轮廓全部填充*/);

	
	//--4.显示结果(原图和结果图显示在一起)
	const int width  = image.cols;
	const int height = image.rows;
	cv::Mat show_image(cv::Size(3*width,height),CV_8UC3);
	//将image拷贝到显示图片指定位置
	image.copyTo(show_image(cv::Rect(0,0,width,height)));
	//将binary,dst转换为3通道，使得show_image和dst通道数一致，或者使用convertTo()函数做操作
	cv::cvtColor(binary,binary,CV_GRAY2RGB);
	cv::cvtColor(dst,dst,CV_GRAY2RGB);
	//将binary,dst拷贝image指定位置
	binary.copyTo(show_image(cv::Rect(width,0,width,height)));
	dst.copyTo(show_image(cv::Rect(2*width,0,width,height)));
	//显示
	cv::imshow("show",show_image);
	cv::waitKey(0);
}
