#include "MathTool.h"


int majorityElement(std::vector<int> nums, int numsSize, int & numCount)
{
    int num = 0;
    int count = 1;
    int i = 0;
    num = nums[0];

    for (i = 1; i < numsSize; i++)
    {
        if (num == nums[i])
        {
            count++;
        }
        else
        {
            count--;
            if (count == 0)
            {
                num = nums[i + 1];
            }
        }
    }

    count = 0;
    for (i = 0; i < numsSize; i++)
    {
        if (num == nums[i])
        {
            count++;
        }
    }

    numCount = count;

    return num;
}



float findMean(std::vector<float> lists){

    if(lists.size()==0){
        return 0;
    }

    float avgValue=0;
    for (int j = 0; j < lists.size(); ++j) {
        avgValue+= lists[j];
    }
    avgValue /=lists.size();

    return avgValue;
}

int findMean(std::vector<int> lists){
    if(lists.size()==0){
        return 0;
    }

    float avgValue=0;
    for (int j = 0; j < lists.size(); ++j) {
        avgValue+= lists[j];
    }
    avgValue /=lists.size();

    return avgValue;
}


bool FloatEqual(float f1,float f2)
{
    if(abs_c(f1-f2)<0.001)
        return true;
    else
        return false;
}

bool FloatNotEqual(float f1,float f2)
{
    if(abs_c(f1-f2)<0.001)
        return false;
    else
        return true;
}

float sigmoid(float x, float a, float b) {

    float y = 1 / (1 + exp(-(a * x - b)));
    return y;
}


#ifdef USE_OCV
void roiScale(cv::Rect inputRoi,cv::Rect & outRoi,int inW,int inH,int outW,int outH){

    float rw=((float)outW)/inW;
    float rh=((float)outH)/inH;
    outRoi.x=inputRoi.x*rw;
    outRoi.width=inputRoi.width*rw;
    outRoi.y=inputRoi.y*rh;
    outRoi.height=inputRoi.height*rh;
}


float getTrackArea(cv::Rect currectSelect){

    float sumTargetSize = currectSelect.width + currectSelect.height;
    float wc_z = currectSelect.width + 0.5*sumTargetSize;
    float hc_z = currectSelect.height + 0.5*sumTargetSize;

    float s_z = sqrtf((wc_z*hc_z));

    float scale_z = (float)127 / s_z;
    float d_search = (255 - 127) / 2;
    float pad = d_search / scale_z;
    float s_x = s_z + 2 * pad;

    return s_x;

}



cv::Rect extendRoiWidthFirst(cv::Rect inputRoi,float extendRate,cv::Rect frameRect){

    cv::Rect outRoi=inputRoi;
    outRoi.x=inputRoi.x-inputRoi.width*extendRate/2.0;
    outRoi.width=inputRoi.width*(1+2.0*extendRate);
    outRoi=outRoi&frameRect;

    return outRoi;
}

cv::Rect extendRoiHeightFirst(cv::Rect inputRoi, float extendRate, cv::Rect frameRect){

    cv::Rect outRoi=inputRoi;
    outRoi.y=inputRoi.y-inputRoi.height*extendRate/2.0;
    outRoi.height=inputRoi.height*(1+1.0*extendRate);
    outRoi=outRoi&frameRect;

    return outRoi; 
}



cv::Rect extendRoi(cv::Rect inputRoi,float extendRate,cv::Rect frameRect){

    cv::Rect outRoi;
    outRoi.x=inputRoi.x-inputRoi.width*extendRate;
    outRoi.y=inputRoi.y-inputRoi.height*extendRate;
    outRoi.width=inputRoi.width*(1+2.0*extendRate);
    outRoi.height=inputRoi.height*(1+2.0*extendRate);
    outRoi=outRoi&frameRect;

    return outRoi;
}

