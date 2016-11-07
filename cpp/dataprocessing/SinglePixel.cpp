#include "SinglePixel.h"

bool SinglePixel::operator<(const SinglePixel& otherPixel) const
{
	return this->m_ToA > otherPixel.m_ToA;
}

ULong64_t SinglePixel::GetIndex()
{
	return this->m_index;
}
short SinglePixel::GetPixX()
{
	return this->m_PixX;
}
short SinglePixel::GetPixY()
{
	return this->m_PixY;
}
double SinglePixel::GetToA()
{
	return this->m_ToA;
}
uint32_t SinglePixel::GetToT()
{
	return this->m_ToT;
}
ULong64_t SinglePixel::GetTriggerNo()
{
	return this->m_triggerNo;
}
ULong64_t SinglePixel::GetSToA()
{
	return this->m_sToA;
}
uint32_t SinglePixel::GetFToA()
{
	return this->m_fToA;
}
void SinglePixel::SetTriggerNo(ULong64_t triggerNo)
{
	this->m_triggerNo = triggerNo;
}
std::ostream& operator<< (std::ostream& os, const SinglePixel& pixel)
{
	os << std::setiosflags(std::ios::right) << "Index:" << pixel.m_index << " * " << std::setw(10) << " pixX:" << pixel.m_PixX << " * " << std::setw(10) << " pixY:" << pixel.m_PixY << " * " << std::setw(10) << " ToA:" << pixel.m_ToA << " * " << std::setw(10) << " ToT:" << pixel.m_ToT << " * " << std::setw(10) << " triggerNo:" << pixel.m_triggerNo << " sToA:" << pixel.m_sToA << " fToA:" << pixel.m_fToA;
	return os;
}
void SinglePixel::JSONify(rapidjson::Writer<rapidjson::StringBuffer> & writer)
{
	writer.StartObject();
	writer.Key("pixel_index");
	writer.Uint64(this->GetIndex());
	writer.Key("pixX");
	writer.Uint(this->GetPixX());
	writer.Key("pixY");
	writer.Uint(this->GetPixY());
	writer.Key("ToA");
	writer.Double(this->GetToA());
	writer.Key("ToT");
	writer.Int(this->GetToT());
	writer.Key("TriggerNo");
	writer.Uint64(this->GetTriggerNo());
	writer.Key("sToA");
	writer.Uint64(this->GetSToA());
	writer.Key("fToA");
	writer.Uint(this->GetFToA());
	writer.EndObject();
}
