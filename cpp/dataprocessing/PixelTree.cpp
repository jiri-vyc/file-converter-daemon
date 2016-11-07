#include "PixelTree.h"

const std::string PixelTree::defaultDataTreeName = "Datatree";

TTree * PixelTree::GetTree(){
	return this->t_data;
}

Int_t PixelTree::Write(const char * name, Int_t option){
	return this->t_data->Write(name, option, 0);
}

void PixelTree::InitializeBranches(){
	this->t_data->Branch("index", &this->m_index, "index/l");
	this->t_data->Branch("PixX", &this->m_PixX, "PixX/S");
	this->t_data->Branch("PixY", &this->m_PixY, "PixY/S");
	this->t_data->Branch("ToA", &this->m_ToA, "ToA/D");
	this->t_data->Branch("ToT", &this->m_ToT, "ToT/I");
	this->t_data->Branch("sToA", &this->m_sToA, "sToA/l");
	this->t_data->Branch("fToA", &this->m_fToA, "fToA/i");
	this->t_data->Branch("triggerNo", &this->m_triggerNo, "triggerNo/l");
}

void PixelTree::SetBranchesAddresses(){
	this->t_data->SetBranchAddress("index", &this->m_index);
	this->t_data->SetBranchAddress("PixX", &this->m_PixX);
	this->t_data->SetBranchAddress("PixY", &this->m_PixY);
	this->t_data->SetBranchAddress("ToA", &this->m_ToA);
	this->t_data->SetBranchAddress("ToT", &this->m_ToT);
	this->t_data->SetBranchAddress("triggerNo", &this->m_triggerNo);
	this->t_data->SetBranchAddress("sToA", &this->m_sToA);
	this->t_data->SetBranchAddress("fToA", &this->m_fToA);
}

bool PixelTree::SavePixel(SinglePixel * currentPixel){
	// arbitrary event index
	this->m_index = currentPixel->GetIndex();
	// pixel X coordinate
	this->m_PixX = currentPixel->GetPixX();
	// pixel Y coordinate
	this->m_PixY = currentPixel->GetPixY();
	// real Time of Acquisition
	this->m_ToA = currentPixel->GetToA();
	// energy value
	this->m_ToT = currentPixel->GetToT();
	// trigger number
	this->m_triggerNo = currentPixel->GetTriggerNo();
	// slow Time of Acquisition
	this->m_sToA = currentPixel->GetSToA();
	// fast Time of Acquisition
	this->m_fToA = currentPixel->GetFToA();

	// save current data into TTree
	this->t_data->Fill();

	return true;
}

SinglePixel * PixelTree::GetPixelAt(ULong64_t index)
{
	this->SetBranchesAddresses();
	this->t_data->GetEntry(index);
	return new SinglePixel(this->m_index, this->m_PixX, this->m_PixY, this->m_ToA, this->m_ToT, this->m_triggerNo, this->m_sToA, this->m_fToA);
}

