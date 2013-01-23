#include "mvtkJPGReader.h"
#include "mvtkVolume.h"
#include <stdio.h>
extern "C" {
#include "mvtk_utilities/jpeg/jpeglib.h"
#include <setjmp.h>
}
mvtkJPGReader::mvtkJPGReader(void)
{

}

mvtkJPGReader::~mvtkJPGReader(void)
{

}

struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}




void mvtkJPGReader::Update()
{
	if(this->m_StartMethod!=NULL){
		this->m_StartMethod();
	}
	this->SortFileNames();
	int file_count=this->_getFileCount();

  struct jpeg_decompress_struct cinfo;
  
  struct my_error_mgr jerr;
  /* More stuff */
  FILE * infile;		/* source file */
  JSAMPARRAY buffer;		/* Output row buffer */
  unsigned char* img_pixels=NULL;
  int img_pixel_offset=0;


  for(int i=0 ; i < file_count; i++) {

	  if(this->m_ProgressMethod!=NULL){
			double ProgressValue=((double)i+1)/((double)file_count);
			this->m_ProgressMethod(&ProgressValue);
	  }

	  const char* strFile=this->_getFileName(i);//读取位图文件

	  if ((infile = fopen(strFile, "rb")) == NULL) {
		mvtkDebugMessage("can't open "<<strFile);
		return ;
	  }

	  /* Step 1: allocate and initialize JPEG decompression object */

	  /* We set up the normal JPEG error routines, then override error_exit. */
	  cinfo.err = jpeg_std_error(&jerr.pub);
	  jerr.pub.error_exit = my_error_exit;
	  /* Establish the setjmp return context for my_error_exit to use. */
	  if (setjmp(jerr.setjmp_buffer)) {
		/* If we get here, the JPEG code has signaled an error.
		 * We need to clean up the JPEG object, close the input file, and return.
		 */
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return ;
	  }
	  jpeg_create_decompress(&cinfo);


	  jpeg_stdio_src(&cinfo, infile);


	  (void) jpeg_read_header(&cinfo, TRUE);
	  (void) jpeg_start_decompress(&cinfo);
	
	  int row_stride = cinfo.output_width * cinfo.output_components;
	  /* Make a one-row-high sample array that will go away when done with image */
	  buffer = (*cinfo.mem->alloc_sarray)
			((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, cinfo.output_height);

	 
	  JDIMENSION readLineNum=0;
	  while(readLineNum < cinfo.output_height){
		  readLineNum+=jpeg_read_scanlines(&cinfo, buffer+readLineNum, cinfo.output_height-readLineNum);
	  }
	  unsigned char* pixel=(unsigned char*)buffer[0];
	  unsigned char* d_pixel=NULL;
	  d_pixel=pixel;
	  int d_w=cinfo.output_width , d_h=cinfo.output_height;
	  if(this->m_ImgProgressMethod!=NULL){
		  this->m_ImgProgressMethod(pixel,d_pixel,MVTK_UNSIGNED_CHAR,cinfo.output_width,cinfo.output_height,d_w,d_h);
	  }

	  if(img_pixels!=NULL){
		  img_pixels+=img_pixel_offset;//放在前面 则第一次的偏移量为0
	  }

	  int ch_num=cinfo.output_components;
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

	  (void) jpeg_finish_decompress(&cinfo);
	 
	  jpeg_destroy_decompress(&cinfo);


	  fclose(infile);

	  if(d_pixel!=NULL&&d_pixel!=pixel){
		  delete[] d_pixel;
		  d_pixel=NULL;
	  }
  }

  if(this->m_EndMethod!=NULL){
	  this->m_EndMethod();
  }
  
}