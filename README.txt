# CS361-Course-Project - Assignment 8 Info

Communications Contract:

A: How to REQUEST data from microservice:
Step 1: Prepare the Request
Update the following in your microservice (would be updated via user input most likely)
    - Route Name: The name of the train route for which they want to update the ticket sales (e.g., "Blue Line").
    - Number of Tickets: The number of tickets they want to sell (e.g., 2).

Step 2: Automatically Done by Microservice
You would run "python choimicroA.py" in the terminal, this runs forever while the testprogram is used to recieve data. After the program writes to request.txt, the microservice will read the request, process it, update the ticket sales via the routes.json, and write the result to response.txt.

B: How to RECIEVE data from microservice (how the user would recieve data):
  Step 1: Call response.txt to be read
  Step 2: Read response.txt and print the response to terminal
  Step 3: Update the JSON with ticket amounts (accumulate tickets or add) for selected route.

C:

