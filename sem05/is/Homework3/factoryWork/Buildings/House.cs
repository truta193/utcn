namespace factoryWork;

public class House : IBuilding
{
    private string owner;
    private string address;
    private float area;
    
    public string Owner { get => owner; set => owner = value; }
    public string Address { get => address; set => address = value; }
    public float Area { get => area; set => area = value; }
    
    public House() { }
    
    public House(string owner, string address, float area)
    {
        this.owner = owner;
        this.address = address;
        this.area = area;
    }

    public override string ToString()
    {
        return $"House: Owner={Owner}, Address={Address}, Area={Area}m²";
    }
}