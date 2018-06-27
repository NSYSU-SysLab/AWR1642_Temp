#pragma once
#include"PropertyDefine.h"
#include <Windows.h>  
#include<fstream>
#include<cmath>
#include<complex>
#define _USE_MATH_DEFINES

MMWProfileCfg  MMWCfg;
namespace WinForm_AWR1642 {

	using namespace std; 
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
			ComPortRefresh();
			comBox_CmdCOM->Text = "COM3";
			comBox_DataCOM->Text = "COM4";
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  comBox_CmdCOM;
	private:Thread ^thread;
	protected:
	private:System::String^fileName="profile.cfg";
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  Btn_Start;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::IO::Ports::SerialPort^  CmdSerialPort;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  loadFileToolStripMenuItem;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comBox_DataCOM;
	private: System::IO::Ports::SerialPort^  DataSerialPort;
	private: System::Windows::Forms::Timer^  timer1;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->comBox_CmdCOM = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Btn_Start = (gcnew System::Windows::Forms::Button());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->CmdSerialPort = (gcnew System::IO::Ports::SerialPort(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->loadFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comBox_DataCOM = (gcnew System::Windows::Forms::ComboBox());
			this->DataSerialPort = (gcnew System::IO::Ports::SerialPort(this->components));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// comBox_CmdCOM
			// 
			this->comBox_CmdCOM->FormattingEnabled = true;
			this->comBox_CmdCOM->Location = System::Drawing::Point(86, 30);
			this->comBox_CmdCOM->Name = L"comBox_CmdCOM";
			this->comBox_CmdCOM->Size = System::Drawing::Size(121, 23);
			this->comBox_CmdCOM->TabIndex = 0;
			this->comBox_CmdCOM->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comBox_CmdCOM_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(62, 15);
			this->label1->TabIndex = 1;
			this->label1->Text = L"CmdPort:";
			// 
			// Btn_Start
			// 
			this->Btn_Start->Location = System::Drawing::Point(86, 99);
			this->Btn_Start->Name = L"Btn_Start";
			this->Btn_Start->Size = System::Drawing::Size(75, 23);
			this->Btn_Start->TabIndex = 2;
			this->Btn_Start->Text = L"Start";
			this->Btn_Start->UseVisualStyleBackColor = true;
			this->Btn_Start->Click += gcnew System::EventHandler(this, &MyForm::Btn_Start_Click);
			// 
			// chart1
			// 
			chartArea1->AxisX->Interval = 1;
			chartArea1->AxisX->Maximum = 10;
			chartArea1->AxisX->Minimum = -10;
			chartArea1->AxisY->Interval = 1;
			chartArea1->AxisY->Maximum = 10;
			chartArea1->AxisY->Minimum = 0;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(372, 49);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(766, 533);
			this->chart1->TabIndex = 3;
			this->chart1->Text = L"chart1";
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadFileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1161, 27);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// loadFileToolStripMenuItem
			// 
			this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
			this->loadFileToolStripMenuItem->Size = System::Drawing::Size(80, 23);
			this->loadFileToolStripMenuItem->Text = L"LoadFile";
			this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadFileToolStripMenuItem_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 67);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(61, 15);
			this->label2->TabIndex = 1;
			this->label2->Text = L"DataPort:";
			// 
			// comBox_DataCOM
			// 
			this->comBox_DataCOM->FormattingEnabled = true;
			this->comBox_DataCOM->Location = System::Drawing::Point(86, 67);
			this->comBox_DataCOM->Name = L"comBox_DataCOM";
			this->comBox_DataCOM->Size = System::Drawing::Size(121, 23);
			this->comBox_DataCOM->TabIndex = 5;
			this->comBox_DataCOM->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comBox_DataCOM_SelectedIndexChanged);
			// 
			// timer1
			// 
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1161, 606);
			this->Controls->Add(this->comBox_DataCOM);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->Btn_Start);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comBox_CmdCOM);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:void ComPortRefresh(void )
	{
		comBox_CmdCOM->Items->Clear();
		cli::array<System::String^>^ Port = SerialPort::GetPortNames();
		comBox_CmdCOM->Items->AddRange(Port);
		comBox_DataCOM->Items->AddRange(Port);
	}
	private: System::Void loadFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			OpenFileDialog ^opnFileDlg = gcnew OpenFileDialog();
			if (opnFileDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			fileName = opnFileDlg->FileName;
			delete opnFileDlg;
	}
	private: System::Void comBox_CmdCOM_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		CmdSerialPort->Encoding = System::Text::Encoding::GetEncoding(28591);
		CmdSerialPort->PortName = comBox_CmdCOM->Text;
		CmdSerialPort->BaudRate = CmdSerialPortBaudRate;
		CmdSerialPort->Parity = Parity::None;
		CmdSerialPort->DataBits = 8;
		CmdSerialPort->StopBits = StopBits::One;
	}
    private: System::Void Btn_Start_Click(System::Object^  sender, System::EventArgs^  e) {
	CmdSerialPort->Open();
	fstream fp;
	fp.open((char*)(void*)Marshal::StringToHGlobalAnsi(fileName), std::ios::in);

	char line[100];
	while (fp.getline(line, sizeof(line), '\n')) {
		System::String^ str = gcnew String(line);
		
		if (str != "")
		{
			CmdSerialPort->WriteLine(str);
			CmdSerialPort->ReadTo("Done");
			Sleep(100);
			cli::array<String^>^result;
			cli::array<Char>^sep = gcnew cli::array<Char>{ ' ' };
			result=str->Split(sep, StringSplitOptions::RemoveEmptyEntries);
			System::String^ string_temp = result[0];
		
	
			if (result[0] == "dfeDataOutputMode")MMWCfg.dfeDataOutputMode=Convert::ToInt32(result[1]);
			if (result[0] == "channelCfg")
			{
				unsigned char Rx = Convert::ToByte(result[1]);
				unsigned char Tx = Convert::ToByte(result[2]);
				for (uint16_t i = 0; i < 4; i++)
				{
				   unsigned char mask = 0x01;
					mask = mask << i;
					MMWCfg.NumOf_Rx += (Rx & mask)>>i;
					MMWCfg.NumOf_Tx += (Tx & mask) >> i;
				}				
			}
			if (result[0] == "adcCfg")
			{
				MMWCfg.ADCBits = Convert::ToInt16(result[1]);
				MMWCfg.ADCOutputFormat = Convert::ToInt16(result[2]);
			}
			if (result[0] == "adcbufCfg")
			{
				MMWCfg.ADCInputFormat = Convert::ToByte(result[1]);
				MMWCfg.ADCInputIQ = Convert::ToByte(result[2]);
				MMWCfg.ADCInputInterleaved = Convert::ToByte(result[3]);
				MMWCfg.ADCInputChirpThreshold = Convert::ToByte(result[4]);
			}
			if (result[0] == "profileCfg")
			{
				MMWCfg.StartFreq= Convert::ToInt32(result[2]);
				MMWCfg.IdleTime = Convert::ToInt32(result[3]);
				MMWCfg.ADCStartTime = Convert::ToInt32(result[4]);
				MMWCfg.RampEndTime = Convert::ToDouble(result[5]);
				MMWCfg.TXOutputPower = Convert::ToInt32(result[6]);
				MMWCfg.TXPhaseShift = Convert::ToInt32(result[7]);
				MMWCfg.FrequencySlop = Convert::ToDouble(result[8]);
				MMWCfg.TXStartTime = Convert::ToInt32(result[9]);
				MMWCfg.ADCSamples = Convert::ToInt32(result[10]);
				MMWCfg.ADCSampleFreq = Convert::ToDouble(result[11]);
				MMWCfg.HPF1 = Convert::ToInt32(result[12]);
				MMWCfg.HPF2 = Convert::ToInt32(result[13]);
				MMWCfg.RXGain = Convert::ToInt32(result[14]);
				RangeFFTSize = MMWCfg.ADCSamples;
			}
			if (result[0] == "frameCfg")
			{
				MMWCfg.FrameChirpStartIndex = Convert::ToByte(result[1]);
				MMWCfg.FrameChirpEndIndex = Convert::ToByte(result[2]);
				MMWCfg.FrameChirpNumber = Convert::ToByte(result[3]);
				MMWCfg.FrameNumbers = Convert::ToByte(result[4]);
				MMWCfg.FramePeriod = Convert::ToDouble(result[5]);
				MMWCfg.FrameTriggered = Convert::ToByte(result[6]);
				MMWCfg.FrameTriggerDelay = Convert::ToByte(result[7]);
				DopplerFFTSize = MMWCfg.FrameChirpNumber*MMWCfg.NumOf_Rx;
			}
		}
		
		delete str;
		
	}
	DataSerialPort->Open();
	thread = gcnew Thread(gcnew ThreadStart(this, &MyForm::ReadFromRadar));
	thread->Start();
	timer1->Enabled = true;
	timer1->Start();
}
	private:void ReadFromRadar()
	{
	
		/*unsigned char ReadBuffer[DATA_PORT_QUEUE_SIZE] = {0};*/
		
		int ReadSize;
		while (true)
		{
		int ByteCounter;
		cli::array<Byte>^ReadBuf = gcnew cli::array<Byte>(DATA_PORT_QUEUE_SIZE);
		if (DataSerialPort->BytesToRead > 0)
		{	
			ReadSize = DataSerialPort->Read(ReadBuf,0, DATA_PORT_QUEUE_SIZE);
			int a = 999;
		}	
		if (ReadSize > 0)
			{
					
				uint32_t PatternIndex = 88888;//設定一個不可能發生的數值，判斷有沒有收到頭碼
				for (uint16_t i = 0; i < ReadSize; i++)
				{
					if (ReadBuf[i] == 2 && ReadBuf[i + 1] == 1 && ReadBuf[i + 2] == 4 && ReadBuf[i + 3] == 3 && ReadBuf[i + 4] == 6 && ReadBuf[i + 5] == 5 && ReadBuf[i + 6] == 8 && ReadBuf[i + 7] == 7)
					{
						PatternIndex = i;
						break;
					}
				}
				if (PatternIndex != 88888)
				{
				   pin_ptr<System::Byte> p = &ReadBuf[0];
				   unsigned char* ReadBufferIndex = p;
				   ReadBufferIndex +=  PatternIndex;
				   ByteCounter += PatternIndex;

				   memcpy(&header, ReadBufferIndex, sizeof(header));
				   ReadBufferIndex += sizeof(DataPacketHeadStruct);
				   ByteCounter += sizeof(DataPacketHeadStruct);
				   if (header.NumTLVs >= 4) MessageBox::Show("!");
				   for (uint16_t i = 0; i < header.NumTLVs; i++)
				   {
					   MmwDemo_output_message_TLV TLV;
					   memcpy(&TLV, ReadBufferIndex,sizeof(MmwDemo_output_message_TLV));
					   ReadBufferIndex += sizeof(MmwDemo_output_message_TLV);
					   ByteCounter += sizeof(MmwDemo_output_message_TLV);
					   switch (TLV.type)
					   {
					   case MMWDEMO_OUTPUT_MSG_DETECTED_POINTS:
					   { 
						  
						   MmwDemo_output_message_dataObjDescr ObjDescribe;
						   memcpy(&ObjDescribe, ReadBufferIndex,sizeof(MmwDemo_output_message_dataObjDescr));
						   ReadBufferIndex += sizeof(MmwDemo_output_message_dataObjDescr);
						   ByteCounter += sizeof(MmwDemo_output_message_dataObjDescr);
						   float div = (float)1.0 / (1 << ObjDescribe.xyzQFormat);
						    ObjData = new  ObjDataStruct[ObjDescribe.numDetetedObj];
						   for (uint16_t j = 0; j < ObjDescribe.numDetetedObj; j++)
						   {
							  ObjStruct TempObj;
							  memcpy(&TempObj, ReadBufferIndex,sizeof(ObjStruct));
							  ReadBufferIndex += sizeof(ObjStruct);
							  ByteCounter += sizeof(ObjStruct);
							  ObjData[j].RangeIndex = TempObj.RangeIndex;
							  ObjData[j].DopplerIndex = TempObj.DopplerIndex;
							  ObjData[j].x = TempObj.x * div;
							  ObjData[j].y = TempObj.y * div;
							  ObjData[j].z = TempObj.z * div;
							  ObjData[j].r= (float)sqrt(pow(ObjData[j].x, 2) + pow(ObjData[j].y, 2) + pow(ObjData[j].z, 2));
							 
							  ObjData[j].thetaH = (float)atan2(ObjData[j].x ,ObjData[j].y);
							  ObjData[j].thetaV = (float)atan2(ObjData[j].z,ObjData[j].y);
							  ObjData[j].vr = (float)(TempObj.DopplerIndex * 1.0000000000000000);
							  ObjData[j].vx =ObjData[j].vr * (float)sin(ObjData[j].thetaV);
							  ObjData[j].vy =ObjData[j].vr * (float)cos(ObjData[j].thetaV) * (float)sin(ObjData[j].thetaH);
							  ObjData[j].rcs = (float)(TempObj.PeakValue * 1.00000000000000);
						   }
						   
					   }
					   break;
					   
					   case MMWDEMO_OUTPUT_MSG_RANGE_PROFILE:
					   {
						   float div = (float)(1.0 / (1 << 8));
						   unsigned short temp;
						  
						   RangeProfile = new float[RangeFFTSize];
						   for (uint16_t j = 0; j < RangeFFTSize; j++)
						   {
							   memcpy(&temp, ReadBufferIndex, sizeof(unsigned short));
							   RangeProfile[j] = temp;
							   ReadBufferIndex += sizeof(unsigned short);
							   ByteCounter+= sizeof(unsigned short);
						   }
						   delete[] RangeProfile;
					   }
					   break;

					   case MMWDEMO_OUTPUT_MSG_NOISE_PROFILE:
					   {
						   float div = (float)(1.0 / (1 << 8));
						   NoiseProfile = new float[RangeFFTSize];
						   unsigned short temp;
						   for (uint16_t j = 0; j < RangeFFTSize; j++)
						   {
							   memcpy(&temp, ReadBufferIndex, sizeof(unsigned short));
							   NoiseProfile[j] = temp;
							   ReadBufferIndex += sizeof(unsigned short);
							   ByteCounter += sizeof(unsigned short);
						   }
						   delete[] NoiseProfile;
					   }
					   break;

					   case MMWDEMO_OUTPUT_MSG_AZIMUT_STATIC_HEAT_MAP:
					   {
						   int VirtualAntenna =MMWCfg.NumOf_Tx*MMWCfg.NumOf_Rx;
						   AzimuthHeatmap = new Complex[VirtualAntenna];
						   Complex temp;
						   for (uint16_t j = 0; j < RangeFFTSize * VirtualAntenna; j++)
						   {
							   memcpy(&temp, ReadBufferIndex, sizeof(Complex));
							   AzimuthHeatmap[j] = temp;
							   ReadBufferIndex += sizeof(Complex);
							   ByteCounter += sizeof(Complex);
						   }
						   delete[]AzimuthHeatmap;
					   }
					   break;
					   case MMWDEMO_OUTPUT_MSG_RANGE_DOPPLER_HEAT_MAP:
					   {
						   RangeDopplerHeatmap = new unsigned char[RangeFFTSize * DopplerFFTSize];
						   float div = (float)(1.0 / (1 << 8));
						   unsigned char temp;
						   for (uint16_t j = 0; j < RangeFFTSize * DopplerFFTSize; j++)
						   {
							   memcpy(&temp,ReadBufferIndex,sizeof(unsigned char));
							   RangeDopplerHeatmap[i] = temp;
							   ReadBufferIndex += sizeof(unsigned char);
							   ByteCounter += sizeof(unsigned char);
						   }
						   delete[] RangeDopplerHeatmap;
					   }
					   break;
					  
					   case MMWDEMO_OUTPUT_MSG_STATS:
					   {
						   MmwDemo_output_message_stats state;
						   memcpy(&state, ReadBufferIndex, sizeof(MmwDemo_output_message_stats));
						   ReadBufferIndex += sizeof(MmwDemo_output_message_stats);
						   ByteCounter += sizeof(MmwDemo_output_message_stats);
					   }
					   break;
					   default:
					   break;
					   }					    
				   }
		     	}
			
			}
			delete ReadBuf;
		}
	}
private: System::Void comBox_DataCOM_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	CmdSerialPort->Encoding = System::Text::Encoding::GetEncoding(28591);
	DataSerialPort->PortName=comBox_DataCOM->Text;
	DataSerialPort->BaudRate = DataSerialPortBaudRate;
	DataSerialPort->Parity = Parity::None;
	DataSerialPort->DataBits = 8;
	DataSerialPort->StopBits = StopBits::One;
}
	
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	chart1->Series["Series1"]->Points->Clear();
	for(uint16_t i=0;i<header.NumDetectedObj;i++)
		chart1->Series["Series1"]->Points->AddXY(ObjData[i].x, ObjData[i].y);
}
};
}
