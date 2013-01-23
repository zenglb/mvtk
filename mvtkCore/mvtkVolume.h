#ifndef __mvtkVolume_h
#define __mvtkVolume_h

#include "mvtkDataObject.h"

class MVTK_COMMON_API mvtkVolume : public mvtkDataObject
{
public:
	MVTK_TYPE(mvtkVolume, mvtkDataObject)

	virtual void PrintSelf(ostream& os){};

	///////////////////////////////////////////////////////////////////////////
	/// Delete the allocated memory (if any) and initialize to default status.
	///////////////////////////////////////////////////////////////////////////
	void Initialize();

	///////////////////////////////////////////////////////////////////////////
	/// Return the data object type.
	/// \return Always return MVTK_VOLUME
	///////////////////////////////////////////////////////////////////////////
	virtual int GetDataObjectType() const { return MVTK_VOLUME; }

	///////////////////////////////////////////////////////////////////////////
	/// Set dimension in x, y, z direction of this volume.
	/// \param dims[0] the dimension in x direction
	/// \param dims[1] the dimension in y direction
	/// \param dims[2] the dimension in z direction
	///////////////////////////////////////////////////////////////////////////
	void SetDimensions(int dims[4])
	{
		m_Dimensions[0] = dims[0];
		m_Dimensions[1] = dims[1];
		m_Dimensions[2] = dims[2];
		m_Dimensions[3] = dims[3];//t 时间
		this->_computeIncrements();
	}

	///////////////////////////////////////////////////////////////////////////
	/// Get dimension in x, y, z direction of this volume.
	/// \param dims[0] Return the dimension in x direction. It is equal to
	/// the return value of GetWidth()
	/// \param dims[1] Return the dimension in y direction. It is equal to
	/// the return value of GetHeight()
	/// \param dims[2] Return the dimension in z direction. It is equal to
	/// the return value of GetSliceNum()
	///////////////////////////////////////////////////////////////////////////
	void GetDimensions(int dims[3]) const 
	{
		dims[0] = m_Dimensions[0];
		dims[1] = m_Dimensions[1];
		dims[2] = m_Dimensions[2];
		dims[3] = m_Dimensions[3];
	}

	///////////////////////////////////////////////////////////////////////////
	/// Set the width of this volume (dimension in x).
	/// \param w The width of this volume, the unit is pixel.	
	///////////////////////////////////////////////////////////////////////////
	void SetWidth(int w) { m_Dimensions[0] = w; this->_computeIncrements(); }

	///////////////////////////////////////////////////////////////////////////
	/// Get the width of this volume (dimension in x).
	/// \return Return the width of this volume, the unit is pixel.	
	///////////////////////////////////////////////////////////////////////////    
	int GetWidth() const { return m_Dimensions[0]; }

	///////////////////////////////////////////////////////////////////////////
	/// Set the height of this volume (dimension in y).
	/// \param h The height of this volume, the unit is pixel.	
	///////////////////////////////////////////////////////////////////////////
	void SetHeight(int h) { m_Dimensions[1] = h; this->_computeIncrements(); }

	///////////////////////////////////////////////////////////////////////////
	/// Get the height of this volume (dimension in y).
	/// \return Return the height of this volume, the unit is pixel.	
	///////////////////////////////////////////////////////////////////////////
	int GetHeight() const { return m_Dimensions[1]; }

	///////////////////////////////////////////////////////////////////////////
	/// Set the slice/image number of this volume (dimension in z).
	/// \param s The image/slice number of this volume.	
	///////////////////////////////////////////////////////////////////////////
	void SetSliceNum(int s) { m_Dimensions[2] = s; }

	///////////////////////////////////////////////////////////////////////////
	/// Provided for convenience, just the same as SetSliceNum().
	///////////////////////////////////////////////////////////////////////////
	void SetImageNum(int s) { this->SetSliceNum(s); }

	///////////////////////////////////////////////////////////////////////////
	/// Get the slice/image number of this volume (dimension in z).
	/// \return Return the image/slice number of this volume.	
	///////////////////////////////////////////////////////////////////////////
	int  GetSliceNum() const { return m_Dimensions[2]; }

	///////////////////////////////////////////////////////////////////////////
	/// Provided for convenience, just the same as GetSliceNum().
	///////////////////////////////////////////////////////////////////////////
	int  GetImageNum() const { return this->GetSliceNum(); }

