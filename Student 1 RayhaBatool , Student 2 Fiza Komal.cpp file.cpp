/*
 * Smart Travel Planner - Component 2: Implementation Submission (Phase 1)
 * Student 1 Name: [Rayha Batool] | Reg No: [F23BAMT003]
 * Student 2 Name: [Fiza Komal] | Reg No: [F23BAMT005]
 * Course: Programming Fundamentals
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Named constants for limits and menu/option bounds
const int MIN_DESTINATION = 1;
const int MAX_DESTINATION = 4;
const int MIN_TRAVELLERS = 1;
const int MAX_TRAVELLERS = 10;
const int MIN_DAYS = 1;
const int MAX_DAYS = 30;
const int MIN_ACTIVITY = 1;
const int MAX_ACTIVITY = 5;
const int FINISH_ACTIVITY_INPUT = 0;
const int MIN_BUDGET = 1;

const int MENU_PLAN_TRIP = 1;
const int MENU_VIEW_DESTINATIONS = 2;
const int MENU_EXIT = 3;

// Displays the main menu and reads a valid choice
int displayAndGetMenuChoice() {
    int choice;
    while (true) {
        cout << "\n=== SMART TRAVEL PLANNER ===\n";
        cout << "1. Plan a trip\n";
        cout << "2. View available destinations\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == MENU_PLAN_TRIP || choice == MENU_VIEW_DESTINATIONS || choice == MENU_EXIT) {
            return choice;
        }
        cout << "Invalid choice. Please enter 1, 2, or 3.\n";
    }
}

// Displays all four destinations with their PKR rates
void displayDestinations() {
    cout << "\n--- Available Destinations (PKR) ---\n";
    cout << "1. Murree  | Accommodation: 9,000/room/night | Transport: 4,000/person | Food: 3,000/person/day\n";
    cout << "2. Hunza   | Accommodation: 12,000/room/night | Transport: 15,000/person | Food: 3,000/person/day\n";
    cout << "3. Swat    | Accommodation: 8,000/room/night | Transport: 6,000/person | Food: 2,000/person/day\n";
    cout << "4. Naran   | Accommodation: 10,000/room/night | Transport: 8,000/person | Food: 2,500/person/day\n";
}

// Looks up destination name by destination ID (1 to 4)
string getDestinationName(int destId) {
    if (destId == 1) return "Murree";
    if (destId == 2) return "Hunza";
    if (destId == 3) return "Swat";
    return "Naran";
}

// Looks up accommodation rate per room per night (PKR)
int getAccommodationRate(int destId) {
    if (destId == 1) return 9000;
    if (destId == 2) return 12000;
    if (destId == 3) return 8000;
    return 10000;
}

// Looks up transport rate per person return trip (PKR)
int getTransportRate(int destId) {
    if (destId == 1) return 4000;
    if (destId == 2) return 15000;
    if (destId == 3) return 6000;
    return 8000;
}

// Looks up food rate per person per day (PKR)
int getFoodRate(int destId) {
    if (destId == 1) return 3000;
    if (destId == 2) return 3000;
    if (destId == 3) return 2000;
    return 2500;
}

// Looks up activity name by activity ID (1 to 5)
string getActivityName(int actId) {
    if (actId == 1) return "Sightseeing";
    if (actId == 2) return "Hiking";
    if (actId == 3) return "Boating";
    if (actId == 4) return "Museum";
    return "Adventure";
}

// Looks up activity price per person (PKR)
int getActivityPrice(int actId) {
    if (actId == 1) return 600;
    if (actId == 2) return 1200;
    if (actId == 3) return 1100;
    if (actId == 4) return 350;
    return 1800;
}

// Displays the five activities and their prices
void displayActivities() {
    cout << "\n--- Activities (PKR per person) ---\n";
    cout << "1. Sightseeing - 600\n";
    cout << "2. Hiking - 1,200\n";
    cout << "3. Boating - 1,100\n";
    cout << "4. Museum - 350\n";
    cout << "5. Adventure - 1,800\n";
    cout << "Enter 1 to 5 to add an activity, or 0 to finish.\n";
}

// Validates and returns destination choice (1 to 4)
int getValidatedDestination() {
    int dest;
    while (true) {
        cout << "Enter destination (1-4): ";
        cin >> dest;
        if (dest >= MIN_DESTINATION && dest <= MAX_DESTINATION) {
            return dest;
        }
        cout << "Invalid destination. Please enter a number from 1 to 4.\n";
    }
}

// Validates and returns number of travellers (1 to 10)
int getValidatedTravellers() {
    int travellers;
    while (true) {
        cout << "Enter number of travellers (1-10): ";
        cin >> travellers;
        if (travellers >= MIN_TRAVELLERS && travellers <= MAX_TRAVELLERS) {
            return travellers;
        }
        cout << "Invalid number of travellers. Please enter a value from 1 to 10.\n";
    }
}

// Validates and returns trip duration in days (1 to 30)
int getValidatedDays() {
    int days;
    while (true) {
        cout << "Enter trip duration in days (1-30): ";
        cin >> days;
        if (days >= MIN_DAYS && days <= MAX_DAYS) {
            return days;
        }
        cout << "Invalid duration. Please enter days from 1 to 30.\n";
    }
}

// Validates and returns budget (> 0)
int getValidatedBudget() {
    int budget;
    while (true) {
        cout << "Enter budget in PKR (greater than 0): ";
        cin >> budget;
        if (budget >= MIN_BUDGET) {
            return budget;
        }
        cout << "Invalid budget. Please enter a whole number greater than 0.\n";
    }
}

// Calculates accommodation cost: rooms * nights * rate, where rooms = ceil(travellers / 2) and nights = days - 1
int calculateAccommodationCost(int destId, int travellers, int days) {
    int nights = days - 1;
    int rooms = (travellers + 1) / 2;
    int rate = getAccommodationRate(destId);
    return rooms * nights * rate;
}

// Calculates transport cost: travellers * transport rate
int calculateTransportCost(int destId, int travellers) {
    return travellers * getTransportRate(destId);
}

// Calculates food cost: travellers * days * food rate
int calculateFoodCost(int destId, int travellers, int days) {
    return travellers * days * getFoodRate(destId);
}

// Calculates total activities cost: travellers * sum of selected activity prices
int calculateActivitiesCost(int travellers, int activityPriceSum) {
    return travellers * activityPriceSum;
}

// Calculates overall trip cost
int calculateTotalCost(int accommodation, int transport, int food, int activities) {
    return accommodation + transport + food + activities;
}

// Prints budget comparison status line in the required format
void printBudgetStatus(int totalCost, int budget) {
    if (totalCost <= budget) {
        int remaining = budget - totalCost;
        cout << "WITHIN BUDGET - remaining PKR " << remaining << "\n";
    }
    else {
        int exceeded = totalCost - budget;
        cout << "OVER BUDGET - exceeded by PKR " << exceeded << "\n";
    }
}

// Displays the full trip summary in the required order
void displayTripSummary(
    int destId,
    int travellers,
    int days,
    const string& selectedActivities,
    int accommodationCost,
    int transportCost,
    int foodCost,
    int activitiesCost,
    int totalCost,
    int budget
) {
    cout << "\n=== TRIP SUMMARY ===\n";
    cout << "Destination: " << getDestinationName(destId) << "\n";
    cout << "Travellers: " << travellers << "\n";
    cout << "Duration: " << days << " days\n";
    cout << "Selected activities: " << (selectedActivities.empty() ? "None" : selectedActivities) << "\n";
    cout << "Accommodation: " << accommodationCost << " PKR\n";
    cout << "Transport: " << transportCost << " PKR\n";
    cout << "Food: " << foodCost << " PKR\n";
    cout << "Activities: " << activitiesCost << " PKR\n";
    cout << "Total estimated cost: " << totalCost << " PKR\n";
    cout << "Budget: " << budget << " PKR\n";
    printBudgetStatus(totalCost, budget);
}

// Handles the complete "Plan a trip" flow
void planTrip() {
    displayDestinations();
    int destId = getValidatedDestination();
    int travellers = getValidatedTravellers();
    int days = getValidatedDays();

    bool act1Selected = false;
    bool act2Selected = false;
    bool act3Selected = false;
    bool act4Selected = false;
    bool act5Selected = false;

    int activityPriceSum = 0;
    string selectedActivities = "";

    while (true) {
        displayActivities();
        int choice;
        cout << "Enter activity choice: ";
        cin >> choice;

        if (choice == FINISH_ACTIVITY_INPUT) {
            break;
        }

        if (choice < MIN_ACTIVITY || choice > MAX_ACTIVITY) {
            cout << "Invalid activity choice. Please enter 1 to 5, or 0 to finish.\n";
            continue;
        }

        bool alreadySelected = false;
        if (choice == 1 && act1Selected) alreadySelected = true;
        if (choice == 2 && act2Selected) alreadySelected = true;
        if (choice == 3 && act3Selected) alreadySelected = true;
        if (choice == 4 && act4Selected) alreadySelected = true;
        if (choice == 5 && act5Selected) alreadySelected = true;

        if (alreadySelected) {
            cout << "Activity is already added.\n";
            continue;
        }

        if (choice == 1) act1Selected = true;
        if (choice == 2) act2Selected = true;
        if (choice == 3) act3Selected = true;
        if (choice == 4) act4Selected = true;
        if (choice == 5) act5Selected = true;

        activityPriceSum += getActivityPrice(choice);
        if (!selectedActivities.empty()) {
            selectedActivities += ", ";
        }
        selectedActivities += getActivityName(choice);
    }

    int budget = getValidatedBudget();

    int accommodationCost = calculateAccommodationCost(destId, travellers, days);
    int transportCost = calculateTransportCost(destId, travellers);
    int foodCost = calculateFoodCost(destId, travellers, days);
    int activitiesCost = calculateActivitiesCost(travellers, activityPriceSum);
    int totalCost = calculateTotalCost(accommodationCost, transportCost, foodCost, activitiesCost);

    displayTripSummary(
        destId,
        travellers,
        days,
        selectedActivities,
        accommodationCost,
        transportCost,
        foodCost,
        activitiesCost,
        totalCost,
        budget
    );
}

int main() {
    int choice = 0;

    while (true) {
        choice = displayAndGetMenuChoice();

        if (choice == MENU_PLAN_TRIP) {
            planTrip();
        }
        else if (choice == MENU_VIEW_DESTINATIONS) {
            displayDestinations();
        }
        else if (choice == MENU_EXIT) {
            cout << "Goodbye! Thank you for using Smart Travel Planner.\n";
            break;
        }
    }

    return 0;
}