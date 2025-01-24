namespace factoryWork;

public abstract class AbstractBuildingPrinter
{
    protected readonly IFormatter formatter;

    public AbstractBuildingPrinter(IFormatter formatter)
    {
        this.formatter = formatter;
    }

    public abstract string Print(IBuilding building);
}