	void  SetTimeInterval(int s) { m_Dimensions[3]=s; this->_computeIncrements(); }
	int  GetTimeInterval() const { return m_Dimensions[3]; }

	///////////////////////////////////////////////////////////////////////////
	/// Get the dimension of this volume.
	/// return 2 --- 2D image \n
	/// return 3 --- 3D image \n
	///////////////////////////////////////////////////////////////////////////
	int  GetDimensionality() const 
	{ 
		if (m_Dimensions[2]==1)
		{
			return 2;
		} 
		else if(m_Dimensions[3]==1)
		{
			return 3;
		}else{
			return 4;//4d 包括时间
		}
	}

	///////////////////////////////////////////////////////////////////////////
	/// Set spacing information in x, y and z axis, the unit is mm.
	/// \param s[0] the spacing (mm) in two adjacent voxels in x axis.
	/// \param s[1] the spacing (mm) in two adjacent voxels in y axis.
	/// \param s[2] the spacing (mm) in two adjacent voxels in z axis.
	///////////////////////////////////////////////////////////////////////////
	void SetSpacings(float s[4])
	{
		m_Spacings[0] = s[0];
		m_Spacings[1] = s[1];
		m_Spacings[2] = s[2];
		m_Spacings[3] = s[3];//时间
	}

	///////////////////////////////////////////////////////////////////////////
	/// Get spacing information in x, y and z axis, the unit is mm.
	/// \param s[0] Return the spacing (mm) in two adjacent voxels in x axis.
	/// It is equal to the return value of GetSpacingX()
	/// \param s[1] Return the spacing (mm) in two adjacent voxels in y axis.
	/// It is equal to the return value of GetSpacingY()
	/// \param s[2] Return the spacing (mm) in two adjacent voxels in z axis.
	/// It is equal to the return value of GetSpacingZ()
	///////////////////////////////////////////////////////////////////////////
	void GetSpacings(float s[4]) const 
	{
		s[0] = m_Spacings[0];
		s[1] = m_Spacings[1];
		s[2] = m_Spacings[2];
		s[3] = m_Spacings[3];//t
	}

	///////////////////////////////////////////////////////////////////////////
	/// Set spacing information in x axis, the unit is mm.
	/// \param px the spacing (mm) in two adjacent voxels in x axis.
	///////////////////////////////////////////////////////////////////////////
	void SetSpacingX(float px) { m_Spacings[0] = px; }

	///////////////////////////////////////////////////////////////////////////
	/// Get spacing information in x axis, the unit is mm.
	/// \return Return the spacing (mm) in two adjacent voxels in x axis.
	///////////////////////////////////////////////////////////////////////////
	float GetSpacingX() const { return m_Spacings[0]; }

	///////////////////////////////////////////////////////////////////////////
	/// Set spacing information in y axis, the unit is mm.
	/// \param py the spacing (mm) in two adjacent voxels in y axis.
	///////////////////////////////////////////////////////////////////////////
	void SetSpacingY(float py) { m_Spacings[1] = py; }

	///////////////////////////////////////////////////////////////////////////
	/// Get spacing information in y axis, the unit is mm.
	/// \return Return the spacing (mm) in two adjacent voxels in y axis.
	///////////////////////////////////////////////////////////////////////////
	float GetSpacingY() const { return m_Spacings[1]; }

	///////////////////////////////////////////////////////////////////////////
	/// Set spacing information in z axis, the unit is mm.
	/// \param pz the spacing (mm) in two adjacent voxels in z axis.
	///////////////////////////////////////////////////////////////////////////
	void SetSpacingZ(float pz) { m_Spacings[2] = pz; }

	///////////////////////////////////////////////////////////////////////////
	/// Get spacing information in z axis, the unit is mm.
	/// \return Return the spacing (mm) in two adjacent voxels in z axis.
	///////////////////////////////////////////////////////////////////////////
	float GetSpacingZ() const { return m_Spacings[2]; }
	
	float GetSpacingT() const { return m_Spacings[3]; }
	void SetSpacingT(float pz) { m_Spacings[3] = pz; }

	///////////////////////////////////////////////////////////////////////////
	/// Set the channel number of this volume.
	/// \param n The channel number of this volume. \n
	/// n = 1 --- gray image \n
	/// n = 3 --- RGB image \n
	/// n = 4 --- RGBA image \n
	///////////////////////////////////////////////////////////////////////////
	void SetChannelNum(int n) { m_NumberOfChannel = n; this->_computeIncrements(); }

