/*
 *
 * 功能：实现不规则图像的ROI分析区域
 *
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define random(x) (rand()%x)

typedef std::vector<cv::Point> Contour; //定义有若干个点组成的封闭轮廓

int main(int argc,char* argv[]){

	//读入一张图片作为背景图片
	cv::Mat bg_image = cv::imread(argv[1]);

	//创建一个和背景图片一样大小的掩码
	cv::Mat mask(bg_image.rows,bg_image.cols,CV_8UC1);
	//矩阵置0
	mask = mask.zeros(mask.size(),mask.type());

	//创建不规则图形，用点集来表示
	std::vector<Contour> contours;

	//创建不规则图形的每个点(顺时针)
	Contour sub_contours;
	//每次生成不一样的随机数
	srand(unsigned(time(0)));
	//获取每一个随机点
	for(int i=0;i<6;i++){
		cv::Point pt(random(bg_image.cols),random(bg_image.rows));
		sub_contours.push_back(pt);
	}
	contours.push_back(sub_contours);

	//生成掩码(下节课和findContours函数一起讲解)
	//参数2的类型:std::vector<std::vector<cv::Point> >
	cv::drawContours(mask,contours,-1, cv::Scalar(255), CV_FILLED,8);

	//创建合成后的矩阵
	cv::Mat dst;

	bg_image.copyTo(dst,mask);	

	cv::imshow("dst",dst);

	cv::waitKey(0);

}
