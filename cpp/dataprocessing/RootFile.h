#pragma once

#include "SingleIndex.h"
#include "SinglePixel.h"
#include "TTree.h"
#include "TFile.h"
#include "PixelTree.h"
#include "Includes.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TPaveStats.h"
#include "TColor.h"

/**
* Wrapper over a single ROOT file - handles its opening, closing and getting the correct data from it (again represented as their respective wrapper objects)
*/
class RootFile {
private:
	bool ok = true;
	std::string m_filename;
	std::string m_treename;
	std::string m_indextreename; 
	TFile * f_data;
	TTree * t_data;
	TTree * t_indexes;
	PixelTree * pixelTree;
public:
	/// DEPRECATED
	/// Default name for the tree containing the pixel data
	/// Is kept for backward compatibility reasons, otherwise defaultDataTreeName is moved to PixelTree class
	const static std::string defaultDataTreeName;
	/// Default name for the tree containing the indexes
	const static std::string defaultIndexTreeName;
	/// Message to be displayed when trying to open invalid, corrupted or non-existant file
	const static std::string invalidFileError;

	/// Creates a new root file with specified name. Sets failed state and prints error message if it is unable to do so.
	RootFile(std::string filename){
		this->m_filename = filename;
		this->m_treename = PixelTree::defaultDataTreeName;	
		this->m_indextreename = RootFile::defaultIndexTreeName;
		this->f_data = new TFile(this->m_filename.c_str(), "READ");
		if (this->f_data->IsZombie()){
			std::cout << "Error opening root file." << std::endl;
			this->ok = false;
			return;
		}
		this->t_data = (TTree*)f_data->Get(this->m_treename.c_str());
		if (!this->t_data){
			std::cout << "Error reading data tree from root file." << std::endl;
			this->ok = false;
		}

		pixelTree = new PixelTree(this->t_data);

		this->t_indexes = (TTree*)f_data->Get(this->m_indextreename.c_str());
		if (!this->t_indexes){
			std::cout << "Error reading index tree from root file." << std::endl;
			this->ok = false;
		}
	}
	/// Closes the ROOT file.
	~RootFile(){
		this->f_data->Close();
		delete this->f_data;
	}
	/// Returns the filename of this ROOT file
	std::string GetFilename();
	/// Returns the tree with the default tree from within this file, if it exists.
	TTree * GetTree();
	/// If it exists, returns a tree with specified name, that is contained in the file.
	TTree * GetTree(std::string treeName);
	/// Returns a single pixel that is in the default data tree on specified position
	SinglePixel * GetPixelAt(ULong64_t index);
	/// Returns a single index that is in the default index tree on specified position
	SingleIndex * GetIndexAt(ULong64_t index);
	/// Checks if the file is in OK state, if it was opened correctly. When there was error or the file is not opened correctly, returns false.
	bool IsOk();
	/// Creates an image preview of the file and the data contained in it
	bool CreatePreview(std::string filename);
};