	///////////////////////////////////////////////////////////////////////////
	/// Just the same as SetChannelNum().
	///////////////////////////////////////////////////////////////////////////
	void SetNumberOfChannel(int n) { this->SetChannelNum(n); }

	///////////////////////////////////////////////////////////////////////////
	/// Get the channel number of this volume.
	/// \return Return the channel number of this volume. \n
	/// return 1 --- gray image \n
	/// return 3 --- RGB image \n
	/// return 4 --- RGBA image \n
	///////////////////////////////////////////////////////////////////////////
	int GetChannelNum() const { return m_NumberOfChannel; }

	///////////////////////////////////////////////////////////////////////////
	/// Just the same as GetChannelNum().
	///////////////////////////////////////////////////////////////////////////
	int GetNumberOfChannel() const { return this->GetChannelNum(); }

	///////////////////////////////////////////////////////////////////////////
	/// Get the increments in x, y and z directions.
	/// \param incs[0] the increment in x directions. It is equal to the 
	/// return value of GetIncrementX()
	/// \param incs[1] the increment in y directions. It is equal to the 
	/// return value of GetIncrementY()
	/// \param incs[2] the increment in z directions. It is equal to the 
	/// return value of GetIncrementZ()	
	///////////////////////////////////////////////////////////////////////////
	void GetIncrements(int incs[3]) const //遍历时候使用，因为是线性存储的
	{
		incs[0] = m_Increments[0];
		incs[1] = m_Increments[1];
		incs[2] = m_Increments[2];
		incs[3] = m_Increments[3];
	}

	///////////////////////////////////////////////////////////////////////////
	/// Get the increment in x direction.
	/// \return Return the increment in x direction. If the channel number
	/// is channelNum, then the return value is channelNum.
	/// \note This function is provided for the convenient traversal of 
	/// the volume. It doesn't take data type of the volume into account.
	/// So if you get the data of a volume in void* form, you must convert
	/// it to unsigned char*, and the increment must multiply Sizeof(data 
	/// type of volume).   
	///////////////////////////////////////////////////////////////////////////
	int GetIncrementX() const { return m_Increments[0]; }

	///////////////////////////////////////////////////////////////////////////
	/// Get the increment in y direction.
	/// \return Return the increment in y direction. If the channel number
	/// is channelNum, then the return value is channelNum * widthOfVolume.
	/// \note This function is provided for the convenient traversal of 
	/// the volume. It doesn't take data type of the volume into account.
	/// So if you get the data of a volume in void* form, you must convert
	/// it to unsigned char*, and the increment must multiply Sizeof(data 
	/// type of volume).   
	///////////////////////////////////////////////////////////////////////////
	int GetIncrementY() const { return m_Increments[1]; }

	///////////////////////////////////////////////////////////////////////////
	/// Get the increment in z direction.
	/// \return Return the increment in z direction. If the channel number
	/// is channelNum, then the return value is channelNum * widthOfVolume
	/// * heightOfVolume.
	/// \note This function is provided for the convenient traversal of 
	/// the volume. It doesn't take data type of the volume into account.
	/// So if you get the data of a volume in void* form, you must convert
	/// it to unsigned char*, and the increment must multiply Sizeof(data 
	/// type of volume).   
	///////////////////////////////////////////////////////////////////////////
	int GetIncrementZ() const { return m_Increments[2]; }
	//时间轴的间隔
	int GetIncrementT() const { return m_Increments[3]; }

	///////////////////////////////////////////////////////////////////////////
	/// Get value of a specified voxel's channel.
	/// \param x the x-coordinate of the voxel in the volume space (in [0, GetWidth()-1])
	/// \param y the y-coordinate of the voxel in the volume space (in [0, GetHeight()-1])
	/// \param z the y-coordinate of the voxel in the volume space (in [0, GetImageNum()-1])
	/// \param c the channel of the specified voxel (in [0, GetChannelNum()-1])
	/// \return Return the value of the specified voxel's channel in double data type.
	/// \note It is a safe but slow function. Use it carefully if you are
	///       concerned about the efficiency.
	///////////////////////////////////////////////////////////////////////////
	double GetData(int x, int y, int z,int t, int c = 0,bool check_bounds=true);

