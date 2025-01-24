using factoryWork.Menu;

namespace factoryWork.Commands;

public class CreateBuildingCommand : ICommand
{
    private readonly StateContext _context;

    public CreateBuildingCommand(StateContext context)
    {
        _context = context;
    }

    public void Execute()
    {
        _context.SetState(new CreateBuildingState());
    }
}

