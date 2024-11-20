import json
import os
import time

# Sample JSON file name
ROUTE_FILE = 'routes.json'
REQUEST_FILE = 'request.txt'
RESPONSE_FILE = 'response.txt'

# Utility function to load JSON data
def load_routes(filename):
    try:
        with open(filename, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        return None

# Utility function to save JSON data
def save_routes(filename, data):
    with open(filename, 'w') as f:
        json.dump(data, f)

# Function to increment ticket sales for a specific route
def increment_ticket_sales(route_name, num_tickets, filename=ROUTE_FILE):
    routes = load_routes(filename)
    if routes is None:
        return "Error: Route file not found."

    for route in routes:
        if route[0] == route_name:
            route[2] += num_tickets
            save_routes(filename, routes)
            return str(route[2])  # Return updated ticket count as a string

    return "No route found"

def main():
    print("Ticket Sales Microservice is running...")
    
    # Main loop to continuously check for requests
    while True:
        if os.path.exists(REQUEST_FILE):
            # Read and process the request
            with open(REQUEST_FILE, 'r') as f:
                request = f.read().strip().split(',')
                route_name = request[0].strip()
                try:
                    num_tickets = int(request[1].strip())
                except ValueError:
                    response = "Error: Invalid ticket number."
                    with open(RESPONSE_FILE, 'w') as f:
                        f.write(response)
                    continue

            # Process the request and get the response
            response = increment_ticket_sales(route_name, num_tickets)

            # Write the response to the response.txt file
            with open(RESPONSE_FILE, 'w') as f:
                f.write(response)

            # Delete the request file to signal completion
            os.remove(REQUEST_FILE)

        time.sleep(1)  # Polling interval

if __name__ == "__main__":
    main()
