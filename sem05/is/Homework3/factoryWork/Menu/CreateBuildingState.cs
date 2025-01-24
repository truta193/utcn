namespace factoryWork.Menu;

using System;

public class CreateBuildingState : IState
{
    public void Execute(StateContext context)
    {
        Console.Clear();
        Console.WriteLine("Choose building type to create:");
        Console.WriteLine("1. Flat");
        Console.WriteLine("2. House");
        Console.WriteLine("3. Hospital");
        Console.WriteLine("4. School");

        string input = Console.ReadLine();
        IBuilding newBuilding = input switch
        {
            "1" => CreateFlat(),
            "2" => CreateHouse(),
            "3" => CreateHospital(),
            "4" => CreateSchool(),
            _ => null
        };

        if (newBuilding != null)
        {
            context.Buildings.Add(newBuilding);
            Console.WriteLine("Building created successfully.");
        }

        Console.WriteLine("Press any key to return...");
        Console.ReadKey();
        context.SetState(new MainMenuState());
    }

    private Flat CreateFlat()
    {
        Console.WriteLine("Enter address:");
        string address = PromptInput();
        Console.WriteLine("Enter number of floors:");
        byte floorCount = byte.Parse(PromptInput());
        Console.WriteLine("Enter number of apartments:");
        byte apartmentCount = byte.Parse(PromptInput());

        return BuildingFactory.CreateBuilding<Flat>(address, floorCount, apartmentCount);

        return new Flat { Address = address, FloorCount = floorCount, ApartmentCount = apartmentCount };
    }
    
    private House CreateHouse()
    {
        try
        {
            Console.WriteLine("Enter owner's name:");
            string owner = PromptInput();
            Console.WriteLine("Enter address:");
            string address = PromptInput();
            Console.WriteLine("Enter area:");
            float area = float.Parse(PromptInput());

            return new House
            {
                Owner = owner,
                Address = address,
                Area = area
            };
        }
        catch (OperationCanceledException)
        {
            Console.WriteLine("Operation canceled.");
            return null;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
            return null;
        }
    }

    
    private Hospital CreateHospital()
    {
        try
        {
            Console.WriteLine("Enter hospital name:");
            string name = PromptInput();
            Console.WriteLine("Enter address:");
            string address = PromptInput();
            Console.WriteLine("Enter departments (comma-separated):");
            string departmentsInput = PromptInput();
            List<string> departments = new List<string>(departmentsInput.Split(","));

            return BuildingFactory.CreateBuilding<Hospital>(name, address, departments);

            return new Hospital
            {
                Name = name,
                Address = address,
                Departments = departments
            };
        }
        catch (OperationCanceledException)
        {
            Console.WriteLine("Operation canceled.");
            return null;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
            return null;
        }
    }
    
    private School CreateSchool()
    {
        try
        {
            Console.WriteLine("Enter school name:");
            string name = PromptInput();
            Console.WriteLine("Enter address:");
            string address = PromptInput();
            Console.WriteLine("Enter number of classes:");
            string classCount = PromptInput();

            return BuildingFactory.CreateBuilding<School>(name, address, classCount);
            return new School
            {
                Name = name,
                Address = address,
                ClassCount = classCount
            };
        }
        catch (OperationCanceledException)
        {
            Console.WriteLine("Operation canceled.");
            return null;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
            return null;
        }
    }



    private string PromptInput()
    {
        string input = Console.ReadLine();
        if (input.ToLower() == "cancel")
            throw new OperationCanceledException("Operation canceled by user.");
        return input;
    }

    // Add methods for other building types similar to CreateFlat
}
