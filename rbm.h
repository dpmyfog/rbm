#ifndef RBM_H
#define RBM_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <utility>

using namespace std;


class RBM{
 public:
  vector<vector<float>> weights;
  vector<int> visibles;
  vector<int> hiddens;
  vector<float> biasHidden;
  vector<float> biasVisible;
	
  
  RBM(int visible, int hidden);


  float getEnergy();
  float getFieldHidden(int hiddenIdx);
  float getFieldVisible(int visibleIdx);
  void updateHidden();
  void updateVisible();
  void setHiddenState(string state);
  void setVisibleState(string state);

  static string toString(vector<int> myState);
  void printConfiguration();
  void printState();
  static void writeArrToFile(string filename, vector<float> myvec);
  static void writeArrToFile(string filename, vector<vector<float>> myvec);
  
};
#endif
