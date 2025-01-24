using factoryWork.Menu;

namespace factoryWork.Commands;

public class ShowBuildingsByTypeCommand : ICommand
{
    private readonly StateContext _context;

    public ShowBuildingsByTypeCommand(StateContext context)
    {
        _context = context;
    }

    public void Execute()
    {
        _context.SetState(new ShowBuildingsByTypeState());
    }
}

