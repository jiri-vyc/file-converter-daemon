#include "RootFile.h"

const std::string RootFile::defaultDataTreeName = PixelTree::defaultDataTreeName;
const std::string RootFile::defaultIndexTreeName = "Indextree";
const std::string RootFile::invalidFileError = "Invalid root file. Can't read.";

TTree * RootFile::GetTree()
{
	return this->GetTree(RootFile::defaultDataTreeName);
}

TTree * RootFile::GetTree(std::string treeName)
{
	if (treeName == this->m_treename){
		return this->t_data;
	}
	else if (treeName == this->m_indextreename){
		return this->t_indexes;
	}
	else {
		return nullptr;
	}
}

SinglePixel * RootFile::GetPixelAt(ULong64_t index)
{
	SinglePixel * np = this->pixelTree->GetPixelAt(index);
	return np;
}

SingleIndex * RootFile::GetIndexAt(ULong64_t index)
{
	Double_t startRow;
	Long64_t startTime;
	TTree * t_indexes = this->GetTree(RootFile::defaultIndexTreeName);
	t_indexes->SetBranchAddress("startRow", &startRow);
	t_indexes->SetBranchAddress("startTime", &startTime);
	t_indexes->GetEntry(index);
	return new SingleIndex(startRow, startTime);
}

std::string RootFile::GetFilename()
{
	return this->m_filename;
}

bool RootFile::IsOk()
{
	return this->ok;
}

bool RootFile::CreatePreview(std::string filename)
{
	TTree * tree = this->GetTree();
	uint32_t entriesCnt = tree->GetEntriesFast();
	SinglePixel * pixel = this->GetPixelAt(entriesCnt-1);
	ULong64_t maxPixToA = pixel->GetToA();
	delete pixel;

	TCanvas * c1 = new TCanvas("c1","c1",1200,600);

	TH1F * h = new TH1F("TPX3 #hits by ToA", "", 500,0,TimeUtils::NanoToSeconds(maxPixToA));
	h->GetXaxis()->SetTitle("Time in seconds");
	h->GetYaxis()->SetTitle("Number of hits");
	h->GetYaxis()->SetTitleOffset(1.2);
	c1->SetFillColorAlpha(4,0.5);


	this->GetTree()->Draw("ToA/1e9>>TPX3 #hits by ToA");

	c1->Modified();
	c1->Update();
	TPaveStats *stats =(TPaveStats*)c1->GetPrimitive("stats");
	stats->SetName("h1stats");
	stats->SetFillColorAlpha(4,0.5);


	c1->SaveAs( (std::string(DATAPATH) + "ROOT/" + filename + ".png").c_str());

	delete c1;
	delete h;
	return true;
}