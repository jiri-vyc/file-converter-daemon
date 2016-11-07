#pragma once
#include "TFile.h"

/**
* Representation of single record in the ROOT database in indexing tree, marking the start row and start time of specified trigger.
*/
class SingleIndex{
private:
	Double_t m_startTime;
	Long64_t m_startRow;
public:
	/// Creates new index for certain time starting on a certain row in the data table
	SingleIndex(Long64_t startRow, Double_t startTime){
		this->m_startRow = startRow;
		this->m_startTime = startTime;
	}
};