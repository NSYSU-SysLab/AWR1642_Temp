#pragma once
#include"PropertyDefine.h"
#include <Windows.h>  
#include<fstream>
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
		CmdSerialPort->WriteLine(str);
		Sleep(500);
		delete str;
	}
	DataSerialPort->Open();
	thread = gcnew Thread(gcnew ThreadStart(this, &MyForm::ReadFromRadar));
	thread->Start();
}
	private:void ReadFromRadar()
	{
	
		cli::array<unsigned char>^ReadBuf = gcnew cli::array<unsigned char>(DATA_PORT_QUEUE_SIZE);
		int ReadSize;
		while (true)
		{
			if (DataSerialPort->BytesToRead > 0)
			{
				ReadSize = DataSerialPort->Read(ReadBuf,0, DATA_PORT_QUEUE_SIZE); 
			}	
			if (ReadSize > 0)
				int a = 999;
			
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
};
}
