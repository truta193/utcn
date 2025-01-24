namespace factoryWork.Menu;

using System;

public class ShowAllBuildingsState : IState
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
            Console.Clear();
        
            Console.WriteLine("Choose format for buildings:");
            Console.WriteLine("1. ToString");
            Console.WriteLine("2. JSON");
            Console.WriteLine("3. CSV");
            Console.WriteLine("4. XML");
            
            string formatChoice = Console.ReadLine();
                
            AbstractBuildingPrinter? printer = formatChoice switch
            {
                "2" => new BuildingPrinter(new JsonFormatter()),
                "3" => new BuildingPrinter(new CsvFormatter()),
                "4" => new BuildingPrinter(new XmlFormatter()),
                _ => null
            };
            
            foreach (var building in context.Buildings)
            {
                if (printer == null)
                {
                    Console.WriteLine(building.ToString());
                    continue;
                }
                
                Console.WriteLine(printer.Print(building));
            }
        }
        Console.WriteLine("Press any key to return to the menu...");
        Console.ReadKey();
        context.SetState(new MainMenuState());
    }
}
