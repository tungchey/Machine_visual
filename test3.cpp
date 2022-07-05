#include<opencv2/opencv.hpp>
#include<iostream>
#include <stdio.h>
#include<math.h>
#include <opencv2\imgproc\types_c.h>
#include <opencv2/imgproc/imgproc_c.h>
using namespace cv;
using namespace std;

/*Mat ImageRotate(Mat image,double angle)
{
    Mat newImg;
    Point2f pt =Point2f((float)image.cols/2,(float)image.rows/2);
    Mat M=getRotationMatrix2D(pt,angle,1.0);
    warpAffine(image,newImg,M,image.size());
    return newImg;
}*/
Mat circle_region_cut(Mat src,int min_r,int max_r)
{
    Mat media_src,rgb_src,ROI;
    src.copyTo(rgb_src);
    cvtColor(src,src,CV_BGR2GRAY);
    medianBlur(src,media_src,5);
    vector<Vec4f>circles;
	Scalar color = Scalar(0, 0, 255);
	HoughCircles(media_src,circles, HOUGH_GRADIENT, 1, 100, 100, 40, min_r, max_r);
    Vec4f c = circles[0];//c[0]c[1]center point,c[2]radius
    int r=c[2]-20;
    /*for (size_t i = 0; i < circles.size(); i++)
	{
		
        //cout<<"number"<<circles[i]<<endl;
		//circle(rgb_src, Point(c[0], c[1]), c[2], color, 2, LINE_AA);
		//circle(rgb_src, Point(c[0], c[1]),1,Scalar(255,0,0), 2, LINE_AA);
        Rect rect(c[0]-r,c[1]-r,2*r,2*r);
        ROI=rgb_src(rect);
        //imshow("ROI",ROI);
        
	}*/
    Rect rect(c[0]-r,c[1]-r+60,2*r,2*r-120);
    ROI=rgb_src(rect);
    //imshow("roi",ROI);
    return ROI;
    //medianBlur(rgb_src,rgb_src, 5);
    //imshow("src",media_src);
    //imshow("circles",rgb_src);
}
Mat circle_region_cut_1(Mat src,int min_r,int max_r)
{
    Mat media_src,rgb_src,ROI;
    src.copyTo(rgb_src);
    cvtColor(src,src,CV_BGR2GRAY);
    medianBlur(src,media_src,5);
    vector<Vec4f>circles;
	Scalar color = Scalar(0, 0, 255);
	HoughCircles(media_src,circles, HOUGH_GRADIENT, 1, 100, 100, 40, min_r, max_r);
    Vec4f c = circles[0];//c[0]c[1]center point,c[2]radius
    int r=c[2]-30;
    /*for (size_t i = 0; i < circles.size(); i++)
	{
		
        //cout<<"number"<<circles[i]<<endl;
		//circle(rgb_src, Point(c[0], c[1]), c[2], color, 2, LINE_AA);
		//circle(rgb_src, Point(c[0], c[1]),1,Scalar(255,0,0), 2, LINE_AA);
        Rect rect(c[0]-r,c[1]-r,2*r,2*r);
        ROI=rgb_src(rect);
        //imshow("ROI",ROI);
        
	}*/
    Rect rect(c[0]-r,c[1]-r+60,2*r,2*r-125);
    ROI=rgb_src(rect);
    //imshow("roi",ROI);
    return ROI;
    //medianBlur(rgb_src,rgb_src, 5);
    //imshow("src",media_src);
    //imshow("circles",rgb_src);
}
Mat circle_region(Mat src,int min_r,int max_r)
{
    Mat media_src,rgb_src,ROI;
    src.copyTo(rgb_src);
    cvtColor(src,src,CV_BGR2GRAY);
    medianBlur(src,media_src,5);
    vector<Vec4f>circles;
	Scalar color = Scalar(0, 0, 255);
	HoughCircles(media_src,circles, HOUGH_GRADIENT, 1, 100, 100, 40, min_r, max_r);
    Vec4f c = circles[0];//c[0]c[1]center point,c[2]radius
    int r=c[2];
    /*for (size_t i = 0; i < circles.size(); i++)
	{
		
        //cout<<"number"<<circles[i]<<endl;
		//circle(rgb_src, Point(c[0], c[1]), c[2], color, 2, LINE_AA);
		//circle(rgb_src, Point(c[0], c[1]),1,Scalar(255,0,0), 2, LINE_AA);
        Rect rect(c[0]-r,c[1]-r,2*r,2*r);
        ROI=rgb_src(rect);
        //imshow("ROI",ROI);
        
	}*/
    Rect rect(c[0]-r,c[1]-r,2*r,2*r);
    ROI=rgb_src(rect);
    //imshow("roi",ROI);
    return ROI;
    //medianBlur(rgb_src,rgb_src, 5);
    //imshow("src",media_src);
    //imshow("circles",rgb_src);
}
void Hough_LineP(Mat src)
{
    Mat dst;
    Mat GaussImg;
    //src=circle_region_cut(src,70,140);
    cvtColor(src,src,CV_BGR2GRAY);
    medianBlur(src, GaussImg, 5);//高斯滤波
    Mat binary;
    //threshold(GaussImg, binary, 128, 255, THRESH_BINARY);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    morphologyEx(GaussImg, binary, MORPH_ERODE, kernel, Point(-1, -1), 1);
    Canny(binary,dst,100,200,3);
    //imshow("canny",dst);
    //waitKey(0);
    vector<Vec4i> lines;
    HoughLinesP(dst,lines,5,CV_PI/180,100,80,30);
    float theta,L1,number;
    Vec4i ll=lines[0];
    number=0;
    L1=abs(ll[3]-ll[1])+abs(ll[2]-ll[0]);//L1距离
    for(size_t i=0;i<lines.size();i++)
    {
        //cout<<i<<endl;
        float temp=0.0;
        Vec4i l=lines[i];
        //line(src,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(0,155,155),1);
        
        temp=abs(l[3]-l[1])+abs(l[2]-l[0]);
        if(temp>L1)
        {
            L1=temp;
            number=i;
        }
        

    }
    Vec4i LL=lines[number];
    line(src,Point(LL[0],LL[1]),Point(LL[2],LL[3]),Scalar(0,155,155),3);
    //imshow("binary",binary);
    //imshow("hough",src);
    //waitKey(0);
    /*Mat binary_;
    vector<Vec4f>circles1;
    threshold(binary, binary_, 200, 255, THRESH_TOZERO);
    imshow("bianry_",binary_);
    //waitKey(0);
	Scalar color = Scalar(0, 0, 255);
	HoughCircles(GaussImg,circles1, HOUGH_GRADIENT, 1,binary_.rows/8, 100, 40, 10, 50);
    Vec4f c = circles1[0];//c[0]c[1]center point,c[2]radius
    for (size_t i = 0; i < circles1.size(); i++)
	{
		circle(src, Point(c[0], c[1]), c[2], color, 2, LINE_AA);
		circle(src, Point(c[0], c[1]),1,Scalar(255,0,0), 2, LINE_AA);
        //imshow("rgbsrc",rgb_src);
	}*/

    if(LL[2]-LL[1]==0)
    {
        theta=0;
    }
    else
    {
        theta=abs(atan2((LL[3]-LL[1]),(LL[2]-LL[1])));
    }
    
    printf("angle=%.4f\n",theta);
    imshow("hough",src);
    //waitKey(0);
}
//direction函数没有使用
void direction(Mat src)
{
    int rows=src.rows;
    int cols=src.cols;
    Mat media_src,rgb_src,ROI;
    Mat binary;
    src.copyTo(rgb_src);
    cvtColor(src,src,CV_BGR2GRAY);
    medianBlur(src,media_src,5);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    morphologyEx(media_src, binary, MORPH_ERODE, kernel, Point(-1, -1), 1);
    vector<Vec4f>circles;
	Scalar color = Scalar(0, 0, 255);
	HoughCircles(binary,circles, HOUGH_GRADIENT, 1, media_src.rows/8, 200, 100, 1, 100);
    Vec4f c = circles[0];//c[0]c[1]center point,c[2]radius
    for (size_t i = 0; i < circles.size(); i++)
	{
		circle(rgb_src, Point(c[0], c[1]), c[2], color, 2, LINE_AA);
		circle(rgb_src, Point(c[0], c[1]),1,Scalar(255,0,0), 2, LINE_AA);
        imshow("rgbsrc",rgb_src);
	}
    if(c[0]<0.5*rows)
    {
        printf("left");
    }
    else
    {
        printf("right");
    }
}

