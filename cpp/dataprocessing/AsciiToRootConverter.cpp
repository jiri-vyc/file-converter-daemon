#include "AsciiToRootConverter.h"

SingleEvent AsciiToRootConverter::GetOneEvent(std::string & line)
{
	SingleEvent c_event;
	if (!this->newFormat){
		c_event.SetFormat(SingleEvent::OLD_FORMAT);
	}
	if (!c_event.ReadFromLine(line)){
			throw "Error reading event data from line.";
	}
	return c_event;
}

bool AsciiToRootConverter::GetOneTriggerPeriod(std::ifstream & file, std::vector<SinglePixel> * pixVector, std::vector<SinglePixel> * prevPixVector, ULong64_t triggerNo, double lastToA)
{
	SingleEvent c_event;
	SinglePixel * c_pixel;
	std::string line;
	int cnt = 0;

	while (getline(file, line))
	{
		if (file.fail()){
			std::cout << "Reading data from file failed." << std::endl;
			return false;
		}

		// If there is an empty line or commented line in the file, ignore it and continue
		if (line.size() == 0 || line.at(0) == '#'){
			continue;
		}
		cnt++;

		c_event = this->GetOneEvent(line);
		
		// If there is empty event, it means trigger happened, break and process this trigger period
		if (c_event.EmptyEvent()) {
			break;
		}

		// Save the data from event in file into Pixel with correct values
		c_pixel = new SinglePixel(&c_event, triggerNo);

		// If current Pixel is within specified search range, check if the ToA doesn't imply the Pixel is an overflow from previous trigger period
		// If yes, push this Pixel back into previous trigger period vector
		// Else just push it into current trigger period vector
		if (cnt < this->overflowSearchRange && lastToA != 0.0) {
			if (c_pixel->GetToA() - lastToA >= -this->overflowTreshold){
				c_pixel->SetTriggerNo(c_pixel->GetTriggerNo() - 1);
				prevPixVector->push_back(*c_pixel);
			}
			else {
				pixVector->push_back(*c_pixel);
			}
		}
		else {
			pixVector->push_back(*c_pixel);
		}

		// Free used memory
		delete c_pixel;
	}

	// Mark end of the file by returning false
	if (file.eof())
	{
		return false;
	}
	return true;
}

RootFile * AsciiToRootConverter::ConvertTPX3Data(std::string filename, std::string outname)
{
	std::ifstream file(filename);

	if (!file.good()){
		std::cout << "Something wrong with the input file." << std::endl;
		return nullptr;
	}

	TFile * f_data = new TFile(outname.c_str(), "RECREATE");
	if (!f_data){
		std::cout << "Error creating new root file." << std::endl;
	}

	PixelTree * dataTree = new PixelTree();
	TTree * t_indexes = new TTree(RootFile::defaultIndexTreeName.c_str(), "Tree with indexing info");

	// We will be switching between pixVector and prevPixVector (in each following trigger period, current pixVector will become prevPixVector).
	// tempVector is helper temporary pointer for allowing this exchange
	std::vector<SinglePixel> *pixVector, *prevPixVector, *tempVector;
	pixVector = new std::vector < SinglePixel > ;
	prevPixVector = new std::vector < SinglePixel > ;

	SinglePixel * currentPixel;

	int cnt = 0;
	bool end = false;

	ULong64_t triggerNo = 0;
	Double_t lastToA = 0.0;
	Double_t startTime = 0.0;
	Long64_t currentRow = 0;

	t_indexes->Branch("startRow", &currentRow, "startRow/L");
	t_indexes->Branch("startTime", &startTime, "startTime/D");


	// Find out size of the file (only for info)
	file.seekg(0, file.end);
	file.clear();
	unsigned long int file_size = file.tellg();
	file.seekg(0, file.beg);
	file.clear();

	std::cout << "ASCII File size: " << file_size << std::endl;

	std::string line;
	// get the first, index line
	getline(file, line);

	try{
		if (file.fail() || line.size() == 0){
			throw "Cannot read first line of file";
		}
		// Determine whether first index line of the file corresponds with the new or old data format
		if (line.at(0) == '#' || line.at(3) == '#'){
			this->newFormat = true;
		} else {
			this->newFormat = false;
		}
		// main working loop
		do
		{
			cnt++;
			// start processing the file
			// read one period between the "trigger lines" from ASCII file
			if (!this->GetOneTriggerPeriod(file, pixVector, prevPixVector, triggerNo, lastToA))
			{
				end = true;
			}

			lastToA = pixVector->back().GetToA();

			triggerNo++;

			// sort pixels within one trigger period
	        // already fully filled vector of pixels from previous trigger
			std::sort(prevPixVector->begin(), prevPixVector->end());

			if (!prevPixVector->empty()){
				// how many entries were added to the data tree, remember for indexing purposes
				currentRow += prevPixVector->size();

				// save the last ToA from previous trigger, for indexing purposes
				startTime += prevPixVector->front().GetToA();
			}

			// save indexing info about current trigger in file
			t_indexes->Fill();
			

			// write sorted data to ROOT file
			while (!prevPixVector->empty())
			{
				currentPixel = &prevPixVector->back();
				prevPixVector->pop_back();

				dataTree->SavePixel(currentPixel);
			}

			// just in case
			prevPixVector->clear();

            // set currently processed vector as vector from previous trigger
            // overflowed data from next trigger will be added
			tempVector = prevPixVector;
			prevPixVector = pixVector;
			pixVector = tempVector;
			

			std::cout.precision(4);
			if (triggerNo % 3 == 0)
			{
				std::cout << "\rProgress: " << (unsigned long int) file.tellg() * 100.0 / file_size << "%";
			}

		} while (!end);

	} catch(const char * e){
		std::cout << e;
		delete pixVector;
		delete prevPixVector;
		delete f_data;
		if (std::remove(outname.c_str()) != 0)
		{
			std::cout << "Error deleting the file" << std::endl;
		}
		return nullptr;
	}

    // now process data from the last trigger in file - during which EOF happened and calculation had to stop
	// sort pixels within one trigger period
	std::sort(prevPixVector->begin(), prevPixVector->end());

	// how many entries were added to the data tree
	currentRow += prevPixVector->size();
	// save the last ToA from previous trigger, for indexing purposes
	startTime += prevPixVector->front().GetToA();
	// save indexing info about current trigger in file
	t_indexes->Fill();

	// write sorted data to ROOT file
	while (!prevPixVector->empty())
	{
		currentPixel = &prevPixVector->back();
		prevPixVector->pop_back();

		dataTree->SavePixel(currentPixel);
	}

	file.close();

	// write data from t_data and t_indexes into currently opened file (should be f_data)
	dataTree->Write("", TObject::kOverwrite);
	t_indexes->Write("", TObject::kOverwrite);
	f_data->Close();

	std::cout << "Converting to root file done." << std::endl;
 
	delete pixVector;
	delete prevPixVector;
	delete f_data;

    // return result in a form of wrapper object RootFile, handling I/O with actual root files
	return new RootFile(outname);
}
