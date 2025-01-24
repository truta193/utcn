using factoryWork.Commands;

namespace factoryWork.Menu;

using System;

using System;

public class MainMenuState : IState
{
    public void Execute(StateContext context)
    {
        var invoker = new MenuInvoker();
        
        invoker.RegisterCommand("1", new ShowAllBuildingsCommand(context));
        invoker.RegisterCommand("2", new ShowBuildingsByTypeCommand(context));
        invoker.RegisterCommand("3", new CreateBuildingCommand(context));
        invoker.RegisterCommand("4", new ExitCommand(context));

        Console.Clear();
        Console.WriteLine("Main Menu:");
        Console.WriteLine("1. Show all buildings");
        Console.WriteLine("2. Show buildings by type");
        Console.WriteLine("3. Create building");
        Console.WriteLine("4. Exit");

        string input = Console.ReadLine();
        invoker.ExecuteCommand(input);
    }
}

