// Author: Jacob Christiansen
// Class: CSCI 2270
// Course Instructor: Rhonda Hoenigman
// Recitation: 105
//
// Assignment 1

//Worked with / assisted Bingham Mitchell, Justin Vuong, Willie Chew, Will Abrams, and Alex Book over the course of this project.

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;



//creating a struct called ITEM that always has 3 strings (even the default constructer creates 3 empty strings)
//ITEM also has a constructor that takes in those 3 strings as parameters, representing the type of item, if it's wanted or being sold, and at what price.
struct ITEM{
	string type;
	string saleORwant; //true = sale, false = want
	string price;

	ITEM(){ //dflt cnstr
		type = "";
		saleORwant = "";
		price = "";
	}
	ITEM(string t, string sow, string p){
		type = t;
		saleORwant = sow;
		price = p;
	}

};

//this is how Prof. Hoenigman's book told us to write a function that removes one spot in an array and shifts all the rest above it around.
void removeMatch(int removeNum, ITEM mBoard[]){
	for(int i=removeNum; i<99; i++){
		mBoard[i].type = mBoard[i+1].type;
		mBoard[i].saleORwant = mBoard[i+1].saleORwant;
		mBoard[i].price = mBoard[i+1].price;
	}
}

int count = 0; //this variable needed to be outside the matchTest fuction that way it wouldn't be reset every time it ran.

//matchTest loops through the full mBoard array looking for matching ITEMS (it won't error on the empty ITEMS because we set them to "" earlier).
//if it finds a match, it calls the removeMatch function, and changes the mBoard array, as well as adding it to the matchArray. (and then returns true)
//if it doesnt't find a match, it just adds it to the mBoard array (or rather, turns the ty, sw, and pr varibales into a new ITEM, then adds it. This is done inside getInfo though, when this fuction returns false)
bool matchTest(ITEM mBoard[], ITEM matchArr[], string ty, string sw, string pr){
	for(int i=0; i<100; i++){
		if(mBoard[i].type == ty && mBoard[i].saleORwant != sw){
			if(mBoard[i].saleORwant == " wanted" && stoi(mBoard[i].price) >= stoi(pr)){

				matchArr[count] = ITEM(ty, "", pr);
				removeMatch(i, mBoard);
				count++;
				return true;
			}
			else if(mBoard[i].saleORwant == " for sale" && stoi(mBoard[i].price) <= stoi(pr)){

				matchArr[count] = ITEM(mBoard[i].type, "", mBoard[i].price);
				removeMatch(i, mBoard);
				count++;
				return true;
			}
		}
	}
	return false;
}

//getInfo opens a file, grabs each line, splits it into different parts (string stream), put them into varibles, and passes them into the the matchTest fucntion.
//if matchTest returns false, then it turns the ty, sw, and pr varibales into a new ITEM, then adds it to the mBoard. A 'true' return will do nothing (handled in matchTest)
void getInfo(string filename, ITEM mBoard[], ITEM matchArr[]){
	ifstream fr;
	fr.open(filename);
	if(fr.is_open()){
		string line;
		int index = 0;
		while(getline(fr, line)){

			stringstream ss(line);
			string ty; //type
			string sw; //for sale/wanted
			string pr; //price

			getline(ss, ty, ',');
			getline(ss, sw, ',');
			getline(ss, pr);


			if(!matchTest(mBoard, matchArr, ty, sw, pr)){
				mBoard[index] = ITEM(ty, sw, pr);
				index++;
			}
		}
	}

	else{
		cout<<"Failed to open file!"<<endl;
	}
}

//outInfo simply loops through my two arrays and prints all the ITEMS from matchArray and mBoard in the desired project format
void outInfo(ITEM mBoard[], ITEM matchArr[]){
	for(int i=0; i<100; i++){
		if(matchArr[i].type != ""){
			cout<<matchArr[i].type<<","<<matchArr[i].price<<endl;
		}
	}
	cout<<"#"<<endl;

	for(int i=0; i<100; i++){
		if(mBoard[i].type != ""){
			cout<<mBoard[i].type<<","<<mBoard[i].saleORwant<<","<<mBoard[i].price<<endl;
		}
	}
	cout<<"#"<<endl;
}


//main simply runs all the other functions above, but first defines all the necesary variables (ITEM arrays), and input arguments from terminal that will determine the reading in file.
int main(int argc, char*argv[]){
	ITEM mBoard[100];
	ITEM matchArr[100];
	getInfo(argv[1], mBoard, matchArr);
	outInfo(mBoard, matchArr);
}