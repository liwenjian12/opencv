/*
 *
 * 功能：非目标区域进行模糊处理，实现对焦效果
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
	cv::threshold(gray,binary,85,255,cv::THRESH_BINARY_INV);
	
	//--4.寻找轮廓
	std::vector<std::vector<cv::Point> > contours;
	cv::Mat binary_copy; //因为findcontours函数会改变输入的图像，所以复制一个图像作为函数的输入
	binary.copyTo(binary_copy);
	cv::findContours(binary_copy,contours,CV_RETR_EXTERNAL/*获取外轮廓*/,CV_CHAIN_APPROX_NONE/*获取每个轮廓的每个像素*/);

	//遍历每一个轮廓，把多余的轮廓去掉
	std::vector<std::vector<cv::Point> >::const_iterator it=contours.begin();
	while(it!=contours.end()){
		if(it->size()<500||cv::boundingRect(*it).width>0.5*image.cols)
			it = contours.erase(it);
		else
			++it;
	}

	//通过绘制轮廓，制作掩码
	cv::Mat mask(image.size(),CV_8U,cv::Scalar(0));
	cv::drawContours(mask,contours,-1/*绘制所有轮廓*/,cv::Scalar(255)/*绘制为白色*/,CV_FILLED/*轮廓全部填充*/);

	cv::Mat dst;

	//对图像进行模糊处理
	cv::blur(image,dst,cv::Size(9,9));
	
	//对目标部分做锐化处理
	cv::Mat horse;
	image.copyTo(horse);
	cv::Mat kernel = (cv::Mat_<float>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
	cv::filter2D(horse,horse,image.depth(),kernel);

	//合成画面，把锐化后的目标部分复制到dst对应的位置
	horse.copyTo(dst,mask);
	
	//--4.显示结果(原图和结果图显示在一起)
	const int width  = image.cols;
	const int height = image.rows;
	cv::Mat show_image(cv::Size(2*width,height),CV_8UC3);
	//将image拷贝到显示图片指定位置
	image.copyTo(show_image(cv::Rect(0,0,width,height)));
	//dst拷贝image指定位置
	dst.copyTo(show_image(cv::Rect(width,0,width,height)));
	//显示
	cv::imshow("show",show_image);
	cv::waitKey(0);
}
