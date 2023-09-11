// Question : Write a program to run a script at a specific time using a Daemon process

#include <time.h>      // Import for time related stuff
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <time.h>

// Define the path to the script you want to execute
#define SCRIPT_PATH "/path/to/your/script.sh"

// Define the time at which you want to execute the script (in HH:MM format)
#define EXECUTION_TIME "12:30"

// Function to execute the script
void executeScript() {
    pid_t child_pid;

    // Create a child process
    if ((child_pid = fork()) == 0) {
        // This code runs in the child process

        // Execute the script using execlp
        if (execlp("/bin/sh", "/bin/sh", SCRIPT_PATH, NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    } else if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

int main() {
    pid_t pid, sid;

    // Create a new process group and session
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // If we got a good PID, then we can exit the parent process
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask (umask)
    umask(0);

    // Open any logs here (e.g., with openlog())

    // Create a new SID for the child process
    sid = setsid();
    if (sid < 0) {
        perror("setsid");
        exit(EXIT_FAILURE);
    }

    // Change the current working directory
    if (chdir("/") < 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Set up a timer to execute the script at a specific time
    struct tm tm;
    time_t now, execution_time;
    struct timeval tv;

    while (1) {
        // Get the current time
        gettimeofday(&tv, NULL);
        now = tv.tv_sec;

        // Parse the execution time from the macro (HH:MM format)
        if (strptime(EXECUTION_TIME, "%H:%M", &tm) == NULL) {
            perror("strptime");
            exit(EXIT_FAILURE);
        }

        // Set the date fields of the tm struct to the current date
        tm.tm_year = localtime(&now)->tm_year;
        tm.tm_mon = localtime(&now)->tm_mon;
        tm.tm_mday = localtime(&now)->tm_mday;

        // Convert the tm struct to a time_t value
        execution_time = mktime(&tm);

        // Calculate the time difference until the execution time
        int time_diff = execution_time - now;

        // Sleep until it's time to execute the script
        sleep(time_diff);

        // Execute the script at the specified time
        executeScript();
    }

    // Clean up resources and close logs if needed

    return EXIT_SUCCESS;
}

