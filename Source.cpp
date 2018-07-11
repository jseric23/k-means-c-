#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <chrono>
#include <algorithm>

#define data_type int

using namespace std;
using namespace chrono;

void Euclidian_dist(vector<data_type> &centroid_x, vector<data_type> &centroid_y, vector<data_type> &dot_x, vector<data_type> &dot_y){	
	
	vector<data_type> dist,result,arr;
	data_type distance, result_x, result_y;

	for (data_type i = 0; i < dot_x.size(); i++)
		{

		for (data_type j = 0; j < centroid_x.size(); j++)
			{


				distance = sqrt(pow((dot_x[i] - centroid_x[j]), 2) + pow((dot_y[i] - centroid_y[j]), 2));
				dist.push_back(distance);

			}

			auto result = min_element(dist.begin(), dist.end()) - dist.begin();
			arr.push_back(result);
			
			//cout << "C" << result << " " << dot_x[i] << " " << dot_y[i] << endl;

			dist.clear();
		}
	
	/*for (vector<data_type>::iterator it = arr.begin(); it != arr.end(); ++it)
		cout << *it << endl;*/

	for (data_type k = 0; k < centroid_x.size(); k++)
	{
		result_x = 0, result_y = 0;
		data_type counter = 0;

		for (data_type z = 0; z < dot_x.size(); z++)
		{

			if (arr[z] == k)
			{
				result_x += dot_x[z];
				result_y += dot_y[z];
				counter++;
			}

		}
		
		result_x = result_x / counter;
		result_y = result_y / counter;
		
		cout << "Updated centroid " << k << " is:" << endl;
		cout << "Centroid[" << k << "] " << result_x << " " << result_y << endl;

	}
	
}

int main(){
	
	//srand(time(NULL));	//uncommenting this line assures random number combination every time compiling the program
	
	ifstream inputFile("input.txt");	//reading of .txt input file with random dots

	vector<data_type> input_x, input_y;
	
	data_type x,y;
	data_type k = 0;

	while(inputFile >> x >> y)	//read random dots from input file and save them to vectors
	{
		input_x.push_back(x);
		input_y.push_back(y);
			
		cout << input_x[k] << " " << input_y[k] << endl;
		k++;
	}
	
	data_type n_centr,n_centrx, n_centry;
	
	vector <data_type> nizx, nizy;

	cout << "Insert number of centroid(s):";
	cin >> n_centr;
	
	auto started = high_resolution_clock::now(); //start time measure
	
	for (int i = 0; i < n_centr; i++)
	{	
		n_centrx = rand() % 1000 + 1;	//random X coordinate in range 1 to 1000
		nizx.push_back(n_centrx);	//fill vector with X coordinates
		
		n_centry = rand() % 1000 + 1;	//random Y coordinate in range 1 to 1000
		nizy.push_back(n_centry);	//fill vector with Y coordinates
		
		cout << "Centroid[" << i << "] = " << nizx[i] << " " << nizy[i] << endl;	
	}
	
	/*for (int j = 0; j < n_centr; j++)
	{
		cout <<"X["<<j<<"] is "<< nizx[j] << endl;
		cout << "Y[" << j << "] is " << nizy[j] << endl;
	}*/

	Euclidian_dist(nizx, nizy, input_x, input_y);
		
	ofstream outputFile("output.txt");	//writing .txt output files with new dots
	
	//outputFile << Euclidian_dist(nizx, nizy, input_x, input_y) << " " << endl; //writing to output.txt in case function return
	
	streambuf *oldbuf = cout.rdbuf();  //save 
	cout.rdbuf(outputFile.rdbuf());

	Euclidian_dist(nizx, nizy, input_x, input_y);  //contents to cout will be written to output.txt
			 
	cout.rdbuf(oldbuf);  //reset back to standard input
	
	outputFile.close();
	
	auto done = high_resolution_clock::now();	//end time measure
	
	cout << "Running time: " << duration_cast<milliseconds>(done - started).count() << "ms" << endl;	//running time in milliseconds
}