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
    int elementCount = 0;
    int sampleCount = 0;

    while (infile.getline(lineArr, MAX_SIZE)){
        RFData[elementCount][sampleCount] = atof(lineArr);
        sampleCount++;
        if (sampleCount == numSample){
            elementCount++;
            sampleCount = 0;
        }
        if (elementCount == numElement){
            break;
        }
    }
}

// Create an array containing the depth location (in z-direction) for each pixel on the scanline
float *genScanlineLocation(int &numPixel)
{

    float depth;
    int pixel;

    cout << "Scanline Depth: ";
    cin >> depth;

    cout << "Number of Pixels: ";
    cin >> pixel;

    float scanlineLocation[pixel];
    for (int i=0; i<pixel; i++){
        scanlineLocation[i] = i*(depth/(pixel-1));
    }

    return scanlineLocation;
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *genElementLocation(int numElement, float PITCH)
{
    float eleLocation[numElement];  

    for (int n=0; n<=numElement-1; n++){
        eleLocation[n] = (n-((numElement-1)/2)) * PITCH;
        cout << n << ":" << eleLocation[n] << endl;
    }
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