#include "mvtkVolumeContourFilter.h"
#include "mvtkVolume.h"

template <typename T>
void mvtkVolumeContourFilter::_internalVoxelClassify(T *data_ptr, int dimension[3], int *InternalVoxel){
	int i;
	int x,y,z;
	int dimx,dimy,dimz,xinc,yinc,zinc;

	dimx = dimension[0];
	dimy = dimension[1];
	dimz = dimension[2];	

	//高维数组映射到低位数组的单位 zlb
	xinc = 1;
	yinc = dimx;
	zinc = dimx * dimy;
	//乘法缓存 zlb 修改
	int tmp;

	double ProgressValue=0;

	//标记内部体素
	for ( z=0; z < dimz; z++)//片
	{
		if(this->m_ProgressMethod!=NULL){
			ProgressValue=((double)(z+1)/((double)dimz*2));
			this->m_ProgressMethod(&ProgressValue);
		}

		for ( y=0; y < dimy; y++)//行
		{
			for ( x=0; x < dimx; x++)//列
			{



				bool CompareVoxel[27]={false};//zlb 优化 //27 想到3x3x3的体型 像素周边 zlb
				//zlb 优化 每个点 节省2*2*27次乘法
				tmp=z*zinc+y*yinc+x;
				InternalVoxel[tmp] = 1;

				CompareVoxel[13] = true;

				//边界情况处理 zlb
				if (x == 0)
				{
					CompareVoxel[0] = CompareVoxel[3] = CompareVoxel[6] = true;
					CompareVoxel[9] = CompareVoxel[12] = CompareVoxel[15] = true;
					CompareVoxel[18] = CompareVoxel[21] = CompareVoxel[24] = true;
				}
				if (x == dimx-1)
				{
					CompareVoxel[2] = CompareVoxel[5] = CompareVoxel[8] = true;
					CompareVoxel[11] = CompareVoxel[14] = CompareVoxel[17] = true;
					CompareVoxel[20] = CompareVoxel[23] = CompareVoxel[26] = true;
				}
				if (y == 0)
				{
					CompareVoxel[0] = CompareVoxel[1] = CompareVoxel[2] = true;
					CompareVoxel[9] = CompareVoxel[10] = CompareVoxel[11] = true;
					CompareVoxel[18] = CompareVoxel[19] = CompareVoxel[20] = true;
				}
				if (y == dimy-1)
				{
					CompareVoxel[6] = CompareVoxel[7] = CompareVoxel[8] = true;
					CompareVoxel[15] = CompareVoxel[16] = CompareVoxel[17] = true;
					CompareVoxel[24] = CompareVoxel[25] = CompareVoxel[26] = true;
				}
				if (z == 0)
				{
					CompareVoxel[0] = CompareVoxel[1] = CompareVoxel[2] = true;
					CompareVoxel[3] = CompareVoxel[4] = CompareVoxel[5] = true;
					CompareVoxel[6] = CompareVoxel[7] = CompareVoxel[8] = true;
				}
				if (z == dimz-1)
				{
					CompareVoxel[18] = CompareVoxel[19] = CompareVoxel[20] = true;
					CompareVoxel[21] = CompareVoxel[22] = CompareVoxel[23] = true;
					CompareVoxel[24] = CompareVoxel[25] = CompareVoxel[26] = true;
				}

				//判断是否为“内点”通过对旁边一个点比较判定 zlb
				for (i = 0;i < 27;i++)
				{
					if (!CompareVoxel[i])
					{
						switch(i)
						{
						case 0:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-zinc-yinc-1]);
							break;
						case 1:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-zinc-yinc]);
							break;
						case 2:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-zinc-yinc+1]);
							break;
						case 3:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-zinc-1]);
							break;
						case 4:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-zinc]);
							break;
						case 5:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-zinc+1]);
							break;
						case 6:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-zinc+yinc-1]);
							break;
						case 7:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-zinc+yinc]);
							break;
						case 8:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-zinc+yinc+1]);
							break;
						case 9:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-yinc-1]);
							break;
						case 10:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-yinc]);
							break;
						case 11:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-yinc+1]);
							break;
						case 12:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp-1]);
							break;
						case 13:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp]);
							break;
						case 14:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+1]);
							break;
						case 15:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+yinc-1]);
							break;
						case 16:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+yinc]);
							break;
						case 17:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+yinc+1]);
							break;
						case 18:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+zinc-yinc-1]);
							break;
						case 19:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+zinc-yinc]);
							break;
						case 20:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+zinc-yinc+1]);
							break;
						case 21:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+zinc-1]);
							break;
						case 22:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+zinc]);
							break;
						case 23:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+zinc+1]);
							break;
						case 24:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+zinc+yinc-1]);
							break;
						case 25:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+zinc+yinc]);
							break;
						case 26:
							CompareVoxel[i] = (data_ptr[tmp] == data_ptr[tmp+zinc+yinc+1]);
							break;
						}												  
					}

					if(!CompareVoxel[i])
					{
						InternalVoxel[z*zinc+y*yinc+x] = 0;
						break;
					}
				}
			}
		}
	}
}

template <typename T>
void mvtkVolumeContourFilter::_execute(T *data_ptr,mvtkVolume* in_data){
	if(in_data->GetNumberOfChannel()!=1){
		mvtkDebugMessage("Invalid channel num, only accept 1.");
		return;
	}

	int x,y,z,dimx,dimy,dimz;

	int DataDimention[3];
	in_data->GetDimensions(DataDimention);

	dimx = DataDimention[0];
	dimy = DataDimention[1];
	dimz = DataDimention[2];

	double ProgressValue=0;

	int* InternalVoxel=new int[dimx*dimy*dimz];//内部体素的标记数组

	int base_count=dimz/2;

	//标记三维内点 zlb
	this->_internalVoxelClassify(data_ptr, DataDimention, InternalVoxel);

	//循环进行后续处理
	for (z = 0;z < dimz;z++)//片
	{
		if(this->m_ProgressMethod!=NULL){
			ProgressValue=((double)((z+1)+base_count)/((double)dimz*2));
			this->m_ProgressMethod(&ProgressValue);
		}

		for (y = 0;y< dimy;y++)//行
		{
			for (x = 0;x < dimx;x++)//列
			{
				if ((InternalVoxel[z*dimx*dimy+y*dimx+x] == 1) && (data_ptr[z*dimx*dimy+y*dimx+x] != (unsigned char)69))
				{
					data_ptr[z*dimx*dimy+y*dimx+x] = (unsigned char)0;
				}
				if ((InternalVoxel[z*dimx*dimy+y*dimx+x] == 0) && (data_ptr[z*dimx*dimy+y*dimx+x] == (unsigned char)69))
				{
					data_ptr[z*dimx*dimy+y*dimx+x] = (unsigned char)71;
				}
			}
		}
	}
	delete[] InternalVoxel;

}