void listAll(string path, const Class* c)  // two-parameter overload
{
    if (path == "")
    {
        path = c->name(); //adding the class name to the path
    }
    else
    {
        path = path + "=>" + c->name(); //adding the subclass name to the path
    }

    cout << path << endl; //printing the current path
    for (int i = 0; i < c->subclasses().size(); i++) //going through all the subclasses of a certain class
    {
        listAll(path, c->subclasses()[i]); //calling listAll to print the subClass
    }
}