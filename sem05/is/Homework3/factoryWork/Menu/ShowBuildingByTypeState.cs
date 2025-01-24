namespace factoryWork.Menu;

using System;

public class ShowBuildingsByTypeState : IState
{
    public void Execute(StateContext context)
    {
        Console.Clear();
        if (context.Buildings.Count == 0)
        {
            Console.WriteLine("No buildings found.");
        }
        else
        {
            Console.WriteLine("Choose building type:");
            Console.WriteLine("1. Flat");
            Console.WriteLine("2. House");
            Console.WriteLine("3. Hospital");
            Console.WriteLine("4. School");

            string input = Console.ReadLine()!;
            Type? selectedType = input switch
            {
                "1" => typeof(Flat),
                "2" => typeof(House),
                "3" => typeof(Hospital),
                "4" => typeof(School),
                _ => null
            };

            if (selectedType == null)
            {
                Console.WriteLine("Invalid choice. Press any key to return...");
                Console.ReadKey();
                context.SetState(new MainMenuState());
                return;
            }

            var filteredBuildings = context.Buildings.FindAll(b => b.GetType() == selectedType);
            Console.Clear();

            if (filteredBuildings.Count == 0)
            {
                Console.WriteLine($"No buildings of type {selectedType.Name} found.");
            }
            else
            {
                Console.WriteLine($"Choose format for {selectedType.Name} buildings:");
                Console.WriteLine("1. ToString");
                Console.WriteLine("2. JSON");
                Console.WriteLine("3. CSV");
                Console.WriteLine("4. Xml");
                
                string formatChoice = Console.ReadLine();
                    
                AbstractBuildingPrinter? printer = formatChoice switch
                {
                    "2" => new BuildingPrinter(new JsonFormatter()),
                    "3" => new BuildingPrinter(new CsvFormatter()),
                    "4" => new BuildingPrinter(new XmlFormatter()),
                    _ => null
                };

                foreach (var building in filteredBuildings)
                {
                    if (printer == null)
                    {
                        Console.WriteLine(building);
                        continue;
                    }
                    
                    Console.WriteLine(building.GetType() + ":\n" + printer.Print(building));
                }
            }
        }
        

        Console.WriteLine("Press any key to return...");
        Console.ReadKey();
        context.SetState(new MainMenuState());
    }
}
