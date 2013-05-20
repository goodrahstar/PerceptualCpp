// 
// Sample voice recognition code for PCSDK 
//

#include <windows.h>
#include <iostream>
#include "conio.h"
#include "pxcvoice.h"
#include "util_pipeline.h"


// ---------- comment this out to command and control  ---------//
// you cannot use both at the same time unfortunately...
#define DICTATION 1;



using namespace std;

class CommandAndControl: public UtilPipeline {

private:
	std::vector<wstring> commands;

public:

	CommandAndControl():UtilPipeline() 	{
		EnableVoiceRecognition();
	}

	void AddCommand(wstring cmd)  {
		commands.push_back(cmd);
	}

	void SetGrammar()	{
		this->SetVoiceCommands(commands);
	}
	
	void PXCAPI OnRecognized(PXCVoiceRecognition::Recognition *data) {
		std::wcout << "\n<COMMAND RECOGNIZED> " << commands[data->label] << flush;
	}
};



class Dictation: public UtilPipeline {

public:

	Dictation():UtilPipeline() 	{
		EnableVoiceRecognition();
	}

	void PXCAPI OnRecognized(PXCVoiceRecognition::Recognition *data) {
		std::wcout << "\n<DICTATION RECOGNIZED> " << data->dictation << flush;
	}
};



int wmain(int argc, wchar_t* argv[]) {

#ifdef DICTATION
		Dictation reco;
#else
		CommandAndControl reco;
		reco.AddCommand(L"hello"); 
		reco.AddCommand(L"show me the weather");
		reco.SetGrammar();
#endif

	reco.Init();
	std::cout << "\nInitialized. Speak....\n" << flush;
	
	while(!_kbhit())
	{
		reco.AcquireFrame(true);  // must have this for processing the audio
		reco.ReleaseFrame();	
		cout << ".";
	}
}
