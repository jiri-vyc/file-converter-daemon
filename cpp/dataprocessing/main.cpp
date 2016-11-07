/*! \mainpage 
 *
 * This is the server part of the visualization application for data from the Timepix3 detector. It consists of tool for converting the raw detector data into ROOT database and of a Data Facade, that provides an interface for working with the data stored this way. 
 *
 * The interface is used in a native Node.js addon and included in the server application, run on Node.js. The server provides an API for sending the data according to user queries.
 * 
In this documentation of the C++ source, you can find description of all the classes and all their APIs

 * \section intro_sec Manual
 *


 *
 * \subsection step1 Run
 *
 All files are located in the <code>/app</code> directory

 - Install prerequisities
 	- node.js v4.4.3 (http://nodejs.org)
 	- npm v2.15v1 (https://www.npmjs.com)
 	- ROOT v5.34 (https://root.cern.ch/content/release-53434)
 - Export ROOT <code>/build/lib/</code> library directory to default library path variable by running command <code>export LD_LIBRARY_PATH=path/to/root/build/lib/:$LD_LIBRARY_PATH</code>
 - Install the server by running <code>npm install</code>
 - Run the server by running <code>npm start</code>
 - Server is now available on the local machine on port 3000

\subsection step2 Build
 All files are located in the <code>/app</code> directory

 - Install prerequisities
 	- All of the above prerequisites
 	- node-gyp v3.3.1 (https://github.com/nodejs/node-gyp)
 - Edit the binding.gyp file in the <code>/cpp/</code> directory to contain correct paths to ROOT libraries and sources in the "libraries" and "include_dirs" options 
 - Export ROOT <code>/build/lib/</code> library directory to default library path variable by running command <code>export LD_LIBRARY_PATH=path/to/root/build/lib/:$LD_LIBRARY_PATH</code>
 - Run <code>node-gyp configure</code> command in the <code>/cpp/</code> directory, to create platform-specific project build files
 - Compile the project by running <code>node-gyp build</code>
 - \ref step1 the server

 * \section intro_secc Manual - The Converter
 All files are located in the <code>/app/cpp/dataprocessing</code> directory.
 The program for converting the data from the ASCII format to ROOT storage is a binary file <code>data/tpx3dataconverter</code>

 * \subsection step3 Run
 The program can be run with following options: <code>tpx3dataconverter input_ascii_file output_root_file 
action_option subject_option</code>


- <code>input_ascii_file</code> is the location of the source ASCII file
- <code>output_root_file</code> is the desired name of the ROOT file
- <code>action_option</code> is the desired action to be performed, can be <code>load</code> for loading and converting the data or <code>show</code> for browsing the data
- <code>subject_option</code> chooses whether the shown data from ROOT file will be the pixel data, or the indexes

\subsection step5 Build

 All files are located in the <code>/app/cpp/dataprocessing</code> directory.

Use any IDE with correctly set include and header directories to ROOT <code>/build/include/</code> directory and linker libraries to <code>/build/lib/</code>. Compile all the C++ sources in the <code>/app/cpp/dataprocessing</code> folder to create an output executable (Unix binary or Windows .exe).

\ref step3 the executable

 * \section copyright Copyright and license
 The MIT License (MIT)

Copyright (c) 2016 Jiri Vycpalek

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Includes.h"
#include <iostream>
#include "AsciiToRootConverter.h"

using namespace std;


int main(int argc, char * argv[])
{
    cout << "Hello" << endl;
	return 0;
//	string filename, what = "data", load = "load", outname = "TPX3data.root";
//	if (argc > 1)
//	{
//		filename = argv[1];
//		cout << "Input file: " << filename << endl;
//	}
//	else 
//	{
//		cout << "No input file specified" << endl;
//		return 0;
//	}
//	if (argc > 2)
//	{
//		outname = argv[2];
//		cout << "Output file: " << outname << endl;
//	}
//	else 
//	{
//		cout << "No output file specified, using \"" << outname << "\"" << endl;
//	}
//	if (argc > 3)
//	{
//		load = argv[3];
//		cout << "What I'm doing: " << load << "ing";
//	}
//	if (argc > 4)
//	{
//		what = argv[4];
//		cout << " " << what << endl;
//	}
//	float start_time = TimeUtils::GetMyCPUTime(TimeUtils::SECONDS);
//
//	AsciiToRootConverter * converter = new AsciiToRootConverter();
//	RootFile * rootFile;
//	if (load == "load")
//	{
//		rootFile = converter->SaveDataASCII(filename, outname);
//	}
//	else {
//		rootFile = new RootFile(outname);
//	}
//
//	float end_time = TimeUtils::GetMyCPUTime(TimeUtils::SECONDS) - start_time;
//
//	cout << "Ending time: " << end_time << endl;
//	if (!rootFile->IsOk()){
//		delete rootFile;
//		delete converter;
//		return 1;
//	}
//
//	if (what == "data")
//		rootFile->GetTree()->Scan();
//
//	if (what == "indexes")
//		rootFile->GetTree("Indextree")->Scan();
//
//	// RootDataFacade * dataFacade = new RootDataFacade(rootFile);
//
//	// PixelInterval * pixInterval = dataFacade->GetInterval(18414630, 99414630);  // size 13109
//
//	// cout << "Size: " << pixInterval->Size() << endl;
//
//	// cout << pixInterval->JSONify() << endl;
//
//	delete converter;
//	// delete dataFacade;
//
//	return 0;
}


