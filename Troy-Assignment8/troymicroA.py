import hashlib
import random
import string
import time

# Simulate a user database with username and password hash
USER_DB = {}

# Simulate session storage
SESSIONS = {}

def generate_token():
    """Generate a random token for session management."""
    return ''.join(random.choices(string.ascii_letters + string.digits, k=16))

def signup(username, password):
    """Register a new user."""
    if username in USER_DB:
        print("Username already exists. Please try a different one.")
    else:
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        USER_DB[username] = hashed_password
        print("Signup successful! You can now log in.")

def login(username, password):
    """Simulate a login function."""
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    if username in USER_DB and USER_DB[username] == hashed_password:
        token = generate_token()
        expiration = time.time() + 600  # Session valid for 10 minutes
        SESSIONS[token] = expiration
        print("Login successful!")
        print("Token:", token)
        print("Session expiration (in seconds):", int(expiration - time.time()))
        return token
    else:
        print("Login failed. Incorrect username or password.")
        return None

def forgot_password(username):
    """Simulate a password reset process."""
    if username in USER_DB:
        new_password = input("Enter your new password: ")
        USER_DB[username] = hashlib.sha256(new_password.encode()).hexdigest()
        print("Password has been reset successfully.")
    else:
        print("Username not found.")

def check_session(token):
    """Simulate checking the session status of a logged-in user."""
    if token in SESSIONS and SESSIONS[token] > time.time():
        print("Session is active.")
    else:
        print("Session expired or invalid.")

def main():
    """Main function to handle user input."""
    token = None
    signup_completed = False

    while True:
        print("\nOptions:")
        if not signup_completed:
            print("1. Signup")
        print("2. Login")
        print("3. Forgot Password")
        print("4. Check Session")
        print("5. Exit")
        
        choice = input("Choose an option: ")

        if choice == "1" and not signup_completed:
            username = input("Enter a new username: ")
            password = input("Enter a new password: ")
            signup(username, password)
            signup_completed = True  # Hide signup option after the first signup
        elif choice == "2":
            username = input("Enter username: ")
            password = input("Enter password: ")
            token = login(username, password)
        elif choice == "3":
            username = input("Enter username for password reset: ")
            forgot_password(username)
        elif choice == "4":
            if token:
                check_session(token)
            else:
                print("Please login first to obtain a session token.")
        elif choice == "5":
            print("Exiting program.")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
