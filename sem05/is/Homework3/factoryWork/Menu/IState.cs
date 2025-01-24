namespace factoryWork.Menu;

public interface IState
{
    void Execute(StateContext context);
}