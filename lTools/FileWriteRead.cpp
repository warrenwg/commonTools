#include "FileWriteRead.h"
#include <time.h>


FileWriteRead::FileWriteRead()
{
}


FileWriteRead::~FileWriteRead()
{
}


void FileWriteRead::writeBin(char* path,void * data,int datalen,int oneDataSize){

		FILE* pFile = NULL;
         if (pFile == NULL)
        {
            pFile = fopen( path, "wb" );
        }
        if (pFile != NULL)
        {
            if ( 0 == fwrite(data, datalen, oneDataSize, pFile ) )
            {
                printf("%s fwrite err\r\n",path);
            }
            fclose(pFile);
        }

}


void FileWriteRead::readBin(char* path,void * data,int datalen,int oneDataSize){


	  FILE* pFile = NULL;
      pFile = fopen(path, "rb");
      if (pFile != NULL)
      {
          if ( 0 == fread(data, datalen,oneDataSize, pFile ) )
          {
              printf( "%s read file error \n",path);
          }

          fclose( pFile );
      }

}








