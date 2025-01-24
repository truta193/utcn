namespace factoryWork;

public class CsvFormatter : IFormatter
{
    public string Format(IBuilding building)
    {
        return building switch
        {
            Flat flat => $"Flat, {flat.Address}, {flat.FloorCount}, {flat.ApartmentCount}",
            House house => $"House, {house.Owner}, {house.Address}, {house.Area}",
            Hospital hospital => $"Hospital, {hospital.Name}, {hospital.Address}, \"{string.Join(";", hospital.Departments)}\"",
            School school => $"School, {school.Name}, {school.Address}, {school.ClassCount}",
            _ => throw new InvalidOperationException("Unsupported building type")
        };
    }
}