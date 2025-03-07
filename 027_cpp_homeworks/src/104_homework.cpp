#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

//add class definitions below this line
class Median{
  public:
    double CalculateMedian(int a, int b){
          vector<int> nums;
          nums.push_back(a);
          nums.push_back(b);
          return getMedian(nums);
      }
    double CalculateMedian(int a, int b, int c){
        vector<int> nums;
        nums.push_back(a);
        nums.push_back(b);
        nums.push_back(c);
        return getMedian(nums);
    }
    double CalculateMedian(int a, int b, int c, int d){
        vector<int> nums;
        nums.push_back(a);
        nums.push_back(b);
        nums.push_back(c);
        nums.push_back(d);
        return getMedian(nums);
    }
    double CalculateMedian(int a, int b, int c, int d, int e){
        vector<int> nums;
        nums.push_back(a);
        nums.push_back(b);
        nums.push_back(c);
        nums.push_back(d);
        nums.push_back(e);
        return getMedian(nums);
    }
    double getMedian(vector<int>& nums){
        sort(nums.begin(), nums.end());
        int size = nums.size();
        if(size%2==0){
            return (nums[size/2-1]+nums[size/2])/2.0;
        }else{
            return nums[size/2];
        }
    }
};
//add class definitions above this line


int main() {

    //DO NOT EDIT code below this line

    Median m;
    cout << m.CalculateMedian(3, 5, 1, 4, 2) << endl;
    cout << m.CalculateMedian(8, 6, 4, 2) << endl;
    cout << m.CalculateMedian(9, 3, 7) << endl;
    cout << m.CalculateMedian(5, 2) << endl;
    Median m2;
    cout << m2.CalculateMedian(24, 22, 21, 23, 20) << endl;
    cout << m2.CalculateMedian(12, 18, 9, 3) << endl;
    cout << m2.CalculateMedian(0, 1, 0) << endl;
    cout << m2.CalculateMedian(5, 3) << endl;

    //DO NOT EDIT code above this line

    return 0;

}
