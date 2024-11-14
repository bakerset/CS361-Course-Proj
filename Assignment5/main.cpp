#include <iostream>
#include <limits>
#include "user.h"

using namespace std;

void display_welcome_message() {
    cout << "=========================================\n";
    cout << "|         WELCOME TO TACTIFIT            |\n";
    cout << "=========================================\n";
    cout << "|   YOUR PERSONAL FITNESS TRACKING APP.  |\n";
    cout << "=========================================\n";
    
    cout << "\nTactiFit is specifically designed for military personnel, helping you to efficiently track your workouts,"; 
    cout << "\nset achievable fitness goals, and monitor your progress over time. With TactiFit, you can optimize your";
    cout << "\ntraining, stay accountable and ensure that you are meeting the rigorous physical demands of military service.";
    cout << "\nThe app provides a user-friendly interface to log workouts, view progress, and adjust your fitness objectives,"; 
    cout << "\nenabling you to enhance your performance and readiness.\n"; // INCLUSIVITY HEURISTIC #1
}

void explain_costs() {
    cout << "==================================\n";
    cout << "|     Costs of Using TactiFit    |        \n";
    cout << "==================================\n";
    cout << "While TactiFit offers many benefits, there are some costs to consider:\n";
    cout << "- Time Commitment: Regularly logging workouts and setting goals may require a few minutes each day.\n";
    cout << "- Effort: Staying disciplined and consistent in tracking your fitness progress can be challenging but is essential for achieving your goals.\n";
    cout << "- Technology Dependence: Ensure you have access to a device and, if applicable, a reliable internet connection to fully utilize TactiFit.\n";
    cout << "These costs should be weighed against the benefits of improved fitness tracking and goal achievement.\n";
}

int main() {
    display_welcome_message();
    User user;
    int choice;

    while (true) {
        cout << "\nMenu Options:\n"; //IH6 menu options
        
        if (!user.is_logged_in() && !user.is_user_registered()) {
            cout << "1. Sign Up\n";
        } else if (!user.is_logged_in()) {
            cout << "1. Login\n";
        }
        
        cout << "2. Log Workout\n"
             << "3. Set Fitness Goal (preferably before logging workout)\n"
             << "4. View Progress\n"
             << "5. Explain Costs of Using TactiFit\n" //remains accesible
             << "6. Exit\n"
             << "7. Search Workout\n";  //new search option - IH7 Search workout
        cout << "Choose an option: "; //IH3 choose options

        cin >> choice;

        //input validation for choice
        if (cin.fail() || choice < 1 || choice > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 7." << endl;
            continue;
        }

        if (choice == 5) {
            explain_costs();
            continue;
        }

        if (!user.is_user_registered() && choice != 1 && choice != 6) {
            cout << "Please sign up first to access other options.\n";
            continue;
        }

        if (!user.is_logged_in() && choice > 1 && choice < 6) {
            cout << "Please log in first to access this feature.\n"; //IH2 Log-in first
            continue;
        }

        switch (choice) {
            case 1: {
                string username, password;
                if (!user.is_user_registered()) {
                    cout << "Choose a username: ";
                    cin >> username;
                    cout << "Choose a password: ";
                    cin >> password;
                    user.sign_up(username, password);
                } else if (!user.is_logged_in()) {
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;
                    user.login(username, password);
                } else {
                    cout << "You are already logged in.\n";
                }
                break;
            }
            case 2:
                user.log_workout();
                break;
            case 3:
                user.set_fitness_goal();
                break;
            case 4:
                user.view_progress();
                break;
            case 6:
                cout << "Goodbye!\n";
                return 0;
            case 7:
                user.search_workout(); //IH7 Search workout
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
