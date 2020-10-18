#include <iostream>
#include "linked_list.h"

int main()
{
    Chain inst = *(new Chain());

    string command;
    int data , data_ref;

    while(cin>>command){
        if(command == "InsertBack"){
            cin>>data;
            inst.InsertBack(data);
        }else if(command == "InsertFront"){
            cin>>data;
            inst.InsertFront(data);
        }else if(command == "InsertAfter"){
            cin>>data>>data_ref;
            inst.InsertAfter(data , data_ref);
        }else if(command == "InsertBefore"){
            cin>>data>>data_ref;
            inst.InsertBefore(data , data_ref);
        }else if(command == "Delete"){
            cin>>data;
            inst.Delete(data);
        }else if(command == "DeleteFront"){
            inst.DeleteFront();

        }else if(command == "DeleteBack"){
            inst.DeleteBack();

        }else if(command == "Reverse"){
            inst.Reverse();
        }else if(command == "Rotate"){
            int k;
            cin>>k;
            inst.Rotate(k);
        }else if(command == "Swap"){
            int j,k;
            cin>>j>>k;
            inst.Swap(j,k);
        }
        else if(command == "PrintChain"){

            cout<<inst.PrintChain()<< '\n';
        }
    }
    
    return 0;
}