#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "LogTool.h"

class Permutate
{
public:
	Permutate();
	~Permutate();

    void permutate(int begin, int end, int a[],std::vector<std::vector<int> >& out);
    void combinate(int iPos, int iProc, int iTol, int iKey, int data[],int des[],std::vector<std::vector<int> >& out);
    std::vector<std::vector<int> > permutateAndcombinate(int selectNum,int totalNum, int data[]);

};
