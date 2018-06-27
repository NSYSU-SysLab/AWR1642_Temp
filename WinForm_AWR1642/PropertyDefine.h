#pragma once
#define CmdSerialPortBaudRate  115200
#define DataSerialPortBaudRate 921600
#define DATA_PORT_QUEUE_SIZE  40480
#define MMWDEMO_OUTPUT_MSG_SEGMENT_LEN 32
#include <stdint.h>

/*!
* @brief
*  Message header for reporting detection information from data path.
*
* @details
*  The structure defines the message header.
*/
struct DataPacketHeadStruct
{
	uint16_t magicNo[4];  /*! @brief   Output buffer magic word */
	uint32_t version; 
	uint32_t TotalPacketLen;/*! @brief   Total packet length including header in Bytes */
	uint32_t Platform; /*! @brief   platform type */
	uint32_t FrameNumber; /*! @brief   Frame number */
	uint32_t TimeCpuCycles;
	uint32_t NumDetectedObj;
	uint32_t NumTLVs;

};
/*!
* @brief
* Structure holds message stats information from data path.
*
* @details
*  The structure holds stats information. This is a payload of the TLV message item
*  that holds stats information.
*/
struct MmwDemo_output_message_stats
{
	/*! @brief   Interframe processing time in usec */
	uint32_t     interFrameProcessingTime;

	/*! @brief   Transmission time of output detection informaion in usec */
	uint32_t     transmitOutputTime;

	/*! @brief   Interframe processing margin in usec */
	uint32_t     interFrameProcessingMargin;

	/*! @brief   Interchirp processing margin in usec */
	uint32_t     interChirpProcessingMargin;

	/*! @brief   CPU Load (%) during active frame duration */
	uint32_t     activeFrameCPULoad;

	/*! @brief   CPU Load (%) during inter frame duration */
	uint32_t     interFrameCPULoad;

};

/*!
* @brief
* Structure holds information about detected objects.
*
* @details
* This information is sent in front of the array of detected objects
*/
struct MmwDemo_output_message_dataObjDescr
{
	/*! @brief   Number of detected objects */
	uint16_t     numDetetedObj;

	/*! @brief   Q format of detected objects x/y/z coordinates */
	uint16_t     xyzQFormat;

} ;

/**
* @brief
*  Message for reporting detected objects from data path.
*
* @details
*  The structure defines the message body for detected objects from from data path.
*/
struct MmwDemo_output_message_TLV
{
	/*! @brief   TLV type */
	uint32_t    type;

	/*! @brief   Length in bytes */
	uint32_t    length;

} ;
/*!
* @brief
*  Message types used in Millimeter Wave Demo for the communication between
*  target and host, and also for Mailbox communication
*  between MSS and DSS on the XWR16xx platform. Message types are used to indicate
*  different type detection information sent out from the target.
*
*/
enum MmwDemo_message_type
{
	/*! @brief   List of detected points */
	MMWDEMO_OUTPUT_MSG_DETECTED_POINTS = 1,
	/*! @brief   Range profile */
	MMWDEMO_OUTPUT_MSG_RANGE_PROFILE,
	/*! @brief   Noise floor profile */
	MMWDEMO_OUTPUT_MSG_NOISE_PROFILE,
	/*! @brief   Samples to calculate static azimuth  heatmap */
	MMWDEMO_OUTPUT_MSG_AZIMUT_STATIC_HEAT_MAP,
	/*! @brief   Range/Doppler detection matrix */
	MMWDEMO_OUTPUT_MSG_RANGE_DOPPLER_HEAT_MAP,
	/*! @brief   Stats information */
	MMWDEMO_OUTPUT_MSG_STATS,

	MMWDEMO_OUTPUT_MSG_MAX

};
struct MMWProfileCfg
{
	 unsigned int dfeDataOutputMode;
	 unsigned int NumOf_Rx;
	 unsigned int NumOf_Tx;
	 
	 unsigned int ADCBits;
	 unsigned int ADCOutputFormat;
	 unsigned char ADCInputFormat;
	 unsigned char  ADCInputIQ;
	 unsigned char  ADCInputInterleaved;
	 unsigned char  ADCInputChirpThreshold;
	 unsigned int StartFreq;
	 unsigned int IdleTime;
	 unsigned int ADCStartTime;
	 double RampEndTime;
	 unsigned int TXOutputPower;
	 unsigned int TXPhaseShift;
	 unsigned int FrequencySlop;
	 unsigned int TXStartTime;
	 unsigned int ADCSamples;
	 unsigned int ADCSampleFreq;
	 unsigned int HPF1;
	 unsigned int HPF2;
	 unsigned int RXGain;
	 unsigned int RangeFFTSize;
	 unsigned char FrameChirpStartIndex;
	 unsigned char FrameChirpEndIndex;
	 unsigned char	 FrameChirpNumber;
	 unsigned char FrameNumbers;
	  double FramePeriod;
	 unsigned char	 FrameTriggered;
	 unsigned char FrameTriggerDelay;
};
public struct ObjStruct
{
	uint16_t RangeIndex;
	uint16_t DopplerIndex;
	uint16_t PeakValue;
	short x, y, z;
};
public struct ObjDataStruct
{
	
	 unsigned short RangeIndex;
	 unsigned short DopplerIndex;
	 float r;
	 float thetaH; //Horizontal Theta
	 float thetaV; //Vertical Theta
	 float rcs;
	 float vr;
	 float vx, vy, vz;
	 float x, y, z;
	
};
struct Complex
{
	short img;
	short real;
};
int RangeFFTSize, DopplerFFTSize;
/**********************/
float *RangeProfile;
float* NoiseProfile;
Complex * AzimuthHeatmap;
unsigned char *RangeDopplerHeatmap;
ObjDataStruct* ObjData;
DataPacketHeadStruct header;
/*********************************/