#include "Permutate.h"


	Permutate::Permutate(){

	}
	
	Permutate::~Permutate(){

	}

//交换函数
void swap(int& a, int& b )
{
	int temp = a;
	a = b;
	b = temp;
}
/*入参：
	begin 要排列的起始位置
	end   要排列的结束位置
	a[]	 要排列的数组
*/
void Permutate::permutate(int begin, int end, int a[],std::vector<std::vector<int> >& out)
{
	if(begin == end)//已经到了最后一个位置，进行输出
	{
		//cout<<"[";
		std::vector<int> tempOut;
		for(int i=0; i < end;i++)
		{
			//cout<<a[i];
			//if(i<end-1){
			//   cout<<",";
			//}
			tempOut.push_back(a[i]);

		}
		out.push_back(tempOut);
		//cout<<"],\\"<<endl;
	}
	for(int i= begin; i < end; i++)
	{
		swap(a[begin],a[i]);
		permutate(begin + 1,end,a,out);//递归下一个位置
		swap(a[i],a[begin]);//回溯
	}
}


void Permutate::combinate(int iPos, int iProc, int iTol, int iKey, int data[],int des[],std::vector<std::vector<int> >& out)
{
	if(iProc > iTol)
	{
		return;
	}
	if(iPos == iKey)
	{
		std::vector<int> tempOut;
		for(int i = 0;i < iKey; i++)
		{
			//cout<<des[i]<<" ";
			tempOut.push_back(des[i]);
		}
		out.push_back(tempOut);
		//cout<<endl;
		return;
	}
	else
	{
		combinate(iPos,iProc+1,iTol,iKey,data,des,out);
		des[iPos] = data[iProc];
		combinate(iPos+1,iProc+1,iTol,iKey,data,des,out);
	}
}


std::vector<std::vector<int> > Permutate::permutateAndcombinate(int selectNum,int totalNum, int data[]){

	std::vector<std::vector<int> > totalOut;

	int* des=(int*)malloc(sizeof(int)*(totalNum+1));
	std::vector<std::vector<int> > vvOut;
	combinate(0, 0, totalNum, selectNum ,data,des,vvOut);

	for(int i=0;i<vvOut.size();i++){
 	   int* aa = (int*)malloc(vvOut[i].size()*sizeof(int));
	   for(int j=0;j<vvOut[i].size();j++){
		aa[j]=vvOut[i][j];
	   }
	   std::vector<std::vector<int> > ttOut;
	   permutate(0,selectNum,aa,ttOut);
          
           for(int i=0;i<ttOut.size();i++){
		totalOut.push_back(ttOut[i]);
	   }
	}
	free(des);


	// for(int i=0;i<totalOut.size();i++){
	//    cout<<"[";
	//    for(int j=0;j<totalOut[i].size();j++){
	// 	cout<<totalOut[i][j];
	// 	if(j<totalOut[i].size()-1){
	// 	   cout<<",";
	// 	}
	//    }	
	//    cout<<"],\\"<<endl;
	// }
	return totalOut;
}