cv::Rect2f extendRoi2f(cv::Rect2f inputRoi,float extendRate){

    cv::Rect2f outRoi;
    outRoi.x=inputRoi.x-inputRoi.width*extendRate;
    outRoi.y=inputRoi.y-inputRoi.height*extendRate;
    outRoi.width=inputRoi.width*(1+2.0*extendRate);
    outRoi.height=inputRoi.height*(1+2.0*extendRate);
    outRoi=outRoi&cv::Rect2f(0,0,1.0f,1.0f);

    return outRoi;
}

cv::RotatedRect extendRotateRoi(cv::RotatedRect inputRoi, float extendRate){

    cv::RotatedRect outRoi=inputRoi;

    // LOGI("beforeRotateRoi: %d %d | %f %f |%f \n",inputRoi.boundingRect().width,inputRoi.boundingRect().height,inputRoi.size.width,inputRoi.size.height,extendRate);
    outRoi.size.width=inputRoi.size.width*(1+2.0*extendRate);
    outRoi.size.height=inputRoi.size.height*(1+2.0*extendRate);
    // LOGI("afterRotateRoi: %d %d | %f %f \n",outRoi.boundingRect().width,outRoi.boundingRect().height,outRoi.size.width,outRoi.size.height);

    return outRoi;
}


cv::Rect cutRoi(cv::Rect inputRoi,float cutRate,cv::Rect frameRect){

    cv::Rect outRoi;
    outRoi.x=inputRoi.x+inputRoi.width*cutRate;
    outRoi.y=inputRoi.y+inputRoi.height*cutRate;
    outRoi.width=inputRoi.width*(1-2.0*cutRate);
    outRoi.height=inputRoi.height*(1-2.0*cutRate);
    outRoi=outRoi&frameRect;

    return outRoi;
}



float calcOverLap(cv::Rect r1, cv::Rect r2) {

    float areaR1 = r1.area();
    float areaR2 = r2.area();
    cv::Rect overR = r1 & r2;

    return (float)overR.area() / (areaR1 + areaR2 - overR.area());
}



float calcOverLap2f(cv::Rect2f r1, cv::Rect2f r2) {

    float areaR1 = r1.area();
    float areaR2 = r2.area();
    cv::Rect2f overR = r1 & r2;

    return (float)overR.area() / (areaR1 + areaR2 - overR.area());
}


float calcCenterDist(cv::Rect r1, cv::Rect r2) {

    cv::Point p1(r1.x + r1.width / 2, r1.y + r1.height / 2);
    cv::Point p2(r2.x + r2.width / 2, r2.y + r2.height / 2);

    float dist = (sqrtf((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y))*2) / (r1.width + r2.width);

    return dist;
}

float calcCenterDistf(cv::Rect2f r1, cv::Rect2f r2) {

    cv::Point2f p1(r1.x + r1.width / 2.0f, r1.y + r1.height / 2.0f);
    cv::Point2f p2(r2.x + r2.width / 2.0f, r2.y + r2.height / 2.0f);
    float dist = (sqrtf((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y))*2);
    return dist;
}



float calcDist(cv::Point2f p1,cv::Point2f p2){

    float dist = std::sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                           (p1.y - p2.y) * (p1.y - p2.y));

    return dist;
}



bool isArmHold(cv::Point2f shouder, cv::Point2f elbow, cv::Point2f handPoint, float rate) {

    float deltaY0 = abs(shouder.y - elbow.y);
    float deltaY1 = elbow.y - handPoint.y;

    if (deltaY1 > 0 && deltaY1 > deltaY0 * rate) {
        return true;
    } else {
        return false;
    }
}


cv::Point2f findStd(std::vector<cv::Point2f> tCenterList){

    cv::Point2f avgPoint(0,0);
    for (int j = 0; j < tCenterList.size(); ++j) {
        avgPoint.x+= tCenterList[j].x;
        avgPoint.y+= tCenterList[j].y;
    }
    avgPoint.x/=tCenterList.size();
    avgPoint.y/=tCenterList.size();

    cv::Point2f diffPoint(0,0);
    for (int j = 0; j < tCenterList.size(); ++j) {
        diffPoint.x+= (tCenterList[j].x-avgPoint.x)*(tCenterList[j].x-avgPoint.x);
        diffPoint.y+= (tCenterList[j].y-avgPoint.y)*(tCenterList[j].y-avgPoint.y);
    }
    diffPoint.x/=tCenterList.size();
    diffPoint.y/=tCenterList.size();

    return diffPoint;
}


