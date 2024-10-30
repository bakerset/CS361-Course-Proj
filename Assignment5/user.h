// user.h
#ifndef USER_H
#define USER_H

#include <vector>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct Workout {
    string date;
    string type;
    int duration;
    string intensity;

    // Constructor to initialize all fields of Workout
    Workout(const string& d = "", const string& t = "", int dur = 0, const string& i = "")
        : date(d), type(t), duration(dur), intensity(i) {}
};

struct FitnessGoal {
    string goalType;
    int target;
    int progress;

    // Constructor to initialize all fields of FitnessGoal
    FitnessGoal(const string& g = "", int tgt = 0, int prog = 0)
        : goalType(g), target(tgt), progress(prog) {}
};

class User {
public:
    User();
    void sign_up(string user, string pass);
    bool login(string user, string pass);
    bool is_user_registered() const { return isRegistered; }
    bool is_logged_in();
    void log_workout();
    void set_fitness_goal();
    void view_progress();
    void undo_workout();
    void undo_goal();

private:
    string username;
    string password;
    bool isAuthenticated;
    bool isRegistered;
    FitnessGoal fitnessGoal;  
    vector<Workout> workoutLog;          // vector to store logged workouts
    stack<vector<Workout>> workoutHistory;
    stack<FitnessGoal> goalHistory;  
};

#endif