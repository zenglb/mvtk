#include "mvtkBMPReader.h"
#include "mvtkVolume.h"

void mvtkBMPReader::Update(){//********ǿ��ע���ڴ�й¶����********�ǵ�delete***����ע���ٶ�***
	if(this->m_StartMethod!=NULL){
		this->m_StartMethod();
	}

	this->SortFileNames();//�ź�˳��
	int file_count=this->_getFileCount();
	
	ifstream* fpi=NULL;
	BITMAPFILEHEADER* strHead=new BITMAPFILEHEADER;
	BITMAPINFOHEADER* strInfo=new BITMAPINFOHEADER;
	unsigned char *imagedata = NULL;//ͼƬ��������Ϣ
	unsigned char* img_pixels=NULL;//Ŀ��ָ�� ��Ϊ����ʹ��char����������char
	int img_pixel_offset=0;//pixel��ƫ������һ��ͼƬ��ƫ����
	unsigned char* s_fill=NULL; //�����ֽ�
	int ss=0;//����ֽ���
	bool is_success_exc=true;

	double ProgressValue=0;

	for (int i=0;i<file_count;i++)
	{
		if(this->m_ProgressMethod!=NULL){
			ProgressValue=((double)i+1)/((double)file_count);
			this->m_ProgressMethod(&ProgressValue);
		}

		const char* strFile=this->_getFileName(i);//��ȡλͼ�ļ�
		fpi=new ifstream(strFile,std::ios_base::binary);
		if(fpi->is_open()){
			fpi->read(reinterpret_cast<char *>(strHead),sizeof(BITMAPFILEHEADER));//���ļ�ͷ
			if(0x4d42!=strHead->bfType){//����bmp
				mvtkDebugMessage(strFile<<" is not a bmp file!");
				is_success_exc=false;
				break;//��������ֱ���˳�
			}
			fpi->read(reinterpret_cast<char *>(strInfo),sizeof(BITMAPINFOHEADER));//����Ϣͷ
			if(strInfo->biClrUsed>0){//��ȡ��ɫ��
				RGBQUAD* strPla=new RGBQUAD[strInfo->biClrUsed*sizeof(RGBQUAD)];
				fpi->read(reinterpret_cast<char *>(strPla),strInfo->biClrUsed * sizeof(RGBQUAD));
				delete strPla;
			}
			ss= strHead->bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER)-strInfo->biClrUsed*sizeof(RGBQUAD);//ƫ��������
			if(ss>0){
				s_fill=new unsigned char[ss];
				fpi->read(reinterpret_cast<char *>(s_fill),ss);
				delete s_fill;
			}
			
			imagedata =new unsigned char[strInfo->biSizeImage];//���������� �����ļ���Ϣͷ�� ���ó�����
			fpi->read(reinterpret_cast<char *>(imagedata),strInfo->biSizeImage);//һ��char��ռ8λ

			//����ת��
			int ch_num=0;
			switch(strInfo->biBitCount){//1��4��8��16��24��32
				case 1:		ch_num=1;break;//��ɫ α��ɫ
				case 4:		ch_num=1;break;//��ɫ α��ɫ
				case 8:		ch_num=1;break;//��ɫ α��ɫ
				case 16:	ch_num=2;break;//��ɫ α��ɫ
				case 24:	ch_num=3;break;//��֧��͸�� ���ɫ
				case 32:	ch_num=4;break;//֧��͸��
			}

			//��ʱ���鹩��ʱ�洢 ���Ժ����ͼ����
			unsigned char* pixel=new unsigned char[strInfo->biWidth*strInfo->biHeight*ch_num];

			int img_offset=0,row_offset=strInfo->biBitCount*strInfo->biWidth;//һ���ֽ�8λ 4�ֽڶ���
			if(row_offset%32){
				row_offset/=32;
				row_offset+=1;
			}else{
				row_offset/=32;
			}
			row_offset*=4;

			for (int h=0;h<strInfo->biHeight;h++){
				if (strInfo->biBitCount>=8){
					memcpy(pixel,imagedata+img_offset,strInfo->biWidth*ch_num);//��ȡһ��
				}else{//ÿλ���и�ֵ �����Ȳ�֧�� ֧���е�û����
					mvtkDebugMessage(strFile<<" Temporarily unsupported file types.");
					is_success_exc=false;
					return;//��������ֱ���˳�
				}
				img_offset+=row_offset;
			}

			int d_w=strInfo->biWidth,d_h=strInfo->biHeight;
			unsigned char* d_pixel=NULL;
			d_pixel=pixel;

			//�����ⲿ��������ͼ���� ������Сͼ��֮��
			if(this->m_ImgProgressMethod!=NULL){
				this->m_ImgProgressMethod(pixel,d_pixel,MVTK_UNSIGNED_CHAR,strInfo->biWidth,strInfo->biHeight,d_w,d_h);
			}

			if(img_pixels!=NULL){
				img_pixels+=img_pixel_offset;//����ǰ�� ���һ�ε�ƫ����Ϊ0
			}

			if(!this->m_OutData->GetIsInitialize()){//��ʼ������
				this->m_OutData->SetChannelNum(ch_num);
				this->m_OutData->SetTimeInterval(1);//ʱ��ά��������Ϊ1 ����һ�û�������ʵ��
				this->m_OutData->SetImageNum(file_count);
				this->m_OutData->SetHeight(d_h);
				this->m_OutData->SetWidth(d_w);
				this->m_OutData->SetDataTypeToUnsignedChar(); //Ҫ���������Ͳ��ܽ�������ĳ�ʼ�� **ע��**
				this->m_OutData->Initialize();//�����곤��ߣ���ɫά�ȣ�ʱ��ά�� ���������� ���ܳ�ʼ��

				img_pixels=(unsigned char*)this->m_OutData->GetData();//��ʼ��ָ��
				img_pixel_offset=d_h*d_w*ch_num;//����ƫ����
			}

			memcpy(img_pixels,d_pixel,img_pixel_offset);

			fpi->close();
			delete fpi;
			fpi=NULL;
			delete[] imagedata;
			imagedata=NULL;
			if(d_pixel!=NULL&&d_pixel!=pixel){
				delete[] d_pixel;
				d_pixel=NULL;
			}
			delete[] pixel;
			pixel=NULL;
		}else{//�ļ��򿪴���
			mvtkDebugMessage(strFile<<" file open error!");
			is_success_exc=false;
			return;//��������ֱ���˳�
		}
		if(fpi!=NULL){
			delete fpi;
			fpi=NULL;
		}
		delete[] imagedata;
		imagedata = NULL;
	}//forѭ������

	if(!is_success_exc){//���ɹ����������
		this->m_OutData->Delete();
		this->m_OutData=mvtkVolume::New();
	}

	delete strHead;
	delete strInfo;

	if(this->m_EndMethod!=NULL){
		this->m_EndMethod();
	}
}