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

//"D:\\VHData\\heart\\heart*" ��������ʽ  ������ʽ �����ļ��б�
void mvtkVolumeReader::SetFilePattern(char* filePattern){
	this->m_FilePattern=new string(filePattern);
	this->RemoveAllFileNames();//���������ʷ��¼
	//�����ļ��б�
	_finddata_t file; 
	long lf; 
	//�޸�����ѡ��·����Ҫ���ҵ��ļ�����
	if((lf = _findfirst(filePattern,&file))==-1l){
		//_findfirst���ص���long��;long __cdecl _findfirst(const char *, struct _finddata_t *) 
		mvtkDebugMessage("File not found!");
		return;//�ļ�û�ҵ�
	}else{
		do{ 
			char full_name[200];
			strcpy(full_name,filePattern);
			char* c=strrchr(full_name,'\\')+1;
			*c=0;//�ض�
			strcpy(c,file.name);
			this->AddFileName(full_name);
		} while( _findnext( lf, &file ) == 0 );
		//int __cdecl _findnext(long, struct _finddata_t *);����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1 
	}
	_findclose(lf); 
}