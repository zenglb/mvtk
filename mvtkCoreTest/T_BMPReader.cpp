#include "mvtkBMPReader.h"
#include "mvtkVolume.h"
#include "mvtkJPGReader.h"
#include "mvtkDICOMReader.h"
#include "mvtkRawReader.h"
#pragma comment(lib,"mvtkCore.lib")

void ProgressDisplay(void* v){
	cout<<*((double*)v)<<endl;
}

void main(){
	mvtkBMPReader* m_bmpreader=mvtkBMPReader::New();
	m_bmpreader->SetFilePattern("D:\\VHData\\heart\\heart*");
	m_bmpreader->SetProgressMethod(ProgressDisplay);
	m_bmpreader->Update();
	mvtkVolume* mv=m_bmpreader->GetOutput();
	unsigned char* m_volume=(unsigned char*)mv->GetData();
	for (int i=0;i<100;i++){
		cout<<hex<<m_volume[i]<<endl;
	}
	m_bmpreader->Delete();

	//mvtkJPGReader* jpgReader=mvtkJPGReader::New();
	//jpgReader->SetFilePattern("D:\\jpg\\*.jpg");
	//jpgReader->SetProgressMethod(ProgressDisplay);
	//jpgReader->Update();
	//mvtkVolume* mv=jpgReader->GetOutput();
	//unsigned char* m_volume=(unsigned char*)mv->GetData();
	//for (int i=0;i<100;i++){
	//	cout<<hex<<m_volume[i]<<endl;
	//}
	//jpgReader->Delete();

	//mvtkDICOMReader* dcomReader=mvtkDICOMReader::New();
	//dcomReader->SetFilePattern("D:\\DICOM\\*.dcm");
	//dcomReader->SetProgressMethod(ProgressDisplay);
	//dcomReader->Update();
	//mvtkVolume* mv=dcomReader->GetOutput();
	//unsigned char* m_volume=(unsigned char*)mv->GetData();
	//for (int i=0;i<100;i++){
	//	cout<<hex<<m_volume[i]<<endl;
	//}
	//dcomReader->Delete();

	//mvtkRawReader* rawReader=mvtkRawReader::New();
	//rawReader->SetFilePattern("D:\\raw\\*.raw");
	//rawReader->SetProgressMethod(ProgressDisplay);
	//rawReader->SetWidth(2048);
	//rawReader->SetHeight(1026);
	//rawReader->Update();
	//mvtkVolume* mv=rawReader->GetOutput();
	//unsigned char* m_volume=(unsigned char*)mv->GetData();
	//for (int i=0;i<100;i++){
	//	cout<<hex<<m_volume[i]<<endl;
	//}
	//rawReader->Delete();

	mv->Delete();
	
	system("pause");
}