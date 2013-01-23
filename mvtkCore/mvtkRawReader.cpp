#include "mvtkRawReader.h"
#include "mvtkVolume.h"

mvtkRawReader::mvtkRawReader(void)
{
}

mvtkRawReader::~mvtkRawReader(void)
{
}
void mvtkRawReader::SetWidth(int w)
{
	this->w=w;
}
void mvtkRawReader::SetHeight(int h)
{
	this->h=h;
}
void mvtkRawReader::Update()
{
	if(this->m_StartMethod!=NULL){
		this->m_StartMethod();
	}
	this->SortFileNames();
	int file_count=this->_getFileCount();
	unsigned char* img_pixels=NULL;
	int img_pixel_offset=0;
	int ch_num=3;
	unsigned char* pixel=new unsigned char[this->w*this->h*ch_num];
	for(int i=0 ; i < file_count; i++ ){
		if(this->m_ProgressMethod!=NULL){
			double ProgressValue=((double)i+1)/((double)file_count);
			this->m_ProgressMethod(&ProgressValue);
		}
		const char* strFile=_getFileName(i);
		ifstream* fpi=NULL;
		fpi=new ifstream(strFile,std::ios_base::binary);
		//FILE* infile=fopen(strFile,"rb");
		if(!fpi->is_open()){
			mvtkDebugMessage("can't open "<<strFile);
			return ;
		}

		int numOfPiexl=this->w*this->h;
		int count=numOfPiexl;

		for(int c=0;c<ch_num;c++){
			for(int i=0;i<numOfPiexl;i++){
				fpi->read(reinterpret_cast<char *>(&pixel[i*ch_num + c]),sizeof(unsigned char));
			}
		}

		unsigned char* d_pixel=pixel;
		int d_w=this->w , d_h=this->h;
		if(this->m_ImgProgressMethod){
			this->m_ImgProgressMethod(pixel,d_pixel,MVTK_UNSIGNED_CHAR,d_w,d_h,d_w,d_h);
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
		if(d_pixel!=NULL&&d_pixel!=pixel){
			delete[] d_pixel;
			d_pixel=NULL;
		}
	}
	delete []pixel;

	if(this->m_EndMethod!=NULL){
		this->m_EndMethod();
	}

}