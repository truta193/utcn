namespace factoryWork;

public class School : IBuilding
{
    private string name;
    private string address;
    private string classCount;
    
    public string Name { get => name; set => name = value; }
    public string Address { get => address; set => address = value; }
    public string ClassCount { get => classCount; set => classCount = value; }
    
    public School() { }
    
    public School(string name, string address, string classCount)
    {
        this.name = name;
        this.address = address;
        this.classCount = classCount;
    }
    
    public override string ToString()
    {
        return $"School: {Name}, Address: {Address}, Classes: {ClassCount}";
    }
}