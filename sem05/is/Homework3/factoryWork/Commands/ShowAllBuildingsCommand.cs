using factoryWork.Menu;

namespace factoryWork.Commands;

public class ShowAllBuildingsCommand : ICommand
{
    private readonly StateContext _context;

    public ShowAllBuildingsCommand(StateContext context)
    {
        _context = context;
    }

    public void Execute()
    {
        _context.SetState(new ShowAllBuildingsState());
    }
}

