#include "mvtkDICOMReader.h"
#include "mvtk_utilities/dicom/DICOMAppHelper.h"
#include "mvtk_utilities/dicom/DICOMParser.h"

mvtkDICOMReader::mvtkDICOMReader(void)
{
	Parser=new DICOMParser();
	AppHelper=new DICOMAppHelper();
}

mvtkDICOMReader::~mvtkDICOMReader(void)
{
	delete Parser;
	delete AppHelper;
}
int mvtkDICOMReader::CanReadFile(const char* fname)
{
	bool canopen=Parser->OpenFile(fname);
	if(! canopen){
		mvtkDebugMessage("DICOMParser couldn't open:"<<fname);
		return 0;
	}
	bool canRead=Parser->IsDICOMFile();
	if(! canRead){
		mvtkDebugMessage("DICOMParser couldn't parse:"<<fname);
		return 0;
	}
	return 1;
}
void mvtkDICOMReader::Update()
{
	if(m_StartMethod != NULL)
		m_StartMethod();
	SortFileNames();
	int file_count=_getFileCount();
	this->Parser->ClearAllDICOMTagCallbacks();
    this->AppHelper->Clear();
    this->AppHelper->RegisterCallbacks(this->Parser);
    this->AppHelper->RegisterPixelDataCallback(this->Parser);
	unsigned char* img_pixels=NULL;
	int img_off_set=0;
	double ProgressValue=0;

	for(int i=0;i<file_count;i++){
		if(this->m_ProgressMethod!=NULL){
			ProgressValue=((double)i+1)/((double)file_count);
			this->m_ProgressMethod(&ProgressValue);
		}

		const char* fname=_getFileName(i);
		Parser->OpenFile(fname);
		Parser->ReadHeader();
		void* imgData=NULL;
		DICOMParser::VRTypes dataType;
		unsigned long imageDataLengthInBytes;
		AppHelper->GetImageData(imgData,dataType,imageDataLengthInBytes);
		if(! imageDataLengthInBytes){
			mvtkDebugMessage("can't read from:"<<fname);
			return;
		}
		int d_w=AppHelper->GetWidth();
		int d_h=AppHelper->GetHeight();
		int ch_num=imageDataLengthInBytes/(d_w*d_h);
		unsigned char* pixels=(unsigned char*)imgData;
		unsigned char* d_pixels=pixels;

		if(m_ImgProgressMethod != NULL)
			this->m_ImgProgressMethod(pixels,d_pixels,MVTK_UNSIGNED_CHAR,d_w,d_h,d_w,d_h);
		if(!this->m_OutData->GetIsInitialize()){//��ʼ������
				this->m_OutData->SetChannelNum(ch_num);
				this->m_OutData->SetTimeInterval(1);//ʱ��ά��������Ϊ1 ����һ�û�������ʵ��
				this->m_OutData->SetImageNum(file_count);
				this->m_OutData->SetHeight(d_h);
				this->m_OutData->SetWidth(d_w);
				this->m_OutData->SetDataTypeToUnsignedChar(); //Ҫ���������Ͳ��ܽ�������ĳ�ʼ�� **ע��**
				this->m_OutData->Initialize();//�����곤��ߣ���ɫά�ȣ�ʱ��ά�� ���������� ���ܳ�ʼ��

				img_pixels=(unsigned char*)this->m_OutData->GetData();//��ʼ��ָ��
				img_off_set=d_w*d_h*ch_num;
		}

		memcpy(img_pixels,d_pixels,img_off_set);
		img_pixels += img_off_set;
	}
}