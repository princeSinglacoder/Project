#include<bits/stdc++.h>
using namespace std;
class Process{
    public:
        int Priority;   // priority can be anything like higher the no. higher the priority
        int id;
        int Arrival_Time;
        int Burst_Time;
        int Remaining_Time;
        int Comp_Time;
        int TA_Time;
        int W_Time;
};
bool comparator(Process p1,Process p2){      // THis is for FCFS and Round-Robin
    return p1.Arrival_Time<p2.Arrival_Time;
}
bool comp(Process p1,Process p2){           // THIs is for SJF and SRTF
    if(p1.Arrival_Time==p2.Arrival_Time){
        return p1.Burst_Time<p2.Burst_Time;
    }
    return p1.Arrival_Time<p2.Arrival_Time;
}
bool priorityComp(Process p1,Process p2){
    if(p1.Arrival_Time==p2.Arrival_Time){
        return p1.Priority>p2.Priority;
    }
    return p1.Arrival_Time<p2.Arrival_Time;
}
void input(vector<Process>&arr){
    int size;
    cout<<"Enter no. of processes in RAM(Ready Queue): ";
    cin>>size;
    arr.resize(size);
    cin.ignore();
    // Now take input Arrival and Burst Time
    for(int i=0;i<size;i++){
        int Arrival,Burst;
        cout<<"Enter Arrival and Burst Time of process"<<i+1<<": ";
        cin>>Arrival>>Burst;
        arr[i].id=i+1,arr[i].Arrival_Time=Arrival,arr[i].Burst_Time=Burst;
    }
}
void performOper_SRTF(vector<Process>&arr,int size){
    if(size==0)return;
    priority_queue<Process, vector<Process>, function<bool(Process, Process)>> pq([](Process p1, Process p2) {
        if (p1.Remaining_Time == p2.Remaining_Time) {
            return p1.Arrival_Time > p2.Arrival_Time; // Tie-breaker by Arrival Time
        }
        return p1.Remaining_Time > p2.Remaining_Time;
    });
    int startTime=0,j=1;
    bool flag=true;
    pq.push(arr[0]);
    while(!pq.empty()){
        Process temp=pq.top();
        if(startTime<temp.Arrival_Time)startTime=temp.Arrival_Time;
        if(startTime>=temp.Arrival_Time){
            pq.pop();
            startTime++;
            temp.Remaining_Time--;
            while(flag){
                if(j==size){
                    flag=false;
                    break;
                }
                if(arr[j].Arrival_Time<=startTime){
                    pq.push(arr[j]);
                    j++;
                }
                else{
                    break;
                }
            }
            if(temp.Remaining_Time){
                pq.push(temp);
            }
            else{
                arr[temp.id-1].Comp_Time=startTime;
                arr[temp.id-1].TA_Time=arr[temp.id-1].Comp_Time-arr[temp.id-1].Arrival_Time;
                arr[temp.id-1].W_Time=arr[temp.id-1].TA_Time-arr[temp.id-1].Burst_Time;
            }
        }
    }
}
void performOper_RoundRobin(vector<Process>&arr,int size,int time_Quantum){
    if(size==0)return;
    int startTime=arr[0].Arrival_Time,j=1;
    bool flag=true;
    queue<Process>q;
    q.push(arr[0]);
    while(!q.empty()){
        Process temp=q.front();
        q.pop();
        if(temp.Burst_Time>=time_Quantum){
            temp.Burst_Time=temp.Burst_Time-time_Quantum;
            startTime+=time_Quantum;
            while(flag){
                if(j==size){
                    flag=false;
                    break;
                }
                if(arr[j].Arrival_Time<=startTime){
                    q.push(arr[j]);
                    j++;
                }
                else{
                    break;
                }
            }
            if(temp.Burst_Time){
                q.push(temp);
            }
            else{  // Means Burst time is zero
                arr[temp.id-1].Comp_Time=startTime;
                arr[temp.id-1].TA_Time=arr[temp.id-1].Comp_Time-arr[temp.id-1].Arrival_Time;
                arr[temp.id-1].W_Time=arr[temp.id-1].TA_Time-arr[temp.id-1].Burst_Time;
            }
        }
        else{      // Means Burst time is about to zero
            startTime+=temp.Burst_Time;
            arr[temp.id-1].Comp_Time=startTime;
            arr[temp.id-1].TA_Time=arr[temp.id-1].Comp_Time-arr[temp.id-1].Arrival_Time;
            arr[temp.id-1].W_Time=arr[temp.id-1].TA_Time-arr[temp.id-1].Burst_Time;
        }
    }
}
void performOper_Priority(vector<Process>&arr,int size){
    if(size==0)return;
    priority_queue<Process,vector<Process>,function<bool(Process,Process)>>pq([](Process p1,Process p2){
        return p1.Priority<p2.Priority; // Max-Heap that contain higher priority process
    });
    int startTime=0,j=1;
    bool flag=true;
    pq.push(arr[0]);
    while(!pq.empty()){
        Process temp=pq.top();
        if(startTime<temp.Arrival_Time)startTime=temp.Arrival_Time;
        if(startTime>=temp.Arrival_Time){
            pq.pop();
            startTime++;
            while(flag){
                if(j==size){
                    flag=false;
                    break;
                }
                if(arr[j].Arrival_Time<=startTime){
                    pq.push(arr[j]);
                    j++;
                }
                else{
                    break;
                }
            }
            temp.Remaining_Time--;
            if(temp.Remaining_Time){
                pq.push(temp);
            }
            else{
                arr[temp.id-1].Comp_Time=startTime;
                arr[temp.id-1].TA_Time=arr[temp.id-1].Comp_Time-arr[temp.id-1].Arrival_Time;
                arr[temp.id-1].W_Time=arr[temp.id-1].TA_Time-arr[temp.id-1].Burst_Time;
            }
        }
    }
}
void performOper_NonPrem(vector<Process>&arr,int size){
    int startTime=0,i=0;
    while(i<arr.size()){
        if(startTime<arr[i].Arrival_Time)startTime=arr[i].Arrival_Time;   // This is Optimization
        if(startTime>=arr[i].Arrival_Time){
            startTime+=arr[i].Burst_Time;
            arr[i].Comp_Time=startTime;
            arr[i].TA_Time=arr[i].Comp_Time-arr[i].Arrival_Time;
            arr[i].W_Time=arr[i].TA_Time-arr[i].Burst_Time;
            i++;
        }
    }
}
void SRTF(vector<Process>&arr){
    input(arr);  // First take the input
    for(int i=0;i<arr.size();i++){
        arr[i].Remaining_Time=arr[i].Burst_Time;
    }
    sort(arr.begin(),arr.end(),comp);
    performOper_SRTF(arr,arr.size());
    cout << "\nSRTF Scheduling: \n";
    cout << "ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto& p : arr) {
        cout << p.id << "\t" << p.Arrival_Time << "\t" << p.Burst_Time << "\t"
             << p.Comp_Time << "\t\t" << p.TA_Time << "\t\t" << p.W_Time << endl;
    }
}
void Round_Robin(vector<Process>&arr){
    input(arr);  // first take the input
    sort(arr.begin(),arr.end(),comparator);
    int time_Quantum;
    cout<<"Enter the Time Quantum: ";
    cin>>time_Quantum;
    performOper_RoundRobin(arr,arr.size(),time_Quantum);
    cout << "\nRound-Robin Scheduling: \n";
    cout << "ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto& p : arr) {
        cout << p.id << "\t" << p.Arrival_Time << "\t" << p.Burst_Time << "\t"
             << p.Comp_Time << "\t\t" << p.TA_Time << "\t\t" << p.W_Time << endl;
    }
}
void PriorityAlgo(vector<Process>&arr){
    input(arr); // first input in process array
    // and also write the priority and remaining time
    for(int i=0;i<arr.size();i++){
        int input_priority;
        cout<<"Enter the priority of "<<i+1<<" element: ";
        cin>>input_priority;
        arr[i].Priority=input_priority;
        arr[i].Remaining_Time=arr[i].Burst_Time;
    }
    sort(arr.begin(),arr.end(),priorityComp);
    performOper_Priority(arr,arr.size());
    cout << "\nPriority Scheduling: \n";
    cout << "Priority\tID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto& p : arr) {
        cout << p.Priority << "\t\t" << p.id << "\t" << p.Arrival_Time << "\t" << p.Burst_Time << "\t"
             << p.Comp_Time << "\t\t" << p.TA_Time << "\t\t" << p.W_Time << endl;
    }
}
void FCFS(vector<Process>&arr){
    input(arr); // First input in Process array
    sort(arr.begin(),arr.end(),comparator);
    performOper_NonPrem(arr,arr.size());
    cout << "\nFCFS Scheduling: \n";
    cout << "ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto& p : arr) {
        cout << p.id << "\t" << p.Arrival_Time << "\t" << p.Burst_Time << "\t"
             << p.Comp_Time << "\t\t" << p.TA_Time << "\t\t" << p.W_Time << endl;
    }
}
void SJF(vector<Process>&arr){
    input(arr); // First input in Process array
    sort(arr.begin(),arr.end(),comp);
    performOper_NonPrem(arr,arr.size());
    // Now print all the data
    cout << "\nSJF Scheduling: \n";
    cout << "ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto& p : arr) {
        cout << p.id << "\t" << p.Arrival_Time << "\t" << p.Burst_Time << "\t"
             << p.Comp_Time << "\t\t" << p.TA_Time << "\t\t" << p.W_Time << endl;
    }
}
int main(){
    cout<<"\n\n\n";
	cout<<"------------------------------------------------\n";
	cout<<"           CPU Scheduling Algorithm             \n";
	cout<<"------------------------------------------------\n";
	cout<<"1. Preemptive Algorithm: a.SRTF b.Round-Robin c.Priority Based\n";
	cout<<"2. Non-Preemptive Algo: a.FCFS b.SJF\n";
	int out;
	char in;
	cout<<"Which Algo u want to choose 'enter both': ";
	cin>>out>>in;
	vector<Process>arr;   // Switch
	if(out==1){
		if(in=='a'){
			SRTF(arr);
		}
		else if(in=='b'){
			Round_Robin(arr);
		}
		else if(in=='c'){
			PriorityAlgo(arr);
		}
		else{
			cout<<"Wrong input";
		}
	}
	else if(out==2){
	    if(in=='a'){  // You choose FCFS 
	        FCFS(arr);
	    }
	    else if(in=='b'){  // You choose SJF
	        SJF(arr);
	    }
	    else{
	    	cout<<"Wrong input";
		}
	}
	else{
		cout<<"Wrong input";
	}
}
