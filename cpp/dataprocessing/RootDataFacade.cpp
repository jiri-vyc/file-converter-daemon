#include "RootDataFacade.h"



Long64_t RootDataFacade::GetClosestTrigger(Double_t time)
{
	//std::cout << "Getting closest trigger for time " << time << std::endl;
	if (time <= 0){
		return 0;
	}
	Double_t startTime;
	if (!this->m_currentRootFile){
		std::cout << RootFile::invalidFileError << std::endl;
		return -1;
	}
	TTree * t_indexes = this->m_currentRootFile->GetTree(RootFile::defaultIndexTreeName);
	Long64_t entries_cnt = t_indexes->GetEntriesFast();
	Long64_t entries_high = entries_cnt - 2;
	Long64_t entries_low = 0;
	Long64_t currIndex = entries_high / 2;
	t_indexes->SetBranchStatus("*", 0);
	t_indexes->SetBranchStatus("startTime", 1);
	t_indexes->SetBranchAddress("startTime", &startTime);
	t_indexes->GetEntry(entries_cnt - 1);

	if (time >= startTime){
        //std::cout << "Found closest trigger " << entries_cnt - 1 << std::endl;
		return entries_cnt - 1;
	}

	while (1)
	{
		// startTime = GetEntry(currIndex)->startTime
		t_indexes->GetEntry(currIndex);


		if (time <= startTime){
			entries_high = currIndex;
			currIndex = (entries_low + currIndex) / 2;
			continue;
		}

		// startTime = GetEntry(currIndex + 1)->startTime
		t_indexes->GetEntry(currIndex + 1);

		if (time > startTime) {
			entries_low = currIndex + 1;
			currIndex = (entries_high + currIndex + 1) / 2;
			if (entries_low == currIndex && currIndex == (entries_cnt - 2)){
				currIndex++;
			}
			continue;
		}
		break;
	}

	//std::cout << "Found closest trigger " << currIndex << std::endl;
	return currIndex;
}

ULong64_t RootDataFacade::GetTriggerStartIndex(ULong64_t triggerNo)
{
	//std::cout << "Getting Trigger start Index for trigger " << triggerNo << std::endl;
	if (!this->m_currentRootFile){
		std::cout << RootFile::invalidFileError << std::endl;
	}
	TTree * t_indexes = this->m_currentRootFile->GetTree(RootFile::defaultIndexTreeName);
	Double_t startTime;
	Long64_t startRow;
	t_indexes->SetBranchAddress("startRow", &startRow);
	t_indexes->SetBranchAddress("startTime", &startTime);
	t_indexes->GetEntry(triggerNo);

	//std::cout << "Got trigger start index " << startRow << std::endl;
	return startRow;
}

ULong64_t RootDataFacade::GetTriggerStartTime(ULong64_t triggerNo)
{
	//std::cout << "Getting Trigger start Index for trigger " << triggerNo << std::endl;
	if (!this->m_currentRootFile){
		std::cout << RootFile::invalidFileError << std::endl;
	}
	TTree * t_indexes = this->m_currentRootFile->GetTree(RootFile::defaultIndexTreeName);
	Double_t startTime;
	Long64_t startRow;
	t_indexes->SetBranchAddress("startRow", &startRow);
	t_indexes->SetBranchAddress("startTime", &startTime);
	t_indexes->GetEntry(triggerNo);

	//std::cout << "Got trigger start index " << startRow << std::endl;
	return startTime;
}

/**
finds the first event with higher ToA than given

searches within one trigger

*/
ULong64_t RootDataFacade::GetIndex(Long64_t triggerNo, Double_t time)
{
	//std::cout << std::fixed << "Getting Index for trigger " << triggerNo << " and time " << time << std::endl;
	if (!this->m_currentRootFile){
		std::cout << RootFile::invalidFileError << std::endl;
	}
	TTree * t_indexes = this->m_currentRootFile->GetTree(RootFile::defaultIndexTreeName);
	TTree * t_data = this->m_currentRootFile->GetTree(RootFile::defaultDataTreeName);
	Long64_t entries_cnt = t_data->GetEntriesFast();

	Long64_t indexes_cnt = t_indexes->GetEntriesFast();
	Double_t ToA;
	t_data->SetBranchAddress("ToA", &ToA);

	Double_t startTime;
	Long64_t startRow;
	Double_t endTime;
	Long64_t endRow;

	// Enable the 2 needed branches
	t_indexes->SetBranchStatus("*", 0);
	t_indexes->SetBranchStatus("startTime", 1);
	t_indexes->SetBranchStatus("startRow", 1);

	// Get start time and start row of next trigger = end time of this trigger
	t_indexes->SetBranchAddress("startRow", &endRow);
	t_indexes->SetBranchAddress("startTime", &endTime);
	t_indexes->GetEntry(triggerNo + 1);

	// Get start time and start row of current trigger
	t_indexes->SetBranchAddress("startRow", &startRow);
	t_indexes->SetBranchAddress("startTime", &startTime);
	t_indexes->GetEntry(triggerNo);


	Double_t deltaTime = time - startTime;

	if (triggerNo == indexes_cnt - 1){
		return startRow;
	}

	Long64_t currIndex = (startRow + endRow) / 2;

	while (1)
	{
		t_data->GetEntry(currIndex);
		if (ToA > deltaTime){
			endRow = currIndex;
			currIndex = (startRow + endRow) / 2;
			if (endRow == currIndex && currIndex == 0){
				currIndex--;
				break;
			}
			continue;
		}

		t_data->GetEntry(currIndex+1);

		if (ToA <= deltaTime){
			startRow = currIndex + 1;
			currIndex = (endRow + startRow) / 2;
			if (startRow == currIndex && currIndex == (entries_cnt - 1)){
				break;
			}
			continue;
		}
		break;
	}

	currIndex++;

	//std::cout << "Index for trigger " << triggerNo << " and time " << time << " is " << currIndex << std::endl;

	return currIndex;
}

