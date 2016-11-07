#include "PixelInterval.h"

using namespace rapidjson;

unsigned int PixelInterval::TriggerCount()
{
    if (this->Size() == 0)
    {
        return 0;
    }
	return this->pixVector.back().GetTriggerNo() - this->pixVector.front().GetTriggerNo() + 1;
}

void PixelInterval::SetStartTime(Double_t time){
	this->startTime = time;
}

Double_t PixelInterval::GetStartTime(){
	return this->startTime;
}

void PixelInterval::Clear()
{
	this->pixVector.clear();
}

void PixelInterval::PopBack()
{
	this->pixVector.pop_back();
}

void PixelInterval::PushBack(SinglePixel elem)
{
	this->pixVector.push_back(elem);
}

bool PixelInterval::Empty()
{
	return this->pixVector.empty();
}

unsigned int PixelInterval::Size()
{
	return this->pixVector.size();
}

SinglePixel PixelInterval::Front()
{
	return this->pixVector.front();
}

SinglePixel PixelInterval::Back()
{
	return this->pixVector.back();
}

SinglePixel PixelInterval::At(unsigned int position)
{
	return this->pixVector.at(position);
}

SinglePixel * PixelInterval::ToArray()
{
	unsigned int size = this->Size();
	SinglePixel * pixArray = new SinglePixel[size];
	for (unsigned int i = 0; i < size; i++)
	{
		pixArray[i] = this->At(i);
	}
	return pixArray;
}

void PixelInterval::Print()
{
	unsigned int size = this->Size();
	std::cout << "Size: " << size << std::endl;
	if (this->Empty()){
		return;
	}
	std::cout << "TriggerCount: " << this->TriggerCount() << std::endl;
	std::cout << "StartTime: " << this->GetStartTime() << std::endl;
	for (unsigned int i = 0; i < size; i++)
	{
		std::cout << this->At(i) << std::endl;
		if (i % 25 == 0 && i / 25 > 0){
			std::cout << "Type <CR> to continue or q to quit ==>" << std::endl;
			if (std::cin.get() == 'q'){
				break;
			}
		}
	}
}

unsigned int PixelInterval::SumEnergy()
{
	unsigned int sum = 0;
	for (unsigned int i = 0; i < this->Size(); i++)
	{
		sum += this->At(i).GetToT();
	}
	return sum;
}

void PixelInterval::JSONify(Writer<StringBuffer> & writer)
{
	writer.StartObject();
	writer.Key("Size");
	writer.Uint(this->Size());
	writer.Key("TriggerCount");
	writer.Uint(this->TriggerCount());
	writer.Key("SumEnergy");
	writer.Uint(this->SumEnergy());
	writer.Key("StartTime");
	writer.Double(this->GetStartTime());
	writer.Key("Pixels");
	writer.StartArray();
	for (unsigned int i = 0; i < this->Size(); i++)
	{
		this->At(i).JSONify(writer);
	}
	writer.EndArray();
	writer.EndObject();
}

std::string PixelInterval::JSONify()
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	this->JSONify(writer);
	return buffer.GetString();
}

