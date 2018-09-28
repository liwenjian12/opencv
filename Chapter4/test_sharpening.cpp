/*
 *
 * 功能：使用算子对图片进行锐化
 *
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc,char* argv[]){

	//读入图片
	cv::Mat image = cv::imread(argv[1]);

	//基于拉普拉斯算子的图像锐化
	//拉普拉斯滤波核3*3 
	//  0  -1   0 
	// -1   5  -1 
	//  0  -1   0  
	cv::Mat kernel = (cv::Mat_<float>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
	cv::Mat sharpen_laplace;
	cv::filter2D(image,sharpen_laplace,image.depth(),kernel);

	cv::imshow("show",sharpen_laplace);
	cv::waitKey(0);
}
