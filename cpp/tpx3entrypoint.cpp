#include "tpx3entrypoint.h"

std::string TPX3EntryPoint::GetFilename(){
	std::string s = this->f_data->GetFilename();
	return s;
}

std::string TPX3EntryPoint::GetTrigger(unsigned int triggerNo){
	RootDataFacade * dataFacade = new RootDataFacade(this->f_data);
	PixelInterval * pixInterval;
	pixInterval = dataFacade->GetTrigger(triggerNo);

	return pixInterval->JSONify();
}

std::string TPX3EntryPoint::GetInterval(double startTime, double timeSlice){
	RootDataFacade * dataFacade = new RootDataFacade(this->f_data);
	PixelInterval * pixInterval;
	pixInterval = dataFacade->GetInterval(startTime, timeSlice);

	std::string json = pixInterval->JSONify();
	delete pixInterval;
	delete dataFacade;
	return json;
}

std::string TPX3EntryPoint::Convert(std::string inFilename, std::string outFilename){
	AsciiToRootConverter * converter = new AsciiToRootConverter();
	RootFile * rf = converter->ConvertTPX3Data(std::string(DATAPATH) + "RAW/" + inFilename, std::string(DATAPATH) + "ROOT/" + outFilename + ".root");
	if (rf && rf->IsOk()){
		rf->CreatePreview(outFilename);
		delete rf;
		return "ok";
	} else {
		return "not ok";
	}
}