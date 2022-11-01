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