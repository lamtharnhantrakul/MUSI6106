
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath;

    long long               iInFileLength       = 0;        //!< length of input file

    clock_t                 time                = 0;

    float                   **ppfAudioData      = 0;  // this is like a double array

    CAudioFileIf            *phAudioFile        = 0;

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments

    sInputFilePath = argv[1];   // Assign input file path to `sInputFilePath` string variable
    sOutputFilePath = argv[2];  // Assign output file path to `sOutputFilePath` string variable
    // cout << sInputFilePath << "\n";
    // cout << sOutputFilePath << "\n";

    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file

    CAudioFileIf::create(phAudioFile);  // need to explcitly create using class static method
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);


    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    time                    = clock();

    // get audio data and write it to the output file

    ppfAudioData = new float* [2];
    for (int i = 0; i < 2; i++)
    {
        ppfAudioData[i] = new float [1024];
    }

    long long int num_frames = 1024;

    std::fstream textWriter(sOutputFilePath, std::fstream::out);
    while (! phAudioFile->isEof()) {
        phAudioFile->readData(ppfAudioData, num_frames);
        for (int j=0; j< 1024; j++) {
            for (int i = 0; i < 2; i++) {
                if (i == 0) {
                    textWriter << ppfAudioData[i][j] << "\t";
                } else {
                    textWriter << ppfAudioData[i][j] << endl;
                }
            }
        }
    }

    cout << "reading/writing done in: \t"    << (clock()-time)*1.F/CLOCKS_PER_SEC << " seconds." << endl;
    //////////////////////////////////////////////////////////////////////////////
    // get audio info and print it to stdout

    //////////////////////////////////////////////////////////////////////////////
    // do processing
    cout << "Processing Complete!!!" << endl << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up

    // DESTROY ARRAY
    // delete second dimension of array
    for (int i=0; i < 2; i++) {
        delete [] ppfAudioData[i];
    }
    // delete first dimension of array
    delete [] ppfAudioData;

    // DESTROY THE `phAudioFile()` object
    CAudioFileIf::destroy(phAudioFile);

    // Didn't close!

    return 0;
    
}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

