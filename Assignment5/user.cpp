#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "user.h"

using namespace std;

User::User() : isAuthenticated(false), isRegistered(false), fitnessGoal("", 0, 0) {}

//sign up for a new user
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

//login for a registered user
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

//check if the user is logged in
bool User::is_logged_in() {
    return isAuthenticated;
}

//INCLUSIVITY HEURISTIC #7
//log a workout session
void User::log_workout() {
    if (!isAuthenticated) {
        cout << "Please log in first." << endl;
        return;
    }
    
    Workout workout;
    string dateInput;
    
    cout << "Enter workout date (YYYY-MM-DD): ";
    cin >> dateInput;

    //validate the date format (simple check, can be expanded)
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
        cin.clear();               //clear the error flag
        cin.ignore(1000, '\n');     //ignore any remaining invalid input
    }

    cout << "Enter workout intensity (e.g., low, medium, high): ";
    cin >> workout.intensity;

    //save current state before logging the new workout
    if (!workoutLog.empty()) {
        workoutHistory.push(workoutLog); //save previous workout log
    }
    workoutLog.push_back(workout); //log new workout
    cout << "Workout logged successfully!" << endl;

    //check if the workout type matches the fitness goal type
    if (fitnessGoal.goalType == workout.type) {
        fitnessGoal.progress++; // Increment progress
        cout << "Progress towards goal: " << fitnessGoal.progress 
             << " out of " << fitnessGoal.target << " workouts completed." << endl;
    } else {
        cout << "This workout does not match your fitness goal type." << endl;
    }

    //prompt user for an undo option immediately after logging
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

//INCLUSIVITY HEURISTIC #7
//set a fitness goal for the user
void User::set_fitness_goal() {
    if (!isAuthenticated) {
        cout << "Please log in first." << endl;
        return;
    }

    //save current goal state before setting a new one
    goalHistory.push(fitnessGoal); //store previous goal state

    cout << "Enter goal type (e.g., cardio, strength): ";
    cin >> fitnessGoal.goalType;
    
    cout << "Enter target (Number of workouts in a month): ";
    while (!(cin >> fitnessGoal.target) || fitnessGoal.target <= 0) {
        cout << "Invalid input. Target must be a positive number. Please enter again: ";
        cin.clear();             
        cin.ignore(1000, '\n');  
    }

    fitnessGoal.progress = 0; //reset progress when setting a new goal
    cout << "Goal set successfully!" << endl;
}

//INCLUSIVITY HEURISTIC #4 and #5
//undo the last logged workout
void User::undo_workout() {
    if (workoutHistory.empty()) {
        cout << "No workout to undo." << endl;
        return;
    }

    //restore the last workout log state
    workoutLog = workoutHistory.top(); //revert to the previous workout log
    workoutHistory.pop(); //remove the last entry from the history
    cout << "Last workout entry undone." << endl;
}

//INCLUSIVITY HEURISTIC #4 and #5 - but for goals
//undo the last fitness goal set
void User::undo_goal() {
    if (goalHistory.empty()) {
        cout << "No fitness goal to undo." << endl;
        return;
    }

    //restore the last fitness goal state
    fitnessGoal = goalHistory.top(); //revert to the previous fitness goal
    goalHistory.pop(); //remove the last entry from the history
    cout << "Last fitness goal entry undone." << endl;
}

//view the user's progress towards fitness goals
void User::view_progress() {
    if (!isAuthenticated) {
        cout << "Please log in first." << endl;
        return;
    }

    cout << "Fitness Goal: " << fitnessGoal.goalType 
         << " - Target: " << fitnessGoal.target 
         << ", Progress: " << fitnessGoal.progress << endl;
    
    cout << "Workout Log:" << endl;

    //display organized list of users workouts
    for (const auto& workout : workoutLog) {
        cout << "Date: " << workout.date 
             << ", Type: " << workout.type
             << ", Duration: " << workout.duration 
             << " mins, Intensity: " << workout.intensity << endl;
    }
}
