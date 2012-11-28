#include "mvtkWriter.h"

void mvtkWriter::AddFileName(const char *inFileName){
	string str=*(new string);
	str=inFileName;
	this->m_FileNames->push_back(str);
}

void mvtkWriter::SortFileNames(){
	this->m_FileNames->sort();
}

int mvtkWriter::_getFileCount(void){
	return this->m_FileNames->size();
}

const char* mvtkWriter::_getFileName(int nIndex){
	list<string>::iterator it=this->m_FileNames->begin();
	advance(it,nIndex);//迭代器往后移动3个
	return it->c_str();
}

mvtkWriter::mvtkWriter(){
	this->m_FileNames=new list<string>;
}
mvtkWriter::~mvtkWriter(){
	list<string>::iterator it;
	for (it=this->m_FileNames->begin();it!=this->m_FileNames->end();++it){
		delete &(*it);
	}
	delete this->m_FileNames;
	this->m_FileNames=NULL;
}