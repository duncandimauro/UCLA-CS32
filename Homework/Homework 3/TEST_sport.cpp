//TEST.cpp

#include <iostream>
#include <string>
using namespace std;


class Sport
{
public:
    Sport(string newName) //CANNOT have a default constructor
        :m_name(newName)
    {
    }

    virtual ~Sport()
    {
    }

    string name() const
    {
        return m_name;
    }

    virtual string icon() const = 0;

    virtual bool isOutdoor() const
    {
        return true;
    }

private:
    string m_name;
};

class Snowboarding : public Sport
{
public:
    Snowboarding(string newName)
        :Sport(newName)
    {
    }

    virtual ~Snowboarding()
    {
        cout << "Destroying the Snowboarding object named " << this->name() << "." << endl;
    }

    virtual string icon() const
    {
        return "a descending snowboarder";
    }
};

class Biathlon : public Sport
{
public:
    Biathlon(string newName, double distance)
        :Sport(newName), m_distance(distance)
    {
    }

    virtual ~Biathlon()
    {
        cout << "Destroying the Biathlon object named " << this->name() << ", distance " << m_distance << " km." << endl;
    }

    virtual string icon() const
    {
        return "a skier with a rifle";
    }

private:
    double m_distance;
};

class FigureSkating : public Sport
{
public:
    FigureSkating(string newName)
        :Sport(newName)
    {
    }

    virtual ~FigureSkating()
    {
        cout << "Destroying the FigureSkating object named " << this->name() << "." << endl;
    }

    virtual string icon() const
    {
        return "a skater in the Biellmann position";
    }

    virtual bool isOutdoor() const
    {
        return false;
    }
};

//Your declarationsand implementations would go here

void display(const Sport* sp)
{
    cout << sp->name() << " is ";
    if (sp->isOutdoor())
        cout << "an outdoor sport ";
    else
        cout << "an indoor sport ";
    cout << "with an icon showing " << sp->icon() << "." << endl;
}

int main()
{
    Sport* sports[4];
    sports[0] = new Snowboarding("Women's halfpipe");
    // Biathlon events have a distance in kilometers
    sports[1] = new Biathlon("Men's pursuit", 12.5);
    sports[2] = new Biathlon("Women's sprint", 7.5);
    sports[3] = new FigureSkating("Pair skating free");

    cout << "Here are the sports." << endl;
    for (int k = 0; k < 4; k++)
        display(sports[k]);

    // Clean up the sports before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete sports[k];
}

//Output produced :
//
//Here are the sports.
//Women's halfpipe is an outdoor sport with an icon showing a descending snowboarder.
//Men's pursuit is an outdoor sport with an icon showing a skier with a rifle.
//Women's sprint is an outdoor sport with an icon showing a skier with a rifle.
//Pair skating free is an indoor sport with an icon showing a skater in the Biellmann position.
//Cleaning up.
//Destroying the Snowboarding object named Women's halfpipe.
//Destroying the Biathlon object named Men's pursuit, distance 12.5 km.
//Destroying the Biathlon object named Women's sprint, distance 7.5 km.
//Destroying the FigureSkating object named Pair skating free.