/*
 *
 * 功能：获取并呈现图像的灰度直方图
 *
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc,char* argv[]){

	//读入图片
	cv::Mat image = cv::imread(argv[1]);

	//转化为灰度图
	cv::cvtColor(image,image,CV_RGB2GRAY);

	//获取直方图
	int histsize[] = {256}; //项的数量
	float range[] = {0, 256}; //像素值的范围
	const float *ranges[] = {range}; 
	int channels[] = {0}; //通道

	cv::Mat hist; //直方图结果
	calcHist(&image, 1, channels, cv::Mat() /*不使用图像作为掩码*/, hist, 1, histsize, ranges);

	//以图形方式显示直方图
	//获取最大值和最小值
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist,&minVal,&maxVal,0,0);
	//显示直方图的图像
	cv::Mat hist_img(histsize[0],histsize[0],CV_8U,cv::Scalar(255));
	//设置最高点为图高的90%
	int high_pt = static_cast<int>(0.9*histsize[0]);
	//每个条目绘制一条垂直线
	for(int h = 0; h<histsize[0]; h++){
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal*high_pt/maxVal);
		//两点之间绘制一条线
		cv::line(hist_img,cv::Point(h,histsize[0]),cv::Point(h,histsize[0]-intensity),cv::Scalar::all(0));
	}

	cv::imshow("hist",hist_img);
	cv::waitKey(0);
	return 0;
}
