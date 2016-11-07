#pragma once
#include "PixelTree.h"
#include "RootFile.h"
#include "SinglePixel.h"
#include "SingleEvent.h"
#include "TTree.h"
#include "TFile.h"

/**
Class responsible for converting the raw data from ASCII files and saving them in ROOT storage. It also provides browsing of the data and the database in general (to examine its indexing etc)
*/
class AsciiToRootConverter {
private:
	/// Parameter that specifies for how many entries will the events in the file be checked whether they don't contained overflowed values from previous trigger
	int overflowSearchRange = 50;
	/// Parameter specifying the minimum difference between the last ToA of the previous trigger and current ToA, that can be taken as not-overflowed value
	int overflowTreshold = 100000;
	/// Processes single trigger period in the data, reads the lines from ASCII files and saves the data in form of SinglePixel's into a vector.
	bool GetOneTriggerPeriod(std::ifstream & file, std::vector<SinglePixel> * pixVector, std::vector<SinglePixel> * prevPixVector, ULong64_t triggerNo, double lastToA);
	/// Gets data about one specific event from given single line in the ASCII file
	SingleEvent GetOneEvent(std::string & line);
	bool newFormat;
public:
	/** Converts all the Timepix 3 detector data from ASCII file specified by the parameter, 
	* creates ROOT file with name specified by the second parameter, 
	* converts the data and saves them into this format.
	* Returns a pointer to this ROOT file with all the data. Returns nullptr if any critical error occurs.
	*/
	RootFile * ConvertTPX3Data(std::string filename, std::string outname);
};
