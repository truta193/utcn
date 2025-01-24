namespace factoryWork.Menu;

using System.Collections.Generic;

public class StateContext
{
    public List<IBuilding> Buildings { get; } = new();
    public IState CurrentState { get; private set; }
    public bool IsRunning { get; set; } = true;

    public void SetState(IState newState)
    {
        CurrentState = newState;
    }

    public void Run()
    {
        while (IsRunning && CurrentState != null)
        {
            CurrentState.Execute(this);
        }
    }
}
