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
#endif