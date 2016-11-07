#include "SingleEvent.h"

bool SingleEvent::EmptyEvent()
{
	if (this->m_matrix_index == 0 && this->m_ToA == 0 && this->m_ToT == 0 && this->m_FToA == 0)
	{
		return true;
	}
	return false;
}

bool SingleEvent::ReadFromLine(std::string data){
	std::stringstream ss(data);

	if (this->m_format == SingleEvent::NEW_FORMAT){
		if (!(ss >> this->m_matrix_index >> this->m_ToA >> this->m_FToA >> this->m_ToT)){
			return false;
		}
	}
	else {
		if(!(ss >> this->m_index >> this->m_matrix_index >> this->m_ToA >> this->m_ToT >> this->m_FToA >> this->m_overflow)){
			return false;
		}
	}
	return true;
}

void SingleEvent::SetFormat(int newFormat){
	this->m_format = newFormat;
}
int SingleEvent::GetFormat(){
	return this->m_format;
}
ULong64_t SingleEvent::GetIndex(){
	return this->m_index;
}
uint32_t SingleEvent::GetMatrixIndex(){
	return this->m_matrix_index;
}
ULong64_t SingleEvent::GetToA(){
	return this->m_ToA;
}
uint32_t SingleEvent::GetToT(){
	return this->m_ToT;
}
uint32_t SingleEvent::GetFToA(){
	return this->m_FToA;
}
uint32_t SingleEvent::GetOverflow(){
	return this->m_overflow;
}