/*
Student Name: Meliksah Turker
Student Number: 2019700120
Project Number: 2
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: The troublesome parts were tracking the table number during percolateUp and percolateDown processes. I carried out this
 by implementing a 2D Array (Matrix). Another and last troublesome part was handling the cases where tableCapacities were equal
 and I had to check for tableNumbers. This especially has been troublesome during percolateDown, specifically a case that I forgot,
 that was the case where index table capacity is lower than both children but children capacities are equal.

*/
#include "RestaurantOrganizer.h"
using namespace std;
int vec[100000][2]; // I created a 2D array in order to be able to track the number of table since the order will shift during percolateUP and percolateDOwns.
                    // First column in this matrix stores the number of table, second column stores the table capacity for that particular table.

RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){
    numberOfTables = tableCapacityInput.size();
    for(int i=0; i<numberOfTables; i++){
        vec[i][0] = i;
        vec[i][1] = tableCapacityInput[i];
        heapUp(i);
        }
}


void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){
    if (vec[0][1] >= groupSize) {
        vec[0][1] -= groupSize;     //as I allocated table to groups, I removed that amount of number of chairs and then percolateDOwned it.
        outFile << vec[0][0] << endl; // this prints the tableNUmber since its column 0.
        heapDown((0));

    } else {
        outFile << -1 << endl;
    }
}



void RestaurantOrganizer::heapUp(int index){
    if(index == 0)
        return;
    int parent = (index-1)/2;

    if(vec[parent][1] > vec[index][1]){
        return;
    }
    else if(vec[index][1] > vec[parent][1] || (vec[index][1] == vec[parent][1] && vec[index][0] < vec[parent][0])){
        swap(vec[index], vec[parent]);
        heapUp(parent);
        // During HeapUp I checked for the cases where table capacities of multiple tables are equal
        // and gave the priority to the one with lesser table number.
    }
    else{
        return;
    }
}


void RestaurantOrganizer::heapDown(int index){
    int left = 2*index+1;
    int right = 2*index+2;
    if(left >= numberOfTables){
        return;
    }

    // Also during HeapDown, I checked for the cases where table capacities of multiple tables are equal
    // and gave the priority to the one with lesser table number.
    // Since there are more checks that we carry out in percolateDown, this method is much longer and complicated
    // in terms of various boolean statements and IFs.
    // I must admit this part has been quite troublesome to implement.

    else if(left == numberOfTables-1 && (vec[left][1] > vec[index][1] || (vec[left][1] == vec[index][1] && vec[left][0] < vec[index][0]))){
        swap(vec[left], vec[index]);
        return;

    }
    else {
        if(vec[index][1] > vec[left][1] && vec[index][1] > vec[right][1]){
            return;
        }
        else if (vec[left][1] == vec[index][1] && vec[right][1] == vec[index][1]) {     // Case where all THREE, index, left and right have equal table capacities.
            if (vec[left][0] < vec[right][0] && vec[left][0] < vec[index][0]) {
                swap(vec[left], vec[index]);
                heapDown(left);
            }
            else if (vec[right][0] < vec[left][0] && vec[right][0] < vec[index][0]) {
                swap(vec[right], vec[index]);
                heapDown(right);
            }
            else{
                return;
            }

        } // Below, there are cases where left and right table capacities are not equal so we choose one of them, comparing their value to index
          // However there are also cases where either left or right tableCapacity is equal to index so I checked their tableNumber to decide.
        else if ((vec[left][1] > vec[right][1] && vec[left][1] > vec[index][1]) || ((vec[left][1] > vec[right][1] && vec[left][1] == vec[index][1]) && vec[left][0] < vec[index][0])) {
            swap(vec[left], vec[index]);
            heapDown(left);
        }
        else if ((vec[right][1] > vec[left][1] && vec[right][1] > vec[index][1]) || ((vec[right][1] > vec[left][1] && vec[right][1] == vec[index][1]) &&(vec[right][0] < vec[index][0]))) {
            swap(vec[right], vec[index]);
            heapDown(right);
        }


        else if(vec[left][1] == vec[right][1] && vec[left][1] > vec[index][1]){ // This was the part that I forgot to implement, which caused the last bit of trouble to me
            if(vec[left][0] < vec[right][0]){                                   // In here I check the case where index capacity is lower than both right and left
                swap(vec[left], vec[index]);                             // But left and right are equal. So decision must be given again, according to tableNUmber.
                heapDown(left);
            }
            else{
                swap(vec[right], vec[index]);
                heapDown(right);

            }

        }
        else {
            return;
        }
    }
}

void RestaurantOrganizer::printSorted(ofstream& outFile) {
    for (int i = 0 ; i < numberOfTables ; i++){
        outFile << vec[0][1] << " ";
        vec[0][1] = -1;
        heapDown(0);

    }

}

