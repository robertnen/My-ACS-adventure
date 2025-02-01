# Introduction to Computer Security - Assignment 2

Deadline: please see curs.upb.ro !

## Homework Customizer

Please download your personalized homework from [https://isc2024.1337.cx].

Enter your Moodle username (WITHOUT the email domain or '@').
Example: "florin.stoian".

This will generate a customized archive with the tasks (for your eyes, only :P).

## Homework Description

The homework contains 4 tasks and a special `remote-shell` one (no flags in
there, but serves as frontend to all others, read on):

  - `message-send`: networking (easy);
  - `ghost-in-the-shell`: networking (moderate);
  - `jwt-auth`: web challenge (moderate);
  - `sqli-cart`: web challenge (moderate/hard);

Each task challenges you to find a "flag", a string with the form
`SpeishFlag{<random hash>}` (internal joke).
There is a single flag per task: if you got one with the appropriate syntax, it 
will be accepted as the correct solution (please take care when decoding or 
manually copying it, e.g. zero vs 'o').
WARNING: the flag is case sensitive! Please copy the whole string (including the
`SpeishFlag{...}` decorator) into the solution file!

Note that all tasks require Internet connectivity (using the same `remote-shell` 
session)!
The SSH session will be automatically terminated after 30 minutes (no matter the
activity). Please the the `remote-shell/task.txt` documentation for
infrastructure details!

WARNING: any unauthorized cyber-attack (especially Denial of Service) on the
assignment's infrastructure is strictly forbidden!

Your final solution will be in the form of a ZIP archive containing the
following files:

  - `flags.txt`: just put your flags in there, one each line, INCLUDING the 
    'SpeishFlag{' prefix! YOU WILL BE PENALIZED IF YOU DON'T FOLLOW THESE EXACT
    INSTRUCTIONS OK?
  - `username.txt`: your username (as file content!! the same as you entered inside
    the homework archive generator webpage)!
  - `readme.txt`: for each task, briefly describe your approach (keep it 
    short - medium, please!);
  - any custom scripts you coded for solving the homework (please don't include
    third party tools, link them in your readme instead).

Please keep the file names as above and available inside the archive's
root directory!

The solution archive must be uploaded to Moodle (https://curs.upb.ro) BEFORE the
deadline!

Note: an automated checker is not included because it is unnecessary: if you
discover the (solely) hidden flag for a task and it has the form mentioned
above, it most certainly will be the correct one and you will get the points (we
also manually check them for typos, but take care when copying them).

If you have any questions, please use the Moodle forum and/or the Teams channel.

GLHF!
