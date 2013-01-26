#include "mvtkBMPReader.h"
#include "mvtkVolume.h"
#include "mvtkIsosurfaceVRScene.h"
#include "GLUTSceneContainer.h"
//#include "mvtkJPGReader.h"
//#include "mvtkDICOMReader.h"
//#include "mvtkRawReader.h"
//#include "mvtkVolumeContourFilter.h"
#pragma comment(lib,"mvtkCore.lib")


void ProgressDisplay(void* v){
	//cout<<*((double*)v)<<endl;
}

void SaveAsDataFile()
{
	mvtkBMPReader* m_bmpreader=mvtkBMPReader::New();
	m_bmpreader->SetFilePattern("D:\\VHData\\heart\\heart*");
	m_bmpreader->SetProgressMethod(ProgressDisplay);
	m_bmpreader->Update();
	mvtkVolume* mv=m_bmpreader->GetOutput();

	m_bmpreader->Delete();

	char* c_output=(char*)mv->GetData();

	int m_Dims[4]={0,0,0,0};
	mv->GetDimensions(m_Dims);
	float m_Spacings[3]={0.33,0.33,0.33};

	struct DataType
	{
		bool isFloat;
		bool isSigned;
		int bitsPerSample;
	};

	const DataType dtUint8={false,false,8};

	FILE *fp;
	fp=fopen("vheart.dat","wb");
	fwrite(m_Dims,sizeof(int),3,fp);
	fwrite(m_Spacings,sizeof(float),3,fp);
	fwrite(&dtUint8,sizeof(DataType),1,fp);
	fwrite(c_output,1,m_Dims[0]*m_Dims[1]*m_Dims[2]*m_Dims[3],fp);
	fclose(fp);

	mv->Delete();
}

void readtest(){
	mvtkBMPReader* m_bmpreader=mvtkBMPReader::New();
	m_bmpreader->SetFilePattern("D:\\VHData\\heart\\heart*");
	m_bmpreader->SetProgressMethod(ProgressDisplay);
	m_bmpreader->Update();
	mvtkVolume* mv=m_bmpreader->GetOutput();
	//unsigned char* m_volume=(unsigned char*)mv->GetData();
	//mvtkVolumeContourFilter* mcf=mvtkVolumeContourFilter::New();
	//mcf->SetProgressMethod(ProgressDisplay);
	//mcf->SetInput(mv);
	//mcf->Update();
	//unsigned char* m_volume=(unsigned char*)mcf->GetOutput()->GetData();

	//for (int i=0;i<100;i++){
	//	cout<<hex<<m_volume[i]<<endl;
	//}
	//mcf->GetOutput()->Delete();
	//mcf->Delete();

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

void rendertest(int argc,char** argv)
{
	glutInit(&argc,argv);

	mvtkBMPReader* m_bmpreader=mvtkBMPReader::New();
	m_bmpreader->SetFilePattern("D:\\VHData\\heart\\heart*");
	m_bmpreader->SetProgressMethod(ProgressDisplay);
	m_bmpreader->Update();
	mvtkVolume* mv=m_bmpreader->GetOutput();
	m_bmpreader->Delete();

	float m_Spacings[4]={0.33,0.33,0.33,0.33};
	mv->SetSpacings(m_Spacings);

	int dimss[4]={0,0,0,0};
	mv->GetDimensions(dimss);

	int len=dimss[0]*dimss[1]*dimss[2]*dimss[3];
	//scene->SetBackGroundColor(1.0f,1.0f,1.0f);
	char * c_output= (char*)mv->GetData();
	for (int i = 0; i < len; i++)
	{
		c_output[i]=c_output[i]==80?0:c_output[i];
		//c_output[i]=c_output[i]!=80?0:c_output[i];
	}

	mvtkIsosurfaceVRScene* scene=new mvtkIsosurfaceVRScene;
	scene->SetBackGroundColor(0.5f,0.5f,0.5f);
	scene->SetData(mv);
	
	GLUTSceneContainer *mainWindow=GLUTSceneContainer::GetMainWindow();
	mainWindow->SetTitle("Test Window");
	mainWindow->SetScene(scene);
	mainWindow->Create(100,100);

	mv->Delete();
}

void main(int argc,char** argv)
{
	rendertest(argc,argv);
	//readtest();
}