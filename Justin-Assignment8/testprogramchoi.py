import os
import time

REQUEST_FILE = 'request.txt'
RESPONSE_FILE = 'response.txt'

def make_request(route_name, num_tickets):
    # Write the request data to request.txt
    with open(REQUEST_FILE, 'w') as f:
        f.write(f"{route_name},{num_tickets}")
    
    # Wait and check for the response
    while not os.path.exists(RESPONSE_FILE):
        time.sleep(1)  # Polling interval

    # Read and print the response
    with open(RESPONSE_FILE, 'r') as f:
        response = f.read()
    print("Response:", response)

    # Clean up the response file
    os.remove(RESPONSE_FILE)

if __name__ == "__main__":
    # Sample request for Blue Line with 3 tickets
    make_request("Blue Line", 3)
