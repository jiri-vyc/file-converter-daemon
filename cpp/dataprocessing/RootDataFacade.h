#pragma once
#include "RootFile.h"
#include "SinglePixel.h"
#include "PixelInterval.h"

/**
Provides a facade for manipulating with data stored in the ROOT files - opens and goes through the root files and provides function to retrieve the data within specified interval - searches for the correct data corresponding with the given interval, using ROOT file's features, indexing, etc. 
*/
class RootDataFacade {
private:
	double m_intervalPeriod;
	RootFile * m_currentRootFile;
	std::vector<RootFile*> m_oldRootFiles;
	RootFile * m_givenRootFile;

	/// Finds the trigger, data of which were recorded in the time closest to the time specified by the parameter
	Long64_t GetClosestTrigger(Double_t time);
	/// Returns an index of the specific pixel from given trigger period, which first exceeds the given time (is the closest, time-wise)
	ULong64_t GetIndex(Long64_t triggerNo, Double_t time);
	/// Returns an index of the first pixel stored in the specidied trigger period.
	ULong64_t GetTriggerStartIndex(ULong64_t triggerNo);
	/// Returns a starting time of pixels within the specidied trigger period.
	ULong64_t GetTriggerStartTime(ULong64_t triggerNo);
public:
	/**
	* Constructor, which loads the data from new ROOT file specified by string filename
	*/
	RootDataFacade(std::string filename){
		this->LoadRootFile(filename);
	}
	/**
	* Constructor, which loads the data from already created/opened ROOT file
	*/
	RootDataFacade(RootFile * rootFile){
		this->m_givenRootFile = rootFile;
		this->m_currentRootFile = rootFile;
	}
	/** Imlicit destructor */
	~RootDataFacade(){
		this->Cleanup();
	}
	/**
	* Switches to currently opened rootfile with given name, or opens a new rootfile
	returns false if unable to open rootfile
	*/
	bool LoadRootFile(std::string filename);
	/**
	Prints a list of all currently loaded ROOT files, that are opened or were opened and are kept in memory.
	*/
	void ListLoadedRootFiles();
	/** 
	* Returns interval of pixels specified by input parameters
	*/
	PixelInterval * GetInterval(Double_t start_time, Double_t interval_period);
	/**
	* Returns interval of all pixels within the specified trigger period
	*/
	PixelInterval * GetTrigger(ULong64_t triggerNo);
	/**
	* Get interval directly following current one of the same size
	*/
	PixelInterval * GetNext();
	/**
	* Get interval directly preceding current one of the same size
	*/
	PixelInterval * GetPrev();
	/**
	* Cleans up the memory - deletes the resources used, which can be safely deleted
	*/
	void Cleanup();
};