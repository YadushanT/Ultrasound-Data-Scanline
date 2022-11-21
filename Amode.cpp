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
    ifstream infile; 
    infile.open(fileName);

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
    infile.close();
    return 0;
}

// Create an array containing the depth location (in z-direction) for each pixel on the scanline
float *genScanlineLocation(int &numPixel)
{

    float depth;

    cout << "Scanline Depth: ";
    cin >> depth;

    cout << "Number of Pixels: ";
    cin >> numPixel;

    float *scanlineLocation;
    scanlineLocation = new float[numPixel];
    for (int i=0; i<numPixel; i++){
        scanlineLocation[i] = i*(depth/(numPixel-1));
        //cout << scanlineLocation[i] << endl;
    }

    return scanlineLocation;
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *genElementLocation(int numElement, float PITCH)
{
    float *eleLocation;
    eleLocation = new float[numElement];  

    for (int n=0; n<=numElement-1; n++){
        eleLocation[n] = (n-((numElement-1)/2)) * PITCH;
        //cout << n << ":" << eleLocation[n] << endl;
    }

    return eleLocation;
}

// Allocate memory to store the beamformed scanline
float *createScanline(int numPixel)
{
    float *scanline;
    scanline = new float[numPixel];
    return scanline;
}

// Beamform the A-mode scanline
void beamform(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel, float FS, float SoS)
{
    /*
    float **tForward;
    tForward = new float*[numPixel];

    float **tBackward;
    tBackward = new float*[numPixel];
    */
    float **tTotal;
    tTotal = new float*[numPixel];

    int **s;
    s = new int*[numPixel];

    float *pReal;
    pReal = new float[numPixel];
    float *pImag;
    pImag = new float[numPixel];

    for (int i=0; i<numPixel; i++){
        float sumReal = 0;
        float sumImag = 0;
        //tBackward[i] = new float[numElement];
        tTotal[i] = new float[numElement];
        s[i] = new int[numElement];

        //*tForward[i] = scanlinePosition[i]/SoS;
        for (int k=0; k<numElement; k++){
            //tBackward[i][k] = (sqrt(pow(scanlinePosition[i], 2) + pow(elementPosition[i], 2)))/SoS;
            tTotal[i][k] = (scanlinePosition[i] + (sqrt(pow(scanlinePosition[i], 2) + pow(elementPosition[i], 2))))/SoS;
            s[i][k] = floor(tTotal[i][k] * FS);
            sumReal = sumReal + realRFData[k][s[i][k]];
            sumImag = sumImag + imagRFData[k][s[i][k]];
            cout << s[i][k] << endl; //why is it not outputting array?
        }
        pReal[i] = sumReal;
        pImag[i] = sumImag;
        scanline[i] = sqrt(pow(pReal[i], 2) + pow(pImag[i], 2));
    }
}

// Write the scanline to a csv file
int outputScanline(const char *fileName, float *scanlinePosition, float *scanline, int numPixel)
{
    ofstream outfile;
    outfile.open(fileName);

    if (outfile.fail()){
        return -1;
    }

    for (int i=0; i<numPixel; i++){
        outfile << scanlinePosition[i] << "," << scanline[i] << endl;
    }
    outfile.close();
    return 0;
}

// Destroy all the allocated memory
void destroyAllArrays(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel)
{
    delete scanline;
    delete scanlinePosition;
    delete elementPosition;

    for (int i=0; i<numElement; i++){
        delete realRFData[i];
        delete imagRFData[i];
    }
}