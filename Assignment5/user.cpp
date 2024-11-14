#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <limits>  // Include this for numeric_limits
#include "user.h"

using namespace std;

// User constructor
User::User() : isAuthenticated(false), isRegistered(false), fitnessGoal("", 0, 0) {}

// Sign-up function
void User::sign_up(string user, string pass) {
    if (isRegistered) {
        cout << "User is already registered. Please log in." << endl;
        return;
    }
    username = user;
    password = pass;
    isRegistered = true;
    cout << "Sign-up successful! You can now log in with your credentials." << endl;
}

// Login function
bool User::login(string user, string pass) {
    if (!isRegistered) {
        cout << "No registered user found. Please sign up first." << endl;
        return false;
    }

    if (user == username && pass == password) {
        isAuthenticated = true;
        cout << "Login successful. Welcome, " << username << "!" << endl;
        return true;
    } else {
        cout << "Invalid credentials. Please try again." << endl;
        return false;
    }
}

bool User::is_logged_in() {
    return isAuthenticated;
}

// Display workout (Moved here so it can be used in view_progress and search_workout)
void User::display_workout(const Workout& workout) const {
    cout << "Date: " << workout.date
         << ", Type: " << workout.type
         << ", Duration: " << workout.duration
         << " mins, Intensity: " << workout.intensity << endl;
}

// Log workout function
void User::log_workout() {
    if (!isAuthenticated) {
        cout << "Please log in first." << endl;
        return;
    }

    Workout workout;
    string dateInput;

    cout << "Enter workout date (YYYY-MM-DD): ";
    cin >> dateInput;

    if (dateInput.length() != 10 || dateInput[4] != '-' || dateInput[7] != '-') {
        cout << "Invalid date format. Please use YYYY-MM-DD." << endl;
        return;
    }
    workout.date = dateInput;

    cout << "Enter workout type (e.g., cardio, strength): ";
    cin >> workout.type;

    cout << "Enter workout duration (minutes): ";
    while (!(cin >> workout.duration) || workout.duration <= 0) {
        cout << "Invalid input. Duration must be a positive number. Please enter again: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Enter workout intensity (e.g., low, medium, high): ";
    cin >> workout.intensity;

    if (!workoutLog.empty()) {
        workoutHistory.push(workoutLog);
    }
    workoutLog.push_back(workout);
    cout << "Workout logged successfully!" << endl;

    if (fitnessGoal.goalType == workout.type) {
        fitnessGoal.progress++;
        cout << "Progress towards goal: " << fitnessGoal.progress 
             << " out of " << fitnessGoal.target << " workouts completed." << endl;
    } else {
        cout << "This workout does not match your fitness goal type." << endl;
    }

    char choice;
    cout << "Would you like to undo this workout? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        undo_workout();
        cout << "Workout entry undone." << endl;
    } else {
        cout << "Workout entry saved." << endl;
    }
}

// Set fitness goal
void User::set_fitness_goal() {
    if (!isAuthenticated) {
        cout << "Please log in first." << endl;
        return;
    }

    goalHistory.push(fitnessGoal);

    cout << "Enter goal type (e.g., cardio, strength): ";
    cin >> fitnessGoal.goalType;

    cout << "Enter target (Number of workouts in a month): ";
    while (!(cin >> fitnessGoal.target) || fitnessGoal.target <= 0) {
        cout << "Invalid input. Target must be a positive number. Please enter again: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    fitnessGoal.progress = 0;
    cout << "Goal set successfully!" << endl;
}

// Undo last workout
void User::undo_workout() {
    if (workoutHistory.empty()) {
        cout << "No workout to undo." << endl;
        return;
    }

    workoutLog = workoutHistory.top();
    workoutHistory.pop();
    cout << "Last workout entry undone." << endl;
}

// Undo last goal
void User::undo_goal() {
    if (goalHistory.empty()) {
        cout << "No fitness goal to undo." << endl;
        return;
    }

    fitnessGoal = goalHistory.top();
    goalHistory.pop();
    cout << "Last fitness goal entry undone." << endl;
}

// View progress
void User::view_progress() {
    if (!isAuthenticated) {
        cout << "Please log in first." << endl;
        return;
    }

    cout << "Fitness Goal: " << fitnessGoal.goalType 
         << " - Target: " << fitnessGoal.target 
         << ", Progress: " << fitnessGoal.progress << endl;

    cout << "Workout Log:" << endl;

    for (const auto& workout : workoutLog) {
        display_workout(workout);
    }
}

// Search workout
void User::search_workout() {
    if (!isAuthenticated) {
        cout << "Please log in first." << endl;
        return;
    }

    int searchOption;
    cout << "Search Workout By:\n";
    cout << "1. Date\n";
    cout << "2. Type\n";
    cout << "Choose an option: ";
    cin >> searchOption;

    if (cin.fail() || (searchOption != 1 && searchOption != 2)) {
        cout << "Invalid choice. Please select 1 or 2." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (searchOption == 1) {
        string dateInput;
        cout << "Enter workout date (YYYY-MM-DD): ";
        cin >> dateInput;

        bool found = false;
        for (const auto& workout : workoutLog) {
            if (workout.date == dateInput) {
                display_workout(workout);
                found = true;
            }
        }
        if (!found) {
            cout << "No workouts found for this date." << endl;
        }

    } else if (searchOption == 2) {
        string typeInput;
        cout << "Enter workout type (e.g., cardio, strength): ";
        cin >> typeInput;

        bool found = false;
        for (const auto& workout : workoutLog) {
            if (workout.type == typeInput) {
                display_workout(workout);
                found = true;
            }
        }
        if (!found) {
            cout << "No workouts found for this type." << endl;
        }
    }
}
