#include<bits/stdc++.h>
using namespace std;
int arr[100][100];
bool checkForHit(int numberToBeChecked,int currentFrame[],int noOfFrames){
    for(int i=0;i<noOfFrames;i++){
        if(currentFrame[i]==numberToBeChecked){
            return true;
        }
    }
    return false;
}
int isThereEmptyFrame(int currentFrame[],int noOfFrames){
    for(int i=0;i<noOfFrames;i++){
        if(currentFrame[i]==-1){
            return i;
        }
    }
    return -999;
}
int findLastIndex(int str[],int n,int currCol,int noOfFrames){
    map<int,int> mp;
    int i=currCol;
    while(mp.size()!=noOfFrames && i>=0){
        i--;
        mp[str[i]]++;
    }
    if(mp.size()!= noOfFrames){
        return -999;
    }
    return str[i];
}
int getIndexOf(int valueToBeReplaced,int currentFrame[],int noOfFrames){
    for(int i=0;i<noOfFrames;i++){
        if(currentFrame[i]==valueToBeReplaced){
            return i;
        }
    }
    return -999;
}
int main(){
    int noOfFrames,n;
    cout<<"Enter number frames:";
    cin>>noOfFrames;
    cout<<"Enter number of pages:";
    cin>>n;
    int str[n];
    cout<<"Enter the string of length "<<n<<" :";
    for(int i=0;i<n;i++){
        cin>>str[i];
    }
    int currentFrames[noOfFrames];
    memset(currentFrames,-1,sizeof(currentFrames));
    int hit = 0;
    int miss = 0;
    int isHit;
    for(int i=0;i<n;i++){
        isHit = checkForHit(str[i],currentFrames,noOfFrames);
        if(isHit){
            hit++;
        }
        else{
            miss++;
            int indexOfEmptyFrame = isThereEmptyFrame(currentFrames,noOfFrames);
            if(indexOfEmptyFrame==-999){ //There is no empty frame
                int valueToBeReplaced = findLastIndex(str,n,i,noOfFrames);
                if(valueToBeReplaced==-999){
                    cout<<"Error1"<<endl;
                }
                int indexToBeReplaced = getIndexOf(valueToBeReplaced,currentFrames,noOfFrames);
                if(indexToBeReplaced==-999){
                    cout<<"Error2"<<endl;
                }
                currentFrames[indexToBeReplaced] = str[i];
            }
            else{
                currentFrames[indexOfEmptyFrame] = str[i];
            }
        }
        for(int j=0;j<noOfFrames;j++){
            arr[j][i] = currentFrames[j];
        }
        arr[noOfFrames][i] = isHit;
    }
    cout<<endl;
    cout<<setw(8)<<"String"<<"  | ";
    for(int i=0;i<n;i++){
        cout<<setw(4)<<str[i];
    }
    cout<<endl;
    for(int i=0;i<n*5;i++){
        cout<<'-';
    }
    cout<<endl;
    for(int i=0;i<noOfFrames;i++){
        cout<<setw(8)<<"frame-"<<i+1<<" | ";
        for(int j=0;j<n;j++){
            cout<<setw(4)<<arr[i][j];
        }
        cout<<endl;
    }
    cout<<setw(12)<<" ";
    for(int j=0;j<n;j++){
            if(arr[noOfFrames][j] == 1){
                cout<<setw(4)<<"^";
            }
            else{
                cout<<setw(4)<<"*";
            }
        }
        cout<<endl;
    cout<<endl<<"Hit:"<<hit<<endl<<"Page Faults:"<<miss<<endl;
    cout<<endl<<"Hit Ratio:"<<(float)hit/n<<endl<<"Page Faults:"<<(float)miss/n<<endl;
    return 0;
}
