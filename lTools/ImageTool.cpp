#include "ImageTool.h"

#ifdef USE_OCV
#include <opencv2/opencv.hpp>

using namespace cv;

using namespace std;

cv::Mat drawMatchImage(cv::Mat src1, cv::Point p1, cv::Mat src2, cv::Point p2){


	std::vector<cv::KeyPoint> kps1 = std::vector<cv::KeyPoint>{cv::KeyPoint(p1, 1)};
	std::vector<cv::KeyPoint> kps2 = std::vector<cv::KeyPoint>{cv::KeyPoint(p2, 1)};

	std::vector<cv::DMatch> matches = std::vector<cv::DMatch>{cv::DMatch(0, 0, 0)};

	cv::Mat matchImage;
	drawMatches(src1, kps1, src2, kps2, matches, matchImage);

	return matchImage;
}


int GetTextProject(cv::Mat src,std::vector<float> &feature, int mode){

    cv::Mat horizonMat;
    cv::Mat floatSrc;
    src.convertTo(floatSrc,CV_32F);

    if (mode == V_PROJECT)
    {
        cv::reduce(floatSrc,horizonMat,0,1);
        feature.clear();
        feature.resize(horizonMat.cols);
        memcpy(&feature[0],horizonMat.data,sizeof(float)*horizonMat.cols);
    }
    else if (mode == H_PROJECT)
    {
        cv::reduce(floatSrc,horizonMat,1,1);
        feature.clear();
        feature.resize(horizonMat.rows);
        memcpy(&feature[0],horizonMat.data,sizeof(float)*horizonMat.rows);
    }
    return 1;
}


int GetTextProject(Mat src, Mat mask, vector<float> &pos, int mode)
{ //vector pos就是用于存储垂直投影和水平投影的位置

    if (mask.cols <= 0)
    {
        mask = cv::Mat::ones(src.size(), CV_8UC1) * 255;
    }

    if (mode == V_PROJECT)
    {
        pos.clear();
        pos.resize(src.cols);
        memset(&pos[0], 0, sizeof(float) * pos.size());

        for (int i = 0; i < src.rows; i++)
        {
            uchar *oneSrc = src.data + src.step * i;
            uchar *oneMask = mask.data + mask.step * i;

            for (int j = 0; j < src.cols; j++)
            {
                if (oneMask[j] > 0)
                {
                    pos[j] += oneSrc[j];
                }
            }
        }

        //normalize
        for (size_t i = 0; i < pos.size(); i++)
        {
            pos[i] = pos[i] / src.rows;
        }
    }
    else if (mode == H_PROJECT)
    {
        pos.clear();
        pos.resize(src.rows);
        memset(&pos[0], 0, sizeof(float) * pos.size());

        // for (size_t i = 0; i < pos.size(); i++)
        // {
        // 	pos[i]=10;
        // }

        for (int i = 0; i < src.rows; i++)
        {
            uchar *oneSrc = src.data + src.step * i;
            uchar *oneMask = mask.data + mask.step * i;
            for (int j = 0; j < src.cols; j++)
            {

                // LOGD("%d oneMask[j]:%d oneSrc[j]:%d \n",j,oneMask[j],oneSrc[j]);
                if (oneMask[j] > 0)
                {
                    pos[i] += oneSrc[j];
                }
            }
        }
        //normalize
        for (size_t i = 0; i < pos.size(); i++)
        {
            pos[i] = pos[i] / src.cols;
        }
    }

    return 1;
}

std::vector<float> createOneHanningVec(int size)
{

    std::vector<float> hannVec;

    for (size_t i = 0; i < size; i++)
    {
        float x = 0.5 * (1 - cos(2 * 3.14159265358979323846 * i / (size - 1)));

        x=sqrtf(x);
        hannVec.push_back(x);
    }

    return hannVec;
}

cv::Mat createHanningMats(int size)
{

    cv::Mat hann = cv::Mat::zeros(cv::Size(size, size), CV_32FC1);

    float sumHann = 0;
    float *one_hann = (float *)(hann.data);
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {

            float y = 0.5 * (1 - cos(2 * 3.14159265358979323846 * i / (size - 1)));
            float x = 0.5 * (1 - cos(2 * 3.14159265358979323846 * j / (size - 1)));

            one_hann[i * size + j] = x * y;
            sumHann += x * y;
        }
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            one_hann[i * size + j] /= sumHann;
        }
    }
}


int drawRotateRect(cv::Mat image,cv::RotatedRect rotateRect,cv::Scalar color){

    cv::Point2f pts[4];
    rotateRect.points(pts);
    
    Point pWarp[1][4] = {{pts[0],pts[1],pts[2],pts[3]}};
    const Point *ppWarp[] = {pWarp[0]};
    int nWarp[] = {4};
    fillPoly(image, ppWarp, nWarp, 1, color);

    return 1;
}


int drawRotateRectLine(cv::Mat image,cv::RotatedRect rotateRect,cv::Scalar color,int lineType){

    cv::Point2f pts[4];
    rotateRect.points(pts);
    
    Point pWarp[1][5] = {{pts[0],pts[1],pts[2],pts[3],pts[0]}};
    const Point *ppWarp[] = {pWarp[0]};
    int nWarp[] = {5};
    polylines(image,ppWarp, nWarp,1,0,color,lineType);

    return 1;
}


