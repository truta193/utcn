using factoryWork.Menu;

var context = new StateContext();
context.SetState(new MainMenuState());
context.Run();