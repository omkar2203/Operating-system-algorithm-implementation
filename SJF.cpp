#include<bits/stdc++.h>
using namespace std;
struct processDetails{
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitTime;
    int processStatus;
};

void sortProcessesWithRespectToArrivalTime(struct processDetails arr[], int n)
{
    int i,j;
    struct processDetails key;
    for (i=1; i<n; i++)
    {
        key = arr[i];
        j = i-1;
        while (j >= 0 && arr[j].arrivalTime > key.arrivalTime)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}
int getTheMinimumBurstTimeLessThanCurrentTime(struct processDetails p[],int n,int currentTime){
    int i;
    int flag = 0;
    for(i=0;i<n;i++){
        if(p[i].arrivalTime > currentTime){
            break;
        }
    }
    int tempMinBurstTime = INT_MAX;
    int res;
    i--;
    while(i>=0){
        if(p[i].burstTime<=tempMinBurstTime && p[i].processStatus == 1){
            flag = 1;
            res = i;
            tempMinBurstTime = p[i].burstTime;
        }
        i--;
    }
    if(flag){
        return res;
    }
    return -999;
}

int main(){
    int numberOfProcesses;
    cout<<"Enter number of processes:";
    cin>>numberOfProcesses;

    struct processDetails p[numberOfProcesses];

    for(int process=0;process<numberOfProcesses;process++){
        cout<<"Enter 'Arrival Time' of process-"<<process<<":";
        cin>>p[process].arrivalTime;
        cout<<"Enter 'Burst Time' of process-"<<process<<":";
        cin>>p[process].burstTime;
        p[process].pid = process;
        p[process].processStatus = 1; //Not Yet Completed
    }
    sortProcessesWithRespectToArrivalTime(p,numberOfProcesses);
    int currentTime = 0,minBurstTimeIndex;
    int idleTime = 0;
    float sumCt=0,sumTat=0,sumWt=0;
    vector<int> vec;
    for(int i=0;i<numberOfProcesses;i++){
        minBurstTimeIndex = getTheMinimumBurstTimeLessThanCurrentTime(p,numberOfProcesses,currentTime);
        if(minBurstTimeIndex==-999){
            do{
                currentTime++;
                idleTime++;
                minBurstTimeIndex=getTheMinimumBurstTimeLessThanCurrentTime(p,numberOfProcesses,currentTime);
            }while(minBurstTimeIndex==-999);
        }
        vec.push_back(minBurstTimeIndex);
        currentTime += p[minBurstTimeIndex].burstTime;
        p[minBurstTimeIndex].processStatus = 0; // Completed
        p[minBurstTimeIndex].completionTime = currentTime;
        sumCt += p[minBurstTimeIndex].completionTime;
        p[minBurstTimeIndex].turnAroundTime = p[minBurstTimeIndex].completionTime - p[minBurstTimeIndex].arrivalTime;
        sumTat += p[minBurstTimeIndex].turnAroundTime;
        p[minBurstTimeIndex].waitTime = p[minBurstTimeIndex].completionTime - p[minBurstTimeIndex].burstTime - p[minBurstTimeIndex].arrivalTime;
        sumWt += p[minBurstTimeIndex].waitTime;
    }

    cout<<endl<<endl;
    cout<<setw(4)<<"pid"<<setw(4)<<"AT"<<setw(4)<<"BT"<<setw(4)<<"CT"<<setw(4)<<"TAT"<<setw(4)<<"WT"<<endl;
    for(int i=0;i<numberOfProcesses;i++){
        cout<<setw(4)<<p[i].pid<<setw(4)<<p[i].arrivalTime<<setw(4)<<p[i].burstTime<<setw(4)<<p[i].completionTime<<setw(4)<<p[i].turnAroundTime<<setw(4)<<p[i].waitTime<<endl;
    }


    cout<<endl<<endl;
    cout<<"Processes executed in this order:";
    for(int i=0;i<vec.size();i++){
        cout<<"p"<<vec[i]<<" ";
    }
    cout<<endl<<endl;
    cout<<"Idle time = "<<idleTime<<"ms"<<endl;
    cout<<"Average completion time : "<<sumCt/numberOfProcesses<<"ms"<<endl;
    cout<<"Average turn around time : "<<sumTat/numberOfProcesses<<"ms"<<endl;
    cout<<"Average wait time : "<<sumWt/numberOfProcesses<<"ms"<<endl;

    return 0;
}
