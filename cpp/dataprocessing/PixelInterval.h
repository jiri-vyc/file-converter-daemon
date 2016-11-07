#pragma once
#include "SinglePixel.h"
#ifdef _WIN32
#include "include\rapidjson\writer.h"
#include "include\rapidjson\prettywriter.h"
#else
#include "include/rapidjson/writer.h"
#include "include/rapidjson/prettywriter.h"
#endif

class SinglePixel;

/**
The class representing an interval of pixels. It is a decorator over the std::vector class, as it provides the same functionality of the vector collection, and only adds a few methods needed for the specific case of pixel interval.
*/
class PixelInterval{
private:
	/// The internal standard vector collection, which is being decorated, providing all the base functionality.
	std::vector<SinglePixel> pixVector;
	/// Base time, from which pixels within this interval start 
	Double_t startTime;
public:
	/// Creates an empty interval of size 0
	PixelInterval(){};
	// Destroys the object and disposes of all the data contained within
	~PixelInterval(){

	};
	/// Shows number of triggers contained in the pixel interval data.
	unsigned int TriggerCount();
	/// Shows summed energy value of all pixel contained in the interval.
	unsigned int SumEnergy();
	/// Returns all the data from the interval in form of a string-encoded JSON object.
	std::string JSONify();
	/// Sends all the data from interval to the specified JSON Writer object.
	void JSONify(rapidjson::Writer<rapidjson::StringBuffer> & writer);
	/// Browse the data contained within this interval in the same fashion, as ROOT's Browse() function. Shows 25 lines of complete data, then queries user if they want to show more.
	void Print();
	/// Converts to a classic array.
	SinglePixel * ToArray();

	Double_t GetStartTime();
	/// Sets starting time of the data within this interval
	void SetStartTime(Double_t time);
	/// std::vector's functionality of the method of the same name
	void PushBack(SinglePixel elem);
	/// std::vector's functionality of the method of the same name
	void PopBack();
	/// std::vector's functionality of the method of the same name
	void Clear();
	/// std::vector's functionality of the method of the same name
	bool Empty();
	/// std::vector's functionality of the method of the same name
	unsigned int Size();	
	/// std::vector's functionality of the method of the same name
	SinglePixel At(unsigned int position);
	/// std::vector's functionality of the method of the same name
	SinglePixel Front();
	/// std::vector's functionality of the method of the same name
	SinglePixel Back();
};