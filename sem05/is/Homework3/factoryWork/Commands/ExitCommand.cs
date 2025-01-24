using factoryWork.Menu;

namespace factoryWork.Commands;

public class ExitCommand : ICommand
{
    private readonly StateContext _context;

    public ExitCommand(StateContext context)
    {
        _context = context;
    }

    public void Execute()
    {
        _context.IsRunning = false;
    }
}