PixelInterval * RootDataFacade::GetInterval(Double_t start_time, Double_t interval_period)
{
    if (!this->m_currentRootFile->IsOk()) {
    	std::cout << "Root file not ok" << std::endl;
    	return new PixelInterval();
    }
	this->m_intervalPeriod = interval_period;
	ULong64_t triggerNo = this->GetClosestTrigger(start_time);
	ULong64_t startIndex = this->GetIndex(triggerNo, start_time);
	ULong64_t endTriggerNo = this->GetClosestTrigger(start_time + interval_period);
	ULong64_t delta = endTriggerNo - triggerNo;
	ULong64_t endIndex = this->GetIndex(triggerNo + delta, start_time + interval_period);
	Double_t triggerStartTime = this->GetTriggerStartTime(triggerNo);

	PixelInterval * pixInterval = new PixelInterval();
	pixInterval->SetStartTime(triggerStartTime);

	SinglePixel * currPixel;
	for (unsigned int i = startIndex; i < endIndex; i++)
	{
		currPixel = this->m_currentRootFile->GetPixelAt(i);
		pixInterval->PushBack(*currPixel);
		delete currPixel;
	}

	return pixInterval;
}

PixelInterval * RootDataFacade::GetTrigger(ULong64_t triggerNo)
{
	ULong64_t startIndex = this->GetIndex(triggerNo, 0);
	ULong64_t endIndex = this->GetIndex(triggerNo + 1, 0);
	PixelInterval * pixInterval = new PixelInterval();
	SinglePixel * currPixel;
	for (unsigned int i = startIndex; i < endIndex; i++)
	{
		currPixel = this->m_currentRootFile->GetPixelAt(i);
		pixInterval->PushBack(*currPixel);
		delete currPixel;
	}
	return pixInterval;
}

bool RootDataFacade::LoadRootFile(std::string filename)
{
	bool currPresent = false;
	RootFile * currPointer;
	for (unsigned int i = 0; i < this->m_oldRootFiles.size(); i++)
	{
		currPointer = this->m_oldRootFiles.at(i);
		if (currPointer->GetFilename() == filename)
		{
			this->m_currentRootFile = currPointer;
			return true;
		}
		if (currPointer == this->m_currentRootFile)
		{
			currPresent = true;
		}
	}
	if (!currPresent)
	{
		this->m_oldRootFiles.push_back(this->m_currentRootFile);
	}
	this->m_currentRootFile = new RootFile(filename);
	if (!this->m_currentRootFile->IsOk())
	{
		return false;
	}
	return true;
}

void RootDataFacade::Cleanup()
{
	RootFile * currPointer;
	while (!this->m_oldRootFiles.empty())
	{
		currPointer = this->m_oldRootFiles.back();
		if (currPointer != this->m_givenRootFile){
			this->m_oldRootFiles.pop_back();
			delete currPointer;
		}
	}
	if (this->m_currentRootFile && (this->m_currentRootFile != this->m_givenRootFile))
	{
		delete m_currentRootFile;
		m_currentRootFile = nullptr;
	}
}

void RootDataFacade::ListLoadedRootFiles()
{
	for (unsigned int i = 0; i < this->m_oldRootFiles.size(); i++)
	{
		std::cout << this->m_oldRootFiles.at(i)->GetFilename() << std::endl;
	}
	std::cout << "Currently in-use rootFile: ";
	if (m_currentRootFile)
	{
		std::cout << this->m_currentRootFile->GetFilename() << std::endl;
	} 
	else 
	{
		std::cout << "No file." << std::endl;
	}
}