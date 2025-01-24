namespace factoryWork;

public class BuildingManager
{
    // public List<IBuilding> Buildings { get; } = new();
    //
    // public void ShowAllBuildings()
    // {
    //     Console.Clear();
    //     if (Buildings.Count == 0)
    //     {
    //         Console.WriteLine("No buildings found.");
    //     }
    //     else
    //     {
    //         foreach (var building in Buildings)
    //         {
    //             Console.WriteLine(building.ToString());
    //         }
    //     }
    //     Console.WriteLine("Press any key to continue...");
    //     Console.ReadKey();
    // }
    //
    // public void ShowBuildingsByType(Type buildingType, Func<IBuilding, string> formatter)
    // {
    //     Console.Clear();
    //     var filteredBuildings = Buildings.FindAll(b => b.GetType() == buildingType);
    //
    //     if (filteredBuildings.Count == 0)
    //     {
    //         Console.WriteLine($"No buildings of type {buildingType.Name} found.");
    //     }
    //     else
    //     {
    //         foreach (var building in filteredBuildings)
    //         {
    //             Console.WriteLine(formatter(building));
    //         }
    //     }
    //     Console.WriteLine("Press any key to continue...");
    //     Console.ReadKey();
    // }
    //
    // public void AddBuilding(IBuilding building)
    // {
    //     Buildings.Add(building);
    //     Console.WriteLine("Building added successfully!");
    //     Console.WriteLine("Press any key to continue...");
    //     Console.ReadKey();
    // }
}