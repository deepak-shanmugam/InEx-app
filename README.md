# InEx-app
> Version 1:

First version of CLI based Income and Expense management app created using C

# Supported Operating System
> Linux, Windows

# Build
> using gcc:
```
gcc -o program main.c app.c session.c record.c storage.c dataProcessing.c
```

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

- user will be able to delete single records in the current session of unsaved records using 'session id'

# Future work
> What can you expect in the future?

- Modification of saved records
- Sorting of records
- Filter reords
- Many more (Suggestions are welcome)

# Disclaimer
> About this project
This is my first complete c project. This program is tested in terms of functionality. However, It might have some minor issues (if any) and limitations in overall functionality. However, More features will be added in the upcoming days. It will be developed as an advanced CLI based Income and Expense management app in future.

Feedback and Corrections are welcome. you can also report bugs in your convenient way.

> Email: deepdeepdeepak@outlook.com

# License
[GNU GENERAL PUBLIC LICENSE](LICENSE.md), Version 3, 29 June 2007
