
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "RingBuffer.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();


// Declare test functions
void generateTestSignal(float*&, int, bool);
void testRingBufferReadHardcode(CRingBuffer<float> *, float *, int, int);
void testRingBufferReadHelper(CRingBuffer<float> *, int , int );
void testOffsetHardcode(CRingBuffer<float> *, float *, int, int);
void testOffsetHelper(CRingBuffer<float> * r, int, int);
void testPostIncHardcode(CRingBuffer<float> *, float * , int);
void testPutGet(CRingBuffer<float> * , float );

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    // You don't need to use an audio file this time, though you can try if you want.
    // std::string             sInputFilePath,                 //!< file paths
    //                         sOutputFilePath;
    // static const int        kBlockSize          = 1024;
    // float                   **ppfAudioData      = 0;
    // CAudioFileIf            *phAudioFile        = 0;
    // CAudioFileIf::FileSpec_t stFileSpec;
    // long long               iInFileLength       = 0;        //!< length of input file

    clock_t                 time                = 0;

    CRingBuffer<float>      *pCRingBuffer       = 0;
    float                   *pfTestSignal       = 0;
    float                   fGain               = 1.f;
    int                     iTestSignalLength   = 16;
    int                     iRingBufferLength    = 8;

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    time                    = clock();



    //////////////////////////////////////////////////////////////////////////////
    // do processing and tests

    pCRingBuffer = new CRingBuffer<float>(iRingBufferLength);

    // Test `put()` and `get()` functions
    cout << "____\n" << endl;
    testPutGet(pCRingBuffer, 100.4);
    testPutGet(pCRingBuffer, 10);

    // Generate Test signal - we hardcode `iTestSignalLength` to 16 to generate a ramp 0 - 15
    // All proceeding test functions assume this ramp of 0-15
    generateTestSignal(pfTestSignal, iTestSignalLength, true);

    // Test ring buffer read using hardcoded values that we expect with the test signal
    testRingBufferReadHardcode(pCRingBuffer, pfTestSignal, iRingBufferLength, iTestSignalLength);

    // Test ring buffer offset with hardcoded values that we expect from the test signal
    testOffsetHardcode(pCRingBuffer, pfTestSignal, iRingBufferLength, iTestSignalLength);

    // Test postInc() functions with hardcoded signal and expected values
    testPostIncHardcode(pCRingBuffer, pfTestSignal, iRingBufferLength);

    cout << "processing done in: \t"    << (clock()-time)*1.F/CLOCKS_PER_SEC << " seconds." << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up

    return 0;
}

// Define Test functions
/*
 * Generate a ramp
 */
void generateTestSignal(float*& pfTestSignal, int iTestSignalLength, bool bAutoPrint){
    cout << "____\n" << endl;
    // fill the test signal, e.g a ramp from 0 - 15
    pfTestSignal = new float [iTestSignalLength];

    for (int i = 0; i < iTestSignalLength; i++)
    {
        pfTestSignal[i] = i;
    }

    if (bAutoPrint) {
        cout << "Test Signal: ";
        for (int i = 0; i < iTestSignalLength; i++)
        {
            cout << pfTestSignal[i] << " ";
        }
        cout << endl;
    }
}

/*
 * Test "wrap around" of Ring Buffer
 */
void testRingBufferReadHardcode(CRingBuffer<float> * pCRingBuffer, float * pfTestSignal, int iRingBufferLength, int iTestSignalLength)
{
    cout << "____\n" << endl;
    pCRingBuffer->reset();

    //Read test signal into array
    for (int i=0; i<iTestSignalLength; i++)
    {
        pCRingBuffer->putPostInc(pfTestSignal[i]);  // increment `write_idx`
    }

    // After wrap around, we expect idx=0 in the ring buffer to be `8`
    testRingBufferReadHelper(pCRingBuffer, 0, 8);
    // After wrap around, we expect idx=3 in the ring buffer to be `11`
    testRingBufferReadHelper(pCRingBuffer, 3, 11);
    // After wrap around we, expect the last value in the ring buffer to be `15`
    testRingBufferReadHelper(pCRingBuffer, iRingBufferLength-1, 15);
}

void testRingBufferReadHelper(CRingBuffer<float> * pCRingBuffer, int iReadIdx, int iExpected)
{
    std::string sTest = "Fail";
    if (pCRingBuffer->get(iReadIdx) == iExpected) {
        sTest="Pass";
    }
    cout << "`testRingBufferReadHardcode()` | Status: " << sTest <<" | Check  value of `pCRingBuffer` at read idx: " << iReadIdx << endl;
}

/*
 * Test "offset" of ring buffer
 */
void testOffsetHardcode(CRingBuffer<float> * pCRingBuffer, float * pfTestSignal, int iRingBufferLength, int iTestSignalLength)
{
    cout << "____\n" << endl;
    pCRingBuffer->reset();
    // Buffer contents should be `[0,1,2,3,4,5,7]` after this operation
    for (int i=0; i<iRingBufferLength; i++)
    {
        pCRingBuffer->putPostInc(pfTestSignal[i]);
    }

    // Set index
    pCRingBuffer->setReadIdx(3);

    //Run offeset test based from this index
    testOffsetHelper(pCRingBuffer, 0, 3);
    testOffsetHelper(pCRingBuffer, -4, 7);
    testOffsetHelper(pCRingBuffer, -12, 5);
    testOffsetHelper(pCRingBuffer, 2, 5);
    testOffsetHelper(pCRingBuffer, 7, 2);
    testOffsetHelper(pCRingBuffer, 12, 2);
}

void testOffsetHelper(CRingBuffer<float> * pCRingBuffer, int iOffset, int iExpected) {
    std::string sTest = "Fail";
    if (pCRingBuffer->get(iOffset) == iExpected) {
        sTest = "Pass";
    }
    cout << "`testOffsetHardcode()` | Status: " << sTest <<" | Check get() with offset: " << iOffset << endl;
}

/*
 * Test operation of putPostInc() and getPostInc()
 */
void testPostIncHardcode(CRingBuffer<float> * pCRingBuffer, float * pfTestSignal, int iRingBufferLength){
    cout << "____\n" << endl;
    pCRingBuffer->reset();
    // Buffer contents should be `[0,1,2,3,4,5,7]` after this operation
    for (int i=0; i<iRingBufferLength; i++)
    {
        pCRingBuffer->putPostInc(pfTestSignal[i]);
    }

    // Read the contents, the value at an index should just be equal to the index because this is a ramp function
    std::string sTest = "Fail";
    for (int i=0; i<iRingBufferLength; i++)
    {
        if (pCRingBuffer->getPostInc() == i)
        {
            sTest = "Pass";
        }
    }
    cout << "`testPostIncHardcode()` | Status: " << sTest <<" | `putPostInc()` and `getPostInc()` behave as expected "<< endl;

}

/*
 * Test basic put() and get() functions
 */
void testPutGet(CRingBuffer<float> * pCRingBuffer, float value){
    pCRingBuffer->reset();

    std::string sTest1 = "Fail";
    pCRingBuffer->put(value);
    if (pCRingBuffer->get() == value) {
        sTest1 = "Pass";
    }
    cout << "`testPutGet()` | Status: " << sTest1 << " | `put()` and `get()` using value: " << value << endl;
}

void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable for Ring Buffer Assignment" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

