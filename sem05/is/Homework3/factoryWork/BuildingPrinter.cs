namespace factoryWork;

public class BuildingPrinter : AbstractBuildingPrinter
{
    public BuildingPrinter(IFormatter formatter) : base(formatter) { }

    public override string Print(IBuilding building)
    {
        return formatter.Format(building);
    }
}