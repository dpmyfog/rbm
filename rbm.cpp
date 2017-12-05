#include <random>
#include <fstream>
#include <cmath>

#include "rbm.h"



using namespace std;

RBM::RBM(int visible, int hidden){
  visibles.resize(visible, 1);
  hiddens.resize(hidden, 1);

  biasVisible.resize(visible, 1);
  biasHidden.resize(hidden, 1);

  weights.resize(visible, vector<float>(hidden, 1));

  //randomize everything
  float randProb = 0;

  for(int i = 0; i < visibles.size(); i++){
    randProb = (float)rand()/RAND_MAX;
    if(randProb > 0.5) visibles[i] = -1;
    randProb = (float) rand()/RAND_MAX;
    biasVisible[i] = randProb;
    randProb = (float)rand()/RAND_MAX;
    if(randProb > 0.5) biasVisible[i]*=-1;
  }

  for(int j = 0; j < hiddens.size(); j++){
    randProb = (float)rand()/RAND_MAX;
    if(randProb > 0.5) hiddens[j] = -1;
    randProb = (float) rand()/RAND_MAX;
    biasHidden[j] = randProb;
    randProb = (float)rand()/RAND_MAX;
    if(randProb > 0.5) biasHidden[j]*=-1;
  }

  for(int row = 0; row < visibles.size(); row++){
    for(int col = 0; col < hiddens.size(); col++){
      randProb = (float)rand()/RAND_MAX;
      weights[row][col] = randProb;
      randProb = (float)rand()/RAND_MAX;
      if(randProb > 0.5) weights[row][col]*=-1;
    }
  }

}

float RBM::getEnergy(){
  float totalEnergy = 0;
  for(int row = 0; row < visibles.size(); row++){
    for(int col = 0; col < hiddens.size(); col++){
      totalEnergy += visibles[row]*weights[row][col]*hiddens[col];
    }
  }
  
  for(int i = 0; i < visibles.size(); i++){
    totalEnergy += visibles[i]*biasVisible[i];
  }
  
  for(int j =0; j < hiddens.size(); j++){
    totalEnergy += hiddens[j]*biasHidden[j];
  }
  return -1*totalEnergy;
}

float RBM::getFieldHidden(int hiddenIdx){
  float field = 0;
  for(int row = 0; row < visibles.size(); row++){
    field += weights[row][hiddenIdx]*visibles[row];
  }
  field+=biasHidden[hiddenIdx];

  return field;
}

float RBM::getFieldVisible(int visibleIdx){
  float field = 0;
  for(int col = 0; col < hiddens.size(); col++){
    field += weights[visibleIdx][col]*hiddens[col];
  }
  field+=biasVisible[visibleIdx];

  return field;
}

void RBM::updateHidden(){
  for(int j = 0; j < hiddens.size(); j++){
    float nume = exp(getFieldHidden(j));
    float denom = nume + exp(-1*getFieldHidden(j));

    float threshold = nume/denom;
    //cout << endl << "index: " << j << "===================" << endl;
    //cout << "probUp: " << threshold << endl;
    float prob = ((float) rand()/ (RAND_MAX));
    //cout << "roll: " << prob << endl;
    if(prob < threshold) hiddens[j] = 1;
    else hiddens[j] = -1;
    
    //cout << RBM::toString(hiddens) << endl;
  }
}

void RBM::updateVisible(){
  for(int i = 0; i < visibles.size(); i++){
    float nume = exp(getFieldVisible(i));
    float denom = nume + exp(-1*getFieldVisible(i));

    float threshold = nume/denom;

    float prob = ((float) rand()/ (RAND_MAX));
    if(prob < threshold) visibles[i] = 1;
    else visibles[i] = -1;
    
  }
}

void RBM::setHiddenState(string state){
  for(int i = 0; i < state.size(); i++){
    if(state[i] == '0') hiddens[i] = -1;
    else hiddens[i] = 1;
  }
}


void RBM::setVisibleState(string state){
  for(int i = 0; i < state.size(); i++){
    if(state[i] == '0') visibles[i] = -1;
    else visibles[i] = 1;
  }
}

string RBM::toString(vector<int> myState){
  string out = "";
  for(int i = 0; i < myState.size(); i++){
    if(myState[i] == -1) out+="0";
    else out+="1";
  }
  return out;
}


void RBM::printConfiguration(){
  
  cout << "WEIGHTS============================" << endl;
  for(int row = 0; row < visibles.size(); row++){
    for(int col = 0; col < hiddens.size(); col++){
      cout << weights[row][col] << " ";
    }
    cout << endl;
  }
  
  cout << "STATE==============================" << endl;
  cout << "VISIBLE:" << endl;
  for(auto e: visibles) cout << e << " ";
  cout << endl;

  cout << "HIDDEN:" << endl;
  for(auto e: hiddens) cout << e << " ";
  cout << endl;

  //for(auto e: bias) cout << e << " ";
  //cout << endl;
}

void RBM::printState(){
  cout << "VISIBLE:" << endl;
  for(auto e:visibles) cout << e << " ";
  cout << endl;

  cout << "HIDDEN:" << endl;
  for(auto e:hiddens) cout << e << " ";
  cout << endl;

}

void RBM::writeArrToFile(string filename, vector<float> myvec){
  ofstream myfile;
  myfile.open(filename);
  for(int i = 0; i < myvec.size(); i++){
    myfile << myvec[i] << endl;
  }
  myfile.close();
  
}

void RBM::writeArrToFile(string filename, vector<vector<float>> myvec){
  ofstream myfile;
  myfile.open(filename);
  for(int i = 0; i < myvec.size(); i++){
    for(int j = 0; j < myvec[0].size(); j++){
      myfile << myvec[i][j] << " ";
    }
    myfile << endl;
  }
  myfile.close();
}