cv::Point2f findMeanPos(std::vector<cv::Point2f> tCenterList){

    cv::Point2f avgPoint(0,0);
    for (int j = 0; j < tCenterList.size(); ++j) {
        avgPoint.x+= tCenterList[j].x;
        avgPoint.y+= tCenterList[j].y;
    }
    avgPoint.x/=tCenterList.size();
    avgPoint.y/=tCenterList.size();

    return avgPoint;
}


long getCvTimeStamp(){
    long time=cv::getTickCount()*1000.0/cv::getTickFrequency();
    return time;
}



double getDistance(cv::Point pointO, cv::Point pointA)
{
    double distance;
    distance = powf((pointO.x - pointA.x), 2) + powf((pointO.y - pointA.y), 2);
    distance = sqrt(distance);
    return distance;
}

/* @function 求四个点所围面积 */
double get4PointArea(std::vector<cv::Point2f> points) {

    double d01, d12, d23, d30, d13;
    double k1, k2, s1, s2;
    d01 = getDistance(points[0], points[1]);
    d12 = getDistance(points[1], points[2]);
    d23 = getDistance(points[2], points[3]);
    d30 = getDistance(points[3], points[0]);
    d13 = getDistance(points[1], points[3]);
    k1 = (d01 + d30 + d13) / 2;
    k2 = (d12 + d23 + d13) / 2;
    s1 = sqrt(k1*(k1 - d01)*(k1 - d30)*(k1 - d13));
    s2 = sqrt(k2*(k2 - d12)*(k2 - d23)*(k2 - d13));
    return s1 + s2;
}



std::vector<cv::RotatedRect> warpRotatePointList(std::vector<cv::RotatedRect> preRotatePointList,cv::Mat homo){

    std::vector<cv::Point2f> preWarpPonits;
    std::vector<cv::Point2f> curWarpPoints;

    for (size_t i = 0; i < preRotatePointList.size(); i++)
    {
        preWarpPonits.push_back(preRotatePointList[i].center);
    }
    cv::perspectiveTransform(preWarpPonits, curWarpPoints, homo);

    std::vector<cv::RotatedRect> warpRotatePointList;
    warpRotatePointList.assign(preRotatePointList.begin(),preRotatePointList.end());
    for (size_t i = 0; i < warpRotatePointList.size(); i++)
    {
        warpRotatePointList[i].center=curWarpPoints[i];
    }

    return warpRotatePointList;
}

cv::Rect findExtendRectInRotateList(std::vector<cv::RotatedRect> rotateList){

    cv::Rect extendRoi=cv::Rect(0,0,0,0);

    for (size_t i = 0; i < rotateList.size(); i++)
    {
        extendRoi=extendRoi|rotateList[i].boundingRect();
    }
    
    return extendRoi;
}




cv::Point2f warpPoint(cv::Point2f prePoint,cv::Mat homo){
    std::vector<cv::Point2f> preWarpPonits={prePoint};
    std::vector<cv::Point2f> curWarpPoints;
    cv::perspectiveTransform(preWarpPonits, curWarpPoints, homo);
    return curWarpPoints[0];
}

cv::Point2f invWarpPoint(cv::Point2f warpPoint,cv::Mat homo){
    std::vector<cv::Point2f> preWarpPonits;
    std::vector<cv::Point2f> curWarpPoints={warpPoint};
    cv::perspectiveTransform(curWarpPoints, preWarpPonits, homo.inv());
    return preWarpPonits[0];
}

cv::Rect warpRect(cv::Rect preRect,cv::Mat homo){

    cv::Point2f warpedPoint=warpPoint(cv::Point(preRect.x,preRect.y),homo);

    return cv::Rect(warpedPoint.x,warpedPoint.y,preRect.width,preRect.height);
}


