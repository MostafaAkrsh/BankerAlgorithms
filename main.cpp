#include "bits/stdc++.h"
#include "windows.h"
#include "fstream"
#include "iostream"
using namespace std;


int main()
{
      ifstream cin("input.txt");

    HANDLE colors = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colors, 0x22);
    cout << "-----------------------------------------------" << endl;
    cout << "||";
    SetConsoleTextAttribute(colors, 0x0A);
    cout << " Welcome To The Banker's Algorithm Project ";
    SetConsoleTextAttribute(colors, 0x22);
    cout << "||" << endl;
    cout << "||";
    SetConsoleTextAttribute(colors, 0x0A);
    cout << "  BY Mostafa Samir Mohamed - Code:1701427  ";
    SetConsoleTextAttribute(colors, 0x22);
    cout << "||" << endl;
    cout << "-----------------------------------------------" << endl << endl << endl;

    SetConsoleTextAttribute(colors, 0x0F);

    int noOfProcesses, noOfResourcesTypes;

    cout << "Please Enter the no of Processes: ";
    cin >> noOfProcesses;
    cout << endl << "Please Enter the no of Resources types: ";
    cin >> noOfResourcesTypes;

    vector<int> Available(noOfResourcesTypes);

    cout << endl << "Enter the no of Available Instances of each Resource type: " << endl;
    for (int i = 0; i < noOfResourcesTypes; i++) {
        cout << "[" << i << "/" << noOfResourcesTypes - 1 << "] : ";
        cin >> Available[i];
    }

    vector<vector<int>> Allocation(noOfProcesses, vector<int>(noOfResourcesTypes));

    cout << endl << "Enter the Allocation Matrix: " << endl;
    for (int i = 0; i < noOfProcesses; i++) {
        for (int j = 0; j < noOfResourcesTypes; j++) {
            cout << "[" << i << "/" << noOfProcesses - 1 << "]" << "[" << j << "/" << noOfResourcesTypes - 1 << "]: ";
            cin >> Allocation[i][j];
        }
    }

    vector<vector<int>> Max(noOfProcesses, vector<int>(noOfResourcesTypes));

    cout << endl << "Enter The Max Matrix: " << endl;
    for (int i = 0; i < noOfProcesses; i++) {
        for (int j = 0; j < noOfResourcesTypes; j++) {
            cout << "[" << i << "/" << noOfProcesses - 1 << "]" << "[" << j << "/" << noOfResourcesTypes - 1 << "]: ";
            cin >> Max[i][j];
        }
    }

    vector<vector<int>> Need(noOfProcesses, vector<int>(noOfResourcesTypes));

    for (int i = 0; i < noOfProcesses; i++) {
        for (int j = 0; j < noOfResourcesTypes; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    cout << endl;
    cout << endl;

    SetConsoleTextAttribute(colors, 0xF0);

    cout << "The Need Matrix" << endl;

    SetConsoleTextAttribute(colors, 0x00);

    cout << endl;

    SetConsoleTextAttribute(colors, 0x0A);
    for (int j = 0; j < noOfResourcesTypes; j++)
        cout << "\t" << "R" << j;

    cout << endl;

    for (int i = 0; i < noOfProcesses; i++) {

        SetConsoleTextAttribute(colors, 0x00 | i + 1);
        cout << "P" << i << "\t";

        for (int j = 0; j < noOfResourcesTypes; j++) {
            {
                SetConsoleTextAttribute(colors, 0x0F);
                cout << Need[i][j] << "\t";
            }
        }
        cout << endl;
    }

    cout << endl;
    SetConsoleTextAttribute(colors, 0x0A);
    cout << "Enter 1 ";
    SetConsoleTextAttribute(colors, 0x0F);
    cout << "For asking about Safe state" << endl;
    SetConsoleTextAttribute(colors, 0x0A);
    cout << "Enter 2 ";
    SetConsoleTextAttribute(colors, 0x0F);
    cout << "For asking about Immediate requests" << endl;
    SetConsoleTextAttribute(colors, 0x0A);
    cout << "Enter Q ";
    SetConsoleTextAttribute(colors, 0x0F);
    cout << "For Quit" << endl;

    char choice;
    cin >> choice;

    switch (choice) {
    case '1':
    {
        vector<int> Work = Available;
        vector<bool> Finish(noOfProcesses, false);

        queue<int> Sequence;

        int flag = 5;
        int ProcessId = 0;



        while (flag)
        {
            bool c = true;

            if (Finish[ProcessId] == false)
            {
                for (int i = 0; i < noOfResourcesTypes; i++)
                {
                    if (Need[ProcessId][i] > Work[i])
                    {
                        c = false;
                        break;
                    }
                }
            }

            if (c == true && Finish[ProcessId] == false)
            {
                for (int i = 0; i < noOfResourcesTypes; i++)
                {
                    Work[i] += Allocation[ProcessId][i];
                }

                Finish[ProcessId] = true;

                Sequence.push(ProcessId);
            }

            ProcessId++;

            if (ProcessId == noOfProcesses)
            {
                ProcessId = 0;
                flag--;
            }

        }

        //Result

        bool result = true;

        for (int i = 0; i < noOfProcesses; i++)
        {
            if (Finish[i] == false)
            {
                result = false;

                break;
            }
        }

        if (result == true)
        {
            SetConsoleTextAttribute(colors, 0xAF);

            cout <<endl<< "Yes, it's Safe State";

            SetConsoleTextAttribute(colors, 0x0A);

            cout << endl << "The Sequece :" << endl;



            for (int i = 0; i < noOfProcesses; i++)
            {
                int p = Sequence.front();
                SetConsoleTextAttribute(colors, 0x00 | p + 1);

                cout <<"P"<< p << " ";
                Sequence.pop();
            }

            cout << endl;
        }

        else
        {
            SetConsoleTextAttribute(colors, 0x4F);

            cout <<endl<< "No, it's not Safe State";

            SetConsoleTextAttribute(colors, 0x00);

            cout << endl;

        }


        break;
    }
    case '2':
    {
        int processRequest;

        cout << endl << "Please Enter the Process Id: ";
        cin >> processRequest;

        vector<int> RequestResources(noOfResourcesTypes);

        cout << endl << "Please Enter the Request: "<<endl;

        for (int i = 0; i < noOfResourcesTypes; i++) {
            cout << "[" << i << "/" << noOfResourcesTypes - 1 << "] : ";
            cin >> RequestResources[i];
        }

        cout << endl;

        bool c = true;

        for (int i = 0; i < noOfResourcesTypes; i++)
        {
            if (RequestResources[i] > Need[processRequest][i] && RequestResources[i] > Available[i] )
            {
                c = false;
            }
        }


        if (c == true)
        {
            for (int i = 0; i < noOfResourcesTypes; i++)
            {
                Available[i] -= RequestResources[i];
                Allocation[processRequest][i] += RequestResources[i];
                Need[processRequest][i] -= RequestResources[i];
            }

            vector<int> Work = Available;
            vector<bool> Finish(noOfProcesses, false);

            queue<int> Sequence;

            int flag = 5;
            int ProcessId = 0;



            while (flag)
            {
                bool c = true;

                if (Finish[ProcessId] == false)
                {
                    for (int i = 0; i < noOfResourcesTypes; i++)
                    {
                        if (Need[ProcessId][i] > Work[i])
                        {
                            c = false;
                            break;
                        }
                    }
                }

                if (c == true && Finish[ProcessId] == false)
                {
                    for (int i = 0; i < noOfResourcesTypes; i++)
                    {
                        Work[i] += Allocation[ProcessId][i];
                    }

                    Finish[ProcessId] = true;

                    Sequence.push(ProcessId);
                }

                ProcessId++;

                if (ProcessId == noOfProcesses)
                {
                    ProcessId = 0;
                    flag--;
                }

            }

            //Result

            bool result = true;

            for (int i = 0; i < noOfProcesses; i++)
            {
                if (Finish[i] == false)
                {
                    result = false;

                    break;
                }
            }

            if (result == true)
            {
                SetConsoleTextAttribute(colors, 0xAF);

                cout << endl << "Yes request can be granted with safe state";

                SetConsoleTextAttribute(colors, 0x0A);

                cout << endl << "The Sequece :" << endl;



                for (int i = 0; i < noOfProcesses; i++)
                {
                    int p = Sequence.front();
                    SetConsoleTextAttribute(colors, 0x00 | p + 1);

                    if (p == processRequest) cout << "P" << p << "req ";
                    else cout << "P" << p << " ";
                    Sequence.pop();
                }

                cout << endl;
            }

            else
            {

                SetConsoleTextAttribute(colors, 0x4F);

                cout << endl << "No, request cannot be granted with safe state";

                SetConsoleTextAttribute(colors, 0x00);

                cout << endl;

            }
        }


        break;
    }
    case 'Q':
    {
        break;
    }
    }

    SetConsoleTextAttribute(colors, 0x0F);
    int wait;
    cin>>wait;


}
