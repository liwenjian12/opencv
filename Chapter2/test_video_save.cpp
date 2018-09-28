#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


int main(int argc,char* argv[]){
	cv::VideoCapture capture(argv[1]);
	if(!capture.isOpened()){
		std::cout<<"video not open."<<std::endl;
		return 1;
	}
	//获取当前视频帧率
	double rate = capture.get(CV_CAP_PROP_FPS);
	//当前视频帧
	cv::Mat frame;
	//每一帧之间的延时
	//与视频的帧率相对应
	int delay = 1000/rate;
	bool stop(false);

	//创建VideoWriter做保存视频
	cv::VideoWriter writer; 
	bool writer_init(false);

	while(!stop){
		if(!capture.read(frame)){
			std::cout<<"no video frame"<<std::endl;
			break;
		}
		if(!writer_init){
			writer.open("VideoOutput.avi",CV_FOURCC('M','J','P','G'),rate,cv::Size(frame.cols,frame.rows));
			writer_init = true;
		}

		/*
		 *
		 * 此处为添加对视频的每一帧的操作方法
		 *
		 */
		
		//写入保存视频
		writer<<frame;

		cv::imshow("video",frame);
		//引入延时
		//也可通过按键停止
		if(cv::waitKey(delay)>0)
			stop = true;
	}
	//关闭视频，手动调用析构函数（非必须）
	capture.release();
	return 0;
}