float getAngelOfTwoVector(cv::Point2f pt1, cv::Point2f pt2, cv::Point2f c)
{
	float theta = atan2(pt1.y - c.y, pt1.x - c.x) - atan2(pt2.y - c.y, pt2.x - c.x);
	if (theta > CV_PI)
		theta -= 2 * CV_PI;
	if (theta < -CV_PI)
		theta += 2 * CV_PI;
 
	theta = theta * 180.0 / CV_PI;
	return theta;
}

int warpAreaPoint(cv::Size imageSize,cv::Mat homo,cv::Point2f & warpCenter,double & warpArea ,double & deltaAngle){

    std::vector<cv::Point2f> srcPos, dstPos;
    srcPos={{0,0},{(float)imageSize.width,0},{(float)imageSize.width,(float)imageSize.height},{0,(float)imageSize.height}};
    cv::perspectiveTransform(srcPos, dstPos, homo);
    for (size_t i = 0; i < dstPos.size(); i++)
    {
        warpCenter.x+=dstPos[i].x;
        warpCenter.y+=dstPos[i].y;          
    }
    warpCenter.x/=dstPos.size();
    warpCenter.y/=dstPos.size();


    deltaAngle=getAngelOfTwoVector(cv::Point2f(imageSize.width,0.0),cv::Point2f(dstPos[1].x-dstPos[0].x,dstPos[1].y-dstPos[0].y),cv::Point2f(0,0));

    warpArea=get4PointArea(dstPos);

    return 1;
}



double distanceFromPointToLine(
    const double &x0, const double &y0,
    const double &x1, const double &y1,
    const double &x2, const double &y2) {
    double d = (fabs((y2 - y1) * x0 + (x1 - x2) * y0 + ((x2 * y1) - (x1 * y2)))) /
               (sqrt((y2 - y1)*(y2 - y1)) + (x1 - x2)*(x1 - x2));
    return d;
}

double yValueInLine(double x0,double x1,double y1,double x2,double y2){

    double k=(y2-y1)/(x2-x1+0.0000001);
    return k*(x0-x1)+y1;
}


void populateInterpPoints(const cv::Point &a, const cv::Point &b, int numPoints,
                          std::vector<cv::Point> &interpCoords) {
    float xStep = ((float) (b.x - a.x)) / (float) (numPoints - 1);
    float yStep = ((float) (b.y - a.y)) / (float) (numPoints - 1);

    interpCoords.push_back(a);
    for (int i = 1; i < numPoints - 1; ++i) {
        interpCoords.push_back(cv::Point(a.x + xStep * i, a.y + yStep * i));
    }    
    interpCoords.push_back(b);
}



bool polynomial_curve_fit(std::vector<cv::Point>& key_point, int n, cv::Mat& A)
{
	//Number of key points
	int N = key_point.size();


	//构造矩阵X
	cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			for (int k = 0; k < N; k++)
			{
				X.at<double>(i, j) = X.at<double>(i, j) +
					std::pow(key_point[k].x, i + j);
			}
		}
	}
 
	//构造矩阵Y
	cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int k = 0; k < N; k++)
		{
			Y.at<double>(i, 0) = Y.at<double>(i, 0) +
				std::pow(key_point[k].x, i) * key_point[k].y;
		}
	}
 
	A = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	//求解矩阵A
	cv::solve(X, Y, A, cv::DECOMP_LU);

    // std::cout<<"A"<<A<<std::endl;
    // for (size_t i = 0; i < key_point.size(); i++)
    // {
	// 	// double y0 = A.at<double>(0, 0) + A.at<double>(1, 0) * key_point[i].x + A.at<double>(2, 0)*std::pow(key_point[i].x, 2);
	// 	double y0 = A.at<double>(0, 0) + A.at<double>(1, 0) * key_point[i].x;        
    //     printf("key_point:%d %d %d %f \n",i,key_point[i].x,key_point[i].y,y0);
    // }



	return true;
}


#endif