/****************************************/
/*   实现自动对比度的函数                  */
/*   目前只有前后中通道调用                */
/*   彩色的已经加入到了函数内部             */
/*****************************************/
void BrightnessAndContrastAuto(const cv::Mat &src, cv::Mat &dst, float clipHistPercent)
{
    CV_Assert(clipHistPercent >= 0);
    CV_Assert((src.type() == CV_8UC1) || (src.type() == CV_8UC3) || (src.type() == CV_8UC4));

    int histSize = 256;
    float alpha, beta;
    double minGray = 0, maxGray = 0;

    //to calculate grayscale histogram
    cv::Mat gray;
    if (src.type() == CV_8UC1) gray = src;
    else if (src.type() == CV_8UC3) cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    else if (src.type() == CV_8UC4) cvtColor(src, gray, cv::COLOR_BGRA2GRAY);
    if (clipHistPercent == 0)
    {
        // keep full available range
        cv::minMaxLoc(gray, &minGray, &maxGray);
    }
    else
    {
        cv::Mat hist; //the grayscale histogram

        float range[] = { 0, 256 };
        const float* histRange = { range };
        bool uniform = true;
        bool accumulate = false;
        cv::calcHist(&gray, 1, 0, cv::Mat (), hist, 1, &histSize, &histRange, uniform, accumulate);

        // calculate cumulative distribution from the histogram
        std::vector<float> accumulator(histSize);
        accumulator[0] = hist.at<float>(0);
        for (int i = 1; i < histSize; i++)
        {
            accumulator[i] = accumulator[i - 1] + hist.at<float>(i);
        }

        // locate points that cuts at required value
        float max = accumulator.back();
        clipHistPercent *= (max / 100.0); //make percent as absolute
        clipHistPercent /= 2.0; // left and right wings
        // locate left cut
        minGray = 0;
        while (accumulator[minGray] < clipHistPercent)
            minGray++;

        // locate right cut
        maxGray = histSize - 1;
        while (accumulator[maxGray] >= (max - clipHistPercent))
            maxGray--;
    }

    // current range
    float inputRange = maxGray - minGray;

    alpha = (histSize - 1) / inputRange;   // alpha expands current range to histsize range
    beta = -minGray * alpha;             // beta shifts current range so that minGray will go to 0

    // Apply brightness and contrast normalization
    // convertTo operates with saurate_cast
    src.convertTo(dst, -1, alpha, beta);

    // restore alpha channel from source
    if (dst.type() == CV_8UC4)
    {
        int from_to[] = { 3, 3};
        cv::mixChannels(&src, 4, &dst,1, from_to, 1);
    }
    return;
}


void BrightnessAndContrastAuto(const cv::Mat &src, cv::Mat &dst,float clipHistPercent, cv::Vec2d& lastGray)
{
    CV_Assert(clipHistPercent >= 0);
    CV_Assert((src.type() == CV_8UC1) || (src.type() == CV_8UC3) || (src.type() == CV_8UC4));

    int histSize = 256;
    float alpha, beta;
    double minGray = 0, maxGray = 0;

    //to calculate grayscale histogram
    cv::Mat gray;
    if (src.type() == CV_8UC1) gray = src;
    else if (src.type() == CV_8UC3) cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    else if (src.type() == CV_8UC4) cvtColor(src, gray, cv::COLOR_BGRA2GRAY);
    if (clipHistPercent == 0)
    {
        // keep full available range
        cv::minMaxLoc(gray, &minGray, &maxGray);
    }
    else
    {
        cv::Mat hist; //the grayscale histogram

        float range[] = { 0, 256 };
        const float* histRange = { range };
        bool uniform = true;
        bool accumulate = false;
        cv::calcHist(&gray, 1, 0, cv::Mat (), hist, 1, &histSize, &histRange, uniform, accumulate);

        // calculate cumulative distribution from the histogram
        std::vector<float> accumulator(histSize);
        accumulator[0] = hist.at<float>(0);
        for (int i = 1; i < histSize; i++)
        {
            accumulator[i] = accumulator[i - 1] + hist.at<float>(i);
        }

        // locate points that cuts at required value
        float max = accumulator.back();
        clipHistPercent *= (max / 100.0); //make percent as absolute
        clipHistPercent /= 2.0; // left and right wings
        // locate left cut
        minGray = 0;
        while (accumulator[minGray] < clipHistPercent)
            minGray++;

        // locate right cut
        maxGray = histSize - 1;
        while (accumulator[maxGray] >= (max - clipHistPercent))
            maxGray--;
    }

    //smooth lastGray
    if(lastGray[0]!=0||lastGray[1]!=0){
        minGray=minGray*0.5+lastGray[0]*0.5;
        maxGray=maxGray*0.5+lastGray[1]*0.5;
    }
    lastGray[0]=minGray;
    lastGray[1]=maxGray;

    // current range
    float inputRange = maxGray - minGray;

    alpha = (histSize - 1) / inputRange;   // alpha expands current range to histsize range
    beta = -minGray * alpha;             // beta shifts current range so that minGray will go to 0

    // Apply brightness and contrast normalization
    // convertTo operates with saurate_cast
    src.convertTo(dst, -1, alpha, beta);

    // restore alpha channel from source
    if (dst.type() == CV_8UC4)
    {
        int from_to[] = { 3, 3};
        cv::mixChannels(&src, 4, &dst,1, from_to, 1);
    }
    return;
}


int sobelcv(cv::Mat& inoutMat){

	cv::Mat XBorder, YBorder, XYBorder;
	Sobel(inoutMat, XBorder, CV_16S, 1, 0, 3, 1.0, 0);
	Sobel(inoutMat, YBorder, CV_16S, 0, 1, 3, 1.0, 0);
	convertScaleAbs(XBorder, XBorder);
	convertScaleAbs(YBorder, YBorder);
	//XY方向上的因
	addWeighted(XBorder, 0.5, YBorder, 0.5, 0, inoutMat);
}


#endif