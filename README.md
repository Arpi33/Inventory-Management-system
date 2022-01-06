# Inventory-Management-system
The application supports a table of records. Define a class called
StoreItem, the instance of which is a record. The program should consist of three
files, which are Inventory.cpp, StoreItem.h and StoreItem.cpp .
The features in this programs are as following:
1. Insertion of a new record
2. Update of a data field in a record
3. Deletion of a data field in a record
4. Deletion of a record
5. Displaying on screen the table of records showing
a. the data fields selected by the user (the user can choose to display every field) and
b. the records which fulfils all the search conditions specified by the user.
A search condition is applicable to only one data field.
If the data field is a text field, a condition can be
i. a full text match (Example : Item name is exactly "HDMI Cable 1m"), or
ii. a sub-string match (Example : Item name contains "Cable")
If the data field is a numeric field, a condition can be
i. a equivalence condition (Example : Cost price is 1000) or
ii. a less than condition (Example : Cost price is less than 1000) or
iii. a more than condition (Example :Cost price is less than 1000 )
Up to three search conditions can be respecified by the user to
be applied together. If the user does not specify any
conditions, every record in the table will be displayed.
6. Sorting by a selected data field of records in ascending or descending order
7. Saving the table into a text file
8. Loading the table from a text file