class mat
{
public:
    void match(Mat& src, Mat& dst, int method);
};

Mat ImageRotate(Mat image,double angle)
{
    Mat newImg;
    Point2f pt =Point2f((float)image.cols/2,(float)image.rows/2);
    Mat M=getRotationMatrix2D(pt,angle,1.0);
    warpAffine(image,newImg,M,image.size());
    return newImg;
}
Mat match_temp(Mat src)//传入一张图
{
    Mat dst = imread("pro_picture/model2.jpg");
    Mat dst1 = imread("pro_picture/model3.png");
    Mat dst2 = imread("pro_picture/model4.png");
    Mat dst3 = imread("pro_picture/model5.png");//创建四个模板

    Mat ROI=circle_region_cut(src,70,130);//裁剪出钥匙
    Mat aaaa=circle_region(src,70,130);//裁剪出钥匙外面的一圈圆，把整张图的ROI限定

    /*threshold(ROI, ROI, 138, 255, THRESH_BINARY);
    threshold(dst, dst, 115, 255, THRESH_BINARY);
    threshold(dst1, dst1, 115, 255, THRESH_BINARY);
    threshold(dst2, dst2, 115, 255, THRESH_BINARY);
    threshold(dst3, dst3, 115, 255, THRESH_BINARY);
    //形态学开运算去除小亮点，方便后续模板匹配
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    morphologyEx(dst, dst, MORPH_OPEN, kernel, Point(-1, -1), 1);
    morphologyEx(ROI, ROI, MORPH_OPEN, kernel, Point(-1, -1), 1);*/
    
    int result_rows = ROI.rows - ROI.rows + 1;
    int result_cols = ROI.cols - ROI.cols + 1;
    Mat result,result1,result2,result3,result4;

    double minval, maxval,minval_1,maxval_1,minval_2,maxval_2,minval_3,maxval_3;
    Point minloc, maxloc, loc,minloc_1,maxloc_1,minloc_2,maxloc_2,minloc_3,maxloc_3;

    matchTemplate(ROI, dst, result, 3);
    //matchTemplate(ROI, dst1, result1, 3);
    matchTemplate(ROI, dst2, result2, 3);
    matchTemplate(ROI, dst3, result3, 3);
    minMaxLoc(result, &minval, &maxval, &minloc, &maxloc, Mat());
    //minMaxLoc(result1, &minval_1, &maxval_1, &minloc_1, &maxloc_1, Mat());
    minMaxLoc(result2, &minval_2, &maxval_2, &minloc_2, &maxloc_2, Mat());
    minMaxLoc(result3, &minval_3, &maxval_3, &minloc_3, &maxloc_3, Mat());

    double temp[3]={maxval,maxval_2,maxval_3};
    printf("%.3f,%.3f,%.3f",temp[0],temp[1],temp[2]);
    //waitKey(0);
    double x=*max_element(temp,temp+4);
    if(x==maxval){loc=maxloc;return dst;}
    //if(x==maxval_1){loc=maxloc_1;return dst1;}
    if(x==maxval_2){loc=maxloc_2;return dst2;}
    if(x==maxval_3){loc=maxloc_3;return dst3;}
}
int main()
{
    //Mat dst = imread("pro_picture/model2.jpg");
    Mat src = imread("pro_picture/88.jpg");//读入图像
    //Mat rotate_tmp=ImageRotate(dst,180);//翻转模板
    //imshow("rotate",rotate_tmp);
    //resize(dst,dst,Size(180,50),0,0,INTER_LINEAR);//放大1.2倍
    resize(src,src,Size(1536,1024),0,0,INTER_LINEAR);
    Mat ROI=circle_region_cut(src,70,130);//裁剪出钥匙
    Mat ROI1=circle_region_cut_1(src,70,130);
    imshow("ROI",ROI);
    imshow("ROI1",ROI1);
    //waitKey(0);
    Mat dst=match_temp(src);
    imshow("select",dst);
    waitKey(0);
    Mat rotate_tmp=ImageRotate(dst,180);//翻转模板
    

    Mat aaaa=circle_region(src,70,130);//裁剪出钥匙外面的一圈圆，把整张图的ROI限定
    Hough_LineP(ROI1);//检测直线段，高斯滤波不行，用中值滤波，为更好检测，在roi区域检测直线段
    
    //imshow("aaaa",aaaa);
    //waitKey(0);
    //direction(aaaa);
    //二值化图像
    threshold(ROI, ROI, 138, 255, THRESH_BINARY);
    threshold(dst, dst, 115, 255, THRESH_BINARY);
    //形态学开运算去除小亮点，方便后续模板匹配
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    morphologyEx(dst, dst, MORPH_OPEN, kernel, Point(-1, -1), 1);
    morphologyEx(ROI, ROI, MORPH_OPEN, kernel, Point(-1, -1), 1);
    //imshow("Thresholding", ROI);
    //waitKey(0);
    //Mat key=circle_region(ROI,)
    //imshow("ROI",ROI);
    /*src.copyTo(rgb_src);
    
    cvtColor(src,src,CV_BGR2GRAY);
    medianBlur(src,media_src,5);
    vector<Vec4f>circles;
	Scalar color = Scalar(0, 0, 255);
	HoughCircles(media_src,circles, HOUGH_GRADIENT, 1, 100, 100, 40, 70, 140);
    
    for (size_t i = 0; i < circles.size(); i++)
	{
		Vec4f c = circles[i];
		circle(rgb_src, Point(c[0], c[1]), c[2], color, 2, LINE_AA);
		circle(rgb_src, Point(c[0], c[1]),1,Scalar(255,0,0), 2, LINE_AA);
	}
    medianBlur(rgb_src,rgb_src, 5);
    imshow("src",media_src);
    imshow("circles",rgb_src);*/

    // Mat ro_dst=ImageRotate(dst,30);

    int result_rows = ROI.rows - ROI.rows + 1;
    int result_cols = ROI.cols - ROI.cols + 1;
    Mat result,result_inv;
   
    double minval, maxval,minval_inv,maxval_inv;
    Point minloc, maxloc, loc,minloc_inv,maxloc_inv,loc_inv;

    result.create(Size(result_cols, result_rows), CV_32FC3);
    matchTemplate(ROI, dst, result, 3);
    matchTemplate(ROI, rotate_tmp, result_inv, 3);
    minMaxLoc(result, &minval, &maxval, &minloc, &maxloc, Mat());
    minMaxLoc(result_inv, &minval_inv, &maxval_inv, &minloc_inv, &maxloc_inv, Mat());
    //normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
    //printf("maxval=%f",maxval);
    waitKey(0);
    loc=maxloc;
    loc_inv=maxloc_inv;
    if(maxval<maxval_inv)
    {
        loc=maxloc_inv;
        printf("direction=right\n");
        imshow("template",rotate_tmp);
    }
    else
    {
        loc=maxloc;
        printf("direction=left\n");
        imshow("template",dst);
    }
    Rect rect;
    // rect.x = loc.x-10;
    // rect.y = loc.y;
    // rect.width = dst.cols+15;//数字为经验之谈
    // rect.height = dst.rows+8;

    rect.x=loc.x-10+20;
    rect.y=loc.y+80;
    rect.width=dst.cols+15;
    rect.height=dst.rows+8;
    rectangle(aaaa, rect, Scalar(0, 0, 255), 2, 8, 0);
    //imshow("temp", dst);
    imshow("ROI", aaaa);
    //imshow("result", result);


    // imshow("origin",dst);
    // imshow("rotate",ro_dst);
    waitKey(0);
}