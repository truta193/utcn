namespace factoryWork;

public class Flat : IBuilding
{
    private string address;
    private byte floorCount;
    private byte apartmentCount;
    
    public string Address { get => address; set => address = value; }
    public byte FloorCount { get => floorCount; set => floorCount = value; }
    public byte ApartmentCount { get => apartmentCount; set => apartmentCount = value; }
    
    public Flat() { }
    
    public Flat(string address, byte floorCount, byte apartmentCount)
    {
        this.address = address;
        this.floorCount = floorCount;
        this.apartmentCount = apartmentCount;
    }
    
    public override string ToString()
    {
        return $"Flat: {Address}, Floors: {FloorCount}, Apartments: {ApartmentCount}";
    }
}