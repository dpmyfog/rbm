#include <iostream>
#include <random>
#include <bitset>
#include <cmath>
#include <map>
#include "rbm.h"


void testDistribution(){
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

  for(auto it = theoretical.begin(); it != theoretical.end(); it++){
    float denom = 1;
    float nume = 1;

    string state = it->first;

    net.setHiddenState(state);

    cout << "about to compute exp" << endl;
    float magnetization = net.getFieldHidden(0);
    nume = exp(magnetization*net.hiddens[0]);
    denom = nume + exp(-1*magnetization*net.hiddens[0]);
    cout << "done computing exp" << endl;
    float probability = nume/denom;
    it->second = probability;
  }

  cout << endl << endl << "THEORETICAL" << endl;
  for(auto it = theoretical.begin(); it != theoretical.end(); it++){
    it->second;
    cout << "State: " << it->first << "  Prob: " << it->second << endl;
  }
  
  
  
}

int main(){
  srand(time(NULL));
  testDistribution();

}
