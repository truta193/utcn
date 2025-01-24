using System.ComponentModel.Design;

namespace factoryWork;

public class Hospital : IBuilding
{
    private string name;
    private string address;
    private List<string> departments;
    
    public string Name { get => name; set => name = value; }
    public string Address { get => address; set => address = value; }
    public List<string> Departments { get => departments; set => departments = value; }
    
    public Hospital() { }
    
    public Hospital(string name, string address, IEnumerable<string> departments)
    {
        this.name = name;
        this.address = address;
        this.departments = new List<string>(departments);
    }
    
    public override string ToString()
    {
        return $"Hospital: {Name}, Address: {Address}, Departments: {string.Join(", ", Departments)}";
    }
}