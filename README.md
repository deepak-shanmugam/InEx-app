# InEx-app
> Version 1:

First and Last version of CLI based Income and Expense management app created using C

# Supported Operating System
> Linux, Windows

# Build
> using gcc:

```
gcc -o program main.c app.c session.c record.c storage.c dataProcessing.c
```
**Note:** *Ignore the warning when executing above command*

# Run
```
./program
```

# Help
> What can you do with the current version of this app?

- Create income or expense records. Fields in a record shown below. (* indicates mandatory)
  - *Date (yyyymmdd)
  - *Amount (Maximum value: 999,999,999.99)
  - *To/From (maximum of 30 characters will be included)
  - Comment (Maximum of 100 characters will be included)
- View all your recently created unsaved records (i.e., Current session)
- Income and Expense records can be distinguished using the sign of Amount field (Negative amount incidates Expenses)
- Drop all the recently created unsaved records in current session 
- Save the current session of records (**Note:** once saved you cannot delete those records through this program)
- View all your saved records

# Next major release
> What features will be included in next major release?

- The software development of this project is discontinued due to poor implementation and lack of knowledge when started. There won't be next release. Please check out my new app 'InEx-plus'.

# Future work
> project discontinued.

# Disclaimer
> About this project

This is my first complete c project. This program is tested in terms of functionality. It might have some minor issues (if any) and having limitations in overall functionality. Due to poor implementation and lack of knowledge when started this project, I am unable to maintain this app and so discontinued. But It will work as mentioned in the #help section (Like a school/College first year simple project created using C)

I am just keeping this repository as an example for bad Implementation of a project in C program. Just because a program works doesn't mean that it is a good program due to several reasons. If you look into this project, you can find all those reasons. Have a nice day.

> Email: deepdeepdeepak@outlook.com

# License
[GNU GENERAL PUBLIC LICENSE](LICENSE.md), Version 3, 29 June 2007
