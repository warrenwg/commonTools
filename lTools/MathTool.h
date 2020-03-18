#pragma once
#include <iostream>
#include <vector>
#include "LogTool.h"

#define min_c(X,Y) ((X) < (Y) ? (X) : (Y))
#define max_c(X,Y) ((X) > (Y) ? (X) : (Y))

#define PREV_INDEX(index,offset,size) (((size) + (index) - (offset)) % (size))
#define NEXT_INDEX(index,offset,size) (((index) + (offset)) % (size))

int majorityElement(std::vector<int> nums, int numsSize, int & numCount);

bool FloatEqual(float f1,float f2);

bool FloatNotEqual(float f1,float f2);

float sigmoid(float x, float a, float b);

float findMean(std::vector<float> lists);

int findMean(std::vector<int> lists);

#ifdef USE_OCV
#include <opencv2/opencv.hpp>


void roiScale(cv::Rect inputRoi,cv::Rect & outRoi,int inW,int inH,int outW,int outH);

float getTrackArea(cv::Rect currectSelect);

cv::Rect extendRoi(cv::Rect inputRoi,float extendRate,cv::Rect frameRect);
cv::Rect2f extendRoi2f(cv::Rect2f inputRoi,float extendRate);

cv::Rect cutRoi(cv::Rect inputRoi,float cutRate,cv::Rect frameRect);

float calcOverLap(cv::Rect r1, cv::Rect r2);

float calcOverLap2f(cv::Rect2f r1, cv::Rect2f r2);

float calcCenterDist(cv::Rect r1, cv::Rect r2);

float calcCenterDistf(cv::Rect2f r1, cv::Rect2f r2);

float calcDist(cv::Point2f p1,cv::Point2f p2);

bool isArmHold(cv::Point2f shouder, cv::Point2f elbow, cv::Point2f handPoint, float rate);

cv::Point2f findStd(std::vector<cv::Point2f> tCenterList);

cv::Point2f findMeanPos(std::vector<cv::Point2f> tCenterList);

long getCvTimeStamp();

#endif
