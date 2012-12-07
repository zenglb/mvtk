#include "mvtkBMPReader.h"
#include "mvtkVolume.h"

void mvtkBMPReader::Update(){//********强烈注意内存泄露问题********记得delete***另外注意速度***
	if(this->m_StartMethod!=NULL){
		this->m_StartMethod();
	}

	this->SortFileNames();//排好顺序
	int file_count=this->_getFileCount();
	
	ifstream* fpi=NULL;
	BITMAPFILEHEADER* strHead=new BITMAPFILEHEADER;
	BITMAPINFOHEADER* strInfo=new BITMAPINFOHEADER;
	unsigned char *imagedata = NULL;//图片的像素信息
	unsigned char* img_pixels=NULL;//目的指针 因为最终使用char所以这里用char
	int img_pixel_offset=0;//pixel的偏移量，一张图片的偏移量
	unsigned char* s_fill=NULL; //填充的字节
	int ss=0;//填充字节数
	bool is_success_exc=true;

	double ProgressValue=0;

	for (int i=0;i<file_count;i++)
	{
		if(this->m_ProgressMethod!=NULL){
			ProgressValue=((double)i+1)/((double)file_count);
			this->m_ProgressMethod(&ProgressValue);
		}

		const char* strFile=this->_getFileName(i);//读取位图文件
		fpi=new ifstream(strFile,std::ios_base::binary);
		if(fpi->is_open()){
			fpi->read(reinterpret_cast<char *>(strHead),sizeof(BITMAPFILEHEADER));//读文件头
			if(0x4d42!=strHead->bfType){//不是bmp
				mvtkDebugMessage(strFile<<" is not a bmp file!");
				is_success_exc=false;
				break;//遇到错误直接退出
			}
			fpi->read(reinterpret_cast<char *>(strInfo),sizeof(BITMAPINFOHEADER));//读信息头
			if(strInfo->biClrUsed>0){//读取调色板
				RGBQUAD* strPla=new RGBQUAD[strInfo->biClrUsed*sizeof(RGBQUAD)];
				fpi->read(reinterpret_cast<char *>(strPla),strInfo->biClrUsed * sizeof(RGBQUAD));
				delete strPla;
			}
			ss= strHead->bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER)-strInfo->biClrUsed*sizeof(RGBQUAD);//偏移量计算
			if(ss>0){
				s_fill=new unsigned char[ss];
				fpi->read(reinterpret_cast<char *>(s_fill),ss);
				delete s_fill;
			}
			
			imagedata =new unsigned char[strInfo->biSizeImage];//读像素数据 根据文件信息头来 别用长宽算
			fpi->read(reinterpret_cast<char *>(imagedata),strInfo->biSizeImage);//一个char形占8位

			//数组转储
			int ch_num=0;
			switch(strInfo->biBitCount){//1、4、8、16、24、32
				case 1:		ch_num=1;break;//单色 伪彩色
				case 4:		ch_num=1;break;//单色 伪彩色
				case 8:		ch_num=1;break;//单色 伪彩色
				case 16:	ch_num=2;break;//单色 伪彩色
				case 24:	ch_num=3;break;//不支持透明 真彩色
				case 32:	ch_num=4;break;//支持透明
			}

			//临时数组供临时存储 用以后面的图像处理
			unsigned char* pixel=new unsigned char[strInfo->biWidth*strInfo->biHeight*ch_num];

			int img_offset=0,row_offset=strInfo->biBitCount*strInfo->biWidth;//一个字节8位 4字节对齐
			if(row_offset%32){
				row_offset/=32;
				row_offset+=1;
			}else{
				row_offset/=32;
			}
			row_offset*=4;

			for (int h=0;h<strInfo->biHeight;h++){
				if (strInfo->biBitCount>=8){
					memcpy(pixel,imagedata+img_offset,strInfo->biWidth*ch_num);//读取一行
				}else{//每位进行赋值 这种先不支持 支持有点没意义
					mvtkDebugMessage(strFile<<" Temporarily unsupported file types.");
					is_success_exc=false;
					return;//遇到错误直接退出
				}
				img_offset+=row_offset;
			}

			int d_w=strInfo->biWidth,d_h=strInfo->biHeight;
			unsigned char* d_pixel=NULL;
			d_pixel=pixel;

			//调用外部函数进行图像处理 可以缩小图像之类
			if(this->m_ImgProgressMethod!=NULL){
				this->m_ImgProgressMethod(pixel,d_pixel,MVTK_UNSIGNED_CHAR,strInfo->biWidth,strInfo->biHeight,d_w,d_h);
			}

			if(img_pixels!=NULL){
				img_pixels+=img_pixel_offset;//放在前面 则第一次的偏移量为0
			}

			if(!this->m_OutData->GetIsInitialize()){//初始化工作
				this->m_OutData->SetChannelNum(ch_num);
				this->m_OutData->SetTimeInterval(1);//时间维度先设置为1 这个我还没想好怎样实现
				this->m_OutData->SetImageNum(file_count);
				this->m_OutData->SetHeight(d_h);
				this->m_OutData->SetWidth(d_w);
				this->m_OutData->SetDataTypeToUnsignedChar(); //要先设置类型才能进行下面的初始化 **注意**
				this->m_OutData->Initialize();//设置完长宽高，颜色维度，时间维度 和数据类型 才能初始化

				img_pixels=(unsigned char*)this->m_OutData->GetData();//初始化指针
				img_pixel_offset=d_h*d_w*ch_num;//计算偏移量
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
		}else{//文件打开错误
			mvtkDebugMessage(strFile<<" file open error!");
			is_success_exc=false;
			return;//遇到错误直接退出
		}
		if(fpi!=NULL){
			delete fpi;
			fpi=NULL;
		}
		delete[] imagedata;
		imagedata = NULL;
	}//for循环结束

	if(!is_success_exc){//不成功则清空数据
		this->m_OutData->Delete();
		this->m_OutData=mvtkVolume::New();
	}

	delete strHead;
	delete strInfo;

	if(this->m_EndMethod!=NULL){
		this->m_EndMethod();
	}
}