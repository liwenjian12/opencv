<!--TOC-->
- [输入](#输入)
  - [载入图片](#载入图片)
  - [载入视频](#载入视频)
  - [摄像头读入视频](#摄像头读入视频)
  - [载入文件](#载入文件)
- [输出](#输出)
  - [写入图片](#写入图片)
  - [输出图片](#输出图片)
  - [输出文件](#输出文件)
  
- [图像处理](#图像处理)
  - [腐蚀](#腐蚀)
  - [模糊](#模糊)
  - [canny边缘检测](#canny边缘检测)
  
<!--/TOC-->
## 输入
#### 载入图片
Mat srcImage = imread("1.jpg");

#### 载入视频
VideoCapture capture("1.avi");
while(1){
  Mat frame;
  capture >> frame;
  imshow("读取视频", frame);
  waitKey(30);
}

#### 摄像头读入视频
VideoCapture capture(0);
while(1){
  Mat frame;
  capture >> frame;
  imshow("读取视频", frame);
  waitKey(30);
}
### 载入文件

## 输入
### 输出图片
imshow("原始图", srcImage);
waitKey(0);
### 输出文件

## 图像处理
#### 腐蚀
Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
Mat dstImage;
erode(srcImage, dstImage, element);

#### 模糊
Mat dstImage;
blur( srcImage, dstImage, Size(7, 7));

#### canny边缘检测
Mat dstImage, edge, grayImage;
dstImage.create(src.Image.size(), srcImage.type() );
cvtColor( srcImage, grayImage, COLOR_BGR2GRAY);   //【2】将原图像转换为灰度图像
blur(grayImage, edge, Size(3, 3) );               //【3】先用使用 3x3内核来降噪
Canny( edge, edge, 3, 9, 3);                      //【4】运行Canny算子







