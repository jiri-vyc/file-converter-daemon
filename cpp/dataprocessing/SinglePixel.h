#pragma once
#include "SingleEvent.h"
#include "Includes.h"
#ifdef _WIN32
#include "include\rapidjson\writer.h"
#include "include\rapidjson\prettywriter.h"
#else
#include "include/rapidjson/writer.h"
#include "include/rapidjson/prettywriter.h"
#endif



/**
* Represents one individial pixel hit on the detector in correct format. 
* It contains correctly calculated values of Time of Arrival, positions on the sensor, energy and correct trigger it belongs to
* It is also a representation of one record stored in the ROOT database.
*/
class SinglePixel{
private:
	ULong64_t m_index;
	short m_PixX;
	short m_PixY;
	double m_ToA;
	uint32_t m_ToT;
	uint32_t m_fToA;
	ULong64_t m_sToA;
	ULong64_t m_triggerNo;
public:
	/// Creates an empty pixel
	SinglePixel(){
		this->m_index = 0;
		this->m_PixX = 0;
		this->m_PixY = 0;
		this->m_ToA = 0;
		this->m_ToT = 0;
		this->m_triggerNo = 0;
		this->m_sToA = 0;
		this->m_fToA = 0;
	};
	/// Calculate all the correct pixel values from given raw values about an event recorded by the sensor. 
	SinglePixel(SingleEvent * c_event, ULong64_t triggerNo){
		this->m_index = c_event->GetIndex();
		this->m_PixX = c_event->GetMatrixIndex() % 256;
		this->m_PixY = c_event->GetMatrixIndex() / 256;
		this->m_ToA = c_event->GetToA() * 25 - c_event->GetFToA() * 1.5625;
		this->m_ToT = c_event->GetToT();
		this->m_sToA = c_event->GetToA();
		this->m_fToA = c_event->GetFToA();
		this->m_triggerNo = triggerNo;
	}
	/// Creates new pixel with exactly the given correct values.
	SinglePixel(ULong64_t index, short PixX, short PixY, double ToA, uint32_t ToT, ULong64_t triggerNo, ULong64_t sToA, uint32_t fToA){
		this->m_index = index;
		this->m_PixX = PixX;
		this->m_PixY = PixY;
		this->m_ToA = ToA;
		this->m_ToT = ToT;
		this->m_fToA = fToA;
		this->m_sToA = sToA;
		this->m_triggerNo = triggerNo;
	}
	/// Implicit destructor
	~SinglePixel(){
		
	}
	/// Compares the ToA value of the two pixels
	bool operator < (const SinglePixel& otherPixel) const;
	/// Prints the pixel with all its attributes
	friend std::ostream& operator<< (std::ostream& os, const SinglePixel& pixel);
	/// Get the arbitrary index of the pixel
	ULong64_t GetIndex();
	/// Get the real X coordinate of the pixel
	short GetPixX();
	/// Get the real Y coordinate of the pixel
	short GetPixY();
	/// Get the correct ToA value of the pixel [in ns]
	double GetToA();
	/// Get the ToT value of the pixel
	uint32_t GetToT();
	/// Get the originally stored, raw ToA value of the event
	ULong64_t GetSToA();
	/// Get the originally stored, raw fToA value of the event 
	uint32_t GetFToA();
	/// Get the number of trigger period, in which the pixel was recorded
	ULong64_t GetTriggerNo();
	/// Set the trigger number of this pixel. Useful for moving overflowed pixel in another trigger period.
	void SetTriggerNo(ULong64_t triggerNo);
	/// Writes the JSON representation of this one single pixel into the specified JSON writer.
	void JSONify(rapidjson::Writer<rapidjson::StringBuffer> & writer);
};
