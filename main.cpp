#include <iostream>
#include <random>
#include <bitset>
#include <cmath>
#include <map>
#include "rbm.h"


void testDistributionHidden(){
  int norm = 0;
  RBM net(5, 2);
  map<string,double> theoretical;
  map<string,double> probs;
//loop 100,000 times
  for(int i = 0; i<100000; i++){
    net.updateHidden();
    string myString = RBM::toString(net.hiddens);
    if (probs.find(myString)==probs.end())
      probs.insert(make_pair(myString, 0));
    if(theoretical.find(myString) == theoretical.end())
      theoretical.insert(make_pair(myString, 0));
    
    probs[myString]+=1;
    norm+=1;
  }
  cout << "PRACTICE" << endl;
  for(auto it = probs.begin(); it != probs.end(); it++){
    it->second = it->second/norm;
    cout << "State: " << it->first << "  Prob: " << it->second << endl;
  }

  //want to calculate a partition function
  float partition = 0;
  for(auto it = theoretical.begin(); it != theoretical.end(); it++){
    string state = it->first;
    net.setHiddenState(state);
    partition+= exp(-1*net.getEnergy());
  }
  for(auto it = theoretical.begin(); it != theoretical.end(); it++){
    net.setHiddenState(it->first);
    it->second = exp(-1*net.getEnergy())/partition;
  }

  
  cout << endl << endl << "THEORETICAL" << endl;
  for(auto it = theoretical.begin(); it != theoretical.end(); it++){
    cout << "State: " << it->first << "  Prob: " << it->second << endl;
  }
}

void testDistributionVisible(){
  int norm = 0;
  RBM net(2, 5);
  map<string,double> theoretical;
  map<string,double> probs;
//loop 100,000 times
  for(int i = 0; i<100000; i++){
    net.updateVisible();
    string myString = RBM::toString(net.visibles);
    if (probs.find(myString)==probs.end())
      probs.insert(make_pair(myString, 0));
    if(theoretical.find(myString) == theoretical.end())
      theoretical.insert(make_pair(myString, 0));
    
    probs[myString]+=1;
    norm+=1;
  }
  cout << "PRACTICE" << endl;
  for(auto it = probs.begin(); it != probs.end(); it++){
    it->second = it->second/norm;
    cout << "State: " << it->first << "  Prob: " << it->second << endl;
  }

  //want to calculate a partition function
  float partition = 0;
  for(auto it = theoretical.begin(); it != theoretical.end(); it++){
    string state = it->first;
    net.setVisibleState(state);
    partition += exp(-1*net.getEnergy());
  }
  for(auto it = theoretical.begin(); it != theoretical.end(); it++){
    net.setVisibleState(it->first);
    it->second = exp(-1*net.getEnergy())/partition;
  }

  
  cout << endl << endl << "THEORETICAL" << endl;
  for(auto it = theoretical.begin(); it != theoretical.end(); it++){
    cout << "State: " << it->first << "  Prob: " << it->second << endl;
  }
}


int main(){
  srand(time(NULL));
  testDistributionVisible();

}
