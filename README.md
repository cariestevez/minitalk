See [subject](https://github.com/cariestevez/minitalk/blob/main/minitalk.en.subject.pdf)

# 💬 minitalk
Simple communication system between two programs: a server and a client. The objective is to send and receive messages using Unix signals, providing an introduction to inter-process communication (IPC) and signal handling in a Unix environment.

## Project Overview:
- Server: Listens for incoming messages from the client. It processes the signals received, reconstructs the message, and displays it on the terminal.
- Client: Sends a message to the server by converting each character of the message into a series of signals (SIGUSR1 and SIGUSR2).
- Signal Handling: Implement efficient signal handling to ensure that messages are correctly sent and received, even in the presence of potential signal loss or overlap.
- Character Encoding: Messages are encoded as sequences of binary signals, representing each character’s ASCII value. The server decodes these signals to reconstruct the original message.

## Key Concepts:
- Inter-Process Communication (IPC): Learn how processes can communicate with each other using Unix signals.
- Signal Handling: Gain experience in handling signals like SIGUSR1 and SIGUSR2, including managing timing and potential signal interruptions.
- Synchronization: Ensure that the server correctly handles incoming signals in the proper order, maintaining message integrity.

## Technologies:
- Programming Language: C
- Operating System: Unix/Linux
- IPC Mechanisms: Unix signals (SIGUSR1, SIGUSR2)

## Usage:
- Go to my [ft_printf repository](https://github.com/cariestevez/ft_printf) and get the code
- Add it to the minitalk folder
- Enter the ft_printf folder and compile running `make`
- Go back up and compile server and client separately running `gcc server_bonus.c ft_printf/libftprintf.a -o server` & `gcc client_bonus.c ft_printf/libftprintf.a -o client`
- Launch `./server`
- Open a new terminal and lauch `./client <serverPID> <"MESSAGE">`
- Have fun chatting!

