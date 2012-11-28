#include "mvtkReader.h"

void mvtkReader::AddFileName(const char *inFileName){
	string str=*(new string);
	str=inFileName;
	this->m_FileNames->push_back(str);
}

void mvtkReader::SortFileNames(){
	if(this->m_FileNames->size()<=1){
		return;
	}
	this->m_FileNames->sort();
}

void mvtkReader::RemoveAllFileNames(){
	list<string>::iterator it;
	for (it=this->m_FileNames->begin();it!=this->m_FileNames->end();++it){
		delete &(*it);
	}
	this->m_FileNames->clear();
}

int mvtkReader::_getFileCount(void){
	return this->m_FileNames->size();
}

const char* mvtkReader::_getFileName(int nIndex){
	list<string>::iterator it=this->m_FileNames->begin();
	advance(it,nIndex);//µü´úÆ÷ÍùºóÒÆ¶¯
	return it->c_str();
}

mvtkReader::mvtkReader(){
	this->m_FileNames=new list<string>;
}
mvtkReader::~mvtkReader(){
	this->RemoveAllFileNames();
	delete this->m_FileNames;
	this->m_FileNames=NULL;
}