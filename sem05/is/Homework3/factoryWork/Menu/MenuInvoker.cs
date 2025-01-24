using factoryWork.Commands;

namespace factoryWork.Menu;

public class MenuInvoker
{
    private readonly Dictionary<string, ICommand> _commands = new();

    public void RegisterCommand(string option, ICommand command)
    {
        _commands[option] = command;
    }

    public void ExecuteCommand(string option)
    {
        if (_commands.ContainsKey(option))
        {
            _commands[option].Execute();
        }
        else
        {
            Console.WriteLine("Invalid choice. Press any key to continue...");
            Console.ReadKey();
        }
    }
}
