#include "mvtkVolumeReader.h"
#include "mvtkVolume.h"
#include <io.h>

mvtkVolumeReader::mvtkVolumeReader(){
	this->m_ImgProgressMethod=NULL;
	memset(this->m_Spacings,0,3*sizeof(float));
	this->m_OutData=mvtkVolume::New();
	this->m_FilePattern=NULL;
}

mvtkVolumeReader::~mvtkVolumeReader(){
	if(this->m_FilePattern){
		delete this->m_FilePattern;
	}
	this->m_ImgProgressMethod=NULL;
}

//"D:\\VHData\\heart\\heart*" 这样的形式  更新样式 更新文件列表
void mvtkVolumeReader::SetFilePattern(char* filePattern){
	this->m_FilePattern=new string(filePattern);
	this->RemoveAllFileNames();//清空所有历史记录
	//更新文件列表
	_finddata_t file; 
	long lf; 
	//修改这里选择路径和要查找的文件类型
	if((lf = _findfirst(filePattern,&file))==-1l){
		//_findfirst返回的是long型;long __cdecl _findfirst(const char *, struct _finddata_t *) 
		mvtkDebugMessage("File not found!");
		return;//文件没找到
	}else{
		do{ 
			char full_name[200];
			strcpy(full_name,filePattern);
			char* c=strrchr(full_name,'\\')+1;
			*c=0;//截断
			strcpy(c,file.name);
			this->AddFileName(full_name);
		} while( _findnext( lf, &file ) == 0 );
		//int __cdecl _findnext(long, struct _finddata_t *);如果找到下个文件的名字成功的话就返回0,否则返回-1 
	}
	_findclose(lf); 
}