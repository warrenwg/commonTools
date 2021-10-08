#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "LogTool.h"

#define min_c(X,Y) ((X) < (Y) ? (X) : (Y))
#define max_c(X,Y) ((X) > (Y) ? (X) : (Y))
#define abs_c(a)   ((a) < 0   ? -(a)  :(a)) 

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

cv::Rect extendRoiWidthFirst(cv::Rect inputRoi, float extendRate, cv::Rect frameRect);
cv::Rect extendRoiHeightFirst(cv::Rect inputRoi, float extendRate, cv::Rect frameRect);
cv::Rect extendRoi(cv::Rect inputRoi, float extendRate, cv::Rect frameRect);
cv::Rect2f extendRoi2f(cv::Rect2f inputRoi, float extendRate);

cv::RotatedRect extendRotateRoi(cv::RotatedRect inputRoi, float extendRate);

cv::Rect cutRoi(cv::Rect inputRoi, float cutRate, cv::Rect frameRect);

float calcOverLap(cv::Rect r1, cv::Rect r2);

float calcOverLap2f(cv::Rect2f r1, cv::Rect2f r2);

float calcCenterDist(cv::Rect r1, cv::Rect r2);

float calcCenterDistf(cv::Rect2f r1, cv::Rect2f r2);

float calcDist(cv::Point2f p1, cv::Point2f p2);

double distanceFromPointToLine(
    const double &x0, const double &y0,//point
    const double &x1, const double &y1,//linePoint0
    const double &x2, const double &y2);//linePoint1

double yValueInLine(double x0,double x1,double y1,double x2,double y2);

bool isArmHold(cv::Point2f shouder, cv::Point2f elbow, cv::Point2f handPoint, float rate);

cv::Point2f findStd(std::vector<cv::Point2f> tCenterList);

cv::Point2f findMeanPos(std::vector<cv::Point2f> tCenterList);

long getCvTimeStamp();

double get4PointArea(std::vector<cv::Point2f> points);

std::vector<cv::RotatedRect> warpRotatePointList(std::vector<cv::RotatedRect> preRotatePointList, cv::Mat homo);

cv::Point2f warpPoint(cv::Point2f prePoint, cv::Mat homo);

cv::Rect warpRect(cv::Rect preRect,cv::Mat homo);

cv::Rect findExtendRectInRotateList(std::vector<cv::RotatedRect> rotateList);

float getAngelOfTwoVector(cv::Point2f pt1, cv::Point2f pt2, cv::Point2f c);

int warpAreaPoint(cv::Size imageSize,cv::Mat homo,cv::Point2f & warpCenter,double & warpArea ,double & deltaAngle);

cv::Point2f invWarpPoint(cv::Point2f warpPoint, cv::Mat homo);

void populateInterpPoints(const cv::Point &a, const cv::Point &b, int numPoints,
                          std::vector<cv::Point> &interpCoords);

bool polynomial_curve_fit(std::vector<cv::Point>& key_point, int n, cv::Mat& A);

#endif
