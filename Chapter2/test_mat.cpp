#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

void info(){
	std::cout<<"Please input parameter..."<<std::endl;
	std::cout<<"1-Function:Create zeros mat with 1 channel"<<std::endl;
	std::cout<<"2-Function:Create zeros mat with 3 channels"<<std::endl;
	std::cout<<"3-Function:Input image and output matrix values"<<std::endl;
	std::cout<<"4-Function:Copy a mat"<<std::endl;
	std::cout<<"5-Function:Deep copy a mat data"<<std::endl;
	std::cout<<"6-Function:Iterate  pixels in a mat"<<std::endl;
	std::cout<<"7-Function:Set ROI and editing"<<std::endl;

}

int main(int argc,char* argv[]){
	//没有输入参数
	if(argc==1){
		info();
		return 1;
	}
	
	switch(atoi(argv[1])){
		case 1:
			{
				std::cout<<"Function 1 : Create zeros mat with 1 channel"<<std::endl;
				//创建一个8*8,位数为8的单通道Mat
				cv::Mat mat(8,8,CV_8UC1);
				//将Mat置0，使得矩阵内所有像素值为0
		      		mat.zeros(mat.size(),mat.type());
				//输出矩阵结果
		       		std::cout<<mat<<std::endl;
				break;
			}
		       
		case 2:
			{
				std::cout<<"Function 2 : Create zeros mat with 3 channels"<<std::endl;
				//创建一个8*8,位数为8的三通道Mat
				cv::Mat mat2(8,8,CV_8UC3);
				//同样将Mat置0，使得矩阵内所有像素值为0
				mat2.zeros(mat2.size(),mat2.type());
				//输出效果，和单通道的矩阵相比，数据量是单通道的三倍
		       		std::cout<<mat2<<std::endl;
				break;
			}

		case 3:
			{
				std::cout<<"Function 3 : Input image and output matrix values"<<std::endl;
				//输入一张图，尺寸为图片原来的尺寸
				cv::Mat mat3 = cv::imread("lena.jpg");
				//修改这个图片Mat的使用尺寸
				cv::resize(mat3,mat3,cv::Size(8,8));
				//输出所有像素值
				std::cout<<mat3<<std::endl;
				break;
			}

		case 4:
			{
				std::cout<<"Function 4 : Copy a mat"<<std::endl;
				//输入一张图
				cv::Mat mat4 = cv::imread("lena.jpg");
				//浅拷贝一个Mat，浅拷贝只数据地址是公用的，所以修改其中一个Mat，两个Mat的值都会被修改
				cv::Mat mat4_1 = mat4;
				//垂直翻转图片
				cv::flip(mat4_1,mat4_1,1);
				//显示效果,两个Mat都被翻转了
				cv::imshow("mat4",mat4);
				cv::imshow("mat4_1",mat4_1);
				cv::waitKey(0);
				break;
			}

		case 5:
			{
				std::cout<<"Function 5 : Deep copy a mat data"<<std::endl;
				//输入一张图片
				cv::Mat mat5 = cv::imread("lena.jpg");
				//深拷贝一个Mat，数据完全复制，没有共用的部分，所以修改任意一个Mat，互不影响
				cv::Mat mat5_1;
				mat5.copyTo(mat5_1);
				//上下翻转矩阵
				cv::flip(mat5_1,mat5_1,0);
				//显示效果，只有一个是被翻转了，另个一不受影响
				cv::imshow("mat5",mat5);
				cv::imshow("mat5_1",mat5_1);
				cv::waitKey(0);
				break;
			}

		case 6:
			{
				std::cout<<"Function 6 : Iterate  pixels in a mat"<<std::endl;
				//输入一张图片
                                cv::Mat mat6 = cv::imread("lena.jpg");
				//重新定义尺寸
				cv::resize(mat6,mat6,cv::Size(8,8));
				//遍历每一个像素的值，可以看到和Function3，输出的结果一致
				for(int j=0;j<mat6.rows;j++){
					for(int i=0;i<mat6.cols;i++){
						std::cout<<(int)mat6.at<cv::Vec3b>(j,i)[0]<<", "<<(int)mat6.at<cv::Vec3b>(j,i)[1]<<", "<<(int)mat6.at<cv::Vec3b>(j,i)[2]<<", ";
					}
					std::cout<<std::endl;
				}
				break;
			}

		case 7:
			{
				std::cout<<"Function 7 : Set ROI and editing"<<std::endl;
				//输入一张图片
				cv::Mat mat7 = cv::imread("lena.jpg");
				//设置ROI位置
				cv::Rect roi(mat7.cols/4,mat7.rows/4,mat7.cols/2,mat7.rows/2);
				cv::Mat mat7_roi = mat7(roi);
				//垂直翻转，这时候，对ROI的任意操作都是在修改原图的基础上操作的
				cv::flip(mat7_roi,mat7_roi,1);
				//显示原图，ROI的部分被修改了
				cv::imshow("mat7",mat7);
				cv::waitKey(0);
				break;
			}
		       
		default:
			{
				info();
				break;
			}
		       
	}
	return 0;

}
