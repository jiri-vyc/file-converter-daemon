#pragma once

#include "TTree.h"
#include <string>
#include <sstream>

/**
* SingleEvent is the most basic data structure that needs to be processed. Represents one single instance of (any) data, that are stored in the files. 
* In reality, it is one line of data in the ASCII file - single event recorded by the detector and written down to disk. 
* It contains exactly the values which are present in the file.
*/
class SingleEvent{
private:
	ULong64_t m_index;
	uint32_t m_matrix_index;
	ULong64_t m_ToA;
	uint32_t m_ToT;
	uint32_t m_FToA;
	uint32_t m_overflow;
	int m_format = SingleEvent::NEW_FORMAT;
public:
	/// Format identifier representing old format of the data (index, matrix index, ToA, ToT, fToA, overflow)
	static const int OLD_FORMAT = 0;
	/// Format identifier representing new format of the data (matrix index, ToA, fToA, ToT)
	static const int NEW_FORMAT = 1;
	/// Creates an empty event
	SingleEvent(){
		this->m_index = 0;
		this->m_matrix_index = 0;
		this->m_ToA = 0;
		this->m_ToT = 0;
		this->m_FToA = 0;
		this->m_overflow = 0;
	};
	/** Reads a data from a string stream and saves them to properties
	* Doesn't check if the saved data make sense. If you supply garbage here, you'll get garbage event.
	*/
	bool ReadFromLine(std::string data);
	/** Creates a new event from a string stream (can be one line in asciifile)
	* Uses ReadFromLine(). Same warning applies.
	*/
	SingleEvent(std::string data){
		this->ReadFromLine(data);
	}
	/**
	* Checks if this is a so-called "empty event", which usually has the function of some delimiter in the data. 
	* Mostly it is an event with all its values 0.
	* Returns true if yes, false otherwise.
	*/
	bool EmptyEvent();
	/** Sets the format of the data to be received */
	void SetFormat(int newFormat);

	int GetFormat();
	ULong64_t GetIndex();
	uint32_t GetMatrixIndex();
	ULong64_t GetToA();
	uint32_t GetToT();
	uint32_t GetFToA();
	uint32_t GetOverflow();
};