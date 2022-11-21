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
    // Create a 2D data matrix RFData of size numElement and numSample
    float **RFData;
    RFData = new float*[numElement];

    //for loop creates new float array of numSample size for each numElement in RFData
    for (int i=0; i<numElement; i++){
        RFData[i] = new float[numSample];
    }

    return RFData; //return RFData
}

int loadRFData(float **RFData, const char *fileName, int numElement, int numSample)
{
    // Open the text file fileName, read the data and store into RFData
    // You can use the getline() command to extract the data lines from the txt files
    ifstream infile; 
    infile.open(fileName);

    if (infile.fail()){ //if file fails to open
        return -1;
    }
    
    const int MAX_SIZE = 20;
    char lineArr[MAX_SIZE];

    for (int i=0; i<numElement; i++){ //for loop to store line in fileName to lineArr for each element in text file
        for (int k=0; k<numSample; k++){
            infile.getline(lineArr, MAX_SIZE);
            RFData[i][k] = atof(lineArr); //convert to float type
        }
    }
    infile.close();
    return 0; //return integer
}

// Create an array containing the depth location (in z-direction) for each pixel on the scanline
float *genScanlineLocation(int &numPixel)
{

    float depth;

    //user inputs for depth and numPixel
    cout << "Scanline Depth: ";
    cin >> depth;

    cout << "Number of Pixels: ";
    cin >> numPixel;

    //new float array scanlineLocation of numPixel size
    float *scanlineLocation;
    scanlineLocation = new float[numPixel];
    for (int i=0; i<numPixel; i++){
        scanlineLocation[i] = i*(depth/(numPixel-1)); //calculates location and stores in i'th element of scanlineLocation
    }

    return scanlineLocation;
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *genElementLocation(int numElement, float PITCH)
{
    //new float array eleLocation of numElement size
    float *eleLocation;
    eleLocation = new float[numElement];  

    //for loop to store element location into each array element
    for (int n=0; n<=numElement-1; n++){
        eleLocation[n] = (n-((numElement-1)/2)) * PITCH;
    }

    return eleLocation;
}

// Allocate memory to store the beamformed scanline
float *createScanline(int numPixel)
{
    //new float type array of numPixel size
    float *scanline;
    scanline = new float[numPixel];
    return scanline;
}

// Beamform the A-mode scanline
void beamform(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel, float FS, float SoS)
{
    
    float tForward[numPixel];
    float tBackward[numPixel][numElement];
    float tTotal[numPixel][numElement];
    int s[numPixel][numElement];
    float pReal[numPixel];
    float pImag[numPixel];

    for (int i=0; i<numPixel; i++){
        float sumReal = 0;
        float sumImag = 0;
        tForward[i] = scanlinePosition[i]/SoS; //calculate time scan travels forward

        for (int k=0; k<numElement; k++){
            tBackward[i][k] = (sqrt(pow(scanlinePosition[i], 2) + pow(elementPosition[k], 2)))/SoS; //calculate time scan travels back to tranducer element
            tTotal[i][k] = tForward[i] + tBackward[i][k]; //calculate total time of scan to travel
            s[i][k] = floor(tTotal[i][k] * FS); //sampling frequency of i'th scanline from k'th tranducer
            sumReal = sumReal + realRFData[k][s[i][k]];
            sumImag = sumImag + imagRFData[k][s[i][k]];
        }
        //store sum into pulse signal arrays
        pReal[i] = sumReal;
        pImag[i] = sumImag;
        scanline[i] = sqrt(pow(pReal[i], 2) + pow(pImag[i], 2)); //calculate scanline at i'th element
    }
}

// Write the scanline to a csv file
int outputScanline(const char *fileName, float *scanlinePosition, float *scanline, int numPixel)
{
    //create and open output.csv
    ofstream outfile;
    outfile.open(fileName);

    if (outfile.fail()){
        return -1;
    }

    for (int i=0; i<numPixel; i++){
        outfile << scanlinePosition[i] << "," << scanline[i] << endl; //store scanlinePosition[i] and scanline[i] separated by comma into csv file
    }
    outfile.close();
    return 0;
}

// Destroy all the allocated memory
void destroyAllArrays(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel)
{
    // delete all arrays and release all memory allocation from arrays
    delete scanline;
    delete scanlinePosition;
    delete elementPosition;

    for (int i=0; i<numElement; i++){
        delete realRFData[i];
        delete imagRFData[i];
    }
}