#include "mvtkBMPReader.h"
#include "mvtkVolume.h"
#pragma comment(lib,"mvtkCore.lib")

void ProgressDisplay(void* v){
	cout<<*((double*)v)<<endl;
}

void main(){
	mvtkBMPReader* m_bmpreader=mvtkBMPReader::New();
	m_bmpreader->SetFilePattern("D:\\VHData\\heart\\heart*");
	m_bmpreader->SetProgressMethod(ProgressDisplay);
	m_bmpreader->Update();
	unsigned char* m_volume=(unsigned char*)m_bmpreader->GetOutput()->GetData();
	//for (int i=0;i<100;i++){
	//	cout<<hex<<m_volume[i]<<endl;
	//}
	system("pause");
}