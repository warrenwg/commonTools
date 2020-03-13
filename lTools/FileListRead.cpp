#include "FileListRead.h"


FileListRead::FileListRead()
{
}


FileListRead::~FileListRead()
{
}


std::vector<std::string> FileListRead::readFileLists(char* dir_name){

	std::vector<std::string> fileLists;

	// check the parameter !
	if( NULL == dir_name )
	{
		cout<<" dir_name is null ! "<<endl;
		return fileLists;
	}
 
	// check if dir_name is a valid dir
	struct stat s;
	lstat( dir_name , &s );
	if( ! S_ISDIR( s.st_mode ) )
	{
		cout<<"dir_name is not a valid directory !"<<endl;
		return fileLists;
	}
	
	struct dirent * filename;    // return value for readdir()
 	DIR * dir;                   // return value for opendir()
	dir = opendir( dir_name );
	if( NULL == dir )
	{
		cout<<"Can not open dir "<<dir_name<<endl;
		return fileLists;
	}
	cout<<"Successfully opened the dir !"<<endl;
	
	/* read all the files in the dir ~ */
	while( ( filename = readdir(dir) ) != NULL )
	{
		// get rid of "." and ".."
		if( strcmp( filename->d_name , "." ) == 0 || strcmp( filename->d_name , "..") == 0    )
			continue;
		
		fileLists.push_back(filename ->d_name);
		cout<<filename ->d_name <<endl;
	}


	return fileLists;
}





