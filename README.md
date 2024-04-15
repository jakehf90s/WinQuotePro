Created an interface(IDatabase) to be used as baseclass for database. Adding new database support just needs to subclass this virtual class, and override the virtual members.
I Created a class MemoryDatabase which is a subclass of IDatabase, it showcases the ease of using a new database without the need for changing anything in the core codes.
Used Qt for GUI, its full-featured and cross-platform.
To add quote:
    fill the fields and click "add" button
To edit:
    just select the quote from the table view, it will update the fields based on current selected, edit the fields and press "update" button
To delete:
    just select the quote then click "delete" button


Building:
   You can use the visual studio project inside src folder
   Using the CMakeList I created, you can actually build this for Linux and Mac OS also. And even into a webassembly binary, to be served as a webui.
