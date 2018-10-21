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
#### XML和YAML文件的读取
//初始化
FileStorage fs2("test.yaml", FileStorage::READ);  
// 第一种方法，对FileNode操作
int frameCount = (int)fs2["frameCount"];
 
// 第二种方法，使用FileNode运算符> > 
std::string date; 
fs2["calibrationDate"] >> date;  
Mat cameraMatrix2, distCoeffs2;  
fs2["cameraMatrix"] >> cameraMatrix2;  
fs2["distCoeffs"] >> distCoeffs2; 
## 输入
### 输出图片
#### imshow
imshow("原始图", srcImage);
waitKey(0);

#### XML和YAML文件的写入
//初始化
FileStorage fs("test.yaml", FileStorage::WRITE); 
Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);  
Mat distCoeffs = (Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);  
fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs; 
#### 添加滑动条
createTrackbar()
```
//-----------------------------------【全局变量声明部分】--------------------------------------
//		描述：全局变量声明
//-----------------------------------------------------------------------------------------------
const int g_nMaxAlphaValue = 100;//Alpha值的最大值
int g_nAlphaValueSlider;//滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;
//声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;
//-----------------------------------【on_Trackbar( )函数】--------------------------------
//		描述：响应滑动条的回调函数
//------------------------------------------------------------------------------------------
void on_Trackbar( int, void* )
{
	//求出当前alpha值相对于最大值的比例
	g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue ;
	//则beta值为1减去alpha值
	g_dBetaValue = ( 1.0 - g_dAlphaValue );
	//根据alpha和beta值进行线性混合
	addWeighted( g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	//显示效果图
	imshow( WINDOW_NAME, g_dstImage );
}
int main( int argc, char** argv)
{
  //加载图像 (两图像的尺寸需相同)
	g_srcImage1 = imread("1.jpg");
  g_srcImage2 = imread("2.jpg");
  //设置滑动条初值为70
	g_nAlphaValueSlider = 70;
	//创建窗体
  namedWindow(WINDOW_NAME, 1);
  //在创建的窗体中创建一个滑动条控件
	char TrackbarName[50];
	sprintf( TrackbarName, "透明值 %d", g_nMaxAlphaValue );
	createTrackbar( TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar );
	//结果在回调函数中显示
	on_Trackbar( g_nAlphaValueSlider, 0 );
	//按任意键退出
	waitKey(0);
return 0;
}
````

#### 鼠标操作
void on_MouseHandle(int event, int x, int y, int flags, vold* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);
main()
{...
  setMouseCallback(WINDOW_NAME,on_MouseHandle,(void*)&srcImage);
  ...
  }
void on_MouseHandle((int event, int x, int y, int flags, void* param)
{
  Mat& image = * (cv::Mat*) param;
  switch(event){
   case EVENT_MOUSEMOVE:
   case EVENT_LBUTTONDOWN: 
	 case EVENT_LBUTTONUP: 
  }
}


#### imwrite
** 阿尔法通道(Alpha Channel)是指一张图片的透明和半透明度 **
```
// createAlpahMat():创建带alpha通道的Mat
void createAlphaMat(Mat &mat){
  for(int i=0;i < mat.rows; ++i){
  for(int j=0;j<mat.cols;++j){
    Vec4b&rgba = mat.at<Vec4b>(i,j);
    rgba[0] = UCHAR_MAX;
    rgba[1] = saturate_cast<uchar>((float(mat.cols - j))/((float)mat.cols) * UCHAR_MAX);
    rgba[2] = saturate_cast<uchar>((float(mat.cols - i))/((float)mat.rows) * UCHAR_MAX);
    rgba[3] = saturate_cast<uchar>( 0.5 * (rgba[1] + rgba[2]));
  }
  }
}
int main()
{
  Mat mat(480, 640, CV_8UC4);
  createAlphaMat(mat);
  vector<int>compression_params;
  compression_params.push_back(IMWRITE_PNG_COMPRESSION);
  compression_params.push_back(9);
  try{
      imwrite("透明Alpha值图", mat, compression_params);
      imshow("", mat);
      waitKey(0）；
      }
}
```
### 输出文件

## 图像处理
#### 腐蚀
Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
Mat dstImage;
erode(srcImage, dstImage, element);

#### 模糊
Mat dstImage;
blur( srcImage, dstImage, Size(7, 7));

#### 图像混合 
cv::addWeighted(): 图像线性混合
图像自定义区域混合：
Mat srcImage4= imread("dota_pa.jpg",1);
Mat logoImage= imread("dota_logo.jpg");
Mat imageROI;//【2】定义一个Mat类型并给其设定ROI区域
imageROI = srcImage4(Rect(200,250,logoImage.cols, logoImage.rows));
addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI):

#### 分离颜色通道&多通道图像混合
split(srcImage,channels);
imageBlueChannel = channels.at(0);
imageGreenChannel= channels.at(1);
imageRedChannel= channels.at(2);
merge(channels, stcImage);    //【5】将三个单通道重新合并成一个三通道

#### 图像对比度、亮度值调整
static void ContrastAndBright(int, void * ){
  for( int y = 0; y < g_srcImage.rows; y++ ){
		for( int x = 0; x < g_srcImage.cols; x++ ){
			for( int c = 0; c < 3; c++ ){
				g_dstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( (g_nContrastValue*0.01)*( g_srcImage.at<Vec3b>(y,x)[c] ) + g_nBrightValue );
			}}}}
 main(){
  //创建轨迹条
	createTrackbar("对比度：", "【效果图窗口】",&g_nContrastValue, 300,ContrastAndBright );
	createTrackbar("亮  度：", "【效果图窗口】",&g_nBrightValue, 200,ContrastAndBright );
	//调用回调函数
	ContrastAndBright(g_nContrastValue,0);
  ContrastAndBright(g_nBrightValue,0);
  }
#### canny边缘检测
Mat dstImage, edge, grayImage;
dstImage.create(src.Image.size(), srcImage.type() );
cvtColor( srcImage, grayImage, COLOR_BGR2GRAY);   //【2】将原图像转换为灰度图像
blur(grayImage, edge, Size(3, 3) );               //【3】先用使用 3x3内核来降噪
Canny( edge, edge, 3, 9, 3);                      //【4】运行Canny算子

#### 离散傅里叶变换
//【1】以灰度模式读取原始图像并显示
Mat srcImage = imread("1.jpg", 0);
//【2】将输入图像延扩到最佳的尺寸，边界用0补充
int m = getOptimalDFTSize( srcImage.rows );
int n = getOptimalDFTSize( srcImage.cols ); 
//将添加的像素初始化为0.
Mat padded;  
copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
//【3】为傅立叶变换的结果(实部和虚部)分配存储空间。
	//将planes数组组合合并成一个多通道的数组complexI
	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexI;
	merge(planes, 2, complexI);   
  
 //【4】进行就地离散傅里叶变换
dft(complexI, complexI);

//【5】将复数转换为幅值，即=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes); // 将多通道数组complexI分离成几个单通道数组，planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude  
	Mat magnitudeImage = planes[0];
//【6】进行对数尺度(logarithmic scale)缩放
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);//求自然对数
//【7】剪切和重分布幅度图象限
//若有奇数行或奇数列，进行频谱裁剪      
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
//重新排列傅立叶图像中的象限，使得原点位于图像中心  
	int cx = magnitudeImage.cols/2;
	int cy = magnitudeImage.rows/2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI区域的左上
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI区域的右上
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI区域的左下
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI区域的右下
//交换象限（左上与右下进行交换）
	Mat tmp;                           
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
//交换象限（右上与左下进行交换）
	q1.copyTo(tmp);                 
	q2.copyTo(q1);
	tmp.copyTo(q2);
//【8】归一化，用0到1之间的浮点值将矩阵变换为可视的图像格式
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX); 
	//【9】显示效果图
imshow("频谱幅值", magnitudeImage); 

### 滤波函数
#### 方框滤波
Mat out;
boxFilter(image,out,-1,Size(5,5));
imshow(out)
#### 均值滤波blur函数
Mat dstImage; 
blur( srcImage, dstImage, Size(7, 7)); 
imshow( "均值滤波【效果图】" ,dstImage ); 
#### 高斯滤波
GaussianBlur( image, out, Size( 5, 5 ), 0, 0 ); 
#### 中值滤波medianBlur
medianBlur ( image, out, 7);
#### 双边滤波bilateralFilter
bilateralFilter ( image, out, 25, 25*2, 25/2 ); 

### 膨胀、腐蚀
//进行膨胀操作 
Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
Mat out;
dilate(image, out, element);
//进行腐蚀操作 
Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
Mat dstImage;
erode(srcImage, dstImage, element);

### 形态学
膨胀
//定义核
Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
//进行形态学操作
morphologyEx(image, image, MORPH_DILATE, element);
图像腐蚀
//定义核
Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
//进行形态学操作
morphologyEx(image, image, MORPH_ERODE, element);

开运算：
morphologyEx(image, image, MORPH_OPEN, element);
闭运算：
morphologyEx(image, image, MORPH_CLOSE, element);

形态学梯度运算：
//定义核
Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  	
morphologyEx(image, image, MORPH_GRADIENT, element);

顶帽运算：
morphologyEx(image, image, MORPH_TOPHAT, element);
黑帽运算：
morphologyEx(image, image, MORPH_BLACKHAT, element);

### 漫水填充floodFill
Rect ccomp;
floodFill(src, Point(50,300), Scalar(155, 255,55), &ccomp, Scalar(20, 20, 20),Scalar(20, 20, 20));
imshow("【效果图】",src);

#### resize函数
//进行尺寸调整操作
resize(tmpImage,dstImage1,Size( tmpImage.cols/2, tmpImage.rows/2 ),(0,0),(0,0),3);
resize(tmpImage,dstImage2,Size( tmpImage.cols*2, tmpImage.rows*2 ),(0,0),(0,0),3);

### 图像金字塔
#### pyrUp函数
//进行向上取样操作
pyrUp( tmpImage, dstImage, Size( tmpImage.cols*2, tmpImage.rows*2 ) );

#### pyrUp函数
//进行向下取样操作

### 阈值函数
//调用阈值函数
threshold(g_grayImage,g_dstImage,g_nThresholdValue,255,g_nThresholdType);
pyrDown( tmpImage, dstImage, Size( tmpImage.cols*2, tmpImage.rows*2 ) );
