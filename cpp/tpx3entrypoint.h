#include <string>
#include "dataprocessing/RootFile.h"
#include "dataprocessing/RootDataFacade.h"
#include "dataprocessing/AsciiToRootConverter.h"
#include "dataprocessing/PixelInterval.h"


class TPX3EntryPoint{
private:
	RootFile * f_data;
public:
	TPX3EntryPoint(std::string rootFilename){
		this->f_data = new RootFile(rootFilename);
	}
	TPX3EntryPoint()
	{
		this->f_data = NULL;
	}
	~TPX3EntryPoint(){
		if (this->f_data){
			delete this->f_data;
		}
	}

	std::string GetFilename();
	std::string GetInterval(double startTime, double timeSlice);
	std::string GetTrigger(unsigned int triggerNo);
	std::string Convert(std::string inFilename, std::string outFilename);
	double Add(double a, double b);
};