	///////////////////////////////////////////////////////////////////////////
	/// Get data pointer of the volume data (changeable). 
	/// \return Return a void pointer to data.
	/// \note The returned type is void *, it must be converted to some
	///       useful data type according to the return value of GetDataType().
	/// \warning The memory is deleted by destructor automatically, so
	///          clients shouldn't delete the pointer returned by this function.
	///////////////////////////////////////////////////////////////////////////
	void* GetData(){return this->m_Data;}

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume. MVTK supports various data type.
	/// \param data_type Its valid value and meaning is shown as follows:\n
	/// MVTK_CHAR            The data type is char \n
	/// MVTK_UNSIGNED_CHAR   The data type is unsigned char \n
	/// MVTK_SHORT           The data type is short \n
	/// MVTK_UNSIGNED_SHORT  The data type is unsigned short \n
	/// MVTK_INT             The data type is int \n
	/// MVTK_UNSIGNED_INT    The data type is unsigned int \n
	/// MVTK_LONG            The data type is long \n
	/// MVTK_UNSIGNED_LONG   The data type is unsigned long \n
	/// MVTK_FLOAT           The data type is float \n
	/// MVTK_DOUBLE          The data type is double \n
	///////////////////////////////////////////////////////////////////////////
	void SetDataType(int data_type){this->m_DataType=data_type;}

	///////////////////////////////////////////////////////////////////////////
	/// Get data type of this volume. MVTK supports various data type.
	/// \return All of the return values and their meaning are shown as follows:\n
	/// MVTK_CHAR            The data type is char \n
	/// MVTK_UNSIGNED_CHAR   The data type is unsigned char \n
	/// MVTK_SHORT           The data type is short \n
	/// MVTK_UNSIGNED_SHORT  The data type is unsigned short \n
	/// MVTK_INT             The data type is int \n
	/// MVTK_UNSIGNED_INT    The data type is unsigned int \n
	/// MVTK_LONG            The data type is long \n
	/// MVTK_UNSIGNED_LONG   The data type is unsigned long \n
	/// MVTK_FLOAT           The data type is float \n
	/// MVTK_DOUBLE          The data type is double \n
	///////////////////////////////////////////////////////////////////////////
	int GetDataType() const { return m_DataType; }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to float.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToFloat() { this->SetDataType(MVTK_FLOAT); }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to double.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToDouble() { this->SetDataType(MVTK_DOUBLE); }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to int.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToInt() { this->SetDataType(MVTK_INT); }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to unsigned int.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToUnsignedInt()	{ this->SetDataType(MVTK_UNSIGNED_INT); }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to long.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToLong() { this->SetDataType(MVTK_LONG); }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to unsigned long.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToUnsignedLong() { this->SetDataType(MVTK_UNSIGNED_LONG); }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to short.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToShort() { this->SetDataType(MVTK_SHORT); }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to unsigned short.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToUnsignedShort() { this->SetDataType(MVTK_UNSIGNED_SHORT); }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to unsigned char.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToUnsignedChar() { this->SetDataType(MVTK_UNSIGNED_CHAR); }

	///////////////////////////////////////////////////////////////////////////
	/// Set data type of this volume to char.
	///////////////////////////////////////////////////////////////////////////
	void SetDataTypeToChar() { this->SetDataType(MVTK_CHAR); }

	//获取最大最小值
	void GetMinMaxValue(double &minVal, double &maxVal);

	bool GetIsInitialize(){
		return this->m_IsInitialize;
	}

	//深拷贝函数
	void DeepCopy(mvtkVolume* in_mvtkVolume,bool setDate=false);

protected:
	mvtkVolume(void);
	virtual ~mvtkVolume(void);    
	void _computeIncrements();

	int   m_Dimensions[4];
	int   m_Increments[4];
	float m_Spacings[4];

	int   m_DataType;
	int   m_NumberOfChannel;

	bool m_IsInitialize;

	//m_Data[t][z][y][x][c]  暂时使用这个顺序(时间，图片，高度，宽度，通道)
	//		如果有卡顿需要优化可以改变存储顺序以最大化使用cache  zenglb 2012-11-24 21:09:08
	void *m_Data;

	//获得最大最小值
	template<typename T>
	void t_GetMinMaxValue(T* data,unsigned size,double &minVal, double &maxVal);
//private:
//	mvtkVolume(const mvtkVolume&);
//	void operator=(const mvtkVolume&);

};

//#define DEFINED_mvtkVolume



#endif


