# 2FA-Simulation
## Aim
The aim of the project is to develop a two-factor authentication system in C that enhances security by requiring users to register with their credentials, log in, and verify their identity through a randomly generated one-time password (OTP). This simulates a real-world application of 2FA, demonstrating how additional verification can protect user accounts from unauthorized access. 

## Introduction

The project implements a <b>Two-Factor Authentication (2FA) system </b> in C, a mechanism that adds an extra layer of security by requiring not only a username and password but also a One-Time Password (OTP) for successful authentication. This method reduces the risk of unauthorized access, even if a user's password is compromised.

## Key Functionalities

1.	<b>User Registration:</b> The program allows new users to register by entering a username and password. The credentials are saved to a file (user.txt) for persistence. If the user already exists, the system prompts the user to choose a different username.

2.	<b>Login Process: </b>Users can log in by providing their username and password. Upon successful credential verification, an OTP is generated and stored in a file (otp.txt), which simulates sending the OTP to the user's device. The user must then input the correct OTP to complete the login process.

3.	<b>OTP Generation:</b> The OTP is a 6-digit randomly generated number that is created using the rand() function seeded by the system time (time(0)), ensuring that each OTP is unique. The OTP is displayed by opening the generated otp.txt file in PowerShell.

4.	<b>File Storage:</b> User credentials and OTPs are stored in text files. This approach simulates persistent storage, allowing the system to retrieve and verify user data across multiple sessions.

5.	<b>Menu System:</b> The main function of the program features a menu that provides options to register a user, log in, or exit the application.

