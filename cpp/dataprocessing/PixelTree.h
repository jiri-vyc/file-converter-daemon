#pragma once

#include "SinglePixel.h"
#include "Includes.h"

/**
* Representation of a single ROOT TTree with pixel values from the TPX3 data
* with branches according to the Pixel's values that need to be saved in the tree
*/
class PixelTree{
	private:
		ULong64_t m_index;
		Short_t m_PixX;
		Short_t m_PixY;
		double m_ToA;
		Int_t m_ToT;
		ULong64_t m_sToA;
		uint32_t m_fToA;
		ULong64_t m_triggerNo;

		TTree * t_data;
	public:
		/// Default name for the tree containing the pixel data
		const static std::string defaultDataTreeName;
		/** Creates new empty pixel tree for writing data */
		PixelTree(){
			this->t_data = new TTree(PixelTree::defaultDataTreeName.c_str(), "Tree with sensor data");
			this->InitializeBranches();
		};
		/** Creates new pixel tree with already existing ROOT TTree, for reading data */
		PixelTree(TTree * rootTree){
			this->t_data = rootTree;
		};
		void InitializeBranches();
		void SetBranchesAddresses();
		TTree * GetTree();
		Int_t Write(const char * name, Int_t option);
		bool SavePixel(SinglePixel * inputPixel);
		SinglePixel * GetPixelAt(ULong64_t index);
};