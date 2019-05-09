#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;
struct Node{
    int data;
    int index=-1;
    int lowLink=-2;
    bool onStack=false;
    vector<int> vector1;
};
int index=0;
stack<int> s;
Node boxes [100100];
int sameScc[100100];
vector<vector<int>> members;
int sccCount=0;
void strongConnect(Node & n) {
    n.index = index;
    n.lowLink = index;
    index++;
    s.push(n.data);
    n.onStack = true;
    vector<int>::iterator itr;
    for(itr=n.vector1.begin(); itr!=n.vector1.end();++itr){
        int to=*itr;
        if(boxes[to].index==-1){
            strongConnect(boxes[to]);
            n.lowLink=min(n.lowLink,boxes[to].lowLink);
        }
        else if(boxes[to].onStack){
            n.lowLink=min(n.lowLink,boxes[to].index);
        }
    }
    if(n.lowLink==n.index) {
        vector<int> a;
        while (boxes[s.top()].data != n.data) {
            boxes[s.top()].onStack = false;
            sameScc[s.top()] = sccCount;
            a.push_back(s.top());
            s.pop();
        }
        boxes[s.top()].onStack = false;
        sameScc[s.top()] = sccCount;
        a.push_back(s.top());
        s.pop();
        members.push_back(a);
        sccCount++;
    }
}
int main(int argc,char*argv[]){
    if(argc!=3){
        cout<<"Run the code with the follwing command: ./project3 [input_file] [output_file]"<<endl;
        return 1;
    }
    ifstream infile(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);
    int N;
    infile>>N;
    for(int i=0;i<N;i++){
        int keynum;
        infile>>keynum;
        boxes[i].data=i;
        for(int j=0;j<keynum;j++){
            int num;
            infile>>num;
            num--;
            boxes[i].vector1.push_back(num);
        }
    }
    for(int i=0;i<N;i++) {
        if (boxes[i].index == -1) {
            strongConnect(boxes[i]);
        }
    }
    bool isChild[sccCount];
    for(int i=0;i<sccCount;i++){
        isChild[i]=false;
    }
    for(int i=0;i<N;i++){
        for(int x:boxes[i].vector1){
            if(sameScc[x]!=sameScc[i]){
                isChild[sameScc[x]]=true;
            }
        }
    }
    vector<int> res;
    int counter=0;
    for(int i=0;i<sccCount;i++){
        if(!isChild[i]){
            counter++;
            res.push_back(members[i].front());
        }
    }
    outfile<<counter<<" ";
    for(int x:res){
        x++;
        outfile<<x<<" ";
    }
    outfile.close();
    return 0;
}