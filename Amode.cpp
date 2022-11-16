#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

float **createDataMatrix(int numElement, int numSample)
{
    // Create a 2D data matrix of size numElement and numSample
    float **RFData;
    RFData = new float*[numElement];
    for (int i=0; i<numElement; i++){
        RFData[i] = new float[numSample];
    }

    return RFData;
}

int loadRFData(float **RFData, const char *fileName, int numElement, int numSample)
{
    // Open the text file fileName, read the data and store into RFData
    // You can use the getline() command to extract the data lines from the txt files
    ifstream infile(fileName); 

    if (infile.fail()){
        return -1;
    }
    
    const int MAX_SIZE = 20;
    char lineArr[MAX_SIZE];
    for (int i=0; i<numElement; i++) {
        for (int j=0; j<numSample; j++) {
            infile.getline(lineArr, MAX_SIZE);
            RFData[i][j] = atof(lineArr);
        }
    }   
}

// Create an array containing the depth location (in z-direction) for each pixel on the scanline
float *genScanlineLocation(int &numPixel)
{

    float depth;
    int numPixel;

    cout << "Scanline Depth: ";
    cin >> depth;

    cout << "Number of Pixels: ";
    cin >> numPixel;

    float scanlineLocation[numPixel];
    for (int i=0; i<numPixel; i++){
        scanlineLocation[i] = i*(depth/(numPixel-1));
    }

    return scanlineLocation;
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *genElementLocation(int numElement, float PITCH)
{
   
}

// Allocate memory to store the beamformed scanline
float *createScanline(int numPixel)
{
    
}

// Beamform the A-mode scanline
void beamform(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel, float FS, float SoS)
{
    
}

// Write the scanline to a csv file
int outputScanline(const char *fileName, float *scanlinePosition, float *scanline, int numPixel)
{
    
}

// Destroy all the allocated memory
void destroyAllArrays(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel)
{
    
}