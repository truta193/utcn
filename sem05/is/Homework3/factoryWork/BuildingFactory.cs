namespace factoryWork;

public static class BuildingFactory
{
    public static T CreateBuilding<T>(params object[] args) where T : IBuilding
    {
        return (T)Activator.CreateInstance(typeof(T), args);
